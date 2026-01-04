#include <linux/module.h>
#define INCLUDE_VERMAGIC
#include <linux/build-salt.h>
#include <linux/elfnote-lto.h>
#include <linux/export-internal.h>
#include <linux/vermagic.h>
#include <linux/compiler.h>

#ifdef CONFIG_UNWINDER_ORC
#include <asm/orc_header.h>
ORC_HEADER;
#endif

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
	{ 0x122c3a7e, "_printk" },
	{ 0x13c49cc2, "_copy_from_user" },
	{ 0x4a453f53, "iowrite32" },
	{ 0xf0fdf6cb, "__stack_chk_fail" },
	{ 0xa78af5f3, "ioread32" },
	{ 0x6b10bee1, "_copy_to_user" },
	{ 0x60a5786d, "platform_get_resource" },
	{ 0x14d9bc1b, "devm_ioremap_resource" },
	{ 0xb8ccf57f, "platform_get_irq" },
	{ 0x3a198b71, "devm_request_threaded_irq" },
	{ 0xe3ec2f2b, "alloc_chrdev_region" },
	{ 0x858c69be, "cdev_init" },
	{ 0x6b732375, "cdev_add" },
	{ 0x4a77885d, "platform_driver_unregister" },
	{ 0xbdfb6dbb, "__fentry__" },
	{ 0x23509fba, "__platform_driver_register" },
	{ 0x5b8239ca, "__x86_return_thunk" },
	{ 0xc892ac3e, "cdev_del" },
	{ 0x6091b333, "unregister_chrdev_region" },
	{ 0xe2fd41e5, "module_layout" },
};

MODULE_INFO(depends, "");

MODULE_ALIAS("of:N*T*Cmyvendor,my-uart");
MODULE_ALIAS("of:N*T*Cmyvendor,my-uartC*");

MODULE_INFO(srcversion, "AA65CFAA49D023F489E6264");
