#include "./cpu.h"

void prob2(float overhead){
	unsigned t;

  for (int i = 1; i <= 8; i++) {
    t = ccnt_read();
    int n = 0;
    t = ccnt_read() - t;

    printf("%dth variable creation : %f\n", i, (float)(t - overhead));
  }

  return;  
}
