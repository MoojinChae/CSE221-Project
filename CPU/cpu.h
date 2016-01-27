#ifndef CPU_H_
#define CPU_H_

#include <stdio.h>
#include <stdlib.h>
#include <stdint.h>
#include <sys/wait.h>
#include <unistd.h>
#include <sys/types.h>
#include <sched.h>

#define OVERHEAD_TEST_NUM 10000

void prob2(float overhead);
void prob4(float overhead);

inline unsigned ccnt_read(){
	unsigned cc;
	asm volatile ("mrc p15, 0, %0, c9, c13, 0" : "=r" (cc));
	return cc;
}

inline unsigned get_overhead(){
	int i=0;
	unsigned start, end;
	float total = 0;

	for(i=1; i<=OVERHEAD_TEST_NUM; i++){
		start = ccnt_read();
		end = ccnt_read();
		total += (float)(end - start);

		printf("%dth measurement overhead: %d\n",i, end - start);
	}
	printf("Avg measurement overhead: %f\n", (float)total/OVERHEAD_TEST_NUM);

	return (total/OVERHEAD_TEST_NUM);
}

#endif