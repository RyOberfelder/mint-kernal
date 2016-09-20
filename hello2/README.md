# Hello 2

Overview of hello2

## hello2.c

The main difference between the hello 1 is the inclustion of the __initdata in the hello. This is meant to help introduce you to the init macros.

## Makefile

(hello2 dir)
`make`

## viewing module info

use the following command to see the module info

` modinfo hello.ko`

## injecting .ko

to inject a kernal, use the follwing command

(hellos dir)
` insmod ./hello.ko`

to see that this worked, go to /proc/modules and cat that. you will see your module

to remove your module, executing the following
`rmmod hello`

look at /var/log/messages to see that it logged to the system files
