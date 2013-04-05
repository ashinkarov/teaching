# Assignment 02
  
This sheet is concerned with an effective implementation of fold/reduction
operations.  Given an _N_ element vector, we want to compute the sum of its
elements.  In all our examples we want _N_ to be a command line parameter and we
initialise the vector with all values set to _1_.  To verify our result, we print
the sum obtained.

 1. Write a *C* program which implements the reduction as described
    above.

 2. Write an OpenCL program which implements the reduction by
    executing a kernel where exactly one thread computes the reductions
    while all other threads idle. Measure and compare the runtimes for 
    1. your C implementation from assignment-01
    2. your OpenCL implementation when run on the CPU 
    3. your OpenCL implementation when run on a GPU. 

    In order to get meaningful results choose an _N_ as close as
    possible to the maximal N that would fit the given memory. You may
    have to repeatedly compute the reduction in order to get large enough
    run times (ie >2 secs).

 3. Write an OpenCL program that implements the reduction as a
    succession of partial reductions that are executed in parallel. You may
    want to use barriers to avoid the need for several kernels. To simplify
    this task you can assume a fixed given _N_ as chosen for the
    measurements in task 2.

 4. Run the solution of task 3 on 
    1. the CPU
    2. the GPU

    and contrast your findings to those of task 2.
