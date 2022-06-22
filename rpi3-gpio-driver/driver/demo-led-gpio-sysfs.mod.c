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
	{ 0xd9726f80, "module_layout" },
	{ 0x64b60eb0, "class_destroy" },
	{ 0x68de7c4, "platform_driver_unregister" },
	{ 0xd4415d08, "__platform_driver_register" },
	{ 0xc5850110, "printk" },
	{ 0xa946dcde, "__class_create" },
	{ 0xc959d152, "__stack_chk_fail" },
	{ 0x82d1e49, "gpiod_set_value" },
	{ 0x3854774b, "kstrtoll" },
	{ 0x4ae75af1, "gpiod_get_value" },
	{ 0x9c26ba74, "gpiod_direction_output" },
	{ 0x53a2f859, "gpiod_direction_input" },
	{ 0x222e7ce2, "sysfs_streq" },
	{ 0x3c3ff9fd, "sprintf" },
	{ 0x40f93f16, "gpiod_get_direction" },
	{ 0x1a1edd5a, "_dev_err" },
	{ 0xed208a09, "device_unregister" },
	{ 0xc6810313, "_dev_info" },
	{ 0xbdfb6dbb, "__fentry__" },
};

MODULE_INFO(depends, "");


MODULE_INFO(srcversion, "945E641F921036B90AB1141");
