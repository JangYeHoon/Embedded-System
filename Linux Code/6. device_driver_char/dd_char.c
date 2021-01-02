#include <linux/init.h>
#include <linux/module.h>
#include <linux/kernel.h>
#include <linux/fs.h>
#include <linux/slab.h>
#include <linux/uaccess.h>
#include <linux/random.h>

#define DEV_MAJOR_NUMBER 225
#define DEV_NAME "dd_char"
#define BUF_SIZE 20

#define CALC_BASE 0x06
#define CNT _IO(CALC_BASE, 0x01)

ssize_t cur_len;
char * char_buf;
int result;

static ssize_t dd_write(struct file * filep, const char * buf, size_t length, loff_t * ofs){
	int ret;
	cur_len = length;
	ret = copy_from_user(char_buf, buf, length);
	printk(KERN_INFO "write_buf : %s\n", char_buf);
	return 0;
}

static ssize_t dd_read(struct file * filep, char * buf, size_t length, loff_t * ofs){
	int ret;
	printk(KERN_INFO "result : %d\n", result);
	ret = copy_to_user(buf, &result, sizeof(result));
	if(ret<0)
		printk(KERN_INFO "copy to user failed!\n");
	return 0;
}

static long dd_ioctl(struct file * file, unsigned int cmd, unsigned long arg){
	int i;
	switch(cmd){
		case CNT:
			printk(KERN_INFO "CNT\n");
			for(i=0;i<cur_len;i++){
				if(('a' <= char_buf[i] && char_buf[i] <= 'z') || ('A' <= char_buf[i] && char_buf[i] <= 'Z'))
					result += 1;
			}
			break;
	}
	return 0;
}

static int dd_open(struct inode * inode, struct file * file){
	printk("Character Device Open\n");
	char_buf = kmalloc(BUF_SIZE, GFP_KERNEL);
	if(!char_buf){
		printk("error allocating\n");
		return -ENOMEM;
	}
	memset(char_buf, 0, BUF_SIZE);
	return 0;
}

static int dd_release(struct inode * inode, struct file * file){
	printk("Character Device Release\n");
	return 0;
}

static struct file_operations dd_test_fops = {
	.owner = THIS_MODULE,
	.open = dd_open,
	.release = dd_release,
	.write = dd_write,
	.read = dd_read,
	.unlocked_ioctl = dd_ioctl
};

static int dd_test_init(void){
	printk(KERN_INFO "init!\n");
	register_chrdev(DEV_MAJOR_NUMBER, DEV_NAME, &dd_test_fops);
	return 0;
}

static void dd_test_exit(void){
	printk(KERN_INFO "exit!\n");
	unregister_chrdev(DEV_MAJOR_NUMBER, DEV_NAME);
}

module_init(dd_test_init);
module_exit(dd_test_exit);
MODULE_LICENSE("GPL");
