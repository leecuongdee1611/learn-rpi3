#include <linux/module.h>
#include <linux/fs.h>
#include <linux/device.h>
#include <linux/slab.h>
#include <linux/cdev.h>
#include <linux/uaccess.h>

#define DRIVER_AUTHOR "Le Hung Cuong"
#define DRIVER_DESC "A sample character device driver"
#define DRIVER_VERSION "0.1"

/* Module Init function  */
static int __init vchar_driver_init(void)
{
	pr_info("Device Driver Insert...Done!!!\n");
}

/* Module Exit function */
static void __exit vchar_driver_exit(void)
{
	pr_info("Device Driver Remove...Done!!!\n");
}

module_init(vchar_driver_init);
module_exit(vchar_driver_exit);

MODULE_LICENSE("GPL");
MODULE_AUTHOR(DRIVER_AUTHOR);
MODULE_DESCRIPTION(DRIVER_DESC);
MODULE_VERSION(DRIVER_VERSION);
