#include <linux/init.h>
#include <linux/module.h>
#include <linux/kernel.h>
#include <linux/fs.h>

#define DEV_MAJOR_NUMBER 220
#define DEV_NAME "driver_exam"

static int driver_exam_write(struct file * file, const char * buf, size_t length, loff_t * ofs) {
 printk(KERN_INFO "driver_exam_write!\n");
 return 0;
}

static ssize_t driver_exam_read(struct file * file, char * buf, size_t length, loff_t * ofs) {
 printk(KERN_INFO "driver_exam_read!\n");
 return 0;
}

static int driver_exam_open(struct inode * inode, struct file * file) {
 printk(KERN_INFO "driver_exam_open!\n");
 return 0;
}

static int driver_exam_release(struct inode * inode, struct file * file) {
 printk(KERN_INFO "driver_exam_release!\n");
 return 0;
}

static struct file_operations driver_exam_fops = {
 .owner = THIS_MODULE,
 .open = driver_exam_open,
 .release = driver_exam_release,
 .write = driver_exam_write,
 .read = driver_exam_read,
};

static int driver_exam_init(void) {
 printk(KERN_INFO "driver_exam_init!\n");
 register_chrdev(DEV_MAJOR_NUMBER, DEV_NAME, &driver_exam_fops);
 return 0;
}

static void driver_exam_exit(void) {
 printk(KERN_INFO "driver_exam_exit\n");
 unregister_chrdev(DEV_MAJOR_NUMBER, DEV_NAME);
}

module_init(driver_exam_init);
module_exit(driver_exam_exit);
MODULE_LICENSE("GPL");
