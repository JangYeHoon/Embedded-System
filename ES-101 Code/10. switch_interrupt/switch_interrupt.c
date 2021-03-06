#include <linux/init.h>
#include <linux/module.h>
#include <linux/kernel.h>
#include <linux/interrupt.h>
#include <linux/delay.h>
#include <linux/gpio.h>

int sw[4] = {4, 17, 27, 22};
int led[4] = {23,24,25,1};

irqreturn_t irq_handler(int irq, void *dev_id){
 int condition = 0;
 int i;
 switch(irq){
  case 60:
   //printk(KERN_INFO "sw1 interrupt ouccerd!\n");
   condition = 0;
   break;
  case 61:
   //printk(KERN_INFO "sw2 interrupt ouccerd!\n");
   condition = 1;
   break;
  case 62:
   //printk(KERN_INFO "sw3 interrupt ouccerd!\n");
   condition = 2;
   break;
  case 63:
   //printk(KERN_INFO "sw4 interrupt ouccerd!\n");
   condition = 3;
   break;
 }
 for (i=0; i<4; i++)
 {
  if (i == condition)
   gpio_direction_output(led[i], 1);
  else
   gpio_direction_output(led[i], 0);
 }
 return 0;
}

static int switch_interrupt_init(void){
 int res, i;
 printk(KERN_INFO "switch_interrupt_init!\n");
 for (i = 0; i < 4; i++){
  res = gpio_request(sw[i], "sw");
  res = gpio_request(led[i], "LED");
  res = request_irq(gpio_to_irq(sw[i]), (irq_handler_t)irq_handler, IRQF_TRIGGER_RISING, "IRQ", (void *)(irq_handler));
  if(res < 0)
   printk(KERN_INFO "request_irq failed!\n");
 }
 return 0;
}

static void switch_interrupt_exit(void){
 int i;
 printk(KERN_INFO "switch_interrupt_exit!\n");
 for(i = 0; i < 4; i++){
  free_irq(gpio_to_irq(sw[i]), (void *)(irq_handler));
  gpio_free(sw[i]);
 }
}

module_init(switch_interrupt_init);
module_exit(switch_interrupt_exit);
MODULE_LICENSE("GPL");
