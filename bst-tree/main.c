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
      bst_tree = insert_bst(bst_tree ,val);
      break;
    case 2:
      pre_order_bst(bst_tree);
      printf("\n");
      break;
    case 3:
      in_order_bst(bst_tree);
      printf("\n");
      break;
    case 4:
      pos_order_bst(bst_tree);
      printf("\n");
      break;
    case 5:
      reserve_bst(bst_tree);
      printf("\n");
      break;
    case 6:
      printf("%d \n", sum_prime_numbers_bst(bst_tree));
      break;
    case 7:
      scanf("%d", &val);
      printf("%d \n", successor_bst(bst_tree, -1, val));
      break;
    case 8:
      scanf("%d", &val);
      path_bst(bst_tree, val);
      printf("\n");
      break;
    case 9:
      scanf("%d", &val);
      remove_bst(bst_tree, val);
      printf("\n");
      break;
    case 10:
      printf("%d \n", sum_all_numbers_bst(bst_tree));
      break;
    case 11:
      scanf("%d", &val);
      prune_bst(bst_tree, val);
      printf("\n");
      break;
    case 12:
      scanf("%d", &val);
      adjust_percentage_bst(bst_tree, val);
      printf("\n");
      break;
    case 13:
      scanf("%d", &val);
      printf("%d \n", exist_bst(bst_tree, val));
      break;
    case 14:
      scanf("%d", &val);
      succession_bst(bst_tree, val);
      printf("\n");
      break;
    case 15:
      scanf("%d", &val);
      printf("%d \n", height_bst(bst_tree));
      break;
    case 99:
      exit(0);
      break;
    }
  }
}