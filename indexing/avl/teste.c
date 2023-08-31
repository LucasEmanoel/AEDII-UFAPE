#include <stdio.h>
#include <stdio_ext.h>
#include <stdlib.h>
#include "teste.h"
#include <string.h>

tree rsd(tree node) {
	tree p, u, t1, t2, t3;
	p = node;
	u = node->left;

	t1 = p->left;
	t2 = u->right;
	t3 = u->left;

	p->left = t2;
	u->right = p;

	if (u->fb == -1) {
		p->fb = 0;
		u->fb = 0;
	} else {
		p->fb = -1;
		u->fb = 1;
	}

	return u;
}
tree rse(tree node) {

	tree p, u, t1, t2, t3;
	p = node;
	u = node->right;

	t1 = p->left;
	t2 = u->left;
	t3 = u->right;

	p->right = t2;
	u->left = p;

	if (u->fb == 1) {
		p->fb = 0;
		u->fb = 0;
	} else {
		// duvidas - caso +2 0 entendi!!
		p->fb = 1;
		u->fb = -1;
	}

	return u;
}
tree rdd(tree node) {
	tree p, u, v, t1, t2, t3, t4;

	p = node;
	u = node->left;
	v = u->right;

	t1 = u->left;
	t2 = v->left;
	t3 = v->right;
	t4 = p->right;

	v->right = p;
	u->right = t2;
	v->left = u;
	p->left = t3;

	switch (v->fb) {
    case -1:
			p->fb = 1;
			u->fb = 0;
			v->fb = 0;
      break;
    case 0:
      p->fb = 0;
      u->fb = 0;
      break;
    case 1:
			p->fb = 0;
			v->fb = 0;
			u->fb = -1;
      break;
  }

	return v;
}
tree rde(tree node) {
	tree p, u, v, t1, t2, t3, t4;

	p = node;
	u = node->right;
	v = u->left;

	//t1 = p->left;
	t2 = v->left;
	t3 = v->right;
	//t4 = u->right;

	v->left = p;
	p->right = t2; 
	v->right = u;
	u->left = t3;
	
	switch (v->fb) {
    case -1:
			v->fb = 0;
			p->fb = 0;
			u->fb = 1;
      break;
    case 0:
      p->fb = 0;
      u->fb = 0;
      break;
    case 1:
			v->fb = 0;
			p->fb = -1;
			u->fb = 0;
      break;
	}
	return v;
}
tree rotation(tree node) {
	if (node->fb > 0) {
		switch (node->right->fb) {
      case 0: 
				return rse(node);
        break;
      case 1:
				//printf("node atual [ val =%d, fb =%d] | rotation rse,node right [ val =%d, fb =%d]\n",node->val, node->fb, node->right->val, node->right->fb);
        return rse(node);
        break;
      case -1:
				//printf("node atual [ val =%d, fb =%d] | rotation rde,node right [ val =%d, fb =%d]\n",node->val, node->fb, node->right->val, node->right->fb);
        return rde(node);
        break;
      }
	} else {
		switch (node->left->fb) {
      case 0:
				return rsd(node);
        break;
      case 1:
				//printf("node atual [ val =%d, fb =%d] | rotation rdd,node left [ val =%d, fb =%d]\n",node->val, node->fb, node->left->val, node->left->fb);
        return rdd(node);
        break;
      case -1:
				//printf("node atual [ val =%d, fb =%d] | rotation rsd,node left [ val =%d, fb =%d]\n",node->val, node->fb, node->left->val, node->left->fb);
        return rsd(node);
        break;
      }
	}
	return node;
}
//
void inicializar(tree *raiz) {
	*raiz = NULL;
}
//
int inicializarTabela(tabela *tab, int * grown) {
	inicializar(&tab->indices);
	tab->arquivo_dados = NULL;

	tab->arquivo_dados = fopen("dados.txt", "a+b");
	tab->indices = carregar_arquivo("indices.txt", tab->indices, grown);

	if(tab->arquivo_dados != NULL)
		return 1;
	else
		return 0;
}
//
void finalizar (tabela *tab) {
	fclose(tab->arquivo_dados);
	salvar_arquivo("indices.txt", tab->indices);
}
//
void adicionarLivro(tabela *tab, dado *livro, int * grown){
	if(tab->arquivo_dados != NULL) {
			
			tipo_dado * novo = (tipo_dado *) malloc(sizeof(tipo_dado));
			novo->chave = livro->codigo;

			fseek(tab->arquivo_dados, 0L, SEEK_END);
			novo->indice = ftell(tab->arquivo_dados);

			fwrite(livro, sizeof(dado), 1, tab->arquivo_dados);
			
			tab->indices = adicionar(tab->indices, novo, grown);
			
	}
}
//
tree adicionar (tree node, tipo_dado *valor, int *grown) {
	if (node == NULL) {
		
		tree new_node = (tree) malloc(sizeof(struct no));
		new_node->left = NULL;
		new_node->right = NULL;
		new_node->fb = 0;
		new_node->val = valor;
		*grown = 1;
		return new_node;
	} else {
		if (node->val->chave <= valor->chave) {
			node->right = adicionar(node->right, valor, grown);

			if (*grown) {
				switch (node->fb) {
				case 0:
					node->fb = 1;
					*grown = 1;
					break;
				case 1:
					*grown = 0;
					return rotation(node);
					break;
				case -1:
					node->fb = 0;
					*grown = 0;
					break;
				}
			}
			// simétrico
		} else {
			node->left = adicionar(node->left, valor, grown);

			if (*grown) {
				switch (node->fb) {
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
					return rotation(node);
					break;
				}
			}
		}

		return node;
	}
}
//
int altura(tree raiz) {
	if(raiz == NULL) {
		return 0;
	}
	return 1 + maior(altura(raiz->right), altura(raiz->left));
}
//
no * procurarLivro(tabela *tab, int chave) {
    if(tab->arquivo_dados != NULL) {
			no *temp;
			temp = tab->indices;
			while(temp!=NULL){
					if(temp->val->chave == chave) {
							dado * encontrado = (dado*) malloc(sizeof(dado));
							fseek(tab->arquivo_dados, temp->val->indice, SEEK_SET);
							
							fread(encontrado, sizeof(dado), 1, tab->arquivo_dados);
							return temp;
					} else {
							if(chave > temp->val->chave)
									temp = temp->right;
							else
									temp = temp->left;                
					}
			}
    }
    return NULL;
}
//
int maior(int a, int b) {
	if(a > b)
		return a;
	else
		return b;
}
//
tipo_dado * maior_elemento(tree raiz) {
	if(raiz == NULL)
			return NULL;
	if(raiz->right == NULL)
			return raiz->val;
	else
			return maior_elemento(raiz->right);
}
//
tipo_dado * menor_elemento(tree raiz) {
	if(raiz == NULL)
			return NULL;
	if(raiz->left == NULL)
			return raiz->val;
	else
			return maior_elemento(raiz->left);
}
//
void pre_order(tree raiz, tabela *tab) {
	if(raiz != NULL) {
		imprimir_elemento(raiz, tab);
		pre_order(raiz->left, tab);
		pre_order(raiz->right, tab);
	}
}

