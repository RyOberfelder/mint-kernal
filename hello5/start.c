/*
 * start.c is how we would do the init as a single file
 */

#include<linux/kernel.h> /* needed because we are going kernel work*/
#include<linux/init.h>
#include<linux/module.h> /* neede because we are building a module */

MODULE_LICENSE("GPL");
MODULE_AUTHOR("Oberfelder");
MODULE_DESCRIPTION("module used to demonstrate the spreading of modules across files");
MODULE_SUPPORTED_DEVICE("testdevice");

static int hello_init(void){
	printk(KERN_ALERT "Hello everyone, this is the kernel speaking\n");
	return 0;
}

module_init(hello_init);
