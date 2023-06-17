#include "avl.h" //importa o arquivo de declaracoes
#include <stdio.h>
#include <stdlib.h>

tree insert_avl(tree node, int val, int *grown){
  if (node == NULL) {
    tree new_node = (tree) malloc(sizeof(struct no));
    new_node->left = NULL;
    new_node->right = NULL;
    new_node->fb = 0;
    new_node->val = val;
    *grown = 1;
    return new_node;
  } else {
    if (node->val <= val) {
      node->right = insert_avl(node->right, val);
      
			if(*grown) {
      	switch(node->fb){
					case 0:
						node->fb = 1;
						*grown = 1;
						break;
					case 1:
						*grown = 0;
						#return rotate() -> implements this function.
						break;
					case -1:
						node->fb = 0;
						*grown = 0;
						break;
				}	
      }
    } else {
      node->left = insert_avl(node->left, val);\
			
			if(*grown){
				switch(node->fb) {
					case 0:
						node->fb = -1;
						*grown = -1;
						break;
					case 1:
						node->fb = 0;
						*grown = 0;
						break;
					case -1:
						*grown = 0;
						#return rotate() -> implements this function.
						break;
				}
			}
    }

    return node;
  }
  
}

void pre_order_avl(tree node){
  if (node != NULL) {
    printf("[%d]", node->val);
    pre_order_avl(node->left);
    pre_order_avl(node->right);
  }
}

void in_order_avl(tree node){
  if (node != NULL) {
    in_order_avl(node->left);
    printf("[%d]", node->val);
    in_order_avl(node->right);
  }
}

void pos_order_avl(tree node){
  if (node != NULL) {
    pos_order_avl(node->left);
    pos_order_avl(node->right);
    printf("[%d]", node->val);
  }
}

void reverse_avl(tree node){
  if (node != NULL) {
    reverse_avl(node->right);
    printf("[%d]", node->val);
    reverse_avl(node->left);
  }
}

int isPrime(int num){
  for (int i = 2; i < num; i++){
    if(num % i == 0) return 1; //nao e primo
  }
  return 0; //e primo
}

int sum_prime_numbers_avl(tree no){
  int aux, i;
  if(no != NULL){
    aux = sum_prime_numbers_avl(no->left) + sum_prime_numbers_avl(no->right);
    if (isPrime(no->val) == 0){
      return aux + 1;
    } else {
      return aux;
    } 
  }
}

int successor_avl(tree node, int suc, int val){
  if (node != NULL) {
    if(node->val > val && node->left == NULL){
      return node->val;
    }
    if (node->val <= val) {
      successor_avl(node->right, suc, val);
    } else {
      suc = node->val;
      successor_avl(node->left, suc, val);
    }
  } else {
    return suc;
  }
}

void path_avl(tree node, int val){
  if (node != NULL && node->val != val) {
    printf("[%d]", node->val);
    if(node->val <= val){
      path_avl(node->right, val);
    } else {
      path_avl(node->left, val);
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

tree remove_avl(tree node, int val){
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
      node->left = remove_avl(node->left, val);
      return node;  
    }
  } else { 
    if (node->val <= val) {
      node->right = remove_avl(node->right, val);
    } else {
      node->left = remove_avl(node->left, val);
    }
    return node;
  }
  
}

int sum_all_numbers_avl(tree node){
  int aux;
  if(node != NULL){
    aux = sum_all_numbers_avl(node->left) + sum_all_numbers_avl(node->right);
    return aux + node->val;
  }
}

int exist_avl(tree node, int val){
  if(node != NULL){
    if (node->val == val) {
      return 1;
    }
    if (node->val <= val) {
      exist_avl(node->right, val);
    } else {
      exist_avl(node->left, val);
    }
  } else {
    return 0;
  }
}

int transform_percentage(int num, float porcentagem){
  return num + ( num * (porcentagem / 100));
}

int adjust_percentage_avl(tree node, float porcentagem){
  if (node != NULL) {
    adjust_percentage_avl(node->left, porcentagem);
    adjust_percentage_avl(node->right, porcentagem);
    node->val = transform_percentage(node->val, porcentagem);
  }
}

int height_avl(tree node){
  int left_height, right_height;
  if(node != NULL){
    left_height = height_avl(node->left);
    right_height = height_avl(node->right);

    if(right_height >= left_height){
      return right_height + 1;
    } else {
      return left_height + 1;
    }
  } else {
    return 0;
  }

}

void succession_avl(tree node, int n){
  if(node != NULL){
    if (node->val == n) {
      in_order_avl(node);
    }
    if (node->val <= n) {
      succession_avl(node->right, n);
    } else {
      succession_avl(node->left, n);
    }
  }
}
