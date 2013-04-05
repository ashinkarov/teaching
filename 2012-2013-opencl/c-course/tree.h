#ifndef __TREE_H__
#define __TREE_H__

struct node
{
  char * data;
  struct node * left;
  struct node * right;
};

struct node *node_allocate ();
void node_add (struct node * root, char * string);
void node_print (struct node * n, int indent);
void node_free (struct node *);


#endif
