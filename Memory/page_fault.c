#include "cpu.h"
#include <errno.h>
#include <fcntl.h>
#include <stddef.h>
#include <stdio.h>
#include <string.h>
#include <sys/mman.h>
#include <sys/types.h>
#include <unistd.h>

int prob3();

int prob3() {
    char *addr;
    int fd = -1;

    // mmap
    if ((fd = open("/home/pi/random", O_RDWR, 0)) == -1) {
        fprintf(stderr, "ERROR: fd open");
        return -1;
    }

    addr = (char *)mmap(NULL, 512 * 1024 * 1024, PROT_READ,
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
    unsigned long long total = 0;

    // Read with 128K distance
    for (int i = 0; i < 128 * 1024 * 1024; i += 128 * 1024) {
        start_time = ccnt_read();
        temp = *(addr + i);
        end_time = ccnt_read();

        if (end_time > start_time) {
            printf("%d\n", end_time - start_time);
            total += (end_time - start_time);
            count++;
        }
    }

    printf("total: %llu, count: %d, average: %llu\n", total, count, total / count);
    return 0;
}

int main() {
    prob3();
    return 0;
}

