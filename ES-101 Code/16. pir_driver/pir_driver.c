#include <linux/init.h>
#include <linux/module.h>
#include <linux/kernel.h>
#include <linux/fs.h>
#include <linux/uaccess.h>
#include <linux/gpio.h>
#include <linux/interrupt.h>

#define DEV_MAJOR_NUMBER 223
#define DEV_NAME "pir_driver"
#define PIR_GPIO 7

static DECLARE_WAIT_QUEUE_HEAD(wait_queue);
int irq_num=0;
int condition = 0;

irqreturn_t irq_handler(int irq, void *dev_id){
 irq_num = irq;
 condition = 1;
 wake_up_interruptible(&wait_queue);
 return IRQ_HANDLED;
}

static ssize_t pir_driver_read(struct file * file, char * buf, size_t length, loff_t * ofs){
 int ret;
 char msg[100];
 printk(KERN_INFO "pir_driver_read!\n");
 ret = wait_event_interruptible(wait_queue, condition != 0);
 condition = 0;
 if(irq_num == gpio_to_irq(PIR_GPIO))
  sprintf(msg, "PIR Detect");
 else
  sprintf(msg, "PIR Not Detect");
 ret = copy_to_user(buf, msg, sizeof(msg));
 irq_num = 0;
 if(ret<0)
  printk(KERN_INFO "pir dirver copy to user failed!\n");
 return 0;
}

static int pir_driver_open(struct inode * inode, struct file * file){
 int ret;
 printk(KERN_INFO "pir_dirver_open!\n");
 ret = gpio_request(PIR_GPIO, "pir");
 if(ret<0)
  printk(KERN_INFO "pir driver gpio_request failed!\n");
 ret = request_irq(gpio_to_irq(PIR_GPIO), (irq_handler_t)irq_handler,IRQF_TRIGGER_FALLING, "IRQ", (void *)(irq_handler));
 if(ret<0)
  printk(KERN_INFO "pir driver request_irq failed!\n");
 return 0;
}
static int pir_driver_release(struct inode * inode, struct file * file){
 printk(KERN_INFO "pir_driver_release!\n");
 free_irq(gpio_to_irq(PIR_GPIO), (void *)(irq_handler));
 gpio_free(PIR_GPIO);
 return 0;
}

static struct file_operations pir_driver_fops = {
 .owner = THIS_MODULE,
 .open = pir_driver_open,
 .release = pir_driver_release,
 .read = pir_driver_read,
};

static int pir_driver_init(void){
 printk(KERN_INFO "pir_driver_init\n");
 register_chrdev(DEV_MAJOR_NUMBER, DEV_NAME, &pir_driver_fops);
 return 0;
}

static void pir_driver_exit(void){
 printk(KERN_INFO "pir_driver_exit!\n");
 unregister_chrdev(DEV_MAJOR_NUMBER, DEV_NAME);
}

module_init(pir_driver_init);
module_exit(pir_driver_exit);
MODULE_LICENSE("GPL");
