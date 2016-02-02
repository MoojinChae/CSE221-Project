#define _GNU_SOURCE
#include "cpu.h"
#include <fcntl.h>
#include <pthread.h>
#include <stdio.h>
#include <stdbool.h>
#include <unistd.h>

int main(){
    int fd;
    unsigned t;
    int num_iter = 100;
    int msg = 1;

    fcntl(fd, F_SETPIPE_SZ, sizeof(msg));

    unsigned overall_t = 0;
    for (int i = 1; i <= num_iter; i++){
        t = ccnt_read();
        write(fd, &msg, sizeof(msg));
        t = ccnt_read() - t;
        //printf("%dth pipe write overhead : %f\n", i, (float)t);
        overall_t += t;
    }
    printf("average of pipe write overhead : %f\n", ((float)overall_t/num_iter));

    overall_t = 0;
    for (int i = 1; i <= num_iter; i++){
        t = ccnt_read();
        read(fd, &msg, sizeof(msg));
        t = ccnt_read() - t;
        //printf("%dth pipe read overhead : %f\n", i, (float)t);
        overall_t += t;
    }
    printf("average of pipe read overhead : %f\n", ((float)overall_t/num_iter));

    close(fd);

    return 0;
}