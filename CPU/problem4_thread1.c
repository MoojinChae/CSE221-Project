#define _GNU_SOURCE
#include "cpu.h"
#include <signal.h>
#include <sys/wait.h>
#include <stdio.h>
#include <syscall.h>
#include <sched.h>
#include <stdlib.h>
#include <unistd.h>
#define STACK_SIZE 8192

unsigned t, overall_t;

int no_work_int(){
    t = ccnt_read() - t;
    overall_t += t;
    //printf("[Clone] a thread creation : %f\n", (float)(t));
    return 0;
}

void create_thread1(float overhead){
    void * stack = malloc(STACK_SIZE);
    pid_t pid;
    overall_t = 0;

    int num_iter = 100000;
    for(int i=1; i<=num_iter; i++){
        t = ccnt_read();
        pid = clone(&no_work_int, (char *)stack + STACK_SIZE, CLONE_SIGHAND|CLONE_FS|CLONE_VM|CLONE_FILES, 0);
        waitpid(pid, NULL, __WALL);
    }

    printf("[Clone] average of threads creation : %f\n", (float)(overall_t/num_iter));
    free(stack);
    return;
}

int main(){
    create_thread1(0);
    return 0;
}

