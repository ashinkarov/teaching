#include <stdio.h>
#include <stdlib.h>
#include <errno.h>

#include "common.h"

/* Multiply two matrices.  */
static void
transpose (unsigned N, float *A)
{
  unsigned i, j;
  float t;

  for (i = 0; i < N; i++)
    for (j = i+1; j < N; j++)
      {
        t = idx (A, N, i, j);
        idx (A, N, i, j) = idx (A, N, j, i);
        idx (A, N, j, i) = t;
      }
}


int
main (int argc, char *argv[])
{
  unsigned N;
  float *A;
  char *ptr;

  if (argc != 2)
    {
      usage (argv[0]);
      return EXIT_FAILURE;
    }

  N = (unsigned) strtoull (argv[1], &ptr, 10);
  if (errno == ERANGE || *ptr)
    {
      (void) fprintf (stderr, "error: invalid number `%s' found\n", argv[1]);
      return EXIT_FAILURE;
    }

  A = (float *) malloc (N * N * sizeof (float));

  init_matrix_seq (N, A);

  print_matrix (N, A);
  transpose (N, A);
  print_matrix (N, A);

  free (A);

  return EXIT_SUCCESS;
}
