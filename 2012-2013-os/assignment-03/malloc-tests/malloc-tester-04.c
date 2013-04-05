#include <stdlib.h>
#include <stdint.h>
#include <string.h>
#include <stdio.h>

#include <sys/resource.h>

#include "malloc-tester.h"

int
main ()
{
    #define N (100 * 1000)

    /* Array of chunks.  */
    struct chunk mem_pool[N];
    size_t pool_idx = 0;

    /* One GB of bytes. */
    const size_t one_gb = 1024 * 1024 * 1024;
    size_t allocated_memory = 0;

    /* Limit our allicated memory to 1GB - 1024.  */
    size_t free_memory = one_gb - 1024;

    size_t i = 0, j = 0, k = 0;

    struct timespec start, finish;
    int success = 0;

    /* Make sure we limit ourselves to 1 GB.  */
    struct rlimit new_limit = {one_gb, one_gb};



    /* Make sure that the structure is being filled with zeroes.  */
    memset (mem_pool, 0, N*sizeof (struct chunk));


    if (-1 == setrlimit (RLIMIT_AS, &new_limit))
        err (EXIT_FAILURE, "setrlimit failed");
    if (-1 == setrlimit (RLIMIT_DATA, &new_limit))
        err (EXIT_FAILURE, "setrlimit failed");

/* Free the cell IDX in the POOL, allocte memory
   of size N.  If malloc failed, goto cleanup.
   Otherwise adjust FREE_MEMORY and ALLOCATAED_MEMORY  */
#define xmalloc(pool, idx, n)                   \
    do {                                        \
        __free (&pool[idx]);                    \
        pool[idx] = __malloc (n);               \
        if (pool[idx].ptr == NULL)              \
            goto cleanup;                       \
        allocated_memory += n;                  \
        free_memory -= n;                       \
    } while (0)

/* Check if IDX cell in POOL contains non-zero
   memory pointer.  If so, free it and update
   ALLOCATED_MEMORY and FREE_MEMORY.  */
#define xfree(pool, idx)                        \
    do {                                        \
        if (pool[idx].ptr) {                    \
            __free (&pool[idx]);                \
            pool[idx].ptr = NULL;               \
            allocated_memory -= pool[idx].sz;   \
            free_memory += pool[idx].sz;        \
        }                                       \
    } while (0)

    /* Start clock.  */
    clock_gettime(CLOCK_REALTIME, &start);

    /* Loop 10 times and for every iteration eat
       more memory, creating more fragmentation.  */
    for (i = 2; i < 12; i++) {
        size_t s, n;

        pool_idx = 0;
        /* N/2  chunks of size 14-i  */
        for (j = 0; j < N/2; j++) {
            if (free_memory < (14 - i))
                break;

            xmalloc (mem_pool, pool_idx, 14-i);
            pool_idx++;
        }

        /* Allocate 4/5 of free memory, and store the
           result in the second half of MEM_POOL.  */
        s = (free_memory - (free_memory / 5))  / (N /2);
        s = s > 0 ? s : 1;
        n = free_memory / s;

        for (k = N/2; k < N/2 + n && k < N; k++) {
            if (free_memory < s)
                break;

            xmalloc (mem_pool, k, s);
        }


        /* Free every i-th chunk in the MEM_POOL.  */
        for (k = 0; k < N-i-1; k+= i) {
            if (free_memory < mem_pool[k].sz)
                break;

            xfree (mem_pool, k);
        }
    }
    /* Mark success of the test.  */
    success = 1;

cleanup:
    /* Free all the non-free memory in the MEM_POOL.  */
    pool_idx = 0;
    for (i = 0; i < N; i++)
        xfree (mem_pool, i);

    /* Stop clock.  */
    clock_gettime(CLOCK_REALTIME, &finish);

    if (success)
        fprintf (stderr, "Total time: %03li\n", xelapsed (finish, start));
    else
        fprintf (stderr, "The test didn't finish successfully\n");

    return success ? EXIT_SUCCESS : EXIT_FAILURE;
}
