Introduction
============

Here you can find some materials which might be useful for the assignment 3.

Description
===========

In this folder you are going to find the following files:
  1. `common.c, common.h` -- files with common matrix procedures
  2. `matmul.c` -- matrix multiplication
  3. `transpose.c` -- matrix transpose
  4. `Makefile`

`common.c` contains functions to initialise matrices, print matrix, and
function `usage`, which is use, in case of incorrect invocation of the
program.

`common.h` is a header containing prototypes for `common.c` functions.

`matmul.c` is a program that reads N from the argument list, generates two
matrices of size NxN where each element is `1.0`, multiplies these matrices
and outputs result on standard output.

`transpose.c` is a program that reads N from the argument list, generates a
matrix of size NxN, fills it with values from 0 to N^2 -1, transposes the
matrix and outputs result on standard output.

`Makefile` defines two rules matmul and transpose, each of which builds
according binary. 

Executing
=========

To compile the binaries, run make:
```
$ make
cc -Wall -Wextra -pedantic -std=c99 -O3   -c -o matmul.o matmul.c
cc -Wall -Wextra -pedantic -std=c99 -O3   -c -o common.o common.c
cc   matmul.o common.o   -o matmul
cc -Wall -Wextra -pedantic -std=c99 -O3   -c -o transpose.o transpose.c
cc   transpose.o common.o   -o transpose
```
Now you have two binaries which you can execute passing N as an argument.

```
$ ./matmul 3
    1.00,     1.00,     1.00
    1.00,     1.00,     1.00
    1.00,     1.00,     1.00

    1.00,     1.00,     1.00
    1.00,     1.00,     1.00
    1.00,     1.00,     1.00

    3.00,     3.00,     3.00
    3.00,     3.00,     3.00
    3.00,     3.00,     3.00
```

and

```
$ ./transpose 3
    0.00,     1.00,     2.00
    3.00,     4.00,     5.00
    6.00,     7.00,     8.00

    0.00,     3.00,     6.00
    1.00,     4.00,     7.00
    2.00,     5.00,     8.00

```

The task
========

Please see `assignment-03.md` in the file list.
