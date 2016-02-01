#include "cpu.h"
#include <signal.h>
#include <stdio.h>
#include <syscall.h>
#include <unistd.h>
#include <wait.h>

void create_process(float overhead, int i){
    unsigned t, overall_t;
    int child_pid = -1;
    int status;

    t = ccnt_read();
    child_pid = fork();
    t = ccnt_read() - t;

    if (child_pid >1){
        child_pid = waitpid(child_pid, &status, 0);
        kill(child_pid, SIGKILL);
        //printf("%dth process killed\n", i);
    }
    else if(child_pid == 0){
        printf("%dth process creation : %f\n", i, (float)(t-overhead));
        return;
    }
    else{
        printf("Fork fail!!");
    }
    return;
}

int main(){
    int parentPid = getpid();
    int num_iter = 100;
    for(int i=1; i<=num_iter; i++){
        create_process(0, i);
        if (parentPid != getpid()) return 0;
    }
    return 0;
}

