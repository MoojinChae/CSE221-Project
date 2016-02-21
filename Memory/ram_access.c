#include "cpu.h"
#include <stdio.h>
#include <stdlib.h>
#include <math.h>

#define LOOP_TIME_TEST_NUM 100000
static const int arr_min_size = 256;
static const int stride_min_size = 128;


void measure_latency(float overhead){
    unsigned t, overall_t;
    int arr_size, stride_size, int_arr_size, int_stride_size;
    void **measure;

    for(int i=0; i<5; i++){
        stride_size = stride_min_size * pow(2,i);
        for(int j=0; j<20; j++){
            arr_size = arr_min_size * pow(2,j);
            int ** array = (int **) malloc(arr_size);

            int_arr_size = arr_size / sizeof(int *);
            int_stride_size = stride_size / sizeof(int *);
            for (int k = 0; k < int_arr_size; k++) {
                array[k] = (int *) &array[(k + int_stride_size) % int_arr_size];
            }

            measure = (void **)array;
            overall_t = 0;
            for(int k=0; k<LOOP_TIME_TEST_NUM; k++){
                t = ccnt_read();
                measure = *measure;
                t = ccnt_read() - t;
                overall_t += t - overhead;
            }
            printf("arr size = %d, stride size = %d, average = %f\n", arr_size, stride_size, (float)overall_t/LOOP_TIME_TEST_NUM);

            free(array);
        }
    }
    
}

int main(){
    measure_latency(0);
}