void pos_order(tree raiz, tabela *tab) {
	if(raiz != NULL) {
		pos_order(raiz->left, tab);
		pos_order(raiz->right, tab);
		imprimir_elemento(raiz, tab);
	}
}

void in_order(tree raiz, tabela *tab) {
	if(raiz != NULL) {
		in_order(raiz->left, tab);
		imprimir_elemento(raiz, tab);
		in_order(raiz->right, tab);
	}
}

tree remover (int valor, tree raiz) {
	if(raiz == NULL) 
		return NULL;
	
	if(raiz->val->chave == valor) {		
		if(raiz->left == NULL) {
			return raiz->right;
		}
		if(raiz->right == NULL) {
			return raiz->left;
		}
		raiz->val = maior_elemento(raiz->left);
		raiz->left = remover(raiz->val->chave, raiz->left);
		return raiz;
	}	
	if(valor > raiz->val->chave) {
			raiz->right = remover(valor, raiz->right);
	} else {
			raiz->left = remover(valor, raiz->left);
	}
	return raiz;
}
//
dado * ler_dados() {
	dado *novo = (dado *) malloc(sizeof(dado));

	getchar();
	printf("Titulo: ");
	fgets(novo->titulo, 80,  stdin);
	tirar_enter(novo->titulo);

	printf("Autor: ");
	fgets(novo->autor, 50,  stdin);
	tirar_enter(novo->autor);

	printf("Isbn: ");
	fgets(novo->isbn, 20,  stdin);
	tirar_enter(novo->isbn);

	printf("Codigo: ");
	scanf("%d", &novo->codigo);
	
	return novo;
}
//
void tirar_enter(char *string) {
	string[strlen(string) -1] = '\0';
}
//
void salvar_arquivo(char *nome, tree a) {
	FILE *arq;
	arq = fopen(nome, "wb");
	if(arq != NULL) {
		salvar_auxiliar(a, arq);
		fclose(arq);
	}
}
//
void salvar_auxiliar(tree raiz, FILE *arq){
	if(raiz != NULL) {
		fwrite(raiz->val, sizeof(tipo_dado), 1, arq);
		salvar_auxiliar(raiz->left, arq);
		salvar_auxiliar(raiz->right, arq);
	}
}
//
tree carregar_arquivo(char *nome, tree a, int * grown) {
	FILE *arq;
	arq = fopen(nome, "rb");
	tipo_dado * temp;
	if(arq != NULL) {
		temp = (tipo_dado *) malloc(sizeof(tipo_dado));
		while(fread(temp, sizeof(tipo_dado), 1, arq)) {
			
			a = adicionar(a, temp, grown);			
			temp = (tipo_dado *) malloc(sizeof(tipo_dado));

		}
		fclose(arq);

	}
	return a;
}
//
void imprimir_elemento(tree raiz, tabela * tab) {
	dado * temp = (dado *) malloc (sizeof(dado));
  temp->codigo = 1000;
  printf("indice: %d\n", raiz->val->indice);

  fseek(tab->arquivo_dados, raiz->val->indice, SEEK_SET);
	int r = fread(temp, sizeof(dado), 1, tab->arquivo_dados);

	printf("[%d, %d, %s, %s, %s ]\n", raiz->val->chave,r, temp->titulo, temp->autor, temp->isbn);
	free(temp);
}

