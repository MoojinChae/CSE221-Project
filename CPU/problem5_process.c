#define _GNU_SOURCE
#include "cpu.h"
#include <fcntl.h>
#include <math.h>
#include <pthread.h>
#include <stdio.h>
#include <stdbool.h>
#include <stdlib.h>
#include <sys/wait.h>
#include <unistd.h>

#define CONTEXT_SWITCHING_NUM 50
int process_context_switching_time();

int process_context_switching_time() {
    int pipefd[2];
    pid_t cpid;
    unsigned msg = 1;
    unsigned end_ccnt = 0;
    unsigned total = 0;
    int context_switch_num = 0;

    if (pipe(pipefd) == -1) {
        perror("pipe");
        return -1;
    }

    fcntl(pipefd[0], F_SETPIPE_SZ, sizeof(msg));
    fcntl(pipefd[1], F_SETPIPE_SZ, sizeof(msg));

    int start_ccnt = 0;

    if ((cpid = fork()) == -1) {
        perror("fork");
        return -1;
    }

    if (cpid == 0) { // Child writes to pipe
        close(pipefd[0]);
        if (write(pipefd[1], &msg, sizeof(msg)) != sizeof(msg)) {
            exit(1);
        }
        exit(1);
    } else { // Parent reads char to pipe
        close(pipefd[1]);
        start_ccnt = ccnt_read();
        if (read(pipefd[0], &msg, sizeof(msg)) != sizeof(msg)) {
            return -1;
        }
        end_ccnt = ccnt_read();
        wait(NULL);
    }

    int diff = end_ccnt - start_ccnt;
    // printf("start: %u, end: %u, diff: %u\n", start_ccnt, end_ccnt, diff);
    return diff;
}

int main() {
    int count = 0;
    double avg = 0.0;
    double stddev = 0.0;
    for (int i = 0; i < 1000; i++) {
        int result = process_context_switching_time();
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

