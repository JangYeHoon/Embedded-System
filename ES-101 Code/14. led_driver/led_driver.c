#include <linux/init.h>
#include <linux/module.h>
#include <linux/kernel.h>
#include <linux/fs.h>
#include <linux/gpio.h>
#include <linux/uaccess.h>

#define DEV_MAJOR_NUMBER 221
#define DEV_NAME "led_driver"

int led[4] = {23, 24, 25, 1};

static int led_driver_write(struct file * file, const char * buf, size_t length, loff_t * ofs){
 int ret, i;
 unsigned char cbuf[4];
 printk(KERN_INFO "led_driver_write!\n");
 ret = copy_from_user(cbuf, buf, length);
 for(i=0;i<4;i++)
  gpio_direction_output(led[i], cbuf[i]);
 return 0;
}

static int led_driver_open(struct inode * inode, struct file * file){
 int ret, i;
 printk(KERN_INFO "led_driver_open!\n");
 for(i=0; i<4; i++){
  ret = gpio_request(led[i], "LED");
  if(ret<0)
   printk(KERN_INFO "led driver gpio request failed!\n");
 }
 return 0;
}

static int led_driver_release(struct inode * inode, struct file * file){
 int i;
 printk(KERN_INFO "led_driver_release!\n");
 for(i=0;i<4;i++)
  gpio_free(led[i]);
 return 0;
}

static struct file_operations led_driver_fops = {
 .owner = THIS_MODULE,
 .open = led_driver_open,
 .release = led_driver_release,
 .write = led_driver_write,
};

static int led_driver_init(void){
 printk(KERN_INFO "led_driver_init!\n");
 register_chrdev(DEV_MAJOR_NUMBER, DEV_NAME, &led_driver_fops);
 return 0;
}

static void led_driver_exit(void){
 printk(KERN_INFO "led_driver_exit!\n");
 unregister_chrdev(DEV_MAJOR_NUMBER, DEV_NAME);
}

module_init(led_driver_init);
module_exit(led_driver_exit);
MODULE_LICENSE("GPL");
