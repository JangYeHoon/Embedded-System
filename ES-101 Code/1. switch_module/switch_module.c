#include <linux/init.h>
#include <linux/module.h>
#include <linux/kernel.h>
#include <linux/gpio.h>

int sw[4] = {4,17,27,22};

static int switch_module_init(void) {
    int ret,i,val;
    printk(KERN_INFO "switch_module_init!\n");
    for (i = 0; i < 4; i++) {
        ret = gpio_request(sw[i], "sw");
        if(ret < 0)
            printk(KERN_INFO "sw_module gpio_request failed!\n");
        else
            ret = gpio_direction_input(sw[i]);
    }
    for (i = 0; i < 4; i++) {
        val = gpio_get_value(sw[i]);
        printk(KERN_ALERT "sw %d value = %d\n", i, val);
    }
    return 0;
}

static void switch_module_exit(void) {
    int i;
    printk(KERN_INFO "switch_module_exit!\n");
    for (i = 0; i < 4; i++)
        gpio_free(sw[i]);
}

module_init(switch_module_init);
module_exit(switch_module_exit);
MODULE_LICENSE("GPL");
