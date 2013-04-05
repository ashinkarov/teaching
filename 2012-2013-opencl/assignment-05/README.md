# Assignment 05

This sheet is meant to serve as exams preparation sheet.  In contrast to
previous sheets no implementation of algorithms is required.  Instead, you
should provide brief but comprehensive written answers or pseudo-code as
indicated.
  
 1. What hardware features of graphics cards potentially do impact an
    OpenCL kernel's performance? Name at least 4 aspects; explain how
    this relates to typical mainstream multi-core systems, and how these
    aspects affect the performance.

 2. Describe the typical components of an OpenCL application and explain
    how they relate to a typical host-GPU hardware setup. Use a sketch of
    a typical OpenCL application in pseudo-code as outline for your
    description.

 3. Consider a kernel that initialises all elements of a three-dimensional
    array _A_ on the device. Assume that the array consists of _2000x100x4_
    integer elements of a 3-dimensional array that is stored in row-major
    order, i.e., the element at index `[4,2,1]` can be found at address
    `A[4*400+2*4+1]`. For convenience, you may write `A[4][2][1]` to denote
    the above selection. Specify a kernel which initialises each legal index
    position `[i,j,k]` in _A_ with the value `i*i*i + j*j*j`. Describe the
    grid of threads that you would launch and provide pseudo-code for the
    kernel. Try to come up with the best possible solution you can think of.

 4. Argue why your chosen solution is superior to other potential solutions.
    Describe at least two such inferior solutions.
