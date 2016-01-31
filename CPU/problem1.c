#include "cpu.h"
#include <stdio.h>

#define READING_TIME_TEST_NUM 10000
#define LOOP_TIME_TEST_NUM 10000

unsigned reading_time_overhead();
unsigned loop_time_overhead();

unsigned reading_time_overhead() {
    unsigned ccnt = 0;
    unsigned total_ccnt = 0;

    for (int i = 0; i < OVERHEAD_TEST_NUM; i++) {
        ccnt = ccnt_read();
        ccnt = ccnt_read() - ccnt;
        total_ccnt += ccnt;
    }

    return total_ccnt / OVERHEAD_TEST_NUM;
}

unsigned loop_time_overhead() {
    unsigned ccnt = 0;

    ccnt = ccnt_read();
    for (int i = 0; i < LOOP_TIME_TEST_NUM; i++) { }
    ccnt = ccnt_read() - ccnt;

    return ccnt / LOOP_TIME_TEST_NUM;
}

int main() {
    printf("reading_time_overhead() : %u cycles\n", reading_time_overhead());
    printf("loop_time_overhead() : %u cycles\n", loop_time_overhead());
    return 0;
}
