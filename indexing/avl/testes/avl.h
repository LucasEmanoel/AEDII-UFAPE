#ifndef AVL_H
#define AVL_H
#include <stdlib.h>

typedef struct index {
	int key;
	int index;
} type_data;

typedef struct no{
  type_data * val;
  int fb;
  struct no *left, *right;
} no;
typedef no * avl_tree;

avl_tree rsd(avl_tree node);
avl_tree rse(avl_tree node);
avl_tree rdd(avl_tree node);
avl_tree rde(avl_tree node);
avl_tree rotation(avl_tree node);
void initialize(avl_tree *no);
avl_tree insert_avl(avl_tree node, type_data *val, int *grown);
int height(avl_tree raiz);
int compare_value(int a, int b);
int min_value(avl_tree node);
int max_value(avl_tree node);
void switch_nodes(avl_tree node, int val);

#endif
