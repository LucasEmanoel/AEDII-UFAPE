#include "avl.h" //importa o arquivo de declaracoes
#include "table.h"
#include <stdio.h>
#include <stdlib.h>

avl_tree rsd(avl_tree node) {
	avl_tree p, u, t1, t2, t3;
	p = node;
	u = node->left;

	t1 = p->left;
	t2 = u->right;
	t3 = u->left;

	p->left = t2;
	u->right = p;

	if (u->fb == -1) {
		p->fb = 0;
		u->fb = 0;
	} else {
		p->fb = -1;
		u->fb = 1;
	}

	return u;
}
avl_tree rse(avl_tree node) {

	avl_tree p, u, t1, t2, t3;
	p = node;
	u = node->right;

	t1 = p->left;
	t2 = u->left;
	t3 = u->right;

	p->right = t2;
	u->left = p;

	if (u->fb == 1) {
		p->fb = 0;
		u->fb = 0;
	} else {
		// duvidas - caso +2 0 entendi!!
		p->fb = 1;
		u->fb = -1;
	}

	return u;
}
avl_tree rdd(avl_tree node) {
	avl_tree p, u, v, t1, t2, t3, t4;

	p = node;
	u = node->left;
	v = u->right;

	t1 = u->left;
	t2 = v->left;
	t3 = v->right;
	t4 = p->right;

	v->right = p;
	u->right = t2;
	v->left = u;
	p->left = t3;

	switch (v->fb) {
    case -1:
			p->fb = 1;
			u->fb = 0;
			v->fb = 0;
      break;
    case 0:
      p->fb = 0;
      u->fb = 0;
      break;
    case 1:
			p->fb = 0;
			v->fb = 0;
			u->fb = -1;
      break;
  }

	return v;
}
avl_tree rde(avl_tree node) {
	avl_tree p, u, v, t1, t2, t3, t4;

	p = node;
	u = node->right;
	v = u->left;

	//t1 = p->left;
	t2 = v->left;
	t3 = v->right;
	//t4 = u->right;

	v->left = p;
	p->right = t2; 
	v->right = u;
	u->left = t3;
	
	switch (v->fb) {
    case -1:
			v->fb = 0;
			p->fb = 0;
			u->fb = 1;
      break;
    case 0:
      p->fb = 0;
      u->fb = 0;
      break;
    case 1:
			v->fb = 0;
			p->fb = -1;
			u->fb = 0;
      break;
	}
	return v;
}
avl_tree rotation(avl_tree node) {
	if (node->fb > 0) {
		switch (node->right->fb) {
      case 0: 
				return rse(node);
        break;
      case 1:
				//printf("node atual [ val =%d, fb =%d] | rotation rse,node right [ val =%d, fb =%d]\n",node->val, node->fb, node->right->val, node->right->fb);
        return rse(node);
        break;
      case -1:
				//printf("node atual [ val =%d, fb =%d] | rotation rde,node right [ val =%d, fb =%d]\n",node->val, node->fb, node->right->val, node->right->fb);
        return rde(node);
        break;
      }
	} else {
		switch (node->left->fb) {
      case 0:
				return rsd(node);
        break;
      case 1:
				//printf("node atual [ val =%d, fb =%d] | rotation rdd,node left [ val =%d, fb =%d]\n",node->val, node->fb, node->left->val, node->left->fb);
        return rdd(node);
        break;
      case -1:
				//printf("node atual [ val =%d, fb =%d] | rotation rsd,node left [ val =%d, fb =%d]\n",node->val, node->fb, node->left->val, node->left->fb);
        return rsd(node);
        break;
      }
	}
	return node;
}

void initialize(avl_tree *no){
	*no = NULL;
}

avl_tree insert_avl(avl_tree node, type_data *val, int *grown) {
	if (node == NULL) {
		avl_tree new_node = (avl_tree) malloc(sizeof(struct no));
		new_node->left = NULL;
		new_node->right = NULL;
		new_node->fb = 0;
		new_node->val = val;
		*grown = 1;
		return new_node;
	} else {
		if (node->val->key <= val->key) {
			node->right = insert_avl(node->right, val, grown);

			if (*grown) {
				switch (node->fb) {
				case 0:
					node->fb = 1;
					*grown = 1;
					break;
				case 1:
					*grown = 0;
					return rotation(node);
					break;
				case -1:
					node->fb = 0;
					*grown = 0;
					break;
				}
			}
			// simétrico
		} else {
			node->left = insert_avl(node->left, val, grown);

			if (*grown) {
				switch (node->fb) {
				case 0:
					node->fb = -1;
					*grown = -1;
					break;
				case 1:
					node->fb = 0;
					*grown = 0;
					break;
				case -1:
					*grown = 0;
					return rotation(node);
					break;
				}
			}
		}

		return node;
	}
}
int compare_value(int a, int b) {
	if(a > b)
		return a;
	else
		return b;
}
int height(avl_tree raiz) {
	if(raiz == NULL) {
		return 0;
	}
	return 1 + compare_value(height(raiz->right), height(raiz->left));
}

int max_value(avl_tree node) {
	if (node == NULL) {
		return -1;
	}
	if (node->right == NULL) {
		return node->val->key;
	} else {
		return max_value(node->right);
	}
}
int min_value(avl_tree node){
	if(node == NULL)
			return -1;
	if(node->left == NULL)
			return node->val->key;
	else
			return min_value(node->left);
}
avl_tree remove_avl(avl_tree node, int val, int *reduce) {
	if (node == NULL) {
		return NULL;
	}
	if (node->val->key == val) { // 90 == 90
		//printf("\nencontrou %d\n",node->val);
		if (node->left != NULL && node->right != NULL) {
			switch_nodes(node, val);
			node->left = remove_avl(node->left, val, reduce);
		}
		if (node->left == NULL) {
			*reduce = 1;
			avl_tree aux = node->right;
      free(node);
			return aux;
		}
		if (node->right == NULL) {
			*reduce = 1;
      avl_tree aux = node->left;
			free(node);
			return aux;
		}
		
		node->val->key = max_value(node->left);
		node->left = remove_avl(node->left, val, reduce);
		
		return node;
	}
	if (node->val->key <= val) { // 80 <= 90 - sim
		node->right = remove_avl(node->right, val, reduce);
		//printf("right %d valor, fb= %d\n",node->val, node->fb);
		if (*reduce) { // sim
			switch (node->fb) {
				case 1:
					node->fb = 0;
					*reduce = 1;
					break;
				case 0:
					node->fb = -1;
					*reduce = 0; //deu erros
					break;
				case -1: // 80 = -1
					return rotation(node);
					break;
				}
		}
	} else { // node left 100
		node->left = remove_avl(node->left, val, reduce);
		//printf("left %d valor, fb= %d\n",node->val, node->fb);
		if (*reduce) {
			switch (node->fb) {
				case 1:
					return rotation(node);
					break;
				case 0:
					node->fb = 1;
					*reduce = 0;
					break;
				case -1:
					node->fb = 0;
					*reduce = 1;
					break;
			}
		}
	}
	return node;
}
void switch_nodes(avl_tree node, int val) {
	avl_tree aux = node->left;
	while (aux->right != NULL) {
		aux = aux->right;
	}
	node->val = aux->val; 
	aux->val->key = val;
}
