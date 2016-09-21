# Hello 5

Overview of the start and stop module

## hello4.c

hello 4 takes in arguments when you place it into the kernel. please refer to the injecting section to see how this works but supporting this ability is the core concept of this module.

## Makefile

(hello4 dir)
`make`

it is important to note that this was actually diffrent than what we had to do before.

to understand the changes please refer to the following site as it is what helped me.

https://www.kernel.org/doc/Documentation/kbuild/makefiles.txt

## viewing module info

use the following command to see the module info

` modinfo hello4.ko`

## injecting .ko

to inject a kernal, use the follwing command

(hellos dir)
` insmod ./hello3.ko`

to see that this worked, go to /proc/modules and cat that. you will see your module

## Arguments

The arguments that you can add are the core of this function

Here is how you can add the following argumetns

#### myshort
(the number should be short)
(give a number not a short, will not inject module and note out of range)
(give it a string and it will not inject, noting invalid parameters)
(giving it arrays are more invalid, implying thats type issues)
 
insmod hello4.ko myshort=36

#### myint
(the number should be an int)
(note myshort for same issues)

insmod hello4.ko myint=10000
#### mylong
(the number should be a long)
(not myshort for same issues)

insmod hello4.ko mylong=4783294
#### mystring
(this should be a string)
(to include a string with spaces, don't throw the "", do '"this is correct"')
(including numbers without quotes or an array syntax, treats it as a quote)
(there could be a length limit to string but not known yet)

insmod hello4.ko mystring="cool-string"
#### myintArray
(this should be an array of ints)
(will not inject should you give it non ints, either one or both)
(can put val in first spot but not sure how to do only second slot)

insmod hello4.ko myintArray=-14,32
## removing .ko
to remove your module, executing the following
`rmmod hello4`

look at /var/log/syslog to see that it logged to the system files
