#ifndef AVL_H
#define AVL_H

/* Implementa uma Arvore AVL
 * 
 * Autor: Thiago da Costa Pereira Senff
 *
 * Versao 1.0.0 24/11/2022
 */


struct node_s{
	int key;
    int height;
	struct node_s *father;
	struct node_s *left;
	struct node_s *right;
};
typedef struct node_s node;

struct tree_s{
	node *root;
	int n_node;
};typedef struct tree_s tree;

tree* create_tree();
int free_tree(tree *t);

/**
 * @brief Insere um valor na arvore
 * 
 * @param t 	arvore
 * @param key 	valor para inserir
 * @return int 	0 se o valor for inserido, 1 caso algum erro ocorra
 */
int insere(tree *t, int key);

/**
 * @brief Devolve o node que possui um valor especifico
 * 
 * @param t 		arvore
 * @param key 		valor
 * @return node* 	node que possui o valor
 */
node* busca(tree *t, int key);

/**
 * @brief Remove um nodo da arvore
 * 
 * @param t 		arvore
 * @param r 		nodo a ser removido
 * @return int 		0 caso o item tenha sido removido, 1 caso algum erro tenha ocorrido
 */
int tree_remove(tree *t, node *r);

/**
 * @brief Devolve o nodo de menor valor da arvore
 * 
 * @param t 		Arvore
 * @return node* 	Nodo de menor valor
 */
node* tree_min(tree *t);

/**
 * @brief Devolve o nodo de maior valor da arvore
 * 
 * @param t 		Arvore
 * @return node* 	Nodo de maior valor
 */
node* tree_max(tree *t);

/**
 * @brief Imprime uma arvore em pre-ordem 
 * 
 * @param t 	Arvore
 * @return int 	0
 */
int print_pre_ordem(tree *t);

/**
 * @brief Imprime uma arvore em pos-ordem
 * 
 * @param t 	Arvore
 * @return int  0
 */
int print_pos_ordem(tree *t);

/**
 * @brief Imprime uma arvore em ordem
 * 
 * @param t 	Arvore
 * @return int 	0
 */
int print_em_ordem(tree *t);



#endif
