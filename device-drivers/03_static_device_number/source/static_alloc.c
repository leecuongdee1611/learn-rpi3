#include <linux/kernel.h>
#include <linux/init.h>
#include <linux/module.h> /* Define module_init module_exit */
#include <linux/fs.h> /* Create device number */

/* Creating the dev with custom major and minor number */
dev_t dev = MKDEV(235, 0);

/*
	Module Init Function
*/
static int __init static_num_init(void)
{
	register_chrdev_region(dev, 1, "Static_Dev");
	printk(KERN_INFO "Major = %d, Minor = %d \n", MAJOR(dev), MINOR(dev));
	printk(KERN_INFO "Kernel Module Inserted Successfully...\n");
	return 0;
}

/*
	Module Exit Function
*/
static void __exit static_num_exit(void)
{
	unregister_chrdev_region(dev, 1);
	printk(KERN_INFO "Kernel Module Removed Successfully...\n");
}

module_init(static_num_init);
module_exit(static_num_exit);

MODULE_LICENSE("GPL");
MODULE_AUTHOR("Le Hung Cuong");
MODULE_DESCRIPTION("Simple linux driver (Statically allocating the Major and Minor number)");
MODULE_VERSION("1.0");
