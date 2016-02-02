#define _GNU_SOURCE
#include "cpu.h"
#include <fcntl.h>
#include <pthread.h>
#include <stdio.h>
#include <stdbool.h>
#include <sys/wait.h>
#include <unistd.h>

#define CONTEXT_SWITCHING_NUM 50
int process_context_switching_time();

int process_context_switching_time() {
    int pipefd[2];
    pid_t cpid;
    unsigned msg = 1;
    unsigned ccnt = 0;
    unsigned total = 0;
    int context_switch_num = 0;

    if (pipe(pipefd) == -1) {
        perror("pipe");
        return -1;
    }

    fcntl(pipefd[0], F_SETPIPE_SZ, sizeof(msg));
    fcntl(pipefd[1], F_SETPIPE_SZ, sizeof(msg));

    // int start_ccnt = ccnt_read();
    if ((cpid = fork()) == -1) {
        perror("fork");
        return -1;
    }

    if (cpid == 0) { // Child writes to pipe
        close(pipefd[0]);
        for (int i = 0; i < CONTEXT_SWITCHING_NUM; i++) {
            printf("Child\n");
            msg = ccnt_read();
            if (write(pipefd[1], &msg, sizeof(msg)) != sizeof(msg)) {
                printf("1\n");
                return -1;
            }
            sleep(1);
        }

        return 0;
    } else { // Parent reads char to pipe
        close(pipefd[1]);
        for (int i = 0; i < CONTEXT_SWITCHING_NUM; i++) {
            if (read(pipefd[0], &msg, sizeof(msg)) != sizeof(msg)) {
                printf("4\n");
                return -1;
            }
            ccnt = ccnt_read();
            printf("Parent: %u, %u\n", ccnt, msg);
            if (ccnt > msg) {
                printf("Added: %u\n", (ccnt - msg));
                total += (ccnt - msg);
                context_switch_num++;
                msg = 4294967295;
            }
        }
        wait(NULL);
    }

    // int end_ccnt = ccnt_read();
    // int diff = end_ccnt - start_ccnt;
    // printf("start: %u, end: %u, diff: %u\n", start_ccnt, end_ccnt, diff);
    // printf("average: %u\n", diff / (CONTEXT_SWITCHING_NUM * 2));

    printf("total: %u, context_switch_num: %u\n", total, context_switch_num);
    unsigned average = total / context_switch_num;
    printf("Average thread context switch time: %u\n", average);
    return 0;
}

int main() {
    process_context_switching_time();
    return 0;
}

