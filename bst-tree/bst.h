#ifndef BST_H
#define BST_H

typedef struct no{
  int val;
  struct no *left, *right;
} no;
typedef no *tree;

tree insert_bst(tree node, int val);
void pre_order_bst(tree node);
void in_order_bst(tree node);
void pos_order_bst(tree node);
void reverse_bst(tree node);
int isPrime(int num);
int sum_prime_numbers_bst(tree no);
int successor_bst(tree node, int suc, int val);
void path_bst(tree node, int val);
void switch_nodes(tree node, int val);
tree remove_bst(tree node, int val);
int sum_all_numbers_bst(tree node);
int exist_bst(tree node, int val);
int transform_percentage(int num, float porcentagem);
int adjust_percentage_bst(tree node, float porcentagem);
int height_bst(tree node);
void succession_bst(tree node, int n);
tree prune_bst(tree node, int val);

#endif
