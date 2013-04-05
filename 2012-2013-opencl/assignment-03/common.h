#ifndef __COMMON_H__
#define __COMMON_H__

/* This is a macro to mimic 2-d array indexing.  */
#define idx(__m, __n, __i, __j) (*(__m + (__i * __n + __j)))

void print_matrix (unsigned, float *);
void init_matrix (unsigned, float *, float);
void init_matrix_seq (unsigned, float *);
void usage (const char * const);

#endif /* __COMMON_H__  */
