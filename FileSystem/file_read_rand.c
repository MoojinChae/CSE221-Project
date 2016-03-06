#include "cpu.h"
#include <fcntl.h>
#include <math.h>
#include <stdbool.h>
#include <stdio.h>
#include <stdlib.h>
#include <sys/types.h>
#include <unistd.h>

int read_file_to_size(unsigned /* size */, bool);

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

    start_time = ccnt_read();

    while (count < size) {
        if ((bytes_read = read(fd, buf, buf_size)) == -1) {
            perror("Error: read()");
            exit(1);
        }
        count += bytes_read;
    }

    end_time = ccnt_read();
    /*
    if (!warmup)
        printf("size: %u start: %u, end: %u, diff = %u\n", size, start_time, end_time, end_time - start_time);
    */

    return end_time - start_time;
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
        read_file_to_size(size, true);
        read_file_to_size(size, true);
        for (int j = 0; j < 10; j++) {
            unsigned cycles = read_file_to_size(size, false);
            prev_avg = avg;
            avg += (cycles - prev_avg) / (j + 1);
            stddev += (cycles - prev_avg) * (cycles - avg);
        }

        stddev = sqrt(stddev / 9);
        printf("size: %d, average = %lf, std = %lf, cyclepermb: %lf\n", size, avg, stddev, avg / i);
    }
    return 0;
}

