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

void inicializar(tree *node);
void adicionar (int valor, tree *node);
void remover (int valor, tree *node);

int altura(tree node);
int maior(int a, int b);
int maior_elemento(tree node);
int menor_elemento(tree node);
void pre_order(tree node);
void pos_order(tree node);
void in_order(tree node);

void imprimir_elemento(tree node);
void imprimir(tree node);


void ajustar(tree *node, tree elemento);
void reajustar(tree *node, tree elemento);
void rotacao_simples_direita(tree *node, tree pivo);
void rotacao_dupla_direita(tree *node, tree pivo);
void rotacao_simples_esquerda(tree *node, tree pivo);
void rotacao_dupla_esquerda(tree *node, tree pivo);

enum cor cor(tree elemento);
int eh_raiz(tree elemento);
int eh_filho_esquerdo(tree elemento);
int eh_filho_direito(tree elemento);
tree irmao(tree elemento);
tree tio(tree elemento);
void retira_duplo_preto(tree *node, tree elemento);

#endif
