#include "bst.h"
#include <stdio.h>
#include <stdlib.h>

int main(int argc, char *argv[])
{
  tree bst_tree;
  int option, aux, val;

  bst_tree = NULL;

  while (1) {
    scanf("%d", &option);
    switch (option)
    {
    case 1:
      scanf("%d", &aux);
      bst_tree = add_bst(bst_tree ,aux);
      break;
    case 2:
      pre_order_bst(bst_tree);
      printf(" -> 2 \n");
      break;
    case 3:
      in_order_bst(bst_tree);
      printf(" -> 3 \n");
      break;
    case 4:
      pos_order_bst(bst_tree);
      printf(" -> 4 \n");
      break;
    case 5:
      reserve_bst(bst_tree);
      printf("- > 5\n");
      break;
    case 6:
      printf("6 -> Quantidade de Numeros Primos: %d", qtd_primos_bst(bst_tree));printf("6 -> Quantidade de Numeros Primos: %d", qtd_primos_bst(bst_tree));
      printf("\n");
      break;
    case 7:
      scanf("%d", &val);
      printf("7 -> Sucessor: %d", sucessor_bst(bst_tree, val));
      printf("\n");
    case 8:
      scanf("%d", &val);
      caminho_bst(bst_tree, val);
      printf("---> 8 caminho \n");
      break;
    case 9:
      scanf("%d", &val);
      remover_bst(bst_tree, val);
      pre_order_bst(bst_tree);
      printf("---> remover 9 \n");
      break;
    case 10:
      printf("Soma Total: %d", somatorio_bst(bst_tree));
      printf("\n");
      break;
    case 11:
      scanf("%d", &val);
      podar_bst(bst_tree, val);
      pre_order_bst(bst_tree);
      printf("---> podar \n");
      break;
    case 12:
      scanf("%d", &val);
      reajuste_bst(bst_tree, val);
      pre_order_bst(bst_tree);
      printf("---->30 porcento \n");
      break;
    case 13:
      scanf("%d", &val);
      printf("%d Existe: %d", val, existe_bst(bst_tree, val));
      printf("\n");
      break;
    case 14:
      scanf("%d", &val);
      descendentes_bst(bst_tree, val);
      printf("\n");
      break;
    case 15:
      scanf("%d", &val);
      int height = altura_bst(bst_tree);
      printf("%d \n", height);
      break;
    case 99:
      exit(0);
    }
  }
}