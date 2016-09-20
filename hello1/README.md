# Hello 1

This is the first example of a kernal module that I have written.

To understand this I would bring your attention to the following.

## hello1.c

This is the c code for the module. This sill give you a basic discription of the module. also refer to http://tldp.org/LDP/lkmpg/2.6/html/lkmpg.html at section 2.1 for more information on this. it is important to note that the original tutorial was not followed to a t, for the simple reason that some things are out of date. as of this writing, the module  versions are well into the 4.0.0s while these directions were written for 2.6 

The inclusion of the author and the licence were included after some examples I haven't been able to find again.

## Makefile

This will be the file that will generate the hello.ko that we will be injecting into the module. to run this, please do the following

(hello1 dir)
`make`

## viewing module info

use the following command to see the module info

` modinfo hello.ko`

## injecting .ko

to inject a kernal, use the follwing command

(hello1 dir)
` insmod ./hello.ko`

to see that this worked, go to /proc/modules and cat that. you will see your module

to remove your module, executing the following
`rmmod hello`

look at /var/log/messages to see that it logged to the system files
