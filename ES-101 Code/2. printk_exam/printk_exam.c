#include <linux/init.h>
#include <linux/module.h>
#include <linux/kernel.h>
#include <linux/delay.h>
#include <linux/kthread.h>

static int printk_exam_init(void)
{
 printk("default message....\n");
 printk(KERN_INFO "info message...\n");
 printk(KERN_ALERT "alert message....\n");
 return 0;
}

static void printk_exam_exit(void) {
 printk(KERN_INFO "module_exit!\n");
}

module_init(printk_exam_init);
module_exit(printk_exam_exit);
MODULE_LICENSE("GPL");
