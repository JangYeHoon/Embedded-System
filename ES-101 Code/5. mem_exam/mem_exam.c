#include <linux/init.h>
#include <linux/module.h>
#include <linux/kernel.h>
#include <linux/slab.h>
#include <linux/vmalloc.h>

void kmem_test(void){
 char *buf;
 printk(KERN_INFO "kmalloc!\n");
 buf = kmalloc(1024, GFP_KERNEL);
 if (buf != NULL){
  sprintf(buf, "mem test!\n");
  printk(KERN_INFO "%s", buf);
  kfree(buf);
 }
 buf = kmalloc(32*PAGE_SIZE, GFP_KERNEL);
 if (buf != NULL){
  sprintf(buf, "mem test 2!\n");
  printk(KERN_INFO "%s", buf);
  kfree(buf);
 }
}

void vmem_test(void) {
 char *buf;
 printk(KERN_INFO "vmalloc!\n");
 buf = vmalloc(64*PAGE_SIZE);
 if (buf != NULL){
  sprintf(buf, "vmem test!\n");
  printk(KERN_INFO "%s", buf);
  vfree(buf);
 }
}

static int mem_exam_init(void) {
 printk(KERN_INFO "mem_exam_init!\n");
 kmem_test();
 vmem_test();
 return 0;
}

static void mem_exam_exit(void){
 printk(KERN_INFO "mem_exam_exit!\n");
}

module_init(mem_exam_init);
module_exit(mem_exam_exit);
MODULE_LICENSE("GPL");
