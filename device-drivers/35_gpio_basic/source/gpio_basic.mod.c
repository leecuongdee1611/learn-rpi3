#include <linux/module.h>
#define INCLUDE_VERMAGIC
#include <linux/build-salt.h>
#include <linux/elfnote-lto.h>
#include <linux/vermagic.h>
#include <linux/compiler.h>

BUILD_SALT;
BUILD_LTO_INFO;

MODULE_INFO(vermagic, VERMAGIC_STRING);
MODULE_INFO(name, KBUILD_MODNAME);

__visible struct module __this_module
__section(".gnu.linkonce.this_module") = {
	.name = KBUILD_MODNAME,
	.init = init_module,
#ifdef CONFIG_MODULE_UNLOAD
	.exit = cleanup_module,
#endif
	.arch = MODULE_ARCH_INIT,
};

#ifdef CONFIG_RETPOLINE
MODULE_INFO(retpoline, "Y");
#endif

static const struct modversion_info ____versions[]
__used __section("__versions") = {
	{ 0x7d0b00ef, "module_layout" },
	{ 0x49f6c524, "gpiod_unexport" },
	{ 0x6091b333, "unregister_chrdev_region" },
	{ 0x61ba7417, "cdev_del" },
	{ 0x89fbe416, "class_destroy" },
	{ 0xf881000e, "device_destroy" },
	{ 0x10407368, "gpiod_export" },
	{ 0x3ae715fa, "gpiod_direction_output_raw" },
	{ 0xfe990052, "gpio_free" },
	{ 0x47229b5c, "gpio_request" },
	{ 0x5dad8514, "device_create" },
	{ 0x663f84fd, "__class_create" },
	{ 0x280ef9cf, "cdev_add" },
	{ 0x32318926, "cdev_init" },
	{ 0xe3ec2f2b, "alloc_chrdev_region" },
	{ 0xbdb2a4e2, "gpiod_set_raw_value" },
	{ 0x56470118, "__warn_printk" },
	{ 0xdcb764ad, "memset" },
	{ 0x12a4e128, "__arch_copy_from_user" },
	{ 0x8da6585d, "__stack_chk_fail" },
	{ 0x6cbbfc54, "__arch_copy_to_user" },
	{ 0xbfb76e02, "gpiod_get_raw_value" },
	{ 0xc442bf2a, "gpio_to_desc" },
	{ 0x92997ed8, "_printk" },
};

MODULE_INFO(depends, "");


MODULE_INFO(srcversion, "74548D59FFB6A652047779F");
