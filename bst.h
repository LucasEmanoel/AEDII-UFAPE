#ifndef BST_H
#define BST_H

typedef struct no{
  int val;
  struct no *left, *right;
} no;
typedef no *tree;

tree add(tree no, int val);
void pre_order(tree no);
void in_order(tree no);
void pos_order(tree no);

#endif
