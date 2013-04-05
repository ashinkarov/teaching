Introduction
============

Welcome to the course, and here are the materials for your first assignment.
We assume that you are familiar with programming in C, some basic UNIX and 
makefiles.  If you are not, it might be a right time to do something about
it.

The machines that are being prepared for this course are:  linux39-50, 
linux70-80 in the lab 2.50.

Description
===========

In this folder you are going to find out two files:
  1. `square.c`
  2. `Makefile`

`square.c` is a minimalistic program written in C99 that should give you enough
understanding on how to create an OpenCL code.  All the program does is creates
an array of random floats, sends it on a device, where they are being squared,
reads the result, compares if the operation was performed correctly and prints
out some info.

`Makefile` defines a couple of environment variables and libraries in order to
build an executable.

Executing
=========

To compile the binary, run make:
```shell
$ make
cc -O3 -Wall -Wextra -I/opt/AMDAPP/include -std=c99 -std=c99 -L/opt/AMDAPP/lib/x86_64  -l OpenCL -o square square.c
square.c: In function ‘main’:
square.c:27: warning: unused parameter ‘argv’
```

Now you should have a binary file called `square`.  You can execute it
using a GPU as a device by running:
```shell
$ ./square
```
and on a CPU by running
```shell
$ ./square CPU
```

The task
========

Please see `assignment-01.md` in the file list.
