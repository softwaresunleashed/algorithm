obj-m += static_allocated_char_driver.o
obj-m += dynamic_allocated_char_driver.o

KDIR = /lib/modules/$(shell uname -r)/build

all:
	make -C $(KDIR)  M=$(shell pwd) modules
clean:
	make -C $(KDIR)  M=$(shell pwd) clean
