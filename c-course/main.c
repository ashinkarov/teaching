#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include "tree.h"

int
main (int argc, char *argv[])
{
  struct node * n = node_allocate ();

  n->data = strdup ("c");

  node_add (n, "b");
  node_add (n, "a");
  node_add (n, "d");
  node_add (n, "f");

  node_print (n, 0);
  node_free (n);

  return EXIT_SUCCESS;
}
