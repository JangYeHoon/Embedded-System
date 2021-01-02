#include <linux/build-salt.h>
#include <linux/module.h>
#include <linux/vermagic.h>
#include <linux/compiler.h>

BUILD_SALT;

MODULE_INFO(vermagic, VERMAGIC_STRING);
MODULE_INFO(name, KBUILD_MODNAME);

__visible struct module __this_module
__attribute__((section(".gnu.linkonce.this_module"))) = {
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
__used
__attribute__((section("__versions"))) = {
	{ 0x865cd05, "module_layout" },
	{ 0x6bc3fbc0, "__unregister_chrdev" },
	{ 0x795fc53d, "__register_chrdev" },
	{ 0xdb7305a1, "__stack_chk_fail" },
	{ 0xf4fa543b, "arm_copy_to_user" },
	{ 0x8f678b07, "__stack_chk_guard" },
	{ 0x61516f5a, "wake_up_process" },
	{ 0x88d313af, "kthread_create_on_node" },
	{ 0xd6b8e852, "request_threaded_irq" },
	{ 0x4a221ce3, "gpiod_to_irq" },
	{ 0x47229b5c, "gpio_request" },
	{ 0xf9a482f9, "msleep" },
	{ 0xeb7100a7, "gpiod_direction_output_raw" },
	{ 0x841fd500, "gpiod_get_raw_value" },
	{ 0x680cd131, "gpio_to_desc" },
	{ 0xb3f7646e, "kthread_should_stop" },
	{ 0x2e5810c6, "__aeabi_unwind_cpp_pr1" },
	{ 0xfe990052, "gpio_free" },
	{ 0x1a374094, "kthread_stop" },
	{ 0x7c32d0f0, "printk" },
	{ 0xb1ad28e0, "__gnu_mcount_nc" },
};

static const char __module_depends[]
__used
__attribute__((section(".modinfo"))) =
"depends=";


MODULE_INFO(srcversion, "91C31A5EE00ADB52A21A6C4");