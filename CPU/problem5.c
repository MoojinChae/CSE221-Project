#define _GNU_SOURCE
#include "cpu.h"
#include <fcntl.h>
#include <pthread.h>
#include <stdio.h>
#include <stdbool.h>
#include <sys/wait.h>
#include <unistd.h>

#define CONTEXT_SWITCHING_NUM 1000
int process_context_switching_time();


// Global variables for process context switch time
bool add_ccnt;
unsigned ccnt;
unsigned total = 0;
int context_switch_num = 0;

int process_context_switching_time() {
    int pipefd[2];
    pid_t cpid;
    char buf = 100;

    if (pipe(pipefd) == -1) {
        perror("pipe");
        return -1;
    }

    fcntl(pipefd[0], F_SETPIPE_SZ, sizeof(char));
    fcntl(pipefd[1], F_SETPIPE_SZ, sizeof(char));

    if ((cpid = fork()) == -1) {
        perror("fork");
        return -1;
    }

    if (cpid == 0) { // Child writes to pipe
        // int diff = 0;
        for (int i = 0; i < CONTEXT_SWITCHING_NUM; i++) {
            /*
            diff = ccnt_read() - ccnt;
            if (add_ccnt) {
                total += diff;
                context_switch_num++;
                add_ccnt = false;
            }
            */
            buf = (buf + 1) % 256;
            printf("Child: buf: %d, ccnt: %u\n", buf, ccnt_read());
            write(pipefd[1], &buf, 1);
        }
    } else { // Parent reads char to pipe
        for (int i = 0; i < CONTEXT_SWITCHING_NUM; i++) {
            printf("Parent: buf: %d, ccnt: %u\n", buf, ccnt_read());
            /*
            add_ccnt = true;
            ccnt = ccnt_read();
            */
            read(pipefd[0], &buf, 1);
        }
        wait(NULL);

        printf("total: %u, context_switch_num: %u\n", total, context_switch_num);
        unsigned average = total / context_switch_num;
        printf("Average process context switch time: %u\n", average);
        return average;
    }

    return 0;
}

int main() {
    process_context_switching_time();
    return 0;
}

