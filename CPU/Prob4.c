#include "./cpu.h"

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
  
  printf ("creating process took %f cycles\n", (float)((overall_t - num_iter*overhead)/num_iter));

  return;
}
