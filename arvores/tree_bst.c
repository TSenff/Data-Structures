#include <stdio.h>
#include <stdlib.h>

#include "tree_bst.h"


/****************** node ***************************/

node* create_node(int key, node *father){
	node *n = malloc(sizeof(node));
	if(n == NULL)
		return NULL;
	n->key    = key;
	n->father = father;
	n->left   = NULL;
	n->right  = NULL;
	return n;
}

int free_node(node *n){
	free(n);
	return 0;
}

/****************** Tree  ***************************/

tree* create_tree(){
	tree *t = malloc(sizeof(tree));
	if(t ==NULL )
		return NULL;
	t->n_node = 0;
	t->root = NULL;
	return t;
}

int free_tree_node(node *n){
	if(n == NULL)
		return 0;
	free_tree_node(n->left);
	free_tree_node(n->right);
	free_node(n);
	return 0;
}

int free_tree(tree *t){
	free_tree_node(t->root);
	free(t);
	return 0;
}

/******** Max/Min e Antecessor/Sucessor ********/

node* node_min(node *n){
	node *min = n;
	if (min == NULL)
		return NULL;
	
	while (min->left != NULL){
		min = min->left;
	}
	return min;
}

node* tree_min(tree *t){
	return node_min(t->root);
}

node* node_max(node *n){
	node *max = n;
	if (max == NULL)
		return NULL;
	
	while (max->right != NULL){
		max = max->right;
	}
	return max;
}

node* tree_max(tree *t){
	return node_max(t->root);
}

node* antecessor(node *n){
	return node_max(n->left);
}

node* sucessor(node *n){
	return node_min(n->right);
}

/******** Operações Basicas ********/

int insere_nodo(node *x, int key){

	if(x->key > key){
		if(x->left != NULL)
			return insere_nodo(x->left,key);
		
		node *n = create_node(key,x);
		if (n == NULL)
			return 1;

		x->left   = n;
		return 0;
	}

	/* Se o valor for igual , vai para a direita*/
	if (x->right != NULL)
		return insere_nodo(x->right,key);
	
	node *n = create_node(key,x);
	if (n == NULL)
		return 1;
	x->right   = n;
	return 0;
	
}

int insere(tree *t, int key){
	if(t->root == NULL){
		node *n = create_node(key, NULL);
		if (n == NULL)
			return 1;		
		t->root = n;
		return 0;
	}
	return insere_nodo(t->root,key);
}

node* busca_nodo(node *n, int key){
	if(n ==NULL)
		return NULL;
	if(n->key > key)
		return busca_nodo(n->left,key);
	if(n->key < key)
		return busca_nodo(n->right,key);
	return n;
}

node* busca(tree *t, int key){
	return busca_nodo(t->root,key);
}

/* Coloca V como filho do pai de U*/
int transplant(tree *t, node *u, node *v){
	/* Se o pai era a raiz v vira a raiz */
	if (u->father == NULL){
		t->root = v;
		
	}
	else{
		/* Garante que o pai de u agora aponta para v */
		if (u == u->father->left){
			u->father->left = v;
		}
		else{
			u->father->right = v;
		}
	}
	/* Muda o pai de v*/
	if (v != NULL)
		v->father = u->father;	
	return 0;
}


int tree_remove(tree *t, node *r){
	node *y;
	/* 1 ou nenhum filho */
	if ( r->left == NULL){
		transplant(t,r,r->right);
		free(r);
		return 0;
	}
	if (r->right == NULL){
		transplant(t,r,r->left);
		free(r);
		return 0;
	}
	/* Dois filhos */
	y = sucessor(r);
	if (y->father != r){
		transplant(t,y,y->right);
		y->right = r->right;
		y->right->father = y;
	}
	transplant(t,r,y);
	y->left = r->left;
	y->left->father = y;
	free(r);
	return 0;
}

/******** Outras operações ********/

int rotacao_esq(tree *t, node *n){
	node *y = n->right;
	n->right = y->left;
	if (y->left != NULL){
		y->left->father = n;
	}
	y->father = n->father;
	if (n->father == NULL){
		t->root = y;
	}
	else{
		if (n == n->father->left)
			n->father->left = y; 
		else
			n->father->right = y;
	}
	y->left = n;
	n->father = y;
	return 0;
}

int rotacao_dir(tree *t, node *n){
	node *y = n->left;
	n->left = y->right;
	if (y->right != NULL){
		y->right->father = n;
	}
	y->father = n->father;
	if (n->father == NULL){
		t->root = y;
	}
	else{
		if (n == n->father->right)
			n->father->right = y; 
		else
			n->father->left = y;
	}
	y->right = n;
	n->father = y;
	return 0;

}


/******** Print ********/

int print_pre_ordem_node(node *n){
	if(n == NULL)
		return 1;
	printf("%i ",n->key);
	print_pre_ordem_node(n->left);
	print_pre_ordem_node(n->right);
	return 0;
}

int print_pos_ordem_node(node *n){
	if(n == NULL)
		return 1;
	print_pos_ordem_node(n->left);
	print_pos_ordem_node(n->right);
	printf("%i ",n->key);
	return 0;
}

int print_ordem_node(node *n){
	if(n == NULL)
		return 1;
	print_ordem_node(n->left);
	printf("%i ",n->key);
	print_ordem_node(n->right);
	return 0;
}

int print_em_ordem(tree *t){
	return print_ordem_node(t->root); 
}

int print_pre_ordem(tree *t){
	return print_pre_ordem_node(t->root);
}

int print_pos_ordem(tree *t){
	return print_pos_ordem_node(t->root);
}
