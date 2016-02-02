#define _GNU_SOURCE
#include "cpu.h"
#include <fcntl.h>
#include <pthread.h>
#include <stdio.h>
#include <stdbool.h>
#include <unistd.h>

int main(){
    int fd[2];
    unsigned t;
    int num_iter = 100;
    int msg = 1;

    if (pipe(fd) == -1) {
        perror("pipe");
        return -1;
    }

    fcntl(fd[0], F_SETPIPE_SZ, sizeof(msg));
    fcntl(fd[1], F_SETPIPE_SZ, sizeof(msg));

    unsigned overall_t = 0;
    for (int i = 1; i <= num_iter; i++){
        t = ccnt_read();
        write(fd[1], &msg, sizeof(msg));
        read(fd[0], &msg, sizeof(msg));
        t = ccnt_read() - t;
        //printf("%dth pipe write overhead : %f\n", i, (float)t);
        overall_t += t;
    }
    printf("average of pipe write overhead : %f\n", ((float)overall_t/num_iter));

    close(fd[0]);
    close(fd[1]);

    return 0;
}
