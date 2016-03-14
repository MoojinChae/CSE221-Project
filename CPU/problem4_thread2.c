#define _GNU_SOURCE
#include "cpu.h"
#include <stdio.h>
#include <syscall.h>
#include <unistd.h>
#include <pthread.h>
#include <math.h>
#include <stdlib.h>

unsigned t, min, max;
int i;
float avg, stddev;
unsigned overhead;

void * no_work_void(void *arg){
    t = ccnt_read() - t;
    float prev_avg = avg;
    avg += (t - overhead - prev_avg) / i;
    stddev += (t - overhead - prev_avg) * (t - overhead - avg);
    if (t-overhead > max) max = t-overhead;
    if (t-overhead < min) min = t-overhead;
    return NULL;
}

void create_thread2(float overhead){
    avg = 0.0;
    stddev = 0.0;
    min = 100000000;
    max = 0;
    
    int num_iter = 100000;
    pthread_t tid[num_iter];
    for(i=1; i<=num_iter; i++){
        t = ccnt_read();
        pthread_create(&tid[i-1], NULL, &no_work_void, NULL);
        
        pthread_join(tid[i-1], NULL);
        usleep(1);
    }
    stddev = sqrt(stddev / (num_iter - 1));
    printf("pthread_create thread : average = %f, std = %f, min = %d, max = %d\n", avg, stddev, min, max);

}

int main(){
    overhead = 8;
    create_thread2(0);
    return 0;
}

