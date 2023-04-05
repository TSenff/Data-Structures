#include "list.h"
#include <stdlib.h>
#include <stdio.h>


node *create_node(void *d){
    node *n = malloc(sizeof(node));
    if (n == NULL)
        return NULL;
    n->data = d;
    n->next = NULL;
    return n;
}

list* create_list(int d_size, void *remove_d){
    list *l = malloc(sizeof(list));
    if (l == NULL)
        return NULL;    
    l->remove_d = remove_d;
    l->data_size = d_size;
    l->first     = NULL;
    l->size      = 0;
    return l;
}

int free_list(list *l){
    node *n = l->first,*r;
    while (n != NULL){
        r = n;
        n = n->next;
        l->remove_d(r->data);
        free(r);
    }
    free(l);
    return 0;
}

int list_add(list *l, void *d){
    node *n = create_node(d);
    if (n == NULL)
        return 1;
    
    l->size++;
    
    if(list_size(l) == 1){
        l->first = n;
        return 0;
    }
    n->next = l->first;
    l->first = n;

    return 0;
}

void* list_get(list* l, int index){
    if (list_size(l) <= index)
        return NULL;
    node *n = l->first;

    for (int i = 1; i <= index; i++)
        n = n->next;


    return n->data;
}

int list_size(list *l){
    return l->size;
}

int list_empty(list *l){
    return l->size == 0;
}
