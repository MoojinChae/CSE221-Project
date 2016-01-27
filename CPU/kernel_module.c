#include <linux/module.h>
#include <linux/kernel.h>

static void enable_ccnt_read(void* data){

	asm volatile("mcr p15, 0, %0, c15, c12, 0" : : "r" (1));

}

int init_module(){

	on_each_cpu(enable_ccnt_read, NULL, 1);

	return 0;
}

void cleanup_module(){}

MODULE_LICENSE("GPL");