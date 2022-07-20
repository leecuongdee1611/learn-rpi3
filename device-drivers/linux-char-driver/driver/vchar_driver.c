#include <linux/module.h>
#include <linux/fs.h>
#include <linux/device.h>
#include <linux/slab.h>
#include <linux/cdev.h>
#include <linux/uaccess.h>

/* Internal Include */
#include "vchar_driver.h"

#define DRIVER_AUTHOR "Le Hung Cuong"
#define DRIVER_DESC "A sample character device driver"
#define DRIVER_VERSION "0.1"

typedef struct vchar_dev {
	unsigned char * control_regs;
	unsigned char * status_regs;	
	unsigned char * data_regs;
} vchar_dev_t;


struct _vchar_drv {
	dev_t dev_num;
	struct class *dev_class;
	struct device *dev;
	vchar_dev_t * vchar_hw;
	struct cdev *vcdev;
	unsigned int open_cnt;
} vchar_drv;

/* Function prototype */
static int __init vchar_driver_init(void);
static void __exit vchar_driver_exit(void);
/* Entry point function */
static int vchar_driver_open(struct inode *inode, struct file *file);
static int vchar_driver_release(struct inode *inode, struct file *file);
static ssize_t vchar_driver_read(struct file *filp, char __user *user_buf, size_t len, loff_t *off);
static ssize_t vchar_driver_write(struct file *filp, const char *user_buf, size_t len, loff_t *off);
/* Device HW function */
int vchar_hw_init(vchar_dev_t *hw);
void vchar_hw_exit(vchar_dev_t *hw);
int vchar_hw_read_data(vchar_dev_t *hw, int start_reg, int num_regs, char* kbuf);
int vchar_hw_write_data(vchar_dev_t *hw, int start_reg, int num_regs, char* kbuf);

/* Ham khoi tao thiet bi */
int vchar_hw_init(vchar_dev_t *hw)
{
	char * buf;
	buf = kzalloc(NUM_DEV_REGS, GFP_KERNEL);
	if (!buf) {
		return -ENOMEM;
	}
	
	hw->control_regs = buf;
	hw->status_regs = hw->control_regs +NUM_CTRL_REGS;
	hw->data_regs = hw->status_regs + NUM_STS_REGS;
	
	//khoi tao gia tri ban dau cho cac thanh ghi
	hw->control_regs[CONTROL_ACCESS_REG] = 0x03;
	hw->status_regs[DEVICE_STATUS_REG] = 0X03;
	
	return 0;
}

/* Ham giai phong thiet bi */
void vchar_hw_exit(vchar_dev_t *hw)
{
	kfree(hw->control_regs);
}

/* Ham doc tu cac thanh ghi du lieu cua thiet bi */
int vchar_hw_read_data(vchar_dev_t *hw, int start_reg, int num_regs, char* kbuf)
{
	int read_bytes = num_regs;
	
	if((hw->control_regs[CONTROL_ACCESS_REG] & CTRL_READ_DATA_BIT) == DISABLE)
		return -1;
	if(kbuf == NULL)
		return -1;
	if(start_reg > NUM_DATA_REGS)
		return -1;
		
	if(num_regs > (NUM_DATA_REGS - start_reg))
		read_bytes = NUM_DATA_REGS - start_reg;
	
	memcpy(kbuf, hw->data_regs + start_reg, read_bytes); // doc du lieu tu kernel buffer vao cac thanh ghi du lieu
	
	hw->status_regs[READ_COUNT_L_REG] += 1;
	if(hw->status_regs[READ_COUNT_L_REG] == 0)
		hw->status_regs[READ_COUNT_H_REG] += 1;
		
	return read_bytes;
}

/* Ham ghi vao cac thanh ghi du lieu cua thiet bi */
int vchar_hw_write_data(vchar_dev_t *hw, int start_reg, int num_regs, char* kbuf)
{
	int write_bytes = num_regs;
	
	if((hw->control_regs[CONTROL_ACCESS_REG] & CTRL_WRITE_DATA_BIT) == DISABLE)
		return -1;
	if(kbuf == NULL)
		return -1;
	if(start_reg > NUM_DATA_REGS)
		return -1;

	if(num_regs > (NUM_DATA_REGS - start_reg)) {
		write_bytes = NUM_DATA_REGS - start_reg;
		hw->status_regs[DEVICE_STATUS_REG] |= STS_DATAREGS_OVERFLOW_BIT;
		}
	
	memcpy(hw->data_regs + start_reg, kbuf, write_bytes); // doc du lieu tu cac thanh ghi du lieu vao kernel buffer
	
	hw->status_regs[WRITE_COUNT_L_REG] += 1;
	if(hw->status_regs[WRITE_COUNT_L_REG] == 0)
		hw->status_regs[WRITE_COUNT_H_REG] += 1;
		
	return write_bytes;
}	

static struct file_operations fops = {
	.owner = THIS_MODULE,
	.open = vchar_driver_open,
	.release = vchar_driver_release,
	.read = vchar_driver_read,
	.write = vchar_driver_write,
};

/* This function will be called when we open the Device file */
static int vchar_driver_open(struct inode *inode, struct file *file)
{
	vchar_drv.open_cnt++;
	pr_info("Driver Open Function Called...!!!\n");
	return 0;
}

/* This function will be called when we close the Device file */
static int vchar_driver_release(struct inode *inode, struct file *file)
{
	pr_info("Driver Release Function Called...!!!\n");
	return 0;
}

