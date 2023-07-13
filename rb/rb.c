#include <stdio.h>
#include <stdlib.h>
#include "rb.h"

tree no_null;

void inicializar(tree *no) {
	*no = NULL;
	no_null = (tree) malloc(sizeof(struct no));
	no_null->cor = DUPLO_PRETO;
	no_null->val = 0;
	no_null->left = NULL;
	no_null->right = NULL;
}

void adicionar(int valor, tree *no) {
	tree posicao, pai, novo;
	posicao = *no;
	pai = NULL;

	while (posicao != NULL) {
		pai = posicao;
		if (valor > posicao->val)
			posicao = posicao->right;
		else
			posicao = posicao->left;
	}

	novo = (tree) malloc(sizeof(struct no));
	novo->val = valor;
	novo->left = NULL;
	novo->right = NULL;
	novo->pai = pai;
	novo->cor = VERMELHO;

	if (eh_raiz(novo))
		*no = novo;
	else {
		if (valor > pai->val)
			pai->right = novo;
		else
			pai->left = novo;
	}

	ajustar(no, novo);
}

void ajustar(tree *no, tree elemento) {
	while (cor(elemento->pai) == VERMELHO && cor(elemento) == VERMELHO) {
		if (cor(tio(elemento)) == VERMELHO) {
			tio(elemento)->cor = PRETO;
			elemento->pai->cor = PRETO;
			elemento->pai->pai->cor = VERMELHO;
			elemento = elemento->pai->pai;
			continue;
		}
		if (eh_filho_esquerdo(elemento) && eh_filho_esquerdo(elemento->pai)) {
			rotacao_simples_direita(no, elemento->pai->pai);
			elemento->pai->cor = PRETO;
			elemento->pai->right->cor = VERMELHO;
			continue;
		}
		// caso 2b: rotação simples esquerda
		if (eh_filho_direito(elemento) && eh_filho_direito(elemento->pai)) {
			rotacao_simples_esquerda(no, elemento->pai->pai);
			elemento->pai->cor = PRETO;
			elemento->pai->left->cor = VERMELHO;
			continue;
		}
		// caso 3a: rotação dupla direita
		if (eh_filho_direito(elemento) && eh_filho_esquerdo(elemento->pai)) {
			rotacao_simples_esquerda(no, elemento->pai);
			rotacao_simples_direita(no, elemento->pai);
			//rotacao_dupla_direita(no, elemento->pai->pai);
			elemento->cor = PRETO;
			elemento->right->cor = VERMELHO;
			continue;
		}
		// caso 3b: rotação dupla esquerda
		if (eh_filho_esquerdo(elemento) && eh_filho_direito(elemento->pai)) {
			rotacao_simples_direita(no, elemento->pai);
			rotacao_simples_esquerda(no, elemento->pai);
			//rotacao_dupla_esquerda(no, elemento->pai->pai);
			elemento->cor = PRETO;
			elemento->left->cor = VERMELHO;
			continue;
		}
	}
	(*no)->cor = PRETO;
}

void rotacao_simples_direita(tree *no, tree pivo) {
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
		*no = u;
	else {
		if (posicao_pivo_left)
			u->pai->left = u;
		else
			u->pai->right = u;
	}
}

void rotacao_simples_esquerda(tree *no, tree pivo) {
	tree u, t1;

	u = pivo->right;
	t1 = u->left;

	int posicao_pivo_right = eh_filho_direito(pivo);

	pivo->right = t1;
	if (t1 != NULL)
		t1->pai = pivo;

	u->left = pivo;
	u->pai = pivo->pai;
	pivo->pai = u;

	if (eh_raiz(u)) {
		*no = u;
	} else {
		if (posicao_pivo_right) {
			u->pai->right = u;
		} else {
			u->pai->left = u;
		}
	}
}
void rotacao_dupla_direita(tree *no, tree pivo) {
	tree u, v, t2, t3;

	u = pivo->left;
	v = u->right;
	t2 = v->left;
	t3 = v->right;

	int posicao_pivo_left = eh_filho_esquerdo(pivo);

	pivo->left = t3;
	if (t3 != NULL) {
		t3->pai = pivo;
	}
	u->right = t2;
	if (t2 != NULL) {
		t2->pai = u;
	}

	v->left = u;
	u->pai = v;
	v->right = pivo;
	pivo->pai = v;

	if (eh_raiz(v)) {
		*no = v;
	} else {
		if (posicao_pivo_left) {
			v->pai->left = v;
		} else {
			v->pai->right = v;
		}
	}
}
void rotacao_dupla_esquerda(tree *no, tree pivo) {
	tree u, v, t2, t3;

	u = pivo->right;
	v = u->left;
	t2 = v->left;
	t3 = v->right;

	int posicao_pivo_right = eh_filho_direito(pivo);

	pivo->right = t2;
	if (t2 != NULL) {
		t2->pai = pivo;
	}
	u->left = t3;
	if (t3 != NULL) {
		t3->pai = u;
	}

	v->left = pivo;
	pivo->pai = v;
	v->right = u;
	u->pai = v;

	if (eh_raiz(v)) {
		*no = v;
	} else {
		if (posicao_pivo_right) {
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
int eh_filho_direito(tree no) {
	return (no->pai != NULL && no == no->pai->right);
}
tree tio(tree elemento) {
	return irmao(elemento->pai);
}

tree irmao(tree elemento) {
	if (eh_filho_esquerdo(elemento))
		return elemento->pai->right;
	else
		return elemento->pai->left;
}

void imprimir(tree no) {
	printf("(");
	if (no != NULL) {
		imprimir_elemento(no);
		imprimir(no->left);
		imprimir(no->right);
	}
	printf(")");
}

int altura(tree no) {
	if (no == NULL) {
		return 0;
	}
	return 1 + maior(altura(no->right), altura(no->left));
}

int maior(int a, int b) {
	if (a > b)
		return a;
	else
		return b;
}

int maior_elemento(tree no) {
	if (no == NULL)
		return -1;
	if (no->right == NULL)
		return no->val;
	else
		return maior_elemento(no->right);
}

int menor_elemento(tree no) {
	if (no == NULL)
		return -1;
	if (no->left == NULL)
		return no->val;
	else
		return maior_elemento(no->left);
}

void pre_order(tree no) {
	if (no != NULL) {
		imprimir_elemento(no);
		pre_order(no->left);
		pre_order(no->right);
	}
}

void pos_order(tree no) {
	if (no != NULL) {
		pos_order(no->left);
		pos_order(no->right);
		imprimir_elemento(no);
	}
}

void in_order(tree no) {
	if (no != NULL) {
		in_order(no->left);
		imprimir_elemento(no);
		in_order(no->right);
	}
}

void imprimir_elemento(tree no) {
	switch (no->cor) {
	case PRETO:
		printf("\x1b[30m[%d]\x1b[0m", no->val);
		break;
	case VERMELHO:
		printf("\x1b[31m[%d]\x1b[0m", no->val);
		break;
	case DUPLO_PRETO:
		printf("\x1b[32m[%d]\x1b[0m", no->val);
		break;
	}
}

void remover(int valor, tree *no) {
	tree posicao;
	posicao = *no;

	while (posicao != NULL) {
		if (valor == posicao->val) {
			if (posicao->left != NULL && posicao->right != NULL) {
				posicao->val = maior_elemento(posicao->left);
				remover(posicao->val, &(posicao->left));
				break;
			}
			
			// O elemento possui apenas um filho (direito)
			if (posicao->left == NULL && posicao->right != NULL) {
				posicao->right->cor = PRETO;
				posicao->right->pai = posicao->pai;

				if (eh_raiz(posicao)) {
					*no = posicao->right;
				} else {
					if (eh_filho_esquerdo(posicao)) {
						posicao->pai->left = posicao->right;
					} else {
						posicao->pai->right = posicao->right;
					}
				}
				free(posicao);
				break;
			}

			// O elemento possui apenas um filho (esquerdo)
			if (posicao->left != NULL && posicao->right == NULL) {
				posicao->left->cor = PRETO;
				posicao->left->pai = posicao->pai;

				if (eh_raiz(posicao)) {
					*no = posicao->left;
				} else {
					if (eh_filho_direito(posicao)) {
						posicao->pai->right = posicao->left;
					} else {
						posicao->pai->left = posicao->left;
					}
				}
				free(posicao);
				break;
			}

			// O elemento não possui filhos
			if (posicao->left == NULL && posicao->right == NULL) {
				if (eh_raiz(posicao)) {
					*no = NULL;
					free(posicao);
					break;
				}
				if (posicao->cor == VERMELHO) {
					if (eh_filho_esquerdo(posicao))
						posicao->pai->left = NULL;
					else
						posicao->pai->right = NULL;
					free(posicao);
					break;
				} else {
					// Se o elemento for preto, substitui pelo duplo preto e depois ajusta a árvore
					no_null->cor = DUPLO_PRETO;
					no_null->pai = posicao->pai;
					if (eh_filho_esquerdo(posicao))
						posicao->pai->left = no_null;
					else
						posicao->pai->right = no_null;
					free(posicao);
					reajustar(no, no_null);
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

void reajustar(tree *no, tree elemento) {
	if (eh_raiz(elemento)) {
		elemento->cor = PRETO;
		if (elemento == no_null) {
			*no = NULL;
		}
		return;
	}
	//case 2
	if (cor(elemento->pai) == PRETO && cor(irmao(elemento)) == VERMELHO
			&& cor(irmao(elemento)->right) == PRETO
			&& cor(irmao(elemento)->left) == PRETO) {
				printf("caso 2\n");
		if (eh_filho_esquerdo(elemento))
			rotacao_simples_esquerda(no, elemento->pai);
		else
			rotacao_simples_direita(no, elemento->pai);

		elemento->pai->pai->cor = PRETO;
		elemento->pai->cor = VERMELHO;

		// Atenção à chamada recursiva do reajustar.
		// O caso 2 não remove o duplo-preto
		reajustar(no, elemento);
		return;
	}

	// caso 3
	if (cor(elemento->pai) == PRETO 
			&& cor(irmao(elemento)) == PRETO
			&& cor(irmao(elemento)->right) == PRETO
			&& cor(irmao(elemento)->left) == PRETO) {
				printf("caso 3\n");
		retira_duplo_preto(no, elemento);
		elemento->pai->cor = DUPLO_PRETO;
		irmao(elemento)->cor = VERMELHO;
		// Verificar e remover o no_null
		// Chamada recursiva para eliminar o duplo preto do elemento P
		reajustar(no, elemento->pai);
		return;
	}

	// caso 4
	if (cor(elemento->pai) == VERMELHO 
			&& cor(irmao(elemento)) == PRETO
			&& cor(irmao(elemento)->right) == PRETO
			&& cor(irmao(elemento)->left) == PRETO) {
				printf("caso 4\n");
		// Verificar e remover o no_null
		retira_duplo_preto(no, elemento);
		elemento->pai->cor = PRETO;
		irmao(elemento)->cor = VERMELHO;
		return;
	}

	// Casos 5 e 6 ficam mais fáceis separando o esquerdo do direito
	// caso 5a
	if (eh_filho_esquerdo(elemento) 
			&& cor(irmao(elemento)) == PRETO
			&& cor(irmao(elemento)->right) == PRETO
			&& cor(irmao(elemento)->left) == VERMELHO) {
				printf("caso 5a\n");
		rotacao_simples_direita(no, irmao(elemento));
		irmao(elemento)->cor = PRETO;
		irmao(elemento)->right->cor = VERMELHO;
		reajustar(no, elemento);
		return;
	}

	// caso 5b
	if (eh_filho_direito(elemento) 
			&& cor(irmao(elemento)) == PRETO
			&& cor(irmao(elemento)->left) == PRETO
			&& cor(irmao(elemento)->right) == VERMELHO) {
		printf("caso 5b\n");
		rotacao_simples_esquerda(no, irmao(elemento));
		irmao(elemento)->cor = PRETO;
		irmao(elemento)->left->cor = VERMELHO;
		reajustar(no, elemento);
		return;
	}

	// caso 6a
	if (eh_filho_esquerdo(elemento) && cor(irmao(elemento)) == PRETO
			&& cor(irmao(elemento)->right) == VERMELHO) {
				printf("caso 6a\n");
		rotacao_simples_esquerda(no, elemento->pai);
		retira_duplo_preto(no, elemento);
		elemento->pai->pai->cor = elemento->pai->cor;
		elemento->pai->cor = PRETO;
		tio(elemento)->cor = PRETO;
		return;
	}

	// caso 6b
	if (eh_filho_direito(elemento) && cor(irmao(elemento)) == PRETO
			&& cor(irmao(elemento)->left) == VERMELHO) {
				printf("caso 6b\n");
		rotacao_simples_direita(no, elemento->pai);
		
		retira_duplo_preto(no, elemento);

		elemento->pai->pai->cor = elemento->pai->cor;
		elemento->pai->cor = PRETO;
		tio(elemento)->cor = PRETO;
		return;
	}
}

void retira_duplo_preto(tree *no, tree elemento) {
	if (elemento == no_null)
		if (eh_filho_esquerdo(elemento))
			elemento->pai->left = NULL;
		else
			elemento->pai->right = NULL;
	else
		elemento->cor = PRETO;
}
