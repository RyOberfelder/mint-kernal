# Character Device

This an an overview of the Character Device Module and what it does

## chardev.c

chardev is a module designed to be a device driver this has specific ways of intereacting with it beyond entering information upon startup and exit of the module.

Pelase refer to the following sections for information on how to use the module.

## Makefile

(chardev dir)
`make`

## viewing module info

use the following command to see the module info

` modinfo chardev.ko`

## injecting .ko

to inject a kernal, use the follwing command

(chardev dir)
` insmod ./chardev.ko`

to see that this worked, go to /proc/modules and cat that. you will see your module

Further if you go to /var/log/syslogs and cat that, you can see any oppening messages

## Interacting with chardev
First thing to do is of course enter the module if you have not done so.

(chardev dir)
` insmod ./chardev.ko`

After that, the module is designed to report important data to the syslog. Please go to /var/log/syslog and you will find the commands entered by the module into the syslog.

The command will look like the following:

` mknod /dev/chardev c 247 0 `

The above is how you will add a device. `mknod` actually adds the device. `/dev/chardev`is the name that you will access when you are writing or reading to the chardev module. c I woula assume in the laguage the driver is writen in, 247 is the Major number assigned to the driver assigned to your driver. lastly, the 0 is the minor number. just keep trying the minor number untill you get one that works for you.

Once that is the case you can do a couple of things.

one thing you can do is cat /dev/chardev

`cat /dev/chardev`

If you cat /dev/chardev, the chardev module will consider that as an attempt to read the file and will increment the file accordingly in it's hello world message. This represents tha ability to attach actions to a device read. Further it proves that state is something that can not only be stored but given to the user for consumption.

in terms of writing to the file. try the following

`echo "hi" > /dev/chardev`

This will count as a write to the device and will execute the write hook.

This results in two events.

The device will not that it can not do this operation in /var/log/syslog, and will pass an error to the user in the user space.

For more information on the specs of how it accomplishs all of that. look into the c file.


## Usefull Sites

https://www.linux.com/learn/kernel-newbie-corner-kernel-debugging-using-proc-sequence-files-part-1

http://lxr.free-electrons.com/source/include/linux/proc_fs.h#L42

http://lxr.free-electrons.com/source/include/linux/fs.h#L1670


