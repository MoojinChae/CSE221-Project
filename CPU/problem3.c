#include "cpu.h"
#include <stdio.h>
#include <syscall.h>
#include <unistd.h>

void prob3(float overhead){
	unsigned t;

	t = ccnt_read();
	syscall(SYS_getpid);
	t = ccnt_read() - t;

	printf("system call(getpid) creation : %f\n", (float)(t - overhead));

	return;  
}

int main(){
	float overhead = 0;//get_overhead();
	prob3(overhead);
	return 0;
}

