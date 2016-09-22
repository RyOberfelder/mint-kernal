# Function Research

This section is not about creating a module but understaning how modules build on each other.

The following are topics on functions that I felt should be noted down for memory purposes.

## Kernal functions vs User functions.

This will be a review of OS class but remember that there are functions that the user can use that are built off functions that the user can't use. The functions that people can not use are system calls, while we usually use library functions.

an example of this was created using the contents of the hello folder. 

make sure to run fun the following make commands in the  hello folder

` make `
` make trace `

This will create the file helloTrace.txt given you have installed build-essentials (please refer to the makefile of the mint-kernal and make that if that is an issue).

All of the functions that you are seeing are system calls and the key part is the write function. That is the part that is the core of the printf() in hello.c

## Name Space

Note that global variables are a big 'issue' with kernels because there are alot of variable names that are already taken. This concept is called namespace pollution. To get around this issue be sure to declare the variable static. If dynamic is neede, look into symbol table and register it into the kernel.

To look at all the symbols, look at the /proc/kallsyms file to see all the available variables. 

## Memory space

One thing to be very clear about is the kernel has functions that will alot virtual memory from physical memory. memory management is huge in the kernal and this will be where most of your issues are. Like segfaults.

## Device drivers.

There is an interesting overview of this as part of the Linux Kernal Module Programming Guide in 3.1.6

I would recomend reading that for driver questions.
