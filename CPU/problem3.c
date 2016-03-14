#include "cpu.h"
#include <stdio.h>
#include <syscall.h>
#include <unistd.h>
#include <sys/types.h>

void prob3(float overhead){
    unsigned t;

    int num_iter = 1;

    for (int i = 1; i <= num_iter; i++){
        t = ccnt_read();
        //syscall(SYS_getpid);
        getpid();
        t = ccnt_read() - t;

        printf("%dth system call creation : %f\n", i, (float)(t - overhead));
    }

    return;  
}

int main(){
    prob3(8);
    return 0;
}

