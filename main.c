#include "bst.h"
#include <stdio.h>
#include <stdlib.h>

int main(int argc, char *argv[])
{
  tree bst_tree;
  int option, val;

  bst_tree = NULL;

  while (1) {
    scanf("%d", &option);
    switch (option) {
    case 1:
      scanf("%d", &val);
      bst_tree = add_bst(bst_tree ,val);
      break;
    case 2:
      printf("2- ");
      pre_order_bst(bst_tree);
      printf("\n");
      break;
    case 3:
      printf("3- ");
      in_order_bst(bst_tree);
      printf("\n");
      break;
    case 4:
      printf("4- ");
      pos_order_bst(bst_tree);
      printf("\n");
      break;
    case 5:
      printf("5- ");
      reserve_bst(bst_tree);
      printf("\n");
      break;
    case 6:
      printf("6- ");
      printf("%d \n", qtd_primos_bst(bst_tree));
      break;
    case 7:
      printf("7- ");
      scanf("%d", &val);
      printf("%d \n", sucessor_bst(bst_tree, -1, val));
      break;
    case 8:
      printf("8- ");
      scanf("%d", &val);
      caminho_bst(bst_tree, val);
      printf("\n");
      break;
    case 9:
      printf("9- ");
      scanf("%d", &val);
      remove_bst(bst_tree, val);
      printf("\n");
      break;
    case 10:
      printf("10- ");
      printf("%d \n", somatorio_bst(bst_tree));
      break;
    case 11:
      printf("11- ");
      scanf("%d", &val);
      podar_bst(bst_tree, val);
      printf("\n");
      break;
    case 12:
      printf("12- ");
      scanf("%d", &val);
      reajuste_bst(bst_tree, val);
      printf("\n");
      break;
    case 13:
      printf("13- ");
      scanf("%d", &val);
      printf("%d \n", existe_bst(bst_tree, val));
      break;
    case 14:
      printf("14- ");
      scanf("%d", &val);
      descendentes_bst(bst_tree, val);
      printf("\n");
      break;
    case 15:
      printf("15- ");
      scanf("%d", &val);
      printf("%d \n", altura_bst(bst_tree));
      break;
    case 99:
      exit(0);
      break;
    }
  }
}