#include "cpu.h"
#include <stdio.h>
#include <stdlib.h>
#include <math.h>

#define LOOP_TIME_TEST_NUM 1000
static const int arr_size = 2*1024*1024;
static const int stride_size = 4096;
static const int cpu_mhz = 700;

void measure_read(float overhead){
    unsigned t, overall_t;
    float avg, stddev;

    int * array = (int *) malloc(sizeof(int) * arr_size);
    for (int i=0; i<arr_size; i++){
        array[i] = (int) rand() % 100;
    }

    avg = 0.0;
    stddev = 0.0;
    for(int i=1; i<=LOOP_TIME_TEST_NUM; i++){
        int * measure = array;
        int m = 0;
        int step = 2;
        overall_t = 0;
        for (int j=0; j<arr_size/2; j+=step){
            t = ccnt_read();
            m = measure[0] + measure[1048576];
            t = ccnt_read() - t;
            overall_t += t - overhead;
            measure += 1;
        }
        float bandwidth = (float)(sizeof(int) * arr_size * cpu_mhz) / overall_t;
        float prev_avg = avg;
        avg += (bandwidth - prev_avg) / i;
        stddev += (bandwidth - prev_avg) * (bandwidth - avg);
    }
    stddev = sqrt(stddev / (LOOP_TIME_TEST_NUM - 1));
    printf("memory read bandwidth avg = %f(Mbyte/sec) std = %f\n", avg, stddev);
    free(array);
}

void measure_write(float overhead){
    unsigned t, overall_t;
    float avg, stddev;
    int * array = (int *) malloc(sizeof(int) * arr_size);

    for (int i=0; i<arr_size; i++){
        array[i] = (int) rand() % 100;
    }

    avg = 0.0;
    stddev = 0.0;
    for(int i=1; i<=LOOP_TIME_TEST_NUM; i++){
        int * measure = array;
        int step = 2;
        overall_t = 0;
        for (int j=1; j<=arr_size/2; j+=step){
            t = ccnt_read();
            measure[0] = 1;
            measure[1048576] = 1;
            t = ccnt_read() - t;
            overall_t += t - overhead;
            measure += 1;
        }
        float bandwidth = (float)(sizeof(int) * arr_size * cpu_mhz) / overall_t;
        float prev_avg = avg;
        avg += (bandwidth - prev_avg) / i;
        stddev += (bandwidth - prev_avg) * (bandwidth - avg);
    }
    stddev = sqrt(stddev / (LOOP_TIME_TEST_NUM - 1));
    printf("memory write bandwidth avg = %f(Mbyte/sec) std = %f\n", avg, stddev);
    free(array);
}

int main(){
    measure_read(0);
    measure_write(0);
}
