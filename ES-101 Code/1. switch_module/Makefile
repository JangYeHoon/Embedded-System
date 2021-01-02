CC = gcc
obj-m := switch_module.o
KDIR := /lib/modules/$(shell uname -r)/build
pwd := $(shell pwd)
default:
	$(MAKE) -C $(KDIR) SUBDIRS=$(PWD) modules
clean:
	rm -f *.ko
	rm -f *.o
	rm -f *.mod.*
	rm -f *.cmd
