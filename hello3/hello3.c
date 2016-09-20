/* if not explained here, please refer to the previous  hello modules*/

#include<linux/init.h>
#include<linux/module.h> 
MODULE_LICENSE("GPL");
MODULE_AUTHOR("Oberfelder");
MODULE_DESCRIPTION("Basic hello world module designed to learn how to build modules");
MODULE_SUPPORTED_DEVICE("testdevice");

/* part of the init module, allows us to have init data with the module*/
static int hello2_data __initdata = 2;

/* functions like c print functionaltiy*/
static int hello_init(void){
	printk(KERN_ALERT "Hello world %d\n", hello2_data);
	return 0;
}

static void hello_exit(void){
	printk(KERN_ALERT "Goodbye cruel world\n");
}

module_init(hello_init);
module_exit(hello_exit);
