#include <unistd.h>
#include <stdlib.h>
#include <stdio.h>
#include <string.h>

struct node {
  struct node *left;
  struct node *right;
  char *data;
};

void
error (char *msg)
{
  fprintf (stderr, "Error: %s\n", msg);
  exit (1);
}

struct node *
alloc_node (struct node *left, struct node *right, char *data)
{
  struct node *node;

  node = malloc (sizeof (struct node));
  if (node == 0)
    error ("memory allocation error");
  node->left = left;
  node->right = right;
  node->data = malloc (strlen (data) + 1);
  if (node->data == 0)
    error ("memory allocation error");
  strcpy (node->data, data);

  return node;
}

struct node *
insert (struct node *tree, char *data)
{
  if (tree == NULL)
    return alloc_node (NULL, NULL, data);
  else
    {
      int cmp = strcmp (tree->data, data);

      if (cmp > 0)
	tree->left = insert (tree->left, data);
      else if (cmp < 0)
	tree->right = insert (tree->right, data);
      return tree;
    }
}

void
print_tree_flat0 (struct node *tree)
{
  if (tree == NULL)
    return;
  else
    {
      print_tree_flat0 (tree->left);
      printf ("%s ", tree->data);
      print_tree_flat0 (tree->right);
    }
}

void
print_tree_flat (struct node *tree)
{
  print_tree_flat0 (tree);
  printf ("\n");
}

void
print_tree0 (struct node *tree, int depth)
{
  if (tree == NULL)
    return;
  else
    {
      print_tree0 (tree->left, depth + 1);
      printf ("%*s%s\n", depth*2, "", tree->data);
      print_tree0 (tree->right, depth + 1);
    }
}

void
print_tree (struct node *tree)
{
  print_tree0 (tree, 0);
}

int
main (int argc, char **argv)
{
  struct node *tree = NULL;

  tree = insert (tree, "dog");
  tree = insert (tree, "cat");
  tree = insert (tree, "wolf");
  tree = insert (tree, "javelina");
  tree = insert (tree, "gecko");
  tree = insert (tree, "coyote");
  tree = insert (tree, "scorpion");

  print_tree_flat (tree);
  printf ("\n");
  print_tree (tree);

  exit (0);
}
