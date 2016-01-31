#ifndef CPU_H_
#define CPU_H_

#include <stdio.h>
#include <stdlib.h>
#include <stdint.h>
#include <sys/wait.h>
#include <unistd.h>
#include <sys/types.h>
#include <sched.h>
#include <syscall.h>

#define OVERHEAD_TEST_NUM 10

unsigned ccnt_read();
unsigned get_overhead();
void prob2(float overhead);
void prob3(float overhead);
void prob4(float overhead);

#endif // CPU_H_
