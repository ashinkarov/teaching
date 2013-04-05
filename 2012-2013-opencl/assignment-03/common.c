#include <stdio.h>

#include "common.h"

/* Print NxN matrix represented with a flat array.  */
void
print_matrix (unsigned N, float *p)
{
  unsigned i, j;

  for (i = 0; i < N; ++i)
    for (j = 0; j < N; ++j)
      printf ("%8.2f%s", idx (p, N, i, j), j == N-1 ? "\n" : ", ");
  printf ("\n");
}

/* Initialize all the elements of the matrix with VALUE.  */
void
init_matrix (unsigned N, float * m, float value)
{
  unsigned i;

  for (i = 0; i < N*N; ++i)
    m[i] = value;
}

/* Initialize matrix with values from 0 to N*N.  */
void
init_matrix_seq (unsigned N, float * m)
{
  unsigned i;

  for (i = 0; i < N*N; ++i)
    m[i] = (float) i;
}

/* Helper function.  Prints instructions to use the program.  */
void
usage (const char * const prog)
{
  (void) fprintf (stderr, "usage: %s <N>\n"
                  "\twhere N will be used to create NxN matrix\n", prog);
}

