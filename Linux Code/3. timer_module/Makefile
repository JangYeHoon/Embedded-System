obj-m += timer_module.o
KDIR := /lib/modules/$(shell uname -r)/build
PWD := $(shell pwd)
defaut:
	$(MAKE) -C $(KDIR) SUBDIRS=$(PWD) modules
