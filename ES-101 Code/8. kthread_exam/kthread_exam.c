#include <linux/init.h>
#include <linux/module.h>
#include <linux/kernel.h>
#include <linux/kthread.h>
#include <linux/delay.h>

struct task_struct *thread_id = NULL;

static int kthread_function(void *arg){
 printk(KERN_INFO "kthread_function ! \n");
 while(!kthread_should_stop()){
  printk(KERN_INFO "running kerel thread..\n");
  ssleep(1);
 }
 printk(KERN_INFO "kthread_should_stop call ! \n");
 return 0;
}

static int kthread_exam_init(void){
 printk(KERN_INFO "kthread_exam_init!\n");
 if(thread_id == NULL)
  thread_id = (struct task_struct *)kthread_run(kthread_function, NULL, "kernel_thread_exam");
 return 0;
}

static void kthread_exam_exit(void){
 if(thread_id){
  kthread_stop(thread_id);
  thread_id = NULL;
 }
 printk(KERN_INFO "kthread_exam_exit!\n");
}

module_init(kthread_exam_init);
module_exit(kthread_exam_exit);
MODULE_LICENSE("GPL");
