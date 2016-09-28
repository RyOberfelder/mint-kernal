/*
 * procfs1.c - we are going to be creating a 'file' in /proc
 *
 */
#include<linux/init.h>
#include<linux/module.h>
#include<linux/kernel.h>
#include<linux/fs.h> /* needed for the general fs */
#include<linux/proc_fs.h> /* this is needed to use the proc fs */
#include<asm/uaccess.h>  /* used for the copy to and from user functions  */

#define procfs_name "helloworld" /* This is where we define proc file name.*/
#define PROCFS_MAX_SIZE 1024

static char procfs_buffer[PROCFS_MAX_SIZE];

/* This is how we  keep track of the number of bytes left to read */
static unsigned long procfs_buffer_size = 0;

MODULE_LICENSE("GPL");
MODULE_AUTHOR("Oberfelder");
MODULE_DESCRIPTION("Creates a simple thing proc file that tells you information when you cat it")
MODULE_SUPPORTED_DEVICE("testdevice");

/* function signatures */
static ssize_t procfs_read(struct file *filp,   /* see include/linux/fs.h */
                           char *buffer,        /* buffer to fill with data */
                           size_t length,       /* length of the buffer */
                           loff_t * offset);

static ssize_t procfs_write(struct file *filp,   /* see include/linux/fs.h */
                           const char *buffer,  /* buffer to fill with data */
                           size_t length,       /* length of the buffer */
                           loff_t * offset);


/**
 * This structure holds information about the proc/ file
 */
struct proc_dir_entry *Our_Proc_File;

/* defined the proc file fop structure used */
static const struct file_operations proc_file_fops = {
 .owner = THIS_MODULE,
 .read  = procfs_read,
 .write = procfs_write,
};

static ssize_t procfs_read(struct file *filp,   /* see include/linux/fs.h */
                           char *buffer,        /* buffer to fill with data */
                           size_t length,       /* length of the buffer */
                           loff_t * offset)
{
	/* section detailing if we have finished reading from the buffer */
	static int finished = 0;
	
	if ( finished ) {
		printk(KERN_INFO "procfs_read: END\n");
		finished = 0;
		return 0;
	}

	finished = 1;
	/* does the error handing if copy to user has issue */
	if ( copy_to_user(buffer, procfs_buffer, procfs_buffer_size) ) {
		return -EFAULT;
	}
	
	printk(KERN_INFO "procfs_read: read %lu bytes\n", procfs_buffer_size);

	return procfs_buffer_size;

}

static ssize_t procfs_write(struct file *filp,   /* see include/linux/fs.h */
                           const char *buffer,  /* buffer to fill with data */
                           size_t length,       /* length of the buffer */
                           loff_t * offset)
{
	/* assures that max buffer size, is upheld */
	if ( length > PROCFS_MAX_SIZE ) {
		procfs_buffer_size = PROCFS_MAX_SIZE;
	} else {
		procfs_buffer_size = length;
	}

	if ( copy_from_user(procfs_buffer, buffer, procfs_buffer_size) ) {
		return -EFAULT;
	}

	printk(KERN_INFO "procfs_write: write %lu bytes\n", procfs_buffer_size);	
	return procfs_buffer_size;


}


static 
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
