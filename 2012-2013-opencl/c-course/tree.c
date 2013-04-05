#include <stdlib.h>
#include <string.h>
#include <stdio.h>

#include "mystring.h"
#include "tree.h"


struct node *
node_allocate ()
{
  struct node * local;

  local = malloc (sizeof (struct node));
  local->left = NULL;
  local->right = NULL;

  return local;
}

void
node_add (struct node * root, char * string)
{
  if (string_compare (root->data, string) == -1)
    {
      if (root->left == NULL)
        {
	  struct node * t = node_allocate ();
	  t->data = strdup (string);
	  root->left = t;
	}
      else
	node_add (root->left, string);
    }
  else
    {
      if (root->right == NULL)
        {
	  struct node * t = node_allocate ();
	  t->data = strdup (string);
	  root->right = t;
	}
      else
	node_add (root->right, string);
    }
}

static void
print_indent (int indent)
{
  int i;
  for (i = 0; i < indent; i++)
    printf ("\t");
}

void
node_print (struct node * n, int indent)
{
  if (n->left != NULL)
    node_print (n->left, indent + 1);
  else
    {
      print_indent (indent + 1);
      printf ("nothing\n");
    }

  print_indent (indent);
  printf ("data: %s\n", n->data);


  if (n->right != NULL)
    node_print (n->right, indent + 1);
  else
    {
      print_indent (indent + 1);
      printf ("nothing\n");
    }
}


void
node_free (struct node * n)
{
  if (n == NULL)
    return;

  node_free (n->left);
  node_free (n->right);

  free (n->data);
  free (n);
}

