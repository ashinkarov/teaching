# Assignment 01

Download files from [here][1].

In assignment-01 you will find your first OpenCL program `square.c`.
Familiarise yourself with the OpenCL environment, compile and run `square.c`.
    
 1. Restructure `square.c` in a way that:
     + exposes more clearly the problem specific parts and that 
     + yields a suitable set of abstractions which
        can conveniently be reused when writing further OpenCL kernels.
    
    Apply good software engineering practice!

 2. Using the new framework from 1., write a program with a kernel which
    computes the sum of two vectors of length _N_, where _N_ is a
    commandline parameter of your program. Initialise the two vectors with
    the integer numbers `1,...,N` each.

 3. In image processing a technique called relaxation is frequently used. It
    refers to an iterative re-computation of an array where each value is
    replaced by a weighted sum of the neighbour elements.
    Implement 1D relaxation on vectors in OpenCL. Recompute all inner
    elements of an _N-element_ vector using the following formula:
    ```a[i] = 0.25*a[i-1] + 0.5*a[i] + 0.25*a[i+1]```
    The elements a[0] and `a[N-1]` are to remain unchanged. Repeat that
    relaxation M times. Initialise M and N from commandline parameters
    and initialise the vector with double values, all values being 0.0 but
    `a[0]` which should be 200.0.

 4. Find a way to measure the wall-clock time of your application. Measure
    execution times of your programs when run on the CPU only and for
    running on the GPU with varying M and N. Contrast these numbers
    and compute the speedups obtained from the GPU use as compared to
    running on the CPU only. How do M and N affect your results?

[1]: https://github.com/ashinkarov/teaching/tree/master/2012-2013-opencl/assignment-01
