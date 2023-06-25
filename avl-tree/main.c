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
      in_order_avl(avl_tree);
      printf("\n");
      break;
    case 4:
      pos_order_avl(avl_tree);
      printf("\n");
      break;
    case 5:
      reverse_avl(avl_tree);
      printf("\n");
      break;
    case 6:
      printf("%d \n", sum_prime_numbers_avl(avl_tree));
      break;
    case 7:
      scanf("%d", &val);
      printf("%d \n", successor_avl(avl_tree, -1, val));
      break;
    case 8:
      scanf("%d", &val);
      path_avl(avl_tree, val);
      printf("\n");
      break;
    case 9:
      scanf("%d", &val);
      remove_avl(avl_tree, val, reduce_aux);
      printf("\n");
      break;
    case 10:
      printf("%d \n", sum_all_numbers_avl(avl_tree));
      break;
    case 11:
      scanf("%d", &val);
      //prune_avl(avl_tree, val);
      printf("\n");
      break;
    case 12:
      scanf("%d", &val);
      adjust_percentage_avl(avl_tree, val);
      printf("\n");
      break;
    case 13:
      scanf("%d", &val);
      printf("%d \n", exist_avl(avl_tree, val));
      break;
    case 14:
      scanf("%d", &val);
      succession_avl(avl_tree, val);
      printf("\n");
      break;
    case 15:
      scanf("%d", &val);
      printf("%d \n", height_avl(avl_tree));
      break;
    case 99:
      exit(0);
      break;
    }
  }
}