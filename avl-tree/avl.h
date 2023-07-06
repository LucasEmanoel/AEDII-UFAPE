#ifndef AVL_H
#define AVL_H

typedef struct no{
  int val;
  int fb;
  struct no *left, *right;
} no;
typedef no *tree;

tree rsd(tree node);
tree rse(tree node);
tree rdd(tree node);
tree rde(tree node);
tree rotation(tree node);
tree insert_avl(tree node, int val, int *grown);
int max_value(tree node);
tree remove_avl(tree node, int val, int *reduce);
void pre_order_avl(tree node);
void switch_nodes(tree node, int val);

#endif
