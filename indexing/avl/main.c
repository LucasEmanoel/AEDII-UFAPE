#include "avl.h"
#include "table.h"
#include <stdio.h>
#include <stdlib.h>

int main(int argc, char *argv[])
{
	table tab;
	avl_tree tree;
	int option, val, grown, reduce = 1;
	tree = NULL;
	initialize_table(&tab, &grown);
	while (1)
	{
		scanf("%d", &option);
		switch (option)
		{
			int valor;
		case 1:
			add_game(&tab, read_all(), &grown);
			break;
		case 2:
			scanf("%d", &val);
			print_element(search_data(&tab, val), &tab);
			break;
		case 3:
			pre_order(tab.indices, &tab);
			printf("\n");
			break;
		case 4:
			scanf("%d", &val);
			remove_avl(tab.indices, val, &reduce);
			break;
		case 10:
			tab.indices = load_files("indices.dat", tab.indices, &grown);
			break;
		case 99:
			finalizar(&tab);
			exit(0);
		}
	}
}