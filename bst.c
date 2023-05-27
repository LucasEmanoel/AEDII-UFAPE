#include "bst.h" //importa o arquivo de declaracoes
#include <stdio.h>
#include <stdlib.h>

tree add(tree node, int val){
  //caso basico, ou seja. casa arvore vazia no primeiro elemento e caso preenchida no ultimo elemento
  if (node == NULL)
  {
    tree new_node = (tree) malloc(sizeof(struct no));
    new_node->left = NULL;
    new_node->right = NULL;
    new_node->val = val;
    return new_node;
  }
  //casos onde tem elementos devemos percorrer recursivamente ate encontrar a posicao ideal.
  else
  {
    //sempre atualizamos os nodes que passamos recursivamente, por isso (node->right), caso o no ja tenha elemento esse valor simplesmennte nao muda.
    if (node->val < val)
    {
      node->right = add(node->right, val);
    } else {
      node->left = add(node->left, val);
    }
    //fiquei em duvida nesse bloco, (solicitar ajuda de alguem)
    return node;
  }
  
}

void pre_order(tree node){
  if (node != NULL) {
    printf("[%d]", node->val);
    pre_order(node->left);
    pre_order(node->right);
  }
}

void in_order(tree node){
  if (node != NULL) {
    in_order(node->left);
    printf("[%d]", node->val);
    in_order(node->right);
  }
}

void pos_order(tree node){
  if (node != NULL) {
    pos_order(node->left);
    pos_order(node->right);
    printf("[%d]", node->val);
  }
}

void reserve_bst(tree node){
  if (node != NULL) {
    reserve_bst(node->right);
    printf("[%d]", node->val);
    reserve_bst(node->left);
  }
}

int ehPrimo(int num){
  for (int i = 2; i < num; i++){
    if(num % i == 0)
      return 1; //nao e primo
  }
  return 0; //e primo
}

int qtd_primos_bst(tree no){
  int aux, i;
  if(no != NULL){
    aux = qtd_primos_bst(no->left) + qtd_primos_bst(no->right);
    if (ehPrimo(no->val) == 0){
      return aux + 1;
    } else {
      return aux;
    } 
  }
}

int sucessor_bst(tree no, int val){
  //implementar
}

void caminho_bst(tree node, int val){
  printf("[%d]", node->val);
  if (node != NULL && node->val != val) {
    if(node->val < val){
      caminho_bst(node->right, val);
    } else {
      caminho_bst(node->left, val);
    }
  }
}