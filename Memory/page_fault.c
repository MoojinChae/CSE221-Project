#include "cpu.h"
#include <errno.h>
#include <fcntl.h>
#include <math.h>
#include <stddef.h>
#include <stdio.h>
#include <string.h>
#include <sys/mman.h>
#include <sys/types.h>
#include <unistd.h>

int prob3(int);

int prob3(int overhead) {
    char *addr;
    int fd = -1;

    // mmap
    if ((fd = open("./random", O_RDWR, 0)) == -1) {
        fprintf(stderr, "ERROR: fd open");
        return -1;
    }

    addr = (char *)mmap(NULL, 64 * 1024 * 1024, PROT_READ,
                        MAP_PRIVATE, fd, 0);

    if (addr == MAP_FAILED) {
        fprintf(stderr, "ERROR: map %d - %s\n", errno, strerror(errno));
        return -1;
    }

    // READING: each read in a page will cause a page fault.
    char temp = 0;
    unsigned start_time = 0;
    unsigned end_time = 0;
    int count = 0;

    // Result Stats
    float avg = 0.0;
    float stddev = 0.0;
    unsigned min = 100000000;
    unsigned max = 0;
    float prev_avg = 0.0;
    unsigned diff = 0;

    // Read with 4K distance
    for (int i = 0; i < 64 * 1024 * 1024; i += 128 * 1024) {
        start_time = ccnt_read();
        temp = *(addr + i);
        end_time = ccnt_read();

        if (end_time > start_time) {
            diff = end_time - start_time;
            // if (diff > 1000000)
                // printf("%d: %d\n", i, end_time - start_time - overhead);
            count++;
            prev_avg = avg;
            avg += (diff - overhead - prev_avg) / count;
            stddev += (diff - overhead - prev_avg) * (diff - overhead - avg);

            if (diff - overhead > max) {
                max = diff - overhead;
            }

            if (diff - overhead < min) {
                min = diff - overhead;
            }
        }
    }


    stddev = sqrt(stddev / (count - 1));
    printf("count = %d, average = %f, std = %f, min = %d, max = %d\n", count, avg, stddev, min, max);
    return 0;
}

int main() {
    prob3(8);
    return 0;
}

