# Hello 3

Overview of hello3

## hello3.c

basically focused on the documentation of the mdoule within the module space. in this regard, refer to the viewing module info section.

## Makefile

(hello3 dir)
`make`

## viewing module info

use the following command to see the module info

` modinfo hello.ko`

please note that there is more information including a decription.

## injecting .ko

to inject a kernal, use the follwing command

(hellos dir)
` insmod ./hello3.ko`

to see that this worked, go to /proc/modules and cat that. you will see your module

to remove your module, executing the following
`rmmod hello3`

look at /var/log/messages to see that it logged to the system files
