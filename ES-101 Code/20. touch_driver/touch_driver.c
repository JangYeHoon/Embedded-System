#include <linux/input.h>
#include <linux/types.h>
#include <linux/i2c.h>
#include <linux/i2c-dev.h>
#include <linux/module.h>
#include <linux/kernel.h>
#include <linux/init.h>
#include <linux/miscdevice.h>
#include <linux/slab.h>
#include <linux/fs.h>
#include <linux/errno.h>

#define TOUCH_CHIP_ADREESS 0x1b
#define TOUCH_READ_REG 0x03

struct touch_sensor {
	struct i2c_client *client;
	struct device *dev;
};

static struct touch_sensor *touch_ptr;

static int touch_open(struct inode * inode, struct file * file){
	printk(KERN_INFO "touch_open, \n");
	return 0;
}

static int touch_release(struct inode * inode, struct file * file){
	printk(KERN_INFO "touch_release, \n");
	return 0;
}

static long touch_ioctl(struct file *file,unsigned int cmd, long unsigned int cData){
	char buffer=0,reg;
	int ret;
	struct i2c_msg msg[] = {
		{
			.addr = TOUCH_CHIP_ADREESS,
			.flags = 0,
			.len = 1,
			.buf = &reg,
		},
		{
			.addr = TOUCH_CHIP_ADREESS,
			.flags = I2C_M_RD,
			.len = 1,
			.buf = &buffer,
		},
	};
	printk(KERN_INFO "touch_ioctl\n");
	reg = TOUCH_READ_REG;	
	ret  = i2c_transfer(touch_ptr->client->adapter, msg, 2);
	return buffer;
}

static struct file_operations touch_fops = {
	.owner			= THIS_MODULE,
	.open			= touch_open,
	.unlocked_ioctl	= touch_ioctl,
	.release		= touch_release,
};

static struct miscdevice touch_driver = {
	.fops	= &touch_fops,
	.name	= "touch",
	.minor	= MISC_DYNAMIC_MINOR,
};

static int touch_probe(struct i2c_client *client, const struct i2c_device_id *id)
{
	struct touch_sensor *sensor;
	int error;
	printk(KERN_INFO "touch_probe, \n");
	sensor = kzalloc(sizeof(struct touch_sensor), GFP_KERNEL);

	if(!i2c_check_functionality(client->adapter, I2C_FUNC_I2C))
	{
		error = -ENODEV;
		goto err_free_mem;
	}
	sensor->client = client;
	sensor->dev = &client->dev;

	i2c_set_clientdata(client,sensor);
	touch_ptr = sensor;

	error = misc_register(&touch_driver);
	if (error) {
		dev_err(&client->dev, "failed to register input device\n");
		goto err_mpuirq_failed;
	}
	return 0;

err_mpuirq_failed:
	misc_deregister(&touch_driver);

err_free_mem:
	kfree(sensor);

	return error;
}

static int touch_remove(struct i2c_client *client){
	printk(KERN_INFO "touch_remove, \n");
	misc_deregister(&touch_driver);
	return 0;
}

static const struct i2c_device_id touch_ids[] = {
	{ "touch", 0 },
	{ }
};
MODULE_DEVICE_TABLE(i2c, touch_ids);

static struct i2c_driver touch_i2c_driver = {
	.driver = {
		.name   = "touch",
		.owner  = THIS_MODULE,
	},
	.probe          = touch_probe,
	.remove         = touch_remove,
	.id_table       = touch_ids,
};

static int touch_init(void){
	printk(KERN_INFO "touch_init, \n");
	return i2c_add_driver(&touch_i2c_driver);
}

static void touch_exit(void){
	printk(KERN_INFO "touch_exit, \n");
	i2c_del_driver(&touch_i2c_driver);
}

module_init(touch_init);
module_exit(touch_exit);

MODULE_LICENSE("GPL");