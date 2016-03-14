#include "cpu.h"
#include <fcntl.h>
#include <math.h>
#include <stdbool.h>
#include <stdint.h>
#include <stdio.h>
#include <stdlib.h>
#include <sys/types.h>
#include <time.h>
#include <unistd.h>

int read_file_to_size(unsigned /* size */, bool);
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

int read_file_to_size(unsigned size, bool warmup) {
    int fd;
    int count = 0;
    int bytes_read = 0;
    char buf[4096];
    int buf_size = 4096;

    fd = open("./random1G", O_RDONLY, 0);

    if (lseek(fd, 0, SEEK_SET) == -1) {
        perror("Error: lseek()");
        exit(1);
    }

    unsigned start_time = 0;
    unsigned end_time = 0;

    struct timespec start, end, time_diff;
    // start_time = ccnt_read();

    clock_gettime(CLOCK_MONOTONIC, &start);
    while (count < size) {
        if ((bytes_read = read(fd, buf, buf_size)) == -1) {
            perror("Error: read()");
            exit(1);
        }
        count += bytes_read;
    }
    clock_gettime(CLOCK_MONOTONIC, &end);
    timespec_subtract(&start, &end, &time_diff);
    printf("INSTANT diff: %ld sec %lld ns, start time: %ld sec %lld ns, end time: %ld sec %lld ns\n", time_diff.tv_sec, (uint64_t)time_diff.tv_nsec, start.tv_sec, (uint64_t)start.tv_nsec, end.tv_sec, (uint64_t)end.tv_nsec);

    // end_time = ccnt_read();
    /*
    if (!warmup)
        printf("size: %u start: %u, end: %u, diff = %u\n", size, start_time, end_time, end_time - start_time);
    */

    // return end_time - start_time;
    return 0;
}

int main(int argc, char* argv[]) {
    const int mb = 1024 * 1024;

    const int const_size = atoi(argv[1]);
    printf("%d\n", const_size);
    for (int i = const_size; i <= const_size; i++) {
        int size = i * mb;
        double avg = 0.0;
        double prev_avg = 0.0;
        double stddev = 0.0;

        // Warm up
        read_file_to_size(size, true);
        read_file_to_size(size, true);

        for (int j = 0; j < 10; j++) {
            unsigned cycles = read_file_to_size(size, false);
            // prev_avg = avg;
            // avg += (cycles - prev_avg) / (j + 1);
            // stddev += (cycles - prev_avg) * (cycles - avg);
        }

        // stddev = sqrt(stddev / 9);
        // printf("size: %d, average = %lf, std = %lf, cyclepermb: %lf\n", size, avg, stddev, avg / i);
    }
    return 0;
}

