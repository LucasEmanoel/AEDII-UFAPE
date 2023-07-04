#ifndef AVL_H
#define AVL_H

typedef struct no{
  int val;
  int fb;
  struct no *left, *right;
} no;
typedef no *tree;

tree insert_avl(tree node, int val, int *grown);
tree remove_avl(tree node, int val, int *reduce);
tree rotatation(tree node);
void pre_order_avl(tree node);
void in_order_avl(tree node);
void pos_order_avl(tree node);
void reverse_avl(tree node);
int isPrime(int num);
int sum_prime_numbers_avl(tree no);
int successor_avl(tree node, int suc, int val);
void path_avl(tree node, int val);
void switch_nodes(tree node, int val);
int sum_all_numbers_avl(tree node);
int exist_avl(tree node, int val);
int transform_percentage(int num, float porcentagem);
int adjust_percentage_avl(tree node, float porcentagem);
int height_avl(tree node);
void succession_avl(tree node, int n);
tree prune_avl(tree node, int val);
int max_value(tree node);

#endif
