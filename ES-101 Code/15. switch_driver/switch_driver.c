#include <linux/init.h>
#include <linux/module.h>
#include <linux/kernel.h>
#include <linux/fs.h>
#include <linux/uaccess.h>
#include <linux/gpio.h>
#include <linux/interrupt.h>
#include <linux/kthread.h>
#include <linux/delay.h>

#define DEV_MAJOR_NUMBER 222
#define DEV_NAME "switch_driver"

int sw[4] = {4, 17, 27, 22};
int led[4] = {23,24,25,1};

struct task_struct *thread_id = NULL;

static int kthread_function(void *arg){
    int i;
    char read_buf[4];
    while(!kthread_should_stop()){
        for (i=0; i<4; i++){
            read_buf[i] = gpio_get_value(sw[i]);
            gpio_direction_output(led[i], read_buf[i]);
        }
        msleep(100);
    }
    return 0;
}

irqreturn_t irq_handler(int irq,void *dev_id){
	switch(irq){
		case 60:
            gpio_direction_output(led[0], 1);
			break;
		case 61:
            gpio_direction_output(led[1], 1);
			break;
		case 62:
            gpio_direction_output(led[2], 1);
			break;
		case 63:
            gpio_direction_output(led[3], 1);
			break;
	}
	return 0;
}

static ssize_t switch_driver_read(struct file * file, char * buf, size_t length, loff_t * ofs){
 int ret, i;
 char read_buf[4];
 printk(KERN_INFO "switch_driver_read!\n");
 for(i = 0; i < 4; i++)
 {
  read_buf[i] = gpio_get_value(sw[i]);
  gpio_direction_output(led[i], read_buf[i]);
 }
 ret = copy_to_user(buf, read_buf, sizeof(read_buf));
 if(ret<0)
  printk(KERN_INFO "switch driver copy to user failed!\n");
 return 0;
}

static int switch_driver_open(struct inode * inode, struct file * file){
 int ret, i;
 printk(KERN_INFO "switch_driver_open!\n");
 for(i=0;i<4;i++){
  ret = gpio_request(sw[i],"sw");
  ret = request_irq(gpio_to_irq(sw[i]),(irq_handler_t)irq_handler,IRQF_TRIGGER_RISING,"IRQ",(void *)(irq_handler));
  if(ret<0)
   printk(KERN_INFO "switch driver gpio_request failed!\n");
  ret = gpio_request(led[i], "LED");
  if(ret<0)
   printk(KERN_INFO "led driver gpio_request failed!\n");
 }
 if(thread_id == NULL)
 thread_id = (struct task_struct *)kthread_run(kthread_function,NULL,"led_thread");
 return 0;
}

static int switch_driver_release(struct inode * inode, struct file * file){
 int i;
 printk(KERN_INFO "switch_driver_release!\n");
 if(thread_id){
     kthread_stop(thread_id);
     thread_id = NULL;
 }
 for(i=0;i<4;i++){
  gpio_free(sw[i]);
  gpio_direction_output(led[i], 0);
  gpio_free(led[i]);
 }
 return 0;
}

static struct file_operations switch_driver_fops = {
 .owner = THIS_MODULE,
 .open = switch_driver_open,
 .release = switch_driver_release,
 .read = switch_driver_read,
};

static int switch_driver_init(void){
 printk(KERN_INFO "switch_driver_init!\n");
 register_chrdev(DEV_MAJOR_NUMBER, DEV_NAME, &switch_driver_fops);
 return 0;
}

static void switch_driver_exit(void){
 printk(KERN_INFO "switch_driver_exit!\n");
 unregister_chrdev(DEV_MAJOR_NUMBER, DEV_NAME);
}

module_init(switch_driver_init);
module_exit(switch_driver_exit);
MODULE_LICENSE("GPL");
