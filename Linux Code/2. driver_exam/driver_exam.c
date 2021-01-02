#include <linux/init.h>
#include <linux/module.h>
#include <linux/kernel.h>
#include <linux/fs.h>

#define DEV_MAJOR_NUMBER 225
#define DEV_NAME "driver_exam"

static ssize_t driver_exam_write(struct file * file, const char * buf, size_t length, loff_t * ofs){
	printk(KERN_INFO "write!\n");
	return 0;
}

static ssize_t driver_exam_read(struct file * file, char * buf, size_t length, loff_t * ofs){
	printk(KERN_INFO "read!\n");
	return 0;
}

static int driver_exam_open(struct inode * inode, struct file * file){
	printk(KERN_INFO "open!\n");
	return 0;
}

static int driver_exam_release(struct inode * inode, struct file * file){
	printk(KERN_INFO "release!\n");
	return 0;
}

static long driver_exam_ioctl(struct file * file, unsigned int cmd, unsigned long arg){
	printk(KERN_INFO "ioctl!\n");
	return 0;
}

static struct file_operations driver_exam_fops = {
	.owner = THIS_MODULE,
	.write = driver_exam_write,
	.read = driver_exam_read,
	.open = driver_exam_open,
	.release = driver_exam_release,
	.unlocked_ioctl = driver_exam_ioctl
};

static int driver_exam_init(void){
	printk(KERN_INFO "20191101096_init!\n");
	register_chrdev(DEV_MAJOR_NUMBER,DEV_NAME,&driver_exam_fops);
	return 0;
}

static void driver_exam_exit(void){
	printk(KERN_INFO "20191101096_exit!\n");
	unregister_chrdev(DEV_MAJOR_NUMBER,DEV_NAME);
}

module_init(driver_exam_init);
module_exit(driver_exam_exit);
MODULE_LICENSE("GPL");
