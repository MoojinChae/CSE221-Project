#include "cpu.h"
#include <stdio.h>

void prob2(float overhead){
	unsigned t;
	int num_iter = 8;

	for (int i = 1; i <= num_iter; i++){
		t = ccnt_read();
		int n = 0;
		t = ccnt_read() - t;

		printf("%dth variable creation : %f\n", i, (float)(t - overhead));
	}

	return;  
}

int main(){
	float overhead = get_overhead();
	printf("====Problem 2 start====\n");
	prob2(overhead);
	printf("====Problem 2 end====\n");
}

