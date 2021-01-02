#include <linux/module.h>
#include <linux/kernel.h>
#include <linux/init.h>
#include <linux/fs.h>
#include <linux/miscdevice.h>
#include <linux/gpio.h>
#include <linux/uaccess.h>

#define LED_BASE 0x56
#define ALL_LED_ON _IO(LED_BASE, 0x31)
#define ALL_LED_OFF _IO(LED_BASE, 0x32)
#define LED_1_ON _IO(LED_BASE,0x33)
#define LED_1_OFF _IO(LED_BASE,0x34)
#define LED_2_ON _IO(LED_BASE,0x35)
#define LED_2_OFF _IO(LED_BASE,0x36)
#define LED_3_ON _IO(LED_BASE,0x37)
#define LED_3_OFF _IO(LED_BASE,0x38)
#define LED_4_ON _IO(LED_BASE,0x39)
#define LED_4_OFF _IO(LED_BASE,0x3a)

int led[4] = {23,24,25,1};
unsigned char cbuf[4]={0,0,0,0};

static long led_misc_driver_2_ioctl(struct file * file, unsigned int cmd, unsigned long arg){
 int i;
 printk(KERN_INFO "led_misc_Driver_2_ioctl!\n");
 switch(cmd){
 case ALL_LED_ON:
  memset(cbuf, 1, sizeof(cbuf));
  break;
 case ALL_LED_OFF:
  memset(cbuf,0,sizeof(cbuf));
  break;
 case LED_1_ON:
  cbuf[0]=1;
  break;
 case LED_1_OFF:
  cbuf[0]=0;
  break;
 case LED_2_ON:
  cbuf[1]=1;
  break;
 case LED_2_OFF:
  cbuf[1]=0;
  break;
 case LED_3_ON:
  cbuf[2]=1;
  break;
 case LED_3_OFF:
  cbuf[2]=0;
  break;
 case LED_4_ON:
  cbuf[3]=1;
  break;
 case LED_4_OFF:
  cbuf[3]=0;
  break;
 }
 for(i=0;i<4;i++)
  gpio_direction_output(led[i], cbuf[i]);
 return 0;
}

static int led_misc_driver_2_open(struct inode * inode, struct file * file){
 int ret, i;
 printk(KERN_INFO "led-Misc_Driver_2_open!\n");
 for(i=0;i<4;i++){
  ret = gpio_request(led[i], "LED");
  if(ret<0)
   printk(KERN_INFO "led driver gpio request failed!\n");
 }
 return 0;
}

static int led_misc_driver_2_release(struct inode * inode, struct file * file){
 int i;
 printk(KERN_INFO "led_misc_driver_2_release");
 for(i=0;i<4;i++)
  gpio_free(led[i]);
 return 0;
}

static struct file_operations led_misc_driver_2_fops = {
 .owner = THIS_MODULE,
 .open = led_misc_driver_2_open,
 .release = led_misc_driver_2_release,
 .unlocked_ioctl = led_misc_driver_2_ioctl,
};

static struct miscdevice led_misc_driver_2_driver = {
 .minor = MISC_DYNAMIC_MINOR,
 .name = "led_misc_driver_2",
 .fops = &led_misc_driver_2_fops,
};

static int led_misc_driver_2_init(void){
 printk(KERN_INFO "led_Misc_dirver_2_init!\n");
 return misc_register(&led_misc_driver_2_driver);
}

static void led_misc_driver_2_exit(void){
 printk(KERN_INFO "led_misc_driver_2_exit!\n");
 misc_deregister(&led_misc_driver_2_driver);
}

module_init(led_misc_driver_2_init);
module_exit(led_misc_driver_2_exit);
MODULE_LICENSE("GPL");
