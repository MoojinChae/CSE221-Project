#define _GNU_SOURCE
#include "cpu.h"
#include <pthread.h>
#include <stdio.h>

void* mythread(void*);
unsigned thread_context_switching_time();

pthread_mutex_t p_mutex;
pthread_cond_t cv;

void* mythread (void* arg) {
    //signal
    printf("HERE!!\n");
    pthread_cond_signal(&cv);
    int pthread_count = 1000;

    // MEASURE
    for (int i = 0; i < 100; i++) {
        printf("\n child_thread %lu, count = %d\n", pthread_self() % 1000, pthread_count++);
        pthread_yield();
    }

    pthread_exit(NULL);
}

unsigned thread_context_switching_time() {
    pthread_t tid;
    int pthread_id;
    int main_count = 0;
    int rc;

    if (pthread_mutex_init(&p_mutex, NULL) != 0) {
        printf("ERROR: mutex init failed\n");
        return 1;
    }

    pthread_mutex_lock(&p_mutex);

    pthread_id = pthread_create(&tid, NULL, mythread, NULL);
    if (pthread_id) {
        printf("ERROR: pthread_create error.\n");
        return 1;
    }
    pthread_cond_wait(&cv, &p_mutex);
    pthread_mutex_unlock(&p_mutex);
    pthread_mutex_destroy(&p_mutex);

    // MEASURE
    for (int i = 0; i < 100; i++) {
        printf("\n main_thread %lu, count = %d\n", pthread_self() % 1000, main_count++);
        pthread_yield();
    }

    pthread_join(tid, NULL);
    printf("\n pthread done");
    return 0;
}

int main() {
    thread_context_switching_time();
    return 0;
}

