#include <stdio.h>
#include <stdlib.h>
#include "teste.h"

int main(int argc, char * argv[]) {
	tabela tab;
	tree avl;
	int opcao, consulta;
	int controleFB;
	inicializarTabela(&tab, &controleFB);

	while(1) {
		scanf("%d", &opcao);

		switch(opcao) {
				int valor;
				case 1:
						printf("%d\n", altura(tab.indices));
						break;
				case 2:
						adicionarLivro(&tab, ler_dados(), &controleFB);
						break;
				case 3:
						printf("%d\n", maior_elemento(tab.indices)->chave);
						break;
				case 4:
						printf("%d\n", menor_elemento(tab.indices)->chave);
						break;
				case 5:
						pre_order(tab.indices, &tab);
						printf("\n");
						break;
				case 6:
						in_order(tab.indices, &tab);
						printf("\n");
						break;
				case 7:
						pos_order(tab.indices, &tab);
						printf("\n");
						break;

				case 10:
						salvar_arquivo("dados.dat", tab.indices);
						break;
				
				case 11:
						tab.indices = carregar_arquivo("indeces.dat", tab.indices, &controleFB);
						break;
				case 12:
					scanf("%d", &consulta);
					imprimir_elemento(procurarLivro(&tab, consulta), &tab);
					break;
				case 99:
						finalizar(&tab);
						exit(0);
		}
	}
}
