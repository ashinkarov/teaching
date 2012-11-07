#include <stdio.h>
#include <stdlib.h>
#include <errno.h>

#include "common.h"

/* Multiply two matrices.  */
static float *
matmul (unsigned N, float *A, float *B)
{
  unsigned i, j, k;
  float * C = (float *) malloc (N * N * sizeof (float));

  for (i = 0; i < N; i++)
    for (j = 0; j < N; j++)
      {
        float s = 0;

        for (k = 0; k < N; k++)
          s += idx (A, N, i, k) * idx (B, N, k, j);

        idx (C, N, i, j) = s;
      }

  return C;
}


int
main (int argc, char *argv[])
{
  unsigned N = 0;
  float *A, *B, *C;
  char *ptr;

  if (argc != 2)
    {
      usage (argv[0]);
      return EXIT_FAILURE;
    }

  N = (unsigned) strtoul (argv[1], &ptr, 10);
  if (errno == ERANGE || *ptr)
    {
      (void) fprintf (stderr, "error: invalid number `%s' found\n", argv[1]);
      return EXIT_FAILURE;
    }

  A = (float *) malloc (N * N * sizeof (float));
  B = (float *) malloc (N * N * sizeof (float));

  init_matrix (N, A, 1.0);
  init_matrix (N, B, 1.0);

  C = matmul (N, A, B);

  print_matrix (N, A);
  print_matrix (N, B);
  print_matrix (N, C);

  free (C);
  free (A);
  free (B);

  return EXIT_SUCCESS;
}
