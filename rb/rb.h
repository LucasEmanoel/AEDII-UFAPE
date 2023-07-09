#ifndef RB_H
#define RB_H

enum cor { VERMELHO , PRETO, DUPLO_PRETO};

typedef int tipo_dado;

typedef struct no{
  tipo_dado val;
  enum cor cor;
  struct no *left, *right, *pai;
} no;
typedef no *tree;

void initialize(tree *no);
void insert_rb(tree *node, int val);
void remove_avl(tree *node, int val);


#endif
