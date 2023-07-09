#include "rb.h" //importa o arquivo de declaracoes
#include <stdio.h>
#include <stdlib.h>

tree no_null;

void initialize(tree *no){
	*no = NULL;

	no_null = (tree) malloc(sizeof(struct no));
	no_null->cor = DUPLO_PRETO;
	no_null->val = 0;
	no_null->left = NULL;
	no_null->right = NULL;
}


void insert_rb(tree *node, int val);
void remove_avl(tree *node, int val);
