#include <stdio.h>
#include <stdlib.h>
#include "rb.h"

tree no_null;

void inicializar(tree *raiz)
{
	*raiz = NULL;
	no_null = (tree)malloc(sizeof(struct no));
	no_null->cor = DUPLO_PRETO;
	no_null->val = 0;
	no_null->left = NULL;
	no_null->right = NULL;
}

void adicionar(int valor, tree *raiz)
{
	tree posicao, pai, novo;
	posicao = *raiz;
	pai = NULL;

	while (posicao != NULL)
	{
		pai = posicao;
		if (valor > posicao->val)
			posicao = posicao->right;
		else
			posicao = posicao->left;
	}

	novo = (tree)malloc(sizeof(struct no));
	novo->val = valor;
	novo->left = NULL;
	novo->right = NULL;
	novo->pai = pai;
	novo->cor = VERMELHO;

	if (eh_raiz(novo))
		*raiz = novo;
	else
	{
		if (valor > pai->val)
			pai->right = novo;
		else
			pai->left = novo;
	}

	ajustar(raiz, novo);
}

void ajustar(tree *raiz, tree elemento)
{
	while (cor(elemento->pai) == VERMELHO && cor(elemento) == VERMELHO)
	{
		if (cor(tio(elemento)) == VERMELHO)
		{
			tio(elemento)->cor = PRETO;
			elemento->pai->cor = PRETO;
			elemento->pai->pai->cor = VERMELHO;
			elemento = elemento->pai->pai;
			continue;
		}
		if (eh_filho_esquerdo(elemento) && eh_filho_esquerdo(elemento->pai))
		{
			rotacao_simples_direita(raiz, elemento->pai->pai);
			elemento->pai->cor = PRETO;
			elemento->pai->right->cor = VERMELHO;
			continue;
		}
		// caso 2b: rotação simples esquerda
		if (eh_filho_direito(elemento) && eh_filho_direito(elemento->pai))
		{
			rotacao_simples_esquerda(raiz, elemento->pai->pai);
			//atualizar cores
			continue;
		}
		// caso 3a: rotação dupla direita
		if (eh_filho_direito(elemento) && eh_filho_esquerdo(elemento->pai))
		{
			rotacao_dupla_direita(raiz, elemento->pai->pai);
			continue;
		}
		// caso 3b: rotação dupla esquerda
		if (eh_filho_esquerdo(elemento) && eh_filho_direito(elemento->pai))
		{
			rotacao_dupla_esquerda(raiz, elemento->pai->pai);
			continue;
		}
	}
	(*raiz)->cor = PRETO;
}

void rotacao_simples_direita(tree *raiz, tree pivo) {
	tree u, t1;
	u = pivo->left;
	t1 = u->right;

	int posicao_pivo_left = eh_filho_esquerdo(pivo);

	pivo->left = t1;
	if (t1 != NULL)
		t1->pai = pivo;

	u->right = pivo;

	u->pai = pivo->pai;
	pivo->pai = u;

	if (eh_raiz(u))
		*raiz = u;
	else
	{
		if (posicao_pivo_left)
			u->pai->left = u;
		else
			u->pai->right = u;
	}
}

