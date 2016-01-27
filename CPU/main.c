#include "cpu.h"

int main()
{

	float overhead;
	overhead = get_overhead();
	printf("Reading overhead time is : %f\n", overhead);

	prob2(overhead);
	prob4(overhead);

	return 0;
}