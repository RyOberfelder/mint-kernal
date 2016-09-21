/* if not explained here, please refer to the previous  hello modules*/

#include<linux/init.h>
#include<linux/module.h>

/* following are more headings used to support param arguments*/
#include<linux/moduleparam.h>
#include<linux/stat.h>  
MODULE_LICENSE("GPL");
MODULE_AUTHOR("Oberfelder");
MODULE_DESCRIPTION("Basic hello world module designed to learn how to build modules");
MODULE_SUPPORTED_DEVICE("testdevice");

static short int myshort = 2;
static int myint = 200;
static long int mylong = 2999;
static char *mystring = "good day to ya!";
static int myintArray[2] = {-1, -1 };
static int arr_argc = 0; 

/* The following comment block is meant to explain how module_param works.*/

/*
 * module_param(foo, init, 0000)
 * The first param is the parameters name
 * the second param is the data type
 * the last arguments is to set the permissions bits. Here they are set to open
 */ 

/* actually defining params*/
module_param(myshort, short, S_IRUSR | S_IWUSR | S_IRGRP | S_IWGRP);
MODULE_PARM_DESC(myshort, "A short integer");
module_param(myint, int, S_IRUSR | S_IWUSR | S_IRGRP | S_IROTH);
MODULE_PARM_DESC(myint, "An integer");
module_param(mylong, long, S_IRUSR);
MODULE_PARM_DESC(mylong, "A long integer");
module_param(mystring, charp, 0000);
MODULE_PARM_DESC(mystring, "A character string");

/* the following should be the array */

/*
 * module_param_arry(name, type, num, pem);
 * The first param is the array's name
 * The second param is the data type of the elements of the array
 * the third argument is a pointer to the variable that will store the number
 * of elements of the array initialized by the user at module loading time
 * the last and fourth argument are the permission bits.
 */

module_param_array(myintArray, int, &arr_argc, 0000);
MODULE_PARM_DESC(myintArray, "An array of integers");

/* functions like c print functionaltiy*/
static int hello_init(void){
	int i;
	printk(KERN_ALERT "Hello world \n===============\n");
	printk(KERN_ALERT "myshort is a short integer: %hd\n", myshort);
	printk(KERN_ALERT "myint is an integer: %d\n", myint);
	printk(KERN_ALERT "mylong is a long integer: %ld\n", mylong);
	printk(KERN_ALERT "mystring is string: %s\n", mystring);
	for (i = 0; i < (sizeof myintArray / sizeof (int));i++)
	{
		printk(KERN_ALERT "myintArray[%d] %d\n",i, myintArray[i]);
	}
	printk(KERN_ALERT "got %d arguments for myintArray.\n", arr_argc);
	return 0;
}

static void hello_exit(void){
	printk(KERN_ALERT "Goodbye cruel world, signing off hello 5\n");
}

module_init(hello_init);
module_exit(hello_exit);
