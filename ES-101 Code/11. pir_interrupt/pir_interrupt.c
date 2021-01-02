#include <linux/init.h>
#include <linux/module.h>
#include <linux/kernel.h>
#include <linux/interrupt.h>
#include <linux/delay.h>
#include <linux/gpio.h>

#define GPIO 7

irqreturn_t irq_handler(int irq, void *dev_id) {
 printk(KERN_INFO "interrupt occured!\n");
 return 0;
}

static int pir_interrupt_init(void){
 int res;
 printk(KERN_INFO "pir_interrupt_init!\n");
 res = gpio_request(GPIO, "gpio");
 res = request_irq(gpio_to_irq(GPIO), (irq_handler_t)irq_handler, IRQF_TRIGGER_FALLING, "IRQ", (void *)(irq_handler));
 if(res<0)
  printk(KERN_INFO "request_irq failed!\n");
 return 0;
}

static void pir_interrupt_exit(void){
 printk(KERN_INFO "pir_interrupt_exit!\n");
 free_irq(gpio_to_irq(GPIO), (void *)(irq_handler));
 gpio_free(GPIO);
}

module_init(pir_interrupt_init);
module_exit(pir_interrupt_exit);
MODULE_LICENSE("GPL");
