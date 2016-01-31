#include "cpu.h"
#include <signal.h>
#include <stdio.h>
#include <syscall.h>
#include <unistd.h>

void prob4(float overhead){
  unsigned t, overall_t;
  int num_iter = 10;
  int child_pid = -1;

  overall_t = 0;
  for (int i = 1; i <= num_iter; i++){
    t = ccnt_read();
    child_pid = fork();
    t = ccnt_read() - t;
    overall_t += (t-overhead);

    if (child_pid >1){
      kill(child_pid, SIGKILL);
      printf("%dth process creation : %f\n", i, (float)(t-overhead));
    }
  }

  printf("avg process creation : %f\n", (float)((overall_t)/num_iter));

  
  return;
}

int main(){
  float overhead = get_overhead();
  printf("====Problem 4 start====\n");
  prob4(overhead);
  printf("====Problem 4 end====\n");
}

