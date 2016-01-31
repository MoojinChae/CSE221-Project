#include "cpu.h"
#include <stdio.h>

inline unsigned ccnt_read(){
    volatile unsigned cc;
    asm volatile("mrc p15, 0, %0, c9, c13, 0" : "=r" (cc));
    return cc;
}

inline unsigned get_overhead(){
    unsigned t;
    float total = 0;

    for (int i = 0; i < 10; i++) {
        t = ccnt_read();
        t = ccnt_read() - t;
        total += (float)t;

        //printf("%dth measurement overhead: %d\n",i, t);
    }
    printf("Avg measurement overhead: %f\n", (float)total/OVERHEAD_TEST_NUM);

    return (total/OVERHEAD_TEST_NUM);
}

