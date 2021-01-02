#include <linux/init.h>
#include <linux/module.h>
#include <linux/kernel.h>
#include <linux/timer.h>

static struct timer_list timer;
static int count = 1;

static void timer_cb(struct timer_list *timer){
	printk(KERN_INFO "timer : %d\n", count);
	timer->expires = jiffies + HZ * 4;
	add_timer(timer);
	count += 1;
}

static int timer_module_init(void){
	printk(KERN_INFO "init!\n");
	timer_setup(&timer,timer_cb,0);
	timer.expires = jiffies + HZ * 4;
	add_timer(&timer);
	return 0;
}

static void timer_module_exit(void){
	printk(KERN_INFO "exit!\n");
	del_timer(&timer);
}

module_init(timer_module_init);
module_exit(timer_module_exit);
MODULE_LICENSE("GPL");
