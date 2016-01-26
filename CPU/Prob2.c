#include <stdio.h>

static inline unsigned int get_cyclecount (void)
{
  unsigned int value;
  // Read CCNT Register
  asm volatile ("MRC p15, 0, %0, c9, c13, 0\t\n": "=r"(value));  
  return value;
}

static inline void init_perfcounters ()
{
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

int main(void) {
  int t;
  int num_iter = 8;

  init_perfcounters();

  unsigned int overhead = get_cyclecount();
  overhead = get_cyclecount() - overhead;

  for (int i = 1; i <= num_iter; i++) {
    t = get_cyclecount();
    int n = 0;
    t = get_cyclecount() - t;

    printf ("function took %d cycles in #%d", t - overhead, i);
  }

  return 0;
}
