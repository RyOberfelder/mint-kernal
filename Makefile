setup: dev-util

dev-util:
	sudo apt-get install vim wget bzip2 xz-utils cmake

kernel-setup:
	sudo apt install vim
	sudo apt-get install build-essential kernel-package libncurses5-dev fakeroot wget bzip2 xz-utils cmake
	sudo apt-get install libssl-dev libssl-doc
	export CONCURRENCY_LEVEL=2
	export CHOST="x86_64-pc-Linux-gnu"
	export CFLAGS="-march=native -O2 -pipe"
	export CXXFLAGS="$CFLAGS"
	mkdir ~/kernel-build
	wget https://www.kernel.org/pub/linux/kernel/v4.x/linux-4.7.2.tar.xz -O ~/kernel-build/linux-4.7.2.tar.xz
	tar -Jxf ~/kernel-build/linux-4.7.2.tar.xz -C ~/kernel-build/
	make -C ~/kernel-build/linux-4.7.2/ mrproper
	cp /boot/config-$(shell uname -r) ~/kernel-build/linux-4.7.2/.config
	yes "" | make -C ~/kernel-build/linux-4.7.2/ oldconfig
	sudo make -C ~/kernel-build/linux-4.7.2/
	sudo make -C ~/kernel-build/linux-4.7.2/ modules_install install

clean:
	rm -rf ~/kernel-build/
