#include "./cpu.h"

#define STACK_SIZE 4096

int cfunc() {
  return 0;
}

void prob4(float overhead) {
  unsigned t, overall_t;
  int num_iter = 10000;
  int child_pid = -1;

  overall_t = 0;
  for (int i = 1; i <= num_iter; i++){
    t = ccnt_read();
    child_pid = fork();
    t = ccnt_read() - t;

    overall_t += t;
    kill(child_pid, SIGKILL);
  }
  
  printf ("creating process took %f cycles", (float)((overall_t - num_iter*overhead)/num_iter));

  // void *child_stack = malloc(STACK_SIZE);

  // overall_t = 0;
  // for (int i = 1; i <= num_iter; i++){
  //   t = ccnt_read();
  //   clone(&cfunc, child_stack+STACK_SIZE, CLONE_FS|CLONE_FILES|CLONE_THREAD|CLONE_SIGHAND|CLONE_VM)
  //   t = ccnt_read() - t;

  //   overall_t += t;
  // }

  // printf ("creating thread took %d cycles", ((overall_t - num_iter*overhead)/num_iter));

  return;
}
