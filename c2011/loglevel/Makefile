obj-m = loglevel.o
KERN_SRC_DIR = /root/linux/
all:
	make -C $(KERN_SRC_DIR) M=$(PWD) modules
clean:
	make -C $(KERN_SRC_DIR) M=$(PWD) clean
