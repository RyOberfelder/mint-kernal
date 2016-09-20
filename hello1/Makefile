# If KERNELRELEASE is defined, we've been invoked from the
# kernel build system and can use its language.
ifneq ($(KERNELRELEASE),)
	obj-m := hello.o

# Otherwise we were called directly from the command
# line; invoke the kernel build system.
else
	KERNELDIR ?= /lib/modules/$(shell uname -r)/build
 	PWD := $(shell pwd)
default:
	make -C $(KERNELDIR) M=$(PWD) modules
endif

# KERNELDIR is being defined as the location of the kernel that we want to be
# injecting our kernel into.

# PWD is litterally the present working Directory

# The obj-m seems to be defining the module in question we want to inject
# Further, the make -C command actually creates the module hello.ko

# Please refer to https://www.mjmwired.net/kernel/Documentation/kbuild/modules.txt for more information
# specifically 2.1
