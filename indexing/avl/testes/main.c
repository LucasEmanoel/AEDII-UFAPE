#include "avl.h"
#include "table.h"
#include <stdio.h>
#include <stdlib.h>

int main(int argc, char *argv[])
{
  table tab;
  avl_tree tree;
  int option, val, grown, reduce = 1;
  
  int *reduce_aux = &reduce;
  tree = NULL;
  initialize_table(&tab, &grown);
  while (1)
  {
    scanf("%d", &option);
    switch (option)
    {
      int valor;
				case 1:
						printf("%d\n", height(tab.indices));
						break;
				case 2:
						add_game(&tab, read_all(), &grown);
						break;
				case 3:
						printf("%d\n", max_value(tab.indices));
						break;
				case 4:
						printf("%d\n", min_value(tab.indices));
						break;
				case 5:
						pre_order(tab.indices, &tab);
						printf("\n");
						break;
				case 10:
						save_file("dados.dat", tab.arquivo_dados);
						break;
				
				case 11:
						tab.indices = load_files("indices.dat", tab.indices, &grown);
						break;
				case 12:
					scanf("%d", &val);
					print_element(search_data(&tab, val), &tab);
					break;
				case 99:
						finalizar(&tab);
						exit(0);
    }
  }
}