#define _GNU_SOURCE
#include "cpu.h"
#include <fcntl.h>
#include <math.h>
#include <stdbool.h>
#include <stdio.h>
#include <stdlib.h>
#include <sys/stat.h>
#include <sys/types.h>
#include <unistd.h>

int read_file_to_size(char* filename, unsigned /* size */);
void read_file_and_calculate_average(char* filename, unsigned size);

int read_file_to_size(char* filename, unsigned size) {
    int fd;
    int total_bytes_read = 0;
    int bytes_read = 0;
    static char block[4096] __attribute__ ((__aligned__ (4096)));
    const int block_size = 4096;

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

    start_time = ccnt_read();

    while (total_bytes_read < size) {
        if ((bytes_read = read(fd, block, block_size)) == -1) {
            perror("Error: read()");
            exit(1);
        }
        total_bytes_read += bytes_read;
    }

    end_time = ccnt_read();

    unsigned diff = end_time - start_time;
    // printf("diff: %u\n", diff);
    unsigned cycles_per_block = (diff * block_size) / size;

    return diff;
}

void read_file_and_calculate_average(char* filename, unsigned size) {
    const int mb = 1024 * 1024;
    const int kb = 1024;

    long long unsigned avg = 0;
    long long unsigned prev_avg = 0;
    long long unsigned total = 0;

    for (int i = 0; i < 10; i++) {
        unsigned cpb = read_file_to_size(filename, size);
        total += cpb;
        // prev_avg = avg;
        // avg += (cpb - prev_avg) / (i + 1);
    }

    printf("size: %u, average cycles: %llu\n", size, total / 10);
    // printf("size: %u, average_cpb: %lf\n", size, avg);
}


int main(int argc, char* argv[]) {

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
    // read_file_and_calculate_average("./random1G", 1*mb*1024);

    return 0;
}

