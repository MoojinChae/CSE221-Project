#define _GNU_SOURCE
#include <fcntl.h>
#include <stdint.h>
#include <stdio.h>
#include <stdlib.h>
#include <sys/stat.h>
#include <sys/types.h>
#include <time.h>
#include <unistd.h>

void timespec_subtract(struct timespec *start, struct timespec *end, struct timespec* diff);

void timespec_subtract(struct timespec *start, struct timespec *end, struct timespec* diff) {
    if ((end->tv_nsec - start->tv_nsec) < 0) {
        diff->tv_sec = end->tv_sec - start->tv_sec - 1;
        diff->tv_nsec = end->tv_nsec - start->tv_nsec + 1000000000;
    } else {
        diff->tv_sec = end->tv_sec - start->tv_sec;
        diff->tv_nsec = end->tv_nsec - start->tv_nsec;
    }
}

int main(int argc, char* argv[]) {
    const int mb = 1024 * 1024;
    pid_t child_pid, wpid;
    int status = 0;

    for (int num_of_processes = 1; num_of_processes <= 16; num_of_processes *= 2) {
        for (int num_of_tries = 0; num_of_tries < 10; num_of_tries++) {
            printf("========START: num_of_processes : %d try: %d========\n", num_of_processes, num_of_tries);
            int curr_child_process = -1;
            for (int i = 0; i < num_of_processes; i++) {
                curr_child_process++;

                if ((child_pid = fork()) == 0) {
                    int fd;
                    int total_bytes_read = 0;
                    int bytes_read = 0;
                    static char block[4096] __attribute__ ((__aligned__ (4096)));
                    const int block_size = 4096;
                    const int size = 8 * mb;
                    struct timespec start, end, time_diff;

                    char filename[80];
                    snprintf(filename, sizeof (filename), "./random8M_%d", curr_child_process);
                    printf("start reading child pid: %d, filename: %s\n", child_pid, filename);

                    if ((fd = open(filename, O_RDONLY | O_DIRECT)) == -1) {
                        perror("Error: read error");
                        exit(1);
                    }

                    if (lseek(fd, 0, SEEK_SET) == -1) {
                        perror("Error: lseek()");
                        exit(1);
                    }

                    clock_gettime(CLOCK_MONOTONIC, &start);

                    while (total_bytes_read < size) {
                        if ((bytes_read = read(fd, block, block_size)) == -1) {
                            perror("Error: read()");
                            exit(1);
                        }
                        total_bytes_read += bytes_read;
                    }

                    clock_gettime(CLOCK_MONOTONIC, &end);
                    timespec_subtract(&start, &end, &time_diff);
                    printf("INSTANT diff: %ld sec %lld ns, start time: %ld sec %lld ns, end time: %ld sec %lld ns\n", time_diff.tv_sec, (uint64_t)time_diff.tv_nsec, start.tv_sec, (uint64_t)start.tv_nsec, end.tv_sec, (uint64_t)end.tv_nsec);
                    close(fd);

                    exit(1);
                }
            }

            while ((wpid = wait(&status)) > 0) {
                printf("end reading child_pid: %d, status: %d\n", (int)wpid, status);
            }
            printf("========END: num_of_processes : %d try: %d========\n\n", num_of_processes, num_of_tries);
        }
    }

    return 0;
}

