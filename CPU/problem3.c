#include "cpu.h"
#include <stdio.h>
#include <syscall.h>
#include <unistd.h>

void prob3(float overhead){
	unsigned t, overall_t;
	int num_iter = 10;

	overall_t = 0;
	for (int i = 1; i <= num_iter; i++){
		t = ccnt_read();
		syscall(SYS_getpid);
		t = ccnt_read() - t;
		overall_t += (t-overhead);

		printf("%dth system call creation : %f\n", i, (float)(t - overhead));
	}

	printf("avg system call creation : %f\n", (float)((overall_t)/num_iter));

  return;  
}

int main(){
    float overhead = get_overhead();
    printf("====Problem 3 start====\n");
    prob3(overhead);
    printf("====Problem 3 end====\n");
}