void rotacao_simples_esquerda(tree *raiz, tree pivo) {
	tree u, t1;

	u = pivo->right;
	t1 = u->left;

	int posicao_pivo_right = eh_filho_direito(pivo);

	pivo->right = t1;
	if(t1 != NULL)
		t1->pai = pivo;

	u->left = pivo;
	u->pai = pivo->pai;
	pivo->pai = u;

	if(eh_raiz(u)){
		*raiz = u;
	}	else {
		if(posicao_pivo_right){
			u->pai->right = u;
		} else {
			u->pai->left = u;
		}
	}
}
void rotacao_dupla_direita(tree *raiz, tree pivo) {
	tree u, v, t2, t3;

	u = pivo->left;
	v = u->right;
	t2 = v->left;
	t3 = v->right;

	int posicao_pivo_left = eh_filho_esquerdo(pivo);

	pivo->left = t3;
	if(t3 != NULL){
		t3->pai = pivo;
	}
	u->right = t2;
	if(t2 != NULL){
		t2->pai = u;
	}

	v->left = u;
	u->pai = v;
	v->right = pivo;
	pivo->pai = v;

	if(eh_raiz(v)){
		*raiz = v;
	}	else {
		if(posicao_pivo_left){
			v->pai->left = v;
		} else {
			v->pai->right = v;
		}
	}
}
void rotacao_dupla_esquerda(tree *raiz, tree pivo) {
	tree u, v, t2, t3;

	u = pivo->right;
	v = u->left;
	t2 = v->left;
	t3 = v->right;

	int posicao_pivo_right = eh_filho_direito(pivo);

	pivo->right = t2;
	if(t2 != NULL){
		t2->pai = pivo;
	}
	u->left = t3;
	if(t3 != NULL){
		t3->pai = u;
	}

	v->left = pivo;
	pivo->pai = v;
	v->right = u;
	u->pai = v;

	if(eh_raiz(v)){
		*raiz = v;
	}	else {
		if(posicao_pivo_right){
			v->pai->right = v;
		} else {
			v->pai->left = v;
		}
	}
}
enum cor cor(tree elemento) {
	enum cor c;
	if (elemento == NULL)
		return PRETO;
	else
		return elemento->cor;
	return c;
}

int eh_raiz(tree elemento) {
	return (elemento->pai == NULL);
}

int eh_filho_esquerdo(tree elemento) {
	return (elemento->pai != NULL && elemento == elemento->pai->left);
}
int eh_filho_direito(tree no){
	return (no->pai != NULL && no == no->pai->right);
}
tree tio(tree elemento)
{
	return irmao(elemento->pai);
}

tree irmao(tree elemento)
{
	if (eh_filho_esquerdo(elemento))
		return elemento->pai->right;
	else
		return elemento->pai->left;
}

void imprimir(tree raiz)
{
	printf("(");
	if (raiz != NULL)
	{
		imprimir_elemento(raiz);
		imprimir(raiz->left);
		imprimir(raiz->right);
	}
	printf(")");
}

int altura(tree raiz)
{
	if (raiz == NULL)
	{
		return 0;
	}
	return 1 + maior(altura(raiz->right), altura(raiz->left));
}

int maior(int a, int b)
{
	if (a > b)
		return a;
	else
		return b;
}

int maior_elemento(tree raiz)
{
	if (raiz == NULL)
		return -1;
	if (raiz->right == NULL)
		return raiz->val;
	else
		return maior_elemento(raiz->right);
}

int menor_elemento(tree raiz)
{
	if (raiz == NULL)
		return -1;
	if (raiz->left == NULL)
		return raiz->val;
	else
		return maior_elemento(raiz->left);
}

void pre_order(tree raiz)
{
	if (raiz != NULL)
	{
		imprimir_elemento(raiz);
		pre_order(raiz->left);
		pre_order(raiz->right);
	}
}

void pos_order(tree raiz)
{
	if (raiz != NULL)
	{
		pos_order(raiz->left);
		pos_order(raiz->right);
		imprimir_elemento(raiz);
	}
}

void in_order(tree raiz)
{
	if (raiz != NULL)
	{
		in_order(raiz->left);
		imprimir_elemento(raiz);
		in_order(raiz->right);
	}
}

void imprimir_elemento(tree raiz)
{
	switch (raiz->cor)
	{
	case PRETO:
		printf("\x1b[30m[%d]\x1b[0m", raiz->val);
		break;
	case VERMELHO:
		printf("\x1b[31m[%d]\x1b[0m", raiz->val);
		break;
	case DUPLO_PRETO:
		printf("\x1b[32m[%d]\x1b[0m", raiz->val);
		break;
	}
}

