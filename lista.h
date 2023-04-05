#ifndef SIMPLE_GENERIC_LIST_H_
#define SIMPLE_GENERIC_LIST_H_

/* Implementa uma lista generica simplesmente encadeada 
 * 
 * Autor: Thiago da Costa Pereira Senff
 *
 * Versao 1.0.0 16/11/2022
 */

struct node_s{
    void* data;
    struct node_s* next;
};
typedef struct node_s node;

struct lista{
    node *first;
    int data_size;
    void (*remove_d)(void *data);
    int size;
};
typedef struct  lista list;

/* Cria uma lista vazia 
*   int d_size        tamanho do dado salvo na lista
*   void *remove_d    ponteiro para funcao que desaloca o dado salvo na lista
*/
list* create_list(int d_size, void *remove_d);

/* Desaloca uma lista */
int free_list(list *l);

/* Adiciona um item na lista, no começo */
int list_add(list *l, void *d);

/* Busca o valor salvo em determinada posicao da lista */
void* list_get(list* l, int index);

/* Retorna o numero de itens na lista */
int list_size(list *l);

/* Retorna 1 se vazia, 0 caso contrario */
int list_empty(list *l);

#endif