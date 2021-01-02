#include <linux/module.h>
#include <linux/kernel.h>
#include <linux/init.h>
#include <linux/fs.h>
#include <linux/miscdevice.h>
#include <linux/mutex.h>

static int misc_driver_open(struct inode * inode, struct file * file){
 printk("misc_driver_open, \n");
 return 0;
}

static int misc_driver_release(struct inode * inode, struct file * file){
 printk("misc_driver_release, \n");
 return 0;
}

static ssize_t misc_driver_read(struct file * file, char * buf, size_t length, loff_t * ofs){
 printk("misc_driver_read, \n");
 return 0;
}

static ssize_t misc_driver_write(struct file * file, const char * buf, size_t length, loff_t * ofs){
 printk("misc_driver_write, \n");
 return 0;
}

static DEFINE_MUTEX(misc_driver_mutex);
static long misc_driver_ioctl(struct file * file, unsigned int cmd, unsigned long arg){
 printk("misc_driver_ioctl, \n");
 switch(cmd){
 default:
  mutex_unlock(&misc_driver_mutex);
  return ENOTTY;
 }
 mutex_unlock(&misc_driver_mutex);
 return 0;
}

static struct file_operations misc_driver_fops = {
 .owner = THIS_MODULE,
 .open = misc_driver_open,
 .release = misc_driver_release,
 .read = misc_driver_read,
 .write = misc_driver_write,
 .unlocked_ioctl = misc_driver_ioctl,
};

static struct miscdevice misc_driver_driver = {
 .minor = MISC_DYNAMIC_MINOR,
 .name = "misc_driver",
 .fops = &misc_driver_fops,
};

static int misc_driver_init(void){
 printk("misc_Driverinit, \n");
 return misc_register(&misc_driver_driver);
}

static void misc_driver_exit(void){
 printk("misc_driver_exit, \n");
 misc_deregister(&misc_driver_driver);
}

module_init(misc_driver_init);
module_exit(misc_driver_exit);
MODULE_LICENSE("GPL");
