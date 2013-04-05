
This sheet is concerned with thread mapping and dynamic workloads.  Assume
the following problem: Given an M by N matrix m of floats and an M element
vector v of integers.  The task is to modify m using the following formula:
```c
m[i,j] = m[i,j] + 2.0
```
iff ```c
j < v[i]```
  
All other elements of m remain unaffected.
  
1. Write an openCL program that implements the above algorithm.
Provide M ad N as commandline parameters and Initialise the vector v
with N. Initialise m any which way you find suitable. Measure the
runtime behaviour for different M and N.
2. Look at different ways to statically map thread spaces to the given task.
What impact does that have on your runtime evaluation? Try to explain
your findings.
3. Experiment with the initialisation of v. What happens if all values in v
are smaller (eg. all values N/2 or all values N/4)? Is the effect identical
for all your thread mappings? What happens if you initialise v with
random numbers within [0,N]? Try to explain your findings.
4. Can you come up with a thread mapping that copes better with a
random initialised v?
