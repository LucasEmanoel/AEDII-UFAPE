#ifndef BST_H
#define BST_H

typedef struct no{
  int val;
  struct no *left, *right;
} no;
typedef no *tree;

tree add(tree node, int val);
void pre_order(tree node);
void in_order(tree node);
void pos_order(tree node);
int qtd_primos_bst(tree node);
void reserve_bst(tree node);
int ehPrimo(int num);
int sucessor_bst(tree node, int val);
void caminho_bst(tree node, int val);
int somatorio(tree node);
int existe(tree node, int val);
int reajuste(tree node, float porcentagem);
#endif
