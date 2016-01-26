#include <unistd.h>
#include <sched.h>
#include <stdio.h>
#include <stdlib.h>

#define STACK_SIZE 4096

static inline unsigned int get_cyclecount (void) {
  unsigned int value;
  // Read CCNT Register
  asm volatile ("MRC p15, 0, %0, c9, c13, 0\t\n": "=r"(value));  
  return value;
}

static inline void init_perfcounters () {
  int value = 1;
  value |= 2;
  value |= 4;
  value |= 16;

  // program the performance-counter control-register
  asm volatile ("MCR p15, 0, %0, c9, c12, 0\t\n" :: "r"(value));  
  // enable all counters
  asm volatile ("MCR p15, 0, %0, c9, c12, 1\t\n" :: "r"(0x8000000f));  
  // clear overflows
  asm volatile ("MCR p15, 0, %0, c9, c12, 3\t\n" :: "r"(0x8000000f));
}

int cfunc() {
  return 0;
}

int main(void) {
  int t, overall_t;
  unsigned int overhead;
  int num_iter = 10000;
  int child_pid = -1;

  init_perfcounters();

  overhead = get_cyclecount();
  overhead = get_cyclecount() - overhead;

  overall_t = 0;
  for (int i = 1; i <= num_iter; i++){
    t = get_cyclecount();
    child_pid = fork();
    t = get_cyclecount() - t;

    overall_t += t;
    kill(child_pid, SIGKILL);
  }
  
  printf ("creating process took %d cycles", ((overall_t - num_iter*overhead)/num_iter));

  void *child_stack = malloc(STACK_SIZE);

  overall_t = 0;
  for (int i = 1; i <= num_iter; i++){
    t = get_cyclecount();
    clone(&cfunc, child_stack+STACK_SIZE, CLONE_FS|CLONE_FILES|CLONE_THREAD|CLONE_SIGHAND|CLONE_VM)
    t = get_cyclecount() - t;

    overall_t += t;
  }

  printf ("creating thread took %d cycles", ((overall_t - num_iter*overhead)/num_iter));

  return 0;
}
