#include <linux/init.h>
#include <linux/module.h>
#include <linux/kernel.h>
#include <linux/delay.h>
#include <linux/gpio.h>
#include <linux/kthread.h>

#define HIGH	1
#define LOW		0

int led[4] = {23, 24, 25, 1};
struct task_struct *thread_id = NULL;

static int kthread_function(void *arg){
 char value = 1, temp = 0;
 int ret, i;
 printk(KERN_INFO "kthread_function ! \n");
 while(!kthread_should_stop()){
  temp = value;
  for(i = 0; i < 4; i++){
   if(temp&0x01)
	ret = gpio_direction_output(led[i], HIGH);
   else
	ret = gpio_direction_output(led[i], LOW);
   temp = temp >> 1;
  }
  value = value << 1;
  if(value == 0x10)
   value = 0x01;
  ssleep(1);
 }
 printk(KERN_INFO "kthread_should_stop call !\n");
 return 0;
}

static int led_kthread_init(void){
 int ret, i;
 printk(KERN_INFO "led_kthread_init!\n");
 for(i = 0; i < 4; i++){
  ret = gpio_request(led[i], "LED");
  if(ret < 0)
   printk(KERN_INFO "gpio_request failed!\n");
 }
 if(thread_id == NULL)
  thread_id = (struct task_struct *)kthread_run(kthread_function, NULL, "led_thread");
 return 0;
}

static void led_kthread_exit(void){
 int i;
 if (thread_id){
  kthread_stop(thread_id);
  thread_id = NULL;
 }
 for(i = 0; i < 4;i++)
  gpio_free(led[i]);
 printk(KERN_INFO "led_kthread_exit!\n");
}

module_init(led_kthread_init);
module_exit(led_kthread_exit);
MODULE_LICENSE("GPL");
