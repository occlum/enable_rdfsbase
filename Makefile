obj-m += enable_rdfsbase.o

all:
	make -C /lib/modules/$(shell uname -r)/build M=$(PWD) modules

install:
	sudo insmod enable_rdfsbase.ko

uninstall:
	sudo rmmod enable_rdfsbase.ko

clean:
	make -C /lib/modules/$(shell uname -r)/build M=$(PWD) clean
	$(RM) *.o.ur-safe
