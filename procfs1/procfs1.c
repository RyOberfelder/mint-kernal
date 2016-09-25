/*
 * procfs.c - we are going to be creating a 'file' in /proc
 *
 */
#include<linux/init.h>
#include<linux/module.h>
#include<linux/kernel.h>
#include<linux/fs.h> /* needed for the general fs */
#include<linux/proc_fs.h> /* this is needed to use the proc fs */

#define procfs_name "helloworld"

MODULE_LICENSE("GPL");
MODULE_AUTHOR("Oberfelder");
MODULE_DESCRIPTION("Creates a simple thing proc file that tells you information when you cat it")
MODULE_SUPPORTED_DEVICE("testdevice");


/* function signatures */
static ssize_t procfs_read(struct file *filp,   /* see include/linux/fs.h */
                           char *buffer,        /* buffer to fill with data */
                           size_t length,       /* length of the buffer */
                           loff_t * offset);

/**
 * This structure holds information about the proc/ file
 *
 */
struct proc_dir_entry *Our_Proc_File;

/* defined the proc file fop structure used */
static const struct file_operations proc_file_fops = {
 .owner = THIS_MODULE,
 .read  = procfs_read,
};

/* Here is where we are going tp put data into the proc fs file
 * Arguments
 * =========
 * 1. The buffer where the data is to be inserted, if you decide to use it.
 * 2. A pointer to a pointer to characters. This is useful if you do not want to use
 *    the buffer alloted by the kernel
 * 3. The current position in the file
 * 4. The size of the buffer in the first argument
 * 5. Write a "1" here to indicate EOF.
 * 6. A pointer to data (useful in case one common read for muliple /proc/... entries
 *
 * Useage and Return Value
 * =======================
 * A return value of zero means you have no further information at this time
 * (end of file). A negative return value is an error condition.
 * 
 * For More Information
 * ====================
 * I would read the comments dispursed through-out the code.
 */
static ssize_t procfs_read(struct file *filp,   /* see include/linux/fs.h */
                           char *buffer,        /* buffer to fill with data */
                           size_t length,       /* length of the buffer */
                           loff_t * offset)
{
	int ret = 0;
	static int finished;
	
	printk(KERN_INFO "procfs_read (/proc/%s) called\n", procfs_name);
	
	if (finished){
		printk(KERN_INFO "procfs_read: END\n");
		finished = 0;
	}

	finished = 1;
	ret = sprintf(buffer, "HelloWorld!\n");
	
	return ret;
}

int build_helloworld(void) {
	Our_Proc_File = proc_create(procfs_name, 0644, NULL, &proc_file_fops);
	if (!Our_Proc_File) {
		printk(KERN_ALERT "Error: Could not initialize /proc/%s\n",
			 procfs_name);
		return -ENOMEM;
	}
	
	/*
    	 * KUIDT_INIT is a macro defined in the file 'linux/uidgid.h'. KGIDT_INIT also appears here.
 	 */ 	 
	proc_set_user(Our_Proc_File, KUIDT_INIT(0), KGIDT_INIT(0));
	proc_set_size(Our_Proc_File, 37);

	printk(KERN_INFO "/proc/%s created\n", procfs_name);
	return 0; /* everything is ok */
}

void exit_helloworld(void)
{
	remove_proc_entry(procfs_name, NULL);
	printk(KERN_INFO "/proc/%s removed \n", procfs_name);
}

module_init(build_helloworld);
module_exit(exit_helloworld);
