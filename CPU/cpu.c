#include "cpu.h"
#include <stdio.h>

unsigned get_overhead() {
    unsigned t;
    float total = 0;

    for (int i = 0; i < OVERHEAD_TEST_NUM; i++) {
        t = ccnt_read();
        t = ccnt_read() - t;
        total += (float)t;
        // printf("%dth measurement overhead: %u\n",i, t);
    }
    printf("Avg measurement overhead: %f\n", (float)total/OVERHEAD_TEST_NUM);

    return (total/OVERHEAD_TEST_NUM);
}

