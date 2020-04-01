obj-m += static_waitqueue_driver.o
obj-m += dynamic_waitqueue_driver.o
KDIR = /lib/modules/$(shell uname -r)/build
all:
	make -C $(KDIR)  M=$(shell pwd) modules
clean:
	make -C $(KDIR)  M=$(shell pwd) clean
