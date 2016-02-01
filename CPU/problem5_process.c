#define _GNU_SOURCE
#include "cpu.h"
#include <fcntl.h>
#include <pthread.h>
#include <stdio.h>
#include <stdbool.h>
#include <sys/wait.h>
#include <unistd.h>

#define CONTEXT_SWITCHING_NUM 10000
int process_context_switching_time();

int process_context_switching_time() {
    int pipefd[2];
    pid_t cpid;
    int msg = 1;

    if (pipe(pipefd) == -1) {
        perror("pipe");
        return -1;
    }

    fcntl(pipefd[0], F_SETPIPE_SZ, sizeof(msg));
    fcntl(pipefd[1], F_SETPIPE_SZ, sizeof(msg));

    int start_ccnt = ccnt_read();
    if ((cpid = fork()) == -1) {
        perror("fork");
        return -1;
    }

    if (cpid == 0) { // Child writes to pipe
        for (int i = 0; i < CONTEXT_SWITCHING_NUM; i++) {
            // printf("Child: ccnt = %u\n", ccnt_read());
            if (write(pipefd[1], &msg, sizeof(msg)) != sizeof(msg)) {
                printf("1\n");
                return -1;
            }

            if (read(pipefd[0], &msg, sizeof(msg)) != sizeof(msg)) {
                printf("2\n");
                return -1;
            }
        }

        return 0;
    } else { // Parent reads char to pipe
        for (int i = 0; i < CONTEXT_SWITCHING_NUM; i++) {
            // printf("Parent: ccnt = %u\n", ccnt_read());
            int ret = 0;
            if ((ret = write(pipefd[1], &msg, sizeof(msg))) != sizeof(msg)) {
                printf("3 - %d\n", ret);
                return -1;
            }

            if (read(pipefd[0], &msg, sizeof(msg)) != sizeof(msg)) {
                printf("4\n");
                return -1;
            }
        }
        wait(NULL);
    }
    int end_ccnt = ccnt_read();
    int diff = end_ccnt - start_ccnt;
    printf("start: %u, end: %u, diff: %u\n", start_ccnt, end_ccnt, diff);
    printf("average: %u\n", diff / (CONTEXT_SWITCHING_NUM * 2));
    return 0;
}

int main() {
    process_context_switching_time();
    return 0;
}

