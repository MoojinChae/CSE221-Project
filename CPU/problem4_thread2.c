#define _GNU_SOURCE
#include "cpu.h"
#include <stdio.h>
#include <syscall.h>
#include <unistd.h>
#include <pthread.h>

void * no_work_void(void *arg){
    return NULL;
}

void create_thread2(float overhead){
    unsigned t;

    int num_iter = 100;
    pthread_t tid[num_iter];
    for(int i=1; i<=num_iter; i++){
        t = ccnt_read();
        pthread_create(&tid[i-1], NULL, &no_work_void, NULL);
        t = ccnt_read() - t;

        printf("[pthread] %dth thread creation : %f\n", i, (float)(t-overhead));
        pthread_join(tid[i-1], NULL);
        usleep(1);
    }
}

int main(){
    create_thread2(0);
    return 0;
}

