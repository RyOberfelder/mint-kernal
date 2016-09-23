/*
 * chardev.c: The point of this is to create a read-only char device that reports back
 * the number of times that you've read from the dev file
 */
#include<linux/init.h>
#include<linux/module.h>

#include<linux/kernel.h> /* Needed for KERN_INFO*/

/* following are more headings used to support the dev device module */
#include<linux/fs.h>
#include<asm/uaccess.h>  /* this is for the put_user */
MODULE_LICENSE("GPL");
MODULE_AUTHOR("Oberfelder");
MODULE_DESCRIPTION("Char device that reports bacek the number of times that you have read from the dev file.");
MODULE_SUPPORTED_DEVICE("testdevice");

/*
 * Prototypes that would normally go in a .h file
 */

int build_chardev(void);
void exit_chardev(void);

/* Its important that this functions are designed to be consumed by char drivers */
static int device_open(struct inode *, struct file *);
static int device_release(struct inode *, struct file *);
static ssize_t device_read(struct file *, char *, size_t, loff_t *);
static ssize_t device_write(struct file *, const char *, size_t, loff_t *);

#define SUCCESS 0
#define DEVICE_NAME "chardev" 	/* Dev name as it appears in /proc/devices   */
#define BUF_LEN 80		/* Max length of the message from the device */

static int Major;		/* Major number assigned to our device driver */
static int Device_Open = 0; 	/* Is device open?
				 * Used to prevent multiple accesses to the device */ 
static char msg[BUF_LEN];	/* The msg the device will give when asked */
static char *msg_Ptr;

/* this defines a structure we use to define permissable actions with the driver */
static struct file_operations fops = {
	.read = device_read,
	.write = device_write,
	.open = device_open,
	.release = device_release
};

/*
 * This function is called when the module is loaded
 */

int build_chardev(void)
{
	Major = register_chrdev(0, DEVICE_NAME, &fops); /*Major assigned number */

	if (Major < 0) {
		printk(KERN_ALERT "Registering char device failed with %d\n", Major);
		return Major;
	}
	printk(KERN_INFO "I was assigned major number %d. To talk to\n", Major);
	printk(KERN_INFO "the driver, create a dev file with\n");
	printk(KERN_INFO "'mknod /dev/%s c %d 0'.\n", DEVICE_NAME, Major);
	printk(KERN_INFO "Try various minor numbers. Try to cat and echo to\n");
	printk(KERN_INFO "the device file.\n");
	printk(KERN_INFO "Remove the device file and module when done.\n");
	return SUCCESS;
}

/*
 * This function is called when the module is unloaded
 */
void exit_chardev(void)
{
	/*
	 * Unregister the device
	 */
	unregister_chrdev(Major, DEVICE_NAME);
}

/*
 * The Methods Section - the abilites of the module to act
 */

/*
 * device_open
 * Called when a process tries to open the device file, for example:
 * 'cat /dev/mycharfile'
 */

static int device_open(struct inode *inode, struct file *file)
{
	static int counter = 0;
	
	if (Device_Open) {
		return -EBUSY;
	}
	
	Device_Open++;
	sprintf(msg, "I already told you %d times Hello world!\n", counter++);
	msg_Ptr = msg;
	try_module_get(THIS_MODULE);

	return SUCCESS;
}

/*
 * This is called when a process closes the device file
 */
static int device_release(struct inode *inode, struct file *file)
{
	Device_Open--; /* We're now ready for our next caller */

	/*
	 * Decrement the usage count, or else once you opened the file, you'll
	 * never get rid of the module
	 */
	module_put(THIS_MODULE);
	
	return 0;
}

/*
 * Called when a process, which already opened the dev file, attemps to
 * read from it.
 */
static ssize_t device_read(struct file *filp, 	/* see include/linux/fs.h */
			   char *buffer,	/* buffer to fill with data */
			   size_t length,	/* length of the buffer */
			   loff_t * offset)
{
	/*
	 * Number of bytes written to the buffer
	 */
	int bytes_read = 0;

	/*
	 * if we're at the end of the message,
	 * return 0 signifying end of file
	 */
	if (*msg_Ptr == 0) {
		return 0;
	}
	/*
	 * Actually put the data into the buffer
	 */
	while (length && *msg_Ptr) {

		/*
		 * The buffer is in the user data segment, not the kernel
		 * segment so "*" assignment won't work. We have to use
		 * put_user which copies data from the kernel data segment to
		 * the user data segment.
		 */
		put_user(*(msg_Ptr++), buffer++);

		length--;
		bytes_read++;
	}

	/*
	 * Most read functions return the number of bytes put into the buffer
	 */
	return bytes_read;
}

/*
 * Called when a process writes to deve file: echo "hi" > /dev/hello
 */
static ssize_t
device_write(struct file *filp, const char *buff, size_t len, loff_t * off)
{
	printk(KERN_ALERT "Sorry, this operation just is not supported friend.\n");
	return -EINVAL;
}

module_init(build_chardev);
module_exit(exit_chardev);
