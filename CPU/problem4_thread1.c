#define _GNU_SOURCE
#include "cpu.h"
#include <signal.h>
#include <stdio.h>
#include <syscall.h>
#include <sched.h>
#include <stdlib.h>
#include <unistd.h>
#define STACK_SIZE 8192

int no_work_int(){
    return 0;
}

void create_thread1(float overhead){
    unsigned t;
    void * stack = malloc(STACK_SIZE);

    int num_iter = 100;
    for(int i=1; i<=num_iter; i++){
        t = ccnt_read();
        clone(&no_work_int, (char *)stack + STACK_SIZE, CLONE_SIGHAND|CLONE_FS|CLONE_VM|CLONE_FILES, 0);
        t = ccnt_read() - t;

        printf("[Clone] %dth thread creation : %f\n", i, (float)(t-overhead));
    }
    free(stack);
    return;
}

int main(){
    create_thread1(0);
    return 0;
}

