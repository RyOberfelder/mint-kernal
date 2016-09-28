# Proc File 2

This is an overview in the creation of a proc file. proc files are simular to device drivers, but focused on offering information about processes and the kernel. This is why these are in the proc section.

## procfs2.c

procfs2.c is an implementation of the proc file that will take information on the write to it and will display that function on the read from the file.

importantly, the open and release functions were added to stop concurancy issues. There was also going to be a setting of permissions but this is actually set in proc_create and so there was no need.

## Makefile

(procfs2 dir)
`make`

## viewing module info

use the following command to see the module info

` modinfo procfs2.ko`

## injecting .ko

to inject a kernal, use the follwing command

(procfs2 dir)
` insmod ./procfs2.ko`

to see that this worked, go to /proc/modules and cat that. you will see your module

Further if you go to /var/log/syslogs and cat that, you can see any oppening messages

## Interacting with procfs2
First thing to do is of course enter the module if you have not done so.

(procfs2 dir)
` insmod ./procfs2.ko`

at this point there will be a procfile called helloworld in the proc directory there are two actions that you can take with this.

First you can write to the proc file

the recomended way to do this is echo something through a pipe to the procfile. an example of this is below.

`echo "This is how this works" > /proc/helloworld`

The other action that you can take is reading the proc file. The recomended way to do this is by catting /proc/helloworld. you can do that by entering the following.

`cat /proc/helloworld`

For both actions, information is logged to var/log/syslog. You can just cat this and that will print out the log info

## Usefull Sites

Here are some of the useful sites used during this section.

https://www.linux.com/learn/kernel-newbie-corner-kernel-debugging-using-proc-sequence-files-part-1

http://lxr.free-electrons.com/source/include/linux/proc_fs.h#L42

http://lxr.free-electrons.com/source/include/linux/fs.h#L1670


