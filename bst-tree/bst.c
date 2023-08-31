#include "bst.h" //importa o arquivo de declaracoes
#include <stdio.h>
#include <stdlib.h>


tree insert_bst(tree node, int val){
  if (node == NULL) {
    tree new_node = (tree) malloc(sizeof(struct no));
    new_node->left = NULL;
    new_node->right = NULL;
    new_node->val = val;
    return new_node;
  } else {
    if (node->val <= val) {
      node->right = insert_bst(node->right, val);
    } else {
      node->left = insert_bst(node->left, val);
    }
    return node;
  }
  
}

void pre_order_bst(tree node){
  if (node != NULL) {
    printf("[%d]", node->val);
    pre_order_bst(node->left);
    pre_order_bst(node->right);
  }
}

void in_order_bst(tree node){
  if (node != NULL) {
    in_order_bst(node->left);
    printf("[%d]", node->val);
    in_order_bst(node->right);
  }
}

void pos_order_bst(tree node){
  if (node != NULL) {
    pos_order_bst(node->left);
    pos_order_bst(node->right);
    printf("[%d]", node->val);
  }
}

void reverse_bst(tree node){
  if (node != NULL) {
    reverse_bst(node->right);
    printf("[%d]", node->val);
    reverse_bst(node->left);
  }
}

int isPrime(int num){
  for (int i = 2; i < num; i++){
    if(num % i == 0) return 1; //nao e primo
  }
  return 0; //e primo
}

int sum_prime_numbers_bst(tree no){
  int aux, i;
  if(no != NULL){
    aux = sum_prime_numbers_bst(no->left) + sum_prime_numbers_bst(no->right);
    if (isPrime(no->val) == 0){
      return aux + 1;
    } else {
      return aux;
    } 
  }
}

int successor_bst(tree node, int suc, int val){
  if (node != NULL) {
    if(node->val > val && node->left == NULL){
      return node->val;
    }
    if (node->val <= val) {
      successor_bst(node->right, suc, val);
    } else {
      suc = node->val;
      successor_bst(node->left, suc, val);
    }
  } else {
    return suc;
  }
}

void path_bst(tree node, int val){
  if (node != NULL && node->val != val) {
    printf("[%d]", node->val);
    if(node->val <= val){
      path_bst(node->right, val);
    } else {
      path_bst(node->left, val);
    }
    
  }
}
void switch_nodes(tree node, int val){
      tree aux = node->left;
      while (aux->right != NULL) {
        aux = aux->right;
      }
      node->val = aux->val;
      aux->val = val;
}

tree remove_bst(tree node, int val){
  if (node == NULL) {
    return NULL;
  }
  
  if(node->val == val){
    if(node->left == NULL && node->right == NULL){
      free(node);
      return NULL;
    }
    if (node->left != NULL && node->right == NULL){
      tree aux = node->left;
      free(node);
      return aux;
    }
    if (node->left == NULL && node->right != NULL){
      tree aux = node->right;
      free(node);
      return aux;
    }   
    if (node->left != NULL && node->right != NULL){
      switch_nodes(node, val);
      node->left = remove_bst(node->left, val);
      return node;  
    }
  } else { 
    if (node->val <= val) {
      node->right = remove_bst(node->right, val);
    } else {
      node->left = remove_bst(node->left, val);
    }
    return node;
  }
  
}

int sum_all_numbers_bst(tree node){
  int aux;
  if(node != NULL){
    aux = sum_all_numbers_bst(node->left) + sum_all_numbers_bst(node->right);
    return aux + node->val;
  }
}

int exist_bst(tree node, int val){
  if(node != NULL){
    if (node->val == val) {
      return 1;
    }
    if (node->val <= val) {
      exist_bst(node->right, val);
    } else {
      exist_bst(node->left, val);
    }
  } else {
    return 0;
  }
}

int transform_percentage(int num, float porcentagem){
  return num + ( num * (porcentagem / 100));
}

int adjust_percentage_bst(tree node, float porcentagem){
  if (node != NULL) {
    adjust_percentage_bst(node->left, porcentagem);
    adjust_percentage_bst(node->right, porcentagem);
    node->val = transform_percentage(node->val, porcentagem);
  }
}

int height_bst(tree node){
  int left_height, right_height;
  if(node != NULL){
    left_height = height_bst(node->left);
    right_height = height_bst(node->right);

    if(right_height >= left_height){
      return right_height + 1;
    } else {
      return left_height + 1;
    }
  } else {
    return 0;
  }

}

void succession_bst(tree node, int n){
  if(node != NULL){
    if (node->val == n) {
      in_order_bst(node);
    }
    if (node->val <= n) {
      succession_bst(node->right, n);
    } else {
      succession_bst(node->left, n);
    }
  }
}

tree prune_bst(tree node, int val){
  if(node != NULL){
    if (node->val == val) {
      if (node->right != NULL) {
        node->right = prune_bst(node->right, node->right->val);
      }
      if (node->left != NULL) {
        node->left = prune_bst(node->left, node->left->val);
      } 
      free(node);
      return NULL;
    }
    if (node->val <= val) {
      node->right = prune_bst(node->right, val);
    } else {
      node->left = prune_bst(node->left, val);
    }
    return node;
  }
}