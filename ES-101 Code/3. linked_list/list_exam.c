#include <linux/init.h>
#include <linux/module.h>
#include <linux/kernel.h>
#include <linux/list.h>
#include <linux/slab.h>

struct node {
	int val;
	struct list_head list;
};

LIST_HEAD(node_head);

static int list_add_func(int value) {
	struct node *new_node;
	new_node = (struct node *)kmalloc(sizeof(struct node), GFP_KERNEL);
	new_node->val = value;
	list_add_tail(&new_node->list, &node_head);
	return 0;
}

static void list_print(void) {
	struct node *print_node;
	list_for_each_entry(print_node, &node_head, list) {
		printk(KERN_INFO "value (%d)", print_node->val);
		if((print_node->list).next != &node_head)
			printk(KERN_INFO ">>");
	}
}

static int list_exam_init(void) {
	printk(KERN_INFO "list_exam_init!\n");
	LIST_HEAD(node_head);
	list_add_func(20);
	list_add_func(200);
	list_add_func(2000);
	list_print();
	return 0;
}

static void list_exam_exit(void) {
	printk(KERN_INFO "list_exam_exit!\n");
}

module_init(list_exam_init);
module_exit(list_exam_exit);
MODULE_LICENSE("GPL");
