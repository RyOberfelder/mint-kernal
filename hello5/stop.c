/*
 * stop.c is how we would do the closing as a single file
 */

#include<linux/kernel.h> /* needed because we are going kernel work*/
#include<linux/init.h>
#include<linux/module.h> /* neede because we are building a module */

static void hello_exit(void){
	printk(KERN_ALERT "Bye everyone, this is the kernel signing off\n");
}

module_exit(hello_exit);
