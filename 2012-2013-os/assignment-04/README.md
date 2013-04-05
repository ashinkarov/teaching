# Task 04

## General requirements
Please submit the assignment as a `*.zip` archive, where every problem 
is stored in its own subdirectory. All the code must be well-commented 
and must come with a `Makefile` which builds a program. Notes and explanations 
may come in a separate file in the problem's directory. For notes and 
explanations use text or _pdf_ format.

## Problem 1.1
Write a sequential C program that initialises two static arrays 
`a` and `b` with 1000 integer values each and then adds
`b` to `a` element-wise. Repeat the additions many times so 
that you obtain several seconds overall runtime. 
You may use 100000 iterations as a first guess.

## Problem 1.2
Write a parallel version of the program which implements the addition as 
a data-parallel operation using _n_ pthreads where _n_ can be specified 
as a command-line parameter.

## Problem 1.3
Compare the runtimes of your two versions (sequential/parallel). Make sure 
you test several different numbers of threads up to at least 30 threads. 
Write a little summary of your observations (< 200 words) and present your
measurements. Make sure you include a brief description on how you obtained 
your measurements and what architecture/hardware you used for your measurements.

## Problem 1.4
This particular data-parallel operation can be implemented without any 
synchronisation other than a final synchronisation of all threads. Investigate 
the impact of a barrier synchronisation after each individual addition for varying 
numbers of threads.Write a little summary of your observations and try to 
come up with an explanation for your results (< 200 words).