void remover(int valor, tree *raiz)
{
	tree posicao;
	posicao = *raiz;

	while (posicao != NULL)
	{
		if (valor == posicao->val)
		{
			if (posicao->left != NULL && posicao->right != NULL)
			{
				posicao->val = maior_elemento(posicao->left);
				remover(posicao->val, &(posicao->left));
				break;
			}

			if (posicao->left == NULL && posicao->right != NULL)
			{
				posicao->right->cor = PRETO;
				posicao->right->pai = posicao->pai;

				if (eh_raiz(posicao))
				{
					*raiz = posicao->right;
				}
				else
				{
					if (eh_filho_esquerdo(posicao))
					{
						posicao->pai->left = posicao->right;
					}
					else
					{
						posicao->pai->right = posicao->right;
					}
				}
				free(posicao);
				break;
			}

			// O elemento possui apenas um filho (esquerdo)
			if ()
			{
			}

			// O elemento não possui filhos
			if (posicao->left == NULL && posicao->right == NULL)
			{
				if (eh_raiz(posicao))
				{
					*raiz = NULL;
					free(posicao);
					break;
				}

				// Remover elemento que não possui filhos e não é raiz
				// Se for vermelho, apenas remove atualizando o ponteiro
				// correspondente do pai
				if (posicao->cor == VERMELHO)
				{
					if (eh_filho_esquerdo(posicao))
						posicao->pai->left = NULL;
					else
						posicao->pai->right = NULL;
					free(posicao);
					break;
				}
				else
				{
					// Se o elemento for preto, substitui pelo duplo preto e depois ajusta a árvore
					no_null->cor = DUPLO_PRETO;
					no_null->pai = posicao->pai;
					if (eh_filho_esquerdo(posicao))
						posicao->pai->left = no_null;
					else
						posicao->pai->right = no_null;
					free(posicao);
					reajustar(raiz, no_null);
					break;
				}
			}
		}
		if (valor > posicao->val)
			posicao = posicao->right;
		else
			posicao = posicao->left;
	}
}

void reajustar(tree *raiz, tree elemento)
{
	if (eh_raiz(elemento))
	{
		elemento->cor = PRETO;
		if (elemento == no_null)
		{
			*raiz = NULL;
		}
		return;
	}

	if (cor(elemento->pai) == PRETO &&
			cor(irmao(elemento)) == VERMELHO &&
			cor(irmao(elemento)->right) == PRETO &&
			cor(irmao(elemento)->left) == PRETO)
	{
		if (eh_filho_esquerdo(elemento))
			rotacao_simples_esquerda(raiz, elemento->pai);
		else
			rotacao_simples_direita(raiz, elemento->pai);

		elemento->pai->pai->cor = PRETO;
		elemento->pai->cor = VERMELHO;

		// Atenção à chamada recursiva do reajustar.
		// O caso 2 não remove o duplo-preto
		reajustar(raiz, elemento);
		return;
	}

	// caso 3
	if ()
	{
		// Verificar e remover o no_null
		// Chamada recursiva para eliminar o duplo preto do elemento P
		//  reajustar(raiz, elemento->pai);
		return;
	}

	// caso 4
	if ()
	{
		// Verificar e remover o no_null
		return;
	}

	// Casos 5 e 6 ficam mais fáceis separando o esquerdo do direito
	// caso 5a
	if ()
	{
		return;
	}

	// caso 5b
	if ()
	{
		return;
	}

	// caso 6a
	if ()
	{
		return;
	}

	// caso 6b
	if ()
	{
		return;
	}
}

void retira_duplo_preto(tree *raiz, tree elemento)
{
	if (elemento == no_null)
		if (eh_filho_esquerdo(elemento))
			elemento->pai->left = NULL;
		else
			elemento->pai->right = NULL;
	else
		elemento->cor = PRETO;
}