/* This function will be called when we read the Device file */
static ssize_t vchar_driver_read(struct file *filp, char __user *user_buf, size_t len, loff_t *off)
{
	char *kernel_buf = NULL;
	int num_bytes = 0;
	
	printk("Handle read event start from %lld, %zu byte\n", *off, len);
	
	kernel_buf = kzalloc(len, GFP_KERNEL);
	if(kernel_buf == NULL)
		return 0;
	
	num_bytes = vchar_hw_read_data(vchar_drv.vchar_hw, *off, len, kernel_buf);
	printk("read %d byte from HW\n", num_bytes);
	
	if(num_bytes < 0)
		return -EFAULT;
	if(copy_to_user(user_buf, kernel_buf, num_bytes))
		return -EFAULT;
	*off += num_bytes;
	return num_bytes;

	pr_info("Driver Read Function Called...!!!");
	return 0;
}

/* This function will be called when we write the Device file */
static ssize_t vchar_driver_write(struct file *filp, const char __user *user_buf, size_t len, loff_t *off)
{
	char *kernel_buf = NULL;
	int num_bytes = 0;
	printk("Handle write event start from %lld, %zu byte\n", *off,len);
	
	kernel_buf = kzalloc(len, GFP_KERNEL);
	if(copy_from_user(kernel_buf, user_buf, len))
		return -EFAULT;
	
	num_bytes = vchar_hw_write_data(vchar_drv.vchar_hw, *off, len, kernel_buf);
	printk("writes %d bytes to HW\n", num_bytes);
	
	if (num_bytes < 0)
		return -EFAULT;
	
	*off += num_bytes;
	return num_bytes;

	pr_info("Driver Write Function Called...!!!");
	return 0;
}

/* Module Init function  */
static int __init vchar_driver_init(void)
{
	int ret = 0;

	/* Allocating Major Number */
	ret = alloc_chrdev_region(&vchar_drv.dev_num, 0, 1, "vchar_device_demo");
	if (ret < 0)
	{
		pr_err("Cannot allocate major number for device \n");
		goto r_register_dev;
	}
	pr_info("Major = %d, Minor = %d \n", MAJOR(vchar_drv.dev_num), MINOR(vchar_drv.dev_num));

	/* Creating struct class */
	vchar_drv.dev_class = class_create(THIS_MODULE, "vchar_class");
	if (vchar_drv.dev_class == NULL)
	{
		pr_err("Cannot create the struct class for device \n");
		goto r_class;
	}

	/* Creating device */
	vchar_drv.dev = device_create(vchar_drv.dev_class, NULL, vchar_drv.dev_num, NULL, "vchar_device");
	if (IS_ERR(vchar_drv.dev))
	{
		pr_err("Cannot create the Device\n");
		goto r_device;
	}

	/* cap phat bo nho cho cac cau truc du lieu cua driver va khoi tao */
	vchar_drv.vchar_hw = kzalloc(sizeof(vchar_dev_t), GFP_KERNEL);
	if (!vchar_drv.vchar_hw)
	{
		pr_err("Cannot allocate data structure of the device \n");
		ret = -ENOMEM;
		goto r_allocate_structure;
	}

	/* khoi tao thiet bi vat ly */
	ret = vchar_hw_init(vchar_drv.vchar_hw);
	if (ret < 0)
	{
		pr_err("Cannot initialize a virtual character device \n");
		goto r_init_hw;
	}

	/* Dang ki entry point voi kernel */
	vchar_drv.vcdev = cdev_alloc();
	if (vchar_drv.vcdev == NULL)
	{
		pr_err("Cannot allocate cdev structure \n");
		goto r_cdev;
	}

	/* Creating cdev structure */
	cdev_init(vchar_drv.vcdev, &fops);

	/* Adding character devcie to the system */
	ret = cdev_add(vchar_drv.vcdev, vchar_drv.dev_num, 1);
	if(ret < 0)
	{
		pr_err("Cannot add the device to the system \n");
		goto r_cdev;
	}

	pr_info("Device Driver Insert...Done!!!\n");
	return 0;

r_cdev:
r_init_hw:
	kfree(vchar_drv.vchar_hw);
r_allocate_structure:
	device_destroy(vchar_drv.dev_class, vchar_drv.dev_num);
r_device:
	class_destroy(vchar_drv.dev_class);
r_class:
	unregister_chrdev_region(vchar_drv.dev_num, 1);
r_register_dev:
	return ret;
}

/* Module Exit function */
static void __exit vchar_driver_exit(void)
{
	/* huy dang ky entry point voi kernel */
	cdev_del(vchar_drv.vcdev);	
	/* giai phong thiet bi vat ly */
	vchar_hw_exit(vchar_drv.vchar_hw);
	/* giai phong bo nho da cap phat cau truc du lieu cua driver */
	kfree(vchar_drv.vchar_hw);
	/* xoa bo device file */
	device_destroy(vchar_drv.dev_class, vchar_drv.dev_num);
	class_destroy(vchar_drv.dev_class);
	/* giai phong device number */
	unregister_chrdev_region(vchar_drv.dev_num, 1);

	pr_info("Device Driver Remove...Done!!!\n");
}

module_init(vchar_driver_init);
module_exit(vchar_driver_exit);

MODULE_LICENSE("GPL");
MODULE_AUTHOR(DRIVER_AUTHOR);
MODULE_DESCRIPTION(DRIVER_DESC);
MODULE_VERSION(DRIVER_VERSION);
