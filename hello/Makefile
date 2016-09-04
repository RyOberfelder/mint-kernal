obj-m += hello-1.o

all:
	make -C /lib/modules/$(shell uname -r)/builds M=$(PWD) modules

clean:
	make -C /lib/modules/$(shell uname -r)/build M=$(PWD) clean
