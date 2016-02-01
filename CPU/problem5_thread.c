#define _GNU_SOURCE
#include "cpu.h"
#include <fcntl.h>
#include <pthread.h>
#include <stdio.h>
#include <stdbool.h>
#include <sys/wait.h>
#include <unistd.h>

#define CONTEXT_SWITCHING_NUM 10000
void* mythread(void*);
unsigned thread_context_switching_time();

// Global variables for thread context switch time
bool add_ccnt;
unsigned ccnt;
unsigned total = 0;
int context_switch_num = 0;

void* mythread (void* arg) {
    int diff = 0;

    for (int i = 0; i < CONTEXT_SWITCHING_NUM; i++) {
        /*
        diff = ccnt_read() - ccnt;
        if (add_ccnt) {
            total += diff;
            context_switch_num++;
            add_ccnt = false;
        }
        */
        // printf("Child_thread %lu, ccnt = %u\n", pthread_self() % 1000, diff);
        pthread_yield();
    }

    pthread_exit(NULL);
}

unsigned thread_context_switching_time() {
    pthread_t tid;
    add_ccnt = false;


    int start_ccnt = ccnt_read();
    int pthread_id = pthread_create(&tid, NULL, mythread, NULL);
    if (pthread_id) {
        printf("ERROR: pthread_create error.\n");
        return 1;
    }

    for (int i = 0; i < CONTEXT_SWITCHING_NUM; i++) {
        // add_ccnt = true;
        // ccnt = ccnt_read();
        // printf("Main_thread %lu, ccnt = %u\n", pthread_self() % 1000, ccnt);
        pthread_yield();
    }

    pthread_join(tid, NULL);
    int end_ccnt = ccnt_read();
    int diff = end_ccnt - start_ccnt;
    printf("start: %u, end: %u, diff: %u\n", start_ccnt, end_ccnt, diff);
    printf("average: %u\n", diff / (CONTEXT_SWITCHING_NUM * 2));
    // unsigned average = total / context_switch_num;
    // printf("Average thread context switch time: %u\n", average);
    return 0;
}

int main() {
    thread_context_switching_time();
    return 0;
}

