# Assignment 04

This sheet is concerned with thread mapping and dynamic workloads.  Assume
the following problem: Given an M by N matrix m of floats and an M element
vector v of integers.  The task is to modify m using the following formula:
> `m[i,j] = m[i,j] + 2.0` iff `j < v[i]`

All other elements of m remain unaffected.
  
 1. Write an OpenCL program that implements the above algorithm.
    Provide _M_ and _N_ as commandline parameters and Initialise the 
    vector _v_ with _N_. Initialise _m_ any which way you find suitable.
    Measure the runtime behaviour for different _M_ and _N_.

 2. Look at different ways to statically map thread spaces to the given
    task.  What impact does that have on your runtime evaluation? Try to 
    explain your findings.

 3. Experiment with the initialisation of _v_. What happens if all values
    in v are smaller (eg. all values _N/2_ or all values _N/4_)? Is the 
    effect identical for all your thread mappings? What happens if you 
    initialise v with random numbers within `[0,N]`? Try to explain your 
    findings.

 4. Can you come up with a thread mapping that copes better with a
    random initialised _v_?
