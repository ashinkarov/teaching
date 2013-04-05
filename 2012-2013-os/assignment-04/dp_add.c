#include <stdlib.h>
#include <stdio.h>
#include <pthread.h>

#define N_THREADS 16
#define SIZE 1000
#define ITERATIONS 100000

typedef struct threadArgs threadArgs_t;

struct threadArgs
{
  int tid;
  int from;
  int to;
};

double a[SIZE];
double b[SIZE];

pthread_barrier_t barrier;

void
sequential ()
{
  /*
   * Here goes the sequential version
   */
}

void *
simd (void *arg)
{
  int tid, from, to;

  tid = ((threadArgs_t *) arg)->tid;
  from = ((threadArgs_t *) arg)->from;
  to = ((threadArgs_t *) arg)->to;

  /*
   * Here, the addition happens....
   */
}

void
initData ()
{
  int i;
  for (i = 0; i < SIZE; i++)
    {
      a[i] = i;
      b[i] = (SIZE - 1) - i;
    }
  pthread_barrier_init (&barrier, NULL, N_THREADS);
}

int
main ()
{
  /*
   * Here you need to create your threads run them end sync them
   */
  return (0);
}
