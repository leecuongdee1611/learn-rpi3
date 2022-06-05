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
	{ 0x95231b80, "param_ops_charp" },
	{ 0xe8d068d1, "param_array_ops" },
	{ 0xe40769c1, "param_ops_int" },
	{ 0x20d256bc, "param_get_int" },
	{ 0x92997ed8, "_printk" },
	{ 0x6c06b27, "param_set_int" },
};

MODULE_INFO(depends, "");


MODULE_INFO(srcversion, "E65A45E5C63A4D0CA5754A3");
