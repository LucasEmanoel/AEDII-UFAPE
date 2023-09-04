#ifndef TABLE_H
#define TABLE_H
#include <stdlib.h>
#include <stdio_ext.h>
#include "./avl.h"
#include "./game.h"

typedef struct table {
	FILE * arquivo_dados;
	avl_tree indices;
} table;

int initialize_table(table *tab,  int * grown);
void finalizar (table *tab) ;
void add_game(table *tab, data *livro, int *grown);
data * read_all();
void remove_enter(char *string);
void save_file(char *name, avl_tree a);
void save_aux(avl_tree root, FILE *arq);
avl_tree load_files(char *name, avl_tree a, int * grown);
void print_element(avl_tree raiz, table * tab);
no * search_data(table *tab, int key);
void pre_order(avl_tree node, table * tab);

#endif

