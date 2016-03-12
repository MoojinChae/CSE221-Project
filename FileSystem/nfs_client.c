#include <sys/types.h>
#include <sys/socket.h>
#include <netdb.h>
#include <stdio.h>
#include <string.h>
#include <time.h>

void timespec_subtract(struct timespec *start, struct timespec *end, struct timespec* diff);
int calculate_size(char* size_in_str, char* unit);

void timespec_subtract(struct timespec *start, struct timespec *end, struct timespec* diff) {
    if ((end->tv_nsec - start->tv_nsec) < 0) {
        diff->tv_sec = end->tv_sec - start->tv_sec - 1;
        diff->tv_nsec = end->tv_nsec - start->tv_nsec + 1000000000;
    } else {
        diff->tv_sec = end->tv_sec - start->tv_sec;
        diff->tv_nsec = end->tv_nsec - start->tv_nsec;
    }
}

int calculate_size(char* size_in_str, char* unit) {
    const int kb = 1024;
    const int mb = 1024 * 1024;
    const int gb = 1024 * 1024 * 1024;

    int size = atoi(size_in_str);

    if (!strcmp(unit, "K"))
        return size * kb;

    if (!strcmp(unit, "M"))
        return size * mb;

    if (!strcmp(unit, "G"))
        return size * gb;

    return size;
}

int main(int argc, char **argv)
{
    int sockfd, n;
    struct sockaddr_in servaddr;

    sockfd = socket(AF_INET, SOCK_STREAM, 0);
    bzero(&servaddr, sizeof(servaddr));

    servaddr.sin_family = AF_INET;
    servaddr.sin_port = htons(atoi(argv[3]));

    inet_pton(AF_INET, "192.168.1.107", &(servaddr.sin_addr));

    if (connect(sockfd, (struct sockaddr *)&servaddr, sizeof(servaddr)) == -1) {
        perror("Error: connect()");
    }

    int block_bytes_read = 0;
    int total_bytes_read = 0;
    int bytes_read = 0;

    const int block_size = 4096;
    const int file_size = calculate_size(argv[1], argv[2]);
    const int iterations = file_size / block_size;
    const char* sendline = "read request";
    char read_block[4096];


    // start timing
    struct timespec start, end, time_diff;
    clock_gettime(CLOCK_MONOTONIC, &start);

    printf("file_size = %d, iterations = %d\n", file_size, iterations);

    for (int i = 0; i < iterations; i++) {
        if (write(sockfd, sendline, strlen(sendline) + 1) == -1) {
            perror("Error: write()");
        }
        block_bytes_read = 0;
        while (block_bytes_read < 4096) {
            if ((bytes_read = read(sockfd, read_block, block_size - block_bytes_read)) == -1) {
                perror("Error: read()");
            }
            block_bytes_read += bytes_read;
            total_bytes_read += bytes_read;
        }
    }

    clock_gettime(CLOCK_MONOTONIC, &end);
    timespec_subtract(&start, &end, &time_diff);

    printf("total_bytes_read = %d\n", total_bytes_read);
    printf("INSTANT time_diff: %ld sec %lld ns, start time: %ld sec %lld ns, end time: %ld sec %lld ns\n", time_diff.tv_sec, (uint64_t)time_diff.tv_nsec, start.tv_sec, (uint64_t)start.tv_nsec, end.tv_sec, (uint64_t)end.tv_nsec);
    // end timing

    close(sockfd);

    return 0;
}

