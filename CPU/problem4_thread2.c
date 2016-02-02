#define _GNU_SOURCE
#include "cpu.h"
#include <stdio.h>
#include <syscall.h>
#include <unistd.h>
#include <pthread.h>

unsigned t, overall_t;

void * no_work_void(void *arg){
    t = ccnt_read() - t;
    overall_t += t;
    //printf("[pthread_create] a thread creation : %f\n", (float)(t));
    return NULL;
}

void create_thread2(float overhead){
    overall_t = 0;

    int num_iter = 100000;
    pthread_t tid[num_iter];
    for(int i=1; i<=num_iter; i++){
        t = ccnt_read();
        pthread_create(&tid[i-1], NULL, &no_work_void, NULL);
        
        pthread_join(tid[i-1], NULL);
        usleep(1);
    }

    printf("[pthread_create] average of threads creation : %f\n", (float)(overall_t/num_iter));

}

int main(){
    create_thread2(0);
    return 0;
}

