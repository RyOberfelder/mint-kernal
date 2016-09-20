/*
 * hello1.c <-- this is the simplest kernal modules
 *
 */


#include<linux/init.h> /* needed by kernel module to create init functions */
#include<linux/module.h> /* needed by all kernel modules*/ 
MODULE_LICENSE("GPL");
MODULE_AUTHOR("Oberfelder");

/* the following is the init for the hello modules*/
static int hello_init(void){
	printk(KERN_ALERT "Hello world!\n");
	return 0;
}
/* the following in the exit needed */
static void hello_exit(void){
	printk(KERN_ALERT "Goodbye cruel world\n");
}
/* the following define the functions as the init and the the exit */
module_init(hello_init);
module_exit(hello_exit);
