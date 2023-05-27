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
      bst_tree = add(bst_tree ,aux);
      break;
    case 2:
      pre_order(bst_tree);
      printf("\n");
      break;
    case 3:
      in_order(bst_tree);
      printf("\n");
      break;
    case 4:
      pos_order(bst_tree);
      printf("\n");
      break;
    case 5:
      reserve_bst(bst_tree);
      printf("\n");
      break;
    case 6:
      printf("Quantidade de Numeros Primos: %d", qtd_primos_bst(bst_tree));
      printf("\n");
      break;
    case 7:
      scanf("%d", &val);
      sucessor_bst(bst_tree, val);
      printf("\n");
    case 8:
      scanf("%d", &val);
      caminho_bst(bst_tree, val);
      printf("\n");
      break;
    case 9:
      break;
    case 10:
      printf("Soma Total: %d", somatorio(bst_tree));
      printf("\n");
      break;
    case 11:
      break;
    case 12:
      scanf("%d", &val);
      reajuste(bst_tree, val);
      pre_order(bst_tree);
      printf("\n");
      break;
    case 13:
      scanf("%d", &val);
      printf("%d Existe: %d", val, existe(bst_tree, val));
      printf("\n");
      break;
    case 14:
      break;
    case 15:
      break;
    case 0:
      exit(0);
    }
  }
}