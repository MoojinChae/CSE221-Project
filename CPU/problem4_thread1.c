#define _GNU_SOURCE
#include "cpu.h"
#include <signal.h>
#include <sys/wait.h>
#include <stdio.h>
#include <syscall.h>
#include <sched.h>
#include <stdlib.h>
#include <unistd.h>
#include <math.h>
#define STACK_SIZE 8192

unsigned t, min, max;
int i;
float avg, stddev;
unsigned overhead;

int no_work_int(){
    t = ccnt_read() - t;
    float prev_avg = avg;
    avg += (t - overhead - prev_avg) / i;
    stddev += (t - overhead - prev_avg) * (t - overhead - avg);
    if (t-overhead > max) max = t-overhead;
    if (t-overhead < min) min = t-overhead;
    return 0;
}

void create_thread1(){
    void * stack = malloc(STACK_SIZE);
    pid_t pid;
    avg = 0.0;
    stddev = 0.0;
    min = 100000000;
    max = 0;

    int num_iter = 100000;
    for(i=1; i<=num_iter; i++){
        t = ccnt_read();
        pid = clone(&no_work_int, (char *)stack + STACK_SIZE, CLONE_SIGHAND|CLONE_FS|CLONE_VM|CLONE_FILES, 0);
        waitpid(pid, NULL, __WALL);
    }
    stddev = sqrt(stddev / (num_iter - 1));
    printf("Clone thread : average = %f, std = %f, min = %d, max = %d\n", avg, stddev, min, max);
    free(stack);
    return;
}

int main(){
    overhead = 8;
    create_thread1();
    return 0;
}

