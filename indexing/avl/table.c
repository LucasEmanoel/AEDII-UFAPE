#include "table.h" 
#include "./avl.h"
#include <stdio.h>
#include <string.h>

int initialize_table(table *tab,  int * grown){
  initialize(&tab->indices);
	tab->arquivo_dados = NULL;

	tab->arquivo_dados = fopen("dados.dat", "a+b");
	tab->indices = load_files("indices.dat", tab->indices, grown);

	if(tab->arquivo_dados != NULL)
		return 1;
	else
		return 0;
}

void finalizar (table *tab) {
	fclose(tab->arquivo_dados);
	save_file("indices.dat", tab->indices);
}
void add_game(table *tab, data *livro, int *grown){
	if(tab->arquivo_dados != NULL) {
			type_data * new = (type_data *) malloc(sizeof(type_data));

			new->key = livro->cod;

			fseek(tab->arquivo_dados, 0L, SEEK_END);
			new->index = ftell(tab->arquivo_dados);

			fwrite(livro, sizeof(data), 1, tab->arquivo_dados);
			tab->indices = insert_avl(tab->indices, new, grown);
	}
}

data * read_all(){
  data *new = (data *) malloc(sizeof(data));
	//__fpurge(stdin);
	getchar();

	printf("Title: ");
	fgets(new->title, 62,  stdin);
	remove_enter(new->title);

	printf("Company: ");
	fgets(new->company, 62,  stdin);
	remove_enter(new->company);

	printf("Type: ");
	fgets(new->type, 32, stdin);
	remove_enter(new->type);

	printf("Platform: ");
	fgets(new->platform, 32,  stdin);
	remove_enter(new->platform);

	printf("Codigo: ");
	scanf("%d", &new->cod);

	return new;
}

void remove_enter(char *string){
  string[strlen(string) -1] = '\0';
}

void save_file(char *name, avl_tree a) {
	FILE *arq;
	arq = fopen(name, "wb");
	if(arq != NULL) {
		save_aux(a, arq);
		fclose(arq);
	}
}

void save_aux(avl_tree root, FILE *arq){
	if(root != NULL) {
		fwrite(root->val, sizeof(type_data), 1, arq);
		save_aux(root->left, arq);
		save_aux(root->right, arq);
	}

}

avl_tree load_files(char *name, avl_tree a, int * grown){
	FILE *arq;
	arq = fopen(name, "rb");
	type_data * temp;
	if(arq != NULL) {
		temp = (type_data *) malloc(sizeof(type_data));
		while(fread(temp, sizeof(type_data), 1, arq)) {
			
			a = insert_avl(a, temp, grown);			
			temp = (type_data *) malloc(sizeof(type_data));

		}
		fclose(arq);

	}
	return a;
}

void print_element(avl_tree raiz, table * tab) {
	data * temp = (data *) malloc (sizeof(data));
  temp->cod = 1000;
  printf("index: %d\n", raiz->val->index);

  fseek(tab->arquivo_dados, raiz->val->index, SEEK_SET);
	
	int r = fread(temp, sizeof(data), 1, tab->arquivo_dados);

	printf("[%d, %d, %s, %s, %s, %s] \n", raiz->val->key,r, temp->title, temp->company, temp->type, temp->platform );
	free(temp);
}

no * search_data(table *tab, int key) {
    if(tab->arquivo_dados != NULL) {
			no * temp;
			temp = tab->indices;
			while(temp!=NULL){
					if(temp->val->key == key) {
							data * encontrado = (data*) malloc(sizeof(data));
							fseek(tab->arquivo_dados, temp->val->index, SEEK_SET);
							
							fread(encontrado, sizeof(data), 1, tab->arquivo_dados);
							return temp;
					} else {
							if(key > temp->val->key)
									temp = temp->right;
							else
									temp = temp->left;                
					}
			}
    }
    return NULL;
}

void pre_order(avl_tree node, table * tab) {
	if (node != NULL) {
		print_element(node, tab);
		pre_order(node->left, tab);
		pre_order(node->right, tab);
	}
}