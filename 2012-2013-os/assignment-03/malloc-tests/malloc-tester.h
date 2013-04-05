#ifndef __MALLOC_TESTER_H__
#define __MALLOC_TESTER_H__

#include <stdlib.h>
#include <time.h>
#include <err.h>

#include <sys/time.h>


/* Structure to track the memory allocations.  */
struct chunk
{
    size_t sz;
    void *ptr;
};


/* Time difference between a and b in microseconds.  */
static int64_t
xelapsed (struct timespec a, struct timespec b)
{
    return ((int64_t)a.tv_sec - b.tv_sec) * 1000000
           + ((int64_t)a.tv_nsec - b.tv_nsec) / 1000LL;
}

/* Wrapper around malloc which works on memory_chunks.  */
static inline struct chunk
__malloc (size_t n)
{
    struct chunk x;

    x.sz = n;

    if (NULL == (x.ptr = malloc (n)))
        warn ("malloc failed");

    return x;
}

/* Wrapper around free to avoid double frees.  */
static inline void
__free (struct chunk * x)
{
    if (x->ptr)
        free (x->ptr);
}



#endif /* __MALLOC_TESTER-H__  */
