#include "cpu.h"
#include <stdio.h>

void prob2(float overhead){
	printf("====Problem 2 start====\n");
	unsigned t;
	int num_iter = 8;

	for (int i = 1; i <= num_iter; i++){
		t = ccnt_read();
		int n = 0;
		t = ccnt_read() - t;

		printf("%dth variable creation : %f\n", i, (float)(t - overhead));
	}

	printf("====Problem 2 end====\n");
	return;  
}
