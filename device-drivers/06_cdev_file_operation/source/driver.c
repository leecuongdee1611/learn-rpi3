#include <linux/kernel.h>
#include <linux/init.h>
#include <linux/module.h> /* Define module_init module_exit */
#include <linux/fs.h> /* Create device number */
#include <linux/device.h> /* Create device file */
//#include <linux/kdev_t.h> /* Create device file */
#include <linux/cdev.h> /* Create cdev structure and file operation  */

dev_t dev = 0;
static struct class *dev_class;
static struct cdev etx_cdev;

/*
	Function Prototype
*/
static int 		__init etx_driver_init(void);
static void 	__exit etx_driver_exit(void);
static int 		etx_open(struct inode *inode, struct file *file);
static int 		etx_release(struct inode *inode, struct file *file);
static ssize_t	etx_read(struct file *filp, char __user *buf, size_t len, loff_t * off);
static ssize_t	etx_write(struct file *filp, const char *buf, size_t len, loff_t * off);

static struct file_operations fops = 
{
	.owner		= THIS_MODULE,
	.read		= etx_read,
	.write		= etx_write,
	.open		= etx_open,
	.release	= etx_release,
};

/*
	This function will be called when we open the Device file
*/
static int 		etx_open(struct inode *inode, struct file *file)
{
	pr_info("Driver Open Function Called...!!!\n");
	return 0;
}

/*
	This function will be called when we close the Device file
*/
static int 		etx_release(struct inode *inode, struct file *file)
{
	pr_info("Driver Release Function Called...!!!\n");
	return 0;
}

/*
	This function will be called when we read the Device file
*/
static ssize_t	etx_read(struct file *filp, char __user *buf, size_t len, loff_t * off)
{
	pr_info("Driver Read Function Called...!!!\n");
	return 0;
}

/*
	This function will be called when we write the Device file
*/
static ssize_t	etx_write(struct file *filp, const char __user *buf, size_t len, loff_t * off)
{
	pr_info("Driver Write Function Called...!!!\n");
	return 0;
}


/*
	Module Init Function
*/
static int __init etx_driver_init(void)
{
	/* Allocating Major number */
	if ((alloc_chrdev_region(&dev, 0, 1, "etx_dev")) < 0)
	{
		printk(KERN_INFO "Cannot allocate major number for device \n");
		return -1;
	}
	pr_info("Major = %d, Minor = %d \n", MAJOR(dev), MINOR(dev));

	/* Creating cdev structure */
	cdev_init(&etx_cdev, &fops);

	/* Adding character device to the system */
	if ((cdev_add(&etx_cdev, dev, 1)) < 0)
	{
		pr_err("Cannot add the device to the system\n");
		goto r_class;
	}

	/* Creating struct class */
	if ((dev_class = class_create(THIS_MODULE,"etx_class")) == NULL)
	{
		pr_err("Cannot create the struct class for device \n");
		goto r_class;
	}

	/* Creating device */
	if ((device_create(dev_class, NULL, dev, NULL, "etx_device")) == NULL)
	{
		pr_err("Cannot create the Device\n");
		goto r_device;
	}

	pr_info("Device Driver Insert...Done!!!\n");
	return 0;

r_device:
	class_destroy(dev_class);
r_class:
	unregister_chrdev_region(dev,1);
	return -1;
}

/*
	Module Exit Function
*/
static void __exit etx_driver_exit(void)
{
	device_destroy(dev_class, dev);
	class_destroy(dev_class);
	cdev_del(&etx_cdev);
	unregister_chrdev_region(dev, 1);
	pr_info("Device Driver Remove...Done!!!\n");
}

module_init(etx_driver_init);
module_exit(etx_driver_exit);

MODULE_LICENSE("GPL");
MODULE_AUTHOR("Le Hung Cuong");
MODULE_DESCRIPTION("Simple linux driver ");
MODULE_VERSION("1.0");
