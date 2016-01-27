#ifndef CPU_H_
#define CPU_H_

#include <stdio.h>
#include <stdlib.h>
#include <stdint.h>
#include <sys/wait.h>
#include <unistd.h>
#include <sys/types.h>
#include <sched.h>

#define OVERHEAD_TEST_NUM 10

void prob2(float overhead);
void prob4(float overhead);

inline unsigned ccnt_read(){
	volatile unsigned cc;
	asm volatile ("mrc p15, 0, %0, c9, c13, 0" : "=r" (cc));
	return cc;
}

inline unsigned get_overhead(){
	unsigned t;
	float total = 0;

	for(int i=1; i<=OVERHEAD_TEST_NUM; i++){
		t = ccnt_read();
		t = ccnt_read() - t;
		total += (float)t;

		printf("%dth measurement overhead: %d\n",i, t);
	}
	printf("Avg measurement overhead: %f\n", (float)total/OVERHEAD_TEST_NUM);

	return (total/OVERHEAD_TEST_NUM);
}

#endif