#include <linux/module.h>
#include <linux/kernel.h>

static void enable_ccnt_read(void* data){
	// PMUSERENR = 1
	asm volatile ("mcr p15, 0, %0, c9, c14, 0" :: "r"(1));

	// PMCR.E (bit 0) = 1
	asm volatile ("mcr p15, 0, %0, c9, c12, 0" :: "r"(1));

	// PMCNTENSET.C (bit 31) = 1
	asm volatile ("mcr p15, 0, %0, c9, c12, 1" :: "r"(1 << 31));
}

int hello_init(void){
	printk(KERN_ALERT "Hello kernel :)\n");
	on_each_cpu(enable_ccnt_read, NULL, 1);
	return 0;
}

void hello_exit(void){
	printk(KERN_ALERT "Goodbye World!\n");
}

module_init(hello_init);
module_exit(hello_exit);

MODULE_LICENSE("GPL");