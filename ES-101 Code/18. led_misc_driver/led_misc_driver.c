#include <linux/module.h>
#include <linux/kernel.h>
#include <linux/init.h>
#include <linux/fs.h>
#include <linux/miscdevice.h>
#include <linux/gpio.h>
#include <linux/uaccess.h>

int led[4] = {23,24,25,1};

static ssize_t led_misc_driver_write(struct file * file, const char * buf, size_t length, loff_t * ofs){
 int ret,i;
 unsigned char cbuf[4];
 printk(KERN_INFO "led_driver_write!\n");
 ret = copy_from_user(cbuf, buf, length);
 for(i=0;i<4;i++)
  gpio_direction_output(led[i],cbuf[i]);
 return 0;
}

static int led_misc_driver_open(struct inode * inode, struct file * file){
 int ret, i;
 printk(KERN_INFO "led_misc_driver_open!\n");
 for(i=0;i<4;i++){
  ret = gpio_request(led[i], "LED");
  if(ret<0)
   printk(KERN_INFO "led driver gpio request failed!\n");
 }
 return 0;
}

static int led_misc_driver_release(struct inode * inode, struct file * file){
 int i;
 printk(KERN_INFO "led_misc_driver_release!\n");
 for(i=0;i<4;i++)
  gpio_free(led[i]);
 return 0;
}

static struct file_operations led_misc_driver_fops = {
 .owner = THIS_MODULE,
 .open = led_misc_driver_open,
 .release = led_misc_driver_release,
 .write = led_misc_driver_write,
};

static struct miscdevice led_misc_driver_driver = {
 .minor = MISC_DYNAMIC_MINOR,
 .name = "led_misc_driver",
 .fops = &led_misc_driver_fops,
};

static int led_misc_driver_init(void){
 printk(KERN_INFO "led_misc_driver_init!\n");
 return misc_register(&led_misc_driver_driver);
}

static void led_misc_driver_exit(void){
 printk(KERN_INFO "led_misc_driver_exit!\n");
 misc_deregister(&led_misc_driver_driver);
}

module_init(led_misc_driver_init);
module_exit(led_misc_driver_exit);
MODULE_LICENSE("GPL");
