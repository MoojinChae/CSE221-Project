#include "cpu.h"
#include <stdio.h>
#include <stdlib.h>
#include <math.h>

#define LOOP_TIME_TEST_NUM 1024*1024
static const int arr_size = 8*1024*1024;
static const int stride_size = 4096;

void measure_read(float overhead){
    unsigned t, overall_t;
    int * array = (int *) malloc(sizeof(int) * arr_size);

    for (int i=0; i<arr_size; i++){
        array[i] = (int) rand() % 100;
    }

    int * measure = array;
    int m = 0;
    int step = 8;
    for (int i=0; i<LOOP_TIME_TEST_NUM; i+=step) {
        t = ccnt_read();
        m = measure[0] + measure[8] + measure[16] + measure[24] + measure[32] + measure[40] + measure[48] + measure[56];
        t = ccnt_read() - t;
        overall_t += t - overhead;
        measure += 64;
        if (measure >= &array[arr_size - 56])
            measure = array;
    }
    printf("average = %f\n", (float)overall_t);
    free(array);
}

void measure_write(float overhead){
    unsigned t, overall_t;
    int * array = (int *) malloc(sizeof(int) * arr_size);

    for (int i=0; i<arr_size; i++){
        array[i] = (int) rand() % 100;
    }

    int * measure = array;
    int step = 8;
    for (int i=0; i<LOOP_TIME_TEST_NUM; i+=step) {
        t = ccnt_read();
        measure[0] = 1;
        measure[8] = 1;
        measure[16] = 1;
        measure[24] = 1;
        measure[32] = 1;
        measure[40] = 1;
        measure[48] = 1;
        measure[56] = 1;
        t = ccnt_read() - t;
        overall_t += t - overhead;
        measure += 64;
        if (measure >= &array[arr_size - 56])
            measure = array;
    }
    printf("average = %f\n", (float)overall_t);
    free(array);
}

int main(){
    measure_read(0);
    measure_write(0);
}
