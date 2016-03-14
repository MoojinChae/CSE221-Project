#define _GNU_SOURCE
#include "cpu.h"
#include <fcntl.h>
#include <math.h>
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
unsigned start_ccnt;
unsigned total = 0;
int context_switch_num = 0;
int pipefd[2];

void* mythread (void* arg) {
    unsigned msg = 1;
    if (write(pipefd[1], &msg, sizeof(msg)) == -1) {
        return 0;
    }

    pthread_yield();
    pthread_exit(NULL);
}

unsigned thread_context_switching_time() {
    unsigned end_ccnt = 0;
    unsigned total = 0;
    unsigned msg = 1;

    if (pipe(pipefd) == -1) {
        perror("pipe");
        return -1;
    }

    fcntl(pipefd[0], F_SETPIPE_SZ, sizeof(msg));
    fcntl(pipefd[1], F_SETPIPE_SZ, sizeof(msg));

    pthread_t tid;

    int pthread_id = pthread_create(&tid, NULL, mythread, NULL);
    if (pthread_id) {
        printf("ERROR: pthread_create error.\n");
        return 1;
    }

    close(pipefd[1]);
    start_ccnt = ccnt_read();
    if (read(pipefd[0], &msg, sizeof(msg)) == -1) {
        perror("Error: read()");
        return -1;
    }
    end_ccnt = ccnt_read();
    pthread_join(tid, NULL);


    int diff = end_ccnt - start_ccnt;
    printf("start: %u, end: %u, diff: %u\n", start_ccnt, end_ccnt, diff);
    return diff;
}

int main() {
    int count = 0;
    double avg = 0.0;
    double stddev = 0.0;

    for (int i = 0; i < 1000; i++) {
        int result = thread_context_switching_time();
        count++;
        double prev_avg = avg;
        result /= 2;
        avg += (result - prev_avg) / count;
        stddev += (result - prev_avg) * (result - avg);
    }

    stddev = sqrt(stddev / (count - 1));
    printf("average: %lf , stddev: %lf\n", avg, stddev);
    return 0;
}

