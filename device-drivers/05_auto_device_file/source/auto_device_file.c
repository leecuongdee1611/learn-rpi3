#include <linux/kernel.h>
#include <linux/init.h>
#include <linux/module.h> /* Define module_init module_exit */
#include <linux/fs.h> /* Create device number */
#include <linux/device.h> /* Create device file */
//#include <linux/kdev_t.h> /* Create device file */

dev_t dev = 0;
static struct class *dev_class;

/*
	Module Init Function
*/
static int __init static_num_init(void)
{
	/* Allocating Major number */
	if ((alloc_chrdev_region(&dev, 0, 1, "etx_dev")) < 0)
	{
		printk(KERN_INFO "Cannot allocate major number for device \n");
		return -1;
	}
	pr_info("Major = %d, Minor = %d \n", MAJOR(dev), MINOR(dev));

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

	pr_info("Kernel Module Inserted Successfully...\n");
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
static void __exit static_num_exit(void)
{
	device_destroy(dev_class, dev);
	class_destroy(dev_class);
	unregister_chrdev_region(dev, 1);
	pr_info("Kernel Module Removed Successfully...\n");
}

module_init(static_num_init);
module_exit(static_num_exit);

MODULE_LICENSE("GPL");
MODULE_AUTHOR("Le Hung Cuong");
MODULE_DESCRIPTION("Simple linux driver ");
MODULE_VERSION("1.0");
