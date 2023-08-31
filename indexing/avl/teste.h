#ifndef TESTE_H
#define TESTE_H

typedef struct livro {
	char titulo[81];
	char autor[51];
	char isbn[21];
	int codigo;
} dado;

typedef struct indice {
	int chave;
	int indice; //posição no arquivo do primeiro byte do registro
} tipo_dado;

typedef struct no{
  tipo_dado * val;
  int fb;
  struct no *left, *right;
} no;

typedef no *tree;

typedef struct tabela {
	FILE *arquivo_dados;
	tree indices;
} tabela;


int inicializarTabela(tabela *tab, int * grown) ;
void finalizar (tabela *tab);
void adicionarLivro(tabela *tab, dado *livro, int *grown);
	

void inicializar(tree *raiz);
tree adicionar (tree node, tipo_dado *valor, int *grown);

int altura(tree raiz);
int maior(int a, int b);
tipo_dado * maior_elemento(tree raiz);
tipo_dado * menor_elemento(tree raiz);
void pre_order(tree raiz, tabela *tab);
void pos_order(tree raiz, tabela *tab);
void in_order(tree raiz, tabela *tab);
tree remover (int valor, tree raiz);
void imprimir_elemento(tree raiz, tabela *tab);
dado * ler_dados();
void tirar_enter(char *string);

no * procurarLivro(tabela *tab, int chave) ; 

void salvar_arquivo(char *nome, tree a);
void salvar_auxiliar(tree raiz, FILE *arq);
tree carregar_arquivo(char *nome, tree a, int * grown);




#endif

