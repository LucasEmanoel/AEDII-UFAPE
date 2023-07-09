#include "avl.h"
#include <stdio.h>
#include <stdlib.h>

int main(int argc, char *argv[])
{
  tree avl_tree;
  int option, val, grown, reduce =1;
  int * grown_aux = &grown;
  int * reduce_aux = &reduce;
  avl_tree = NULL;

  while (1) {
    scanf("%d", &option);
    switch (option) {
    case 1:
      scanf("%d", &val);
      avl_tree = insert_avl(avl_tree ,val, grown_aux);
      break;
    case 2:
      pre_order_avl(avl_tree);
      printf("\n");
      break;
    case 3:
      scanf("%d", &val);
      avl_tree = remove_avl(avl_tree, val, reduce_aux);
      break;
    case 99:
      exit(0);
      break;
    }
  }
}