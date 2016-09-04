setup: dev-util

dev-util:
	sudo apt install vim
	sudo apt-get install build-essential kernel-package libncurses5-dev fakeroot wget bzip2 xz-utils
	export CONCURRENCY_LEVEL=2
	export CHOST="x86_64-pc-Linux-gnu"
	export CFLAGS="-march=native -O2 -pipe"
	export CXXFLAGS="$CFLAGS"
	mkdir ~/kernel-build
	wget https://www.kernel.org/pub/linux/kernel/v4.x/linux-4.7.2.tar.xz -O ~/kernel-build/linux-4.7.2.tar.xz
	tar -Jxf ~/kernel-build/linux-4.7.2.tar.xz -C ~/kernel-build/
	cp /boot/config-$(shell uname -r) ~/kernel-build/linux-4.7.2/.config
	yes "" | make -C ~/kernel-build/linux-4.7.2/ oldconfig
#	fakeroot make-kpkg --initrd --append-to-version=-mint-$(HOSTNAME)-$(date +"%m-%d-%y") kernal_image kernal_headers

clean:
	rm -rf ~/kernel-build/
