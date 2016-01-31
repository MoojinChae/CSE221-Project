#ifndef CPU_H_
#define CPU_H_

#define OVERHEAD_TEST_NUM 2000

__attribute__((always_inline)) static unsigned ccnt_read()
{
    unsigned cc;
    asm volatile("mrc p15, 0, %0, c9, c13, 0" : "=r" (cc));
    return cc;
}
unsigned get_overhead();

void prob2(float overhead);
void prob3(float overhead);
void prob4(float overhead);

#endif // CPU_H_
