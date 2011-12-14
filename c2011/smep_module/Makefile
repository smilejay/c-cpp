obj-m += smep.o
KERNEL_BUILD := /lib/modules/$(shell uname -r)/build
all:
	make -C $(KERNEL_BUILD) M=$(PWD) modules
clean:
	make -C $(KERNEL_BUILD) M=$(PWD) clean
