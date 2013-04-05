# Assignment 03
  
This sheet is concerned with the impact of memory management on
performance.  We will primarily look at matrix multiplication and at matrix
transposition.  We start out from two matrices of size _NxN_ where _N_ is a command
line parameter as in the last sheet.  A sequential C version for matrix
multiplication and transposition can be downloaded from [here][1].


 1. Write an OpenCL program that creates two _NxN_ matrices A and B on
    the host, initialises these arrays of floating point numbers with all
    elements being _1.0_ and subsequently computes the matrix product of
    the two arrays on the devices. Measure the runtimes for increasing _N_
    and compare them against sequential runtimes on the host.

 2. Write an OpenCL program that creates an _NxN_ matrix A on the host,
    and then transposes this matrix on the devices. Measure the runtimes
    for increasing N and compare them against sequential runtimes on the
    host.

 3. Modify your solution for task 2 in a way that enables the use of local
    memory and avoids coalescing problems. Measure the runtimes for
    increasing N and compare them against the runtimes obtained in
    task 2.

 4. Use your best transposition technique in order to improve your matrix
    multiply solution, i.e., transpose the matrix B before computing the
    matrix product of A and B. Quantify the resulting effect on the overall
    runtime for increasing values of N.

[1]: https://github.com/ashinkarov/teaching/blob/master/2012-2013-opencl/assignment-03
