#define _GNU_SOURCE
#include "cpu.h"
#include <fcntl.h>
#include <math.h>
#include <stdbool.h>
#include <stdint.h>
#include <stdio.h>
#include <stdlib.h>
#include <sys/stat.h>
#include <sys/types.h>
#include <time.h>
#include <unistd.h>

struct result {
    unsigned cycle;
    struct timespec time;
};

void timespec_subtract(struct timespec *start, struct timespec *end, struct timespec* diff);
void timespec_add(struct timespec *to, struct timespec *from);
struct result read_file_to_size(char* filename, unsigned /* size */);
void read_file_and_calculate_average(char* filename, unsigned size);


void timespec_subtract(struct timespec *start, struct timespec *end, struct timespec* diff) {
    if ((end->tv_nsec - start->tv_nsec) < 0) {
        diff->tv_sec = end->tv_sec - start->tv_sec - 1;
        diff->tv_nsec = end->tv_nsec - start->tv_nsec + 1000000000;
    } else {
        diff->tv_sec = end->tv_sec - start->tv_sec;
        diff->tv_nsec = end->tv_nsec - start->tv_nsec;
    }
}

void timespec_add(struct timespec *to, struct timespec *from)
{
    if ((to->tv_nsec + from->tv_nsec) >= 1000000000) {
        to->tv_sec = to->tv_sec + from->tv_sec + 1;
        to->tv_nsec = to->tv_nsec + from->tv_nsec - 1000000000;
    } else {
        to->tv_sec = to->tv_sec + from->tv_sec;
        to->tv_nsec = to->tv_nsec + from->tv_nsec;
    }
}

struct result read_file_to_size(char* filename, unsigned size) {
    int fd;
    int total_bytes_read = 0;
    int bytes_read = 0;
    static char block[4096] __attribute__ ((__aligned__ (4096)));
    const int block_size = 4096;
    struct timespec start, end, time_diff;

    if ((fd = open(filename, O_RDONLY | O_DIRECT)) == -1) {
        perror("Error: read error");
        exit(1);
    }


    if (lseek(fd, 0, SEEK_SET) == -1) {
        perror("Error: lseek()");
        exit(1);
    }

    // use time instead
    unsigned start_time = 0;
    unsigned end_time = 0;

    clock_gettime(CLOCK_MONOTONIC, &start);
    start_time = ccnt_read();

    while (total_bytes_read < size) {
        if ((bytes_read = read(fd, block, block_size)) == -1) {
            perror("Error: read()");
            exit(1);
        }
        total_bytes_read += bytes_read;
    }

    end_time = ccnt_read();
    clock_gettime(CLOCK_MONOTONIC, &end);

    unsigned cycle_diff = end_time - start_time;
    unsigned cycles_per_block = (cycle_diff * block_size) / size;

    timespec_subtract(&start, &end, &time_diff);

    struct result res;
    res.cycle = cycle_diff;
    res.time = time_diff;

    uint64_t total_time_in_ns = (((uint64_t)res.time.tv_sec * 1000000000) + res.time.tv_nsec);
    printf("INSTANT start time: %ld sec %lld ns, end time: %ld sec %lld ns\n", start.tv_sec, (uint64_t)start.tv_nsec, end.tv_sec, (uint64_t)end.tv_nsec);
    printf("INSTANT size: %u, time: %ld sec %lld ns, time in ns: %lld, cycles: %u\n", size, res.time.tv_sec, (uint64_t)res.time.tv_nsec, total_time_in_ns, res.cycle);

    return res;
}

void read_file_and_calculate_average(char* filename, unsigned size) {
    const int mb = 1024 * 1024;
    const int kb = 1024;

    long long unsigned avg = 0;
    long long unsigned prev_avg = 0;
    struct timespec total_time;
    long long unsigned total_cycle = 0;

    const int rep_count = 10;

    total_time.tv_sec = 0;
    total_time.tv_nsec = 0;

    for (int i = 0; i < rep_count; i++) {
        struct result res = read_file_to_size(filename, size);
        timespec_add(&total_time, &res.time);
        total_cycle += res.cycle;
        // printf("TOTAL size: %u, time in s.ns: %lld.%ld, cycles: %llu\n", size, (long long int)(total_time.tv_sec), total_time.tv_nsec, total_cycle);
        // prev_avg = avg;
        // avg += (cpb - prev_avg) / (i + 1);
    }

    uint64_t total_time_avg_in_ns = (((uint64_t)total_time.tv_sec * 1000000000) + total_time.tv_nsec) / rep_count;
    printf("size: %u, average time in ns: %lld, average cycles: %llu\n", size, total_time_avg_in_ns, total_cycle / rep_count);
    // printf("size: %u, average time in s.ns: %lld.%ld, average cycles: %llu\n", size, (long long int)(total_time.tv_sec) / rep_count, total_time.tv_nsec / rep_count, total_cycle / rep_count);
    // printf("size: %u, average_cpb: %lf\n", size, avg);
}


int main(int argc, char* argv[]) {

    const int gb = 1024 * 1024 * 1024;
    const int mb = 1024 * 1024;
    const int kb = 1024;

    read_file_and_calculate_average("./random4K", 4*kb);
    read_file_and_calculate_average("./random8K", 8*kb);
    read_file_and_calculate_average("./random16K", 16*kb);
    read_file_and_calculate_average("./random32K", 32*kb);
    read_file_and_calculate_average("./random64K", 64*kb);
    read_file_and_calculate_average("./random128K", 128*kb);
    read_file_and_calculate_average("./random256K", 256*kb);
    read_file_and_calculate_average("./random512K", 512*kb);
    read_file_and_calculate_average("./random1M", 1*mb);
    read_file_and_calculate_average("./random2M", 2*mb);
    read_file_and_calculate_average("./random4M", 4*mb);
    read_file_and_calculate_average("./random8M", 8*mb);
    read_file_and_calculate_average("./random16M", 16*mb);
    read_file_and_calculate_average("./random32M", 32*mb);
    read_file_and_calculate_average("./random64M", 64*mb);
    read_file_and_calculate_average("./random128M", 128*mb);
    read_file_and_calculate_average("./random256M", 256*mb);
    read_file_and_calculate_average("./random512M", 512*mb);
    read_file_and_calculate_average("./random1G", 1*gb);
    /*
    read_file_and_calculate_average("./random1_128G", (1024 + 128)*mb);
    read_file_and_calculate_average("./random1_256G", (1024 + 256)*mb);
    */

    return 0;
}

