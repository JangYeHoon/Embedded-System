#include <linux/init.h>
#include <linux/module.h>
#include <linux/kernel.h>
#include <linux/kthread.h>
#include <linux/delay.h>
#include <linux/kfifo.h>

struct kfifo fifo;
struct task_struct * thread_id = NULL;

static int kthread_function(void *arg){
	int i = 0;
	int ret;
	unsigned int val;
	printk(KERN_INFO "kthread_function!\n");
	while(!kthread_should_stop()){
		if(!kfifo_is_full(&fifo))
			kfifo_in(&fifo, &i, sizeof(i));
		++i;
		ssleep(4);
	}
	printk(KERN_INFO "kthread_should_stop call!\n");
	while(!kfifo_is_empty(&fifo)){
		ret = kfifo_out(&fifo, &val, sizeof(val));
		printk(KERN_INFO "kthread : %u\n", val);
	}
	return 0;
}

static int kthread_exam_init(void){
	int ret;
	printk(KERN_INFO "init\n");
	ret = kfifo_alloc(&fifo, 50, GFP_KERNEL);
	if (ret)
		printk(KERN_ERR "error kfifo_alloc!\n");
	if(thread_id == NULL)
		thread_id = (struct task_struct *)kthread_run(kthread_function,NULL,"kernel_thread_exam");
	return 0;
}

static void kthread_exam_exit(void){
	if(thread_id){
		kthread_stop(thread_id);
		thread_id = NULL;
	}
	kfifo_free(&fifo);
	printk(KERN_INFO "exit!\n");
}

module_init(kthread_exam_init);
module_exit(kthread_exam_exit);
MODULE_LICENSE("GPL");
