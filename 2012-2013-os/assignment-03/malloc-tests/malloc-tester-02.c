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

    /* One GB of bytes. */
    const size_t one_gb = 1024 * 1024 * 1024;
    size_t allocated_memory = 0;

    /* Limit our allicated memory to 1GB - 1024.  */
    size_t free_memory = one_gb - 1024;

    size_t i = 0;

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

    /* Allocate N chunks 5 KB each.  */
    for (i = 0; i < N; i++) {
        if (free_memory < 5000)
            break;

        xmalloc (mem_pool, i, 5000);
    }

    /* Free all the N allocated chunks.  */
    for (i = 0; i < N; i++)
        xfree (mem_pool, i);

    /* Allocate a 1/4 GB chunks three times.  */
    xmalloc (mem_pool, 0, one_gb/4);
    xmalloc (mem_pool, 1, one_gb/4);
    xmalloc (mem_pool, 2, one_gb/4);

    /* Mark success of the test.  */
    success = 1;

cleanup:
    /* Free all the non-free memory in the MEM_POOL.  */
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
