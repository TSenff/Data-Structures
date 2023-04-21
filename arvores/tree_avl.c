#include <stdio.h>

#include <stdlib.h>

#include "tree_avl.h"



/******** Outras operações ********/
/******** Manutencao AVL ********/


/**
 * @brief Atualiza a altura de um nodo
 * 
 * @param n        nodo a ser atualizado
 * @return int     0 caso o nodo tenha sido atualizado, 1 caso não ocorra mudança
 */
int update_height(node *n){
    if (n == NULL)
        return 1;    
    int left = -1, right = -1;
    if (n->left != NULL)
        left = n->left->height;
    
    if (n->right != NULL)
        right = n->right->height;
    
    right++;
    left++;

    /* Se lado direito for o mais alto, verifica se atualiza*/
    if (right > left ){
        if (right == n->height){
            return 1;
        }
        n->height = right;
        return 0;
    }

    /* Se lado esquerdo for iguai ou mais alto, verifica se atualiza*/        
    if (left == n->height)
        return 1;

    n->height = left;
    return 0;
}


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
    update_height(n);
    update_height(y);

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

    update_height(n);
    update_height(y);

	return 0;
}




int maintain_tree(tree *t, node *n){
    int left = -1, right = -1;
    if (n->left != NULL)
        left = n->left->height;
    
    if (n->right != NULL)
        right = n->right->height;




    switch (left - right){
    case -2:
        rotacao_esq(t,n); 
        break;
    case 2:
        rotacao_dir(t,n);
         break;
    default:
        break;
    }

    return 1;
}

/****************** node ***************************/

node* create_node(int key, node *father){
	node *n = malloc(sizeof(node));
	if(n == NULL)
		return NULL;
    n->height = 0;
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

int insere_nodo(tree *t, node *x, int key){
	if(x->key > key){
        /* COntinua percorendo a arvore para esquerda */
		if(x->left != NULL){
			if (insere_nodo(t, x->left, key))
                return 1;
            if(!update_height(x))
                maintain_tree(t,x); 
            return 0;
        }
		/* Insere na esquerda de x*/
        node *n = create_node(key,x);
		if (n == NULL)
			return 1;

		x->left   = n;
        if(!update_height(x))
            maintain_tree(t,x); 
		return 0;
	}

    /* COntinua percorendo a arvore para Direita */
	if (x->right != NULL){
		if( insere_nodo(t, x->right, key) )
            return 1;
        if(!update_height(x))
            maintain_tree(t,x); 
        return 0;
    }

	/* Insere na direita de x*/
	node *n = create_node(key,x);
	if (n == NULL)
		return 1;
	x->right   = n;
    if(!update_height(x))
        maintain_tree(t,x);    
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
	return insere_nodo(t,t->root,key);
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


/*  Garante que tudo acima esta funcionando */
 int check_all_fathers(tree *t, node *y){
	while (y != NULL){
		if (!update_height(y)){
            maintain_tree(t,y);
		}
        y = y->father;
	}    
    return 0;
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
	node * temp;
	/* 1 ou nenhum filho */
	if ( r->left == NULL){
		temp = r->father;
        transplant(t,r,r->right);
		
		check_all_fathers(t,temp);
		free(r);
		return 0;
	}
	if (r->right == NULL){
		transplant(t,r,r->left);
        temp = r->left;
		check_all_fathers(t, temp);
		free(r);
		return 0;
	}
	/* Dois filhos */
	node *y = sucessor(r);
    temp = y->father;
	if (y->father != r){
		transplant(t,y,y->right);
		y->right = r->right;
		y->right->father = y;
	}
    else{
        temp = y;
    }
	transplant(t,r,y);
	y->left = r->left;
	y->left->father = y;
    check_all_fathers(t, temp);
	free(r);
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
    printf("#######################\n");
	printf("%i (%i) \n",n->key, n->height);
	if (n->left != NULL)
        printf("Esquerda = %i\n", n->left->key);
    if (n->right != NULL)
        printf("Direita = %i\n", n->right->key);
    printf("#######################\n");

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
