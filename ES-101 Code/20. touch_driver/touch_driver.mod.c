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
	{ 0xa01d7bfa, "i2c_del_driver" },
	{ 0x85bb297f, "i2c_register_driver" },
	{ 0x37a0cba, "kfree" },
	{ 0xd8312179, "_dev_err" },
	{ 0x43ed0435, "misc_register" },
	{ 0xfbd8da33, "kmem_cache_alloc_trace" },
	{ 0xa66ba2dc, "kmalloc_caches" },
	{ 0xdb7305a1, "__stack_chk_fail" },
	{ 0xfa2becde, "i2c_transfer" },
	{ 0x8f678b07, "__stack_chk_guard" },
	{ 0x5d67afc3, "misc_deregister" },
	{ 0x2e5810c6, "__aeabi_unwind_cpp_pr1" },
	{ 0x7c32d0f0, "printk" },
	{ 0xb1ad28e0, "__gnu_mcount_nc" },
};

static const char __module_depends[]
__used
__attribute__((section(".modinfo"))) =
"depends=";

MODULE_ALIAS("i2c:touch");

MODULE_INFO(srcversion, "47D8793ADECC687ECB41C5B");
