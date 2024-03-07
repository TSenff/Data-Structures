#ifndef GENERIC_STACK_H_
#define GENERIC_STACK_H_
#include <stdlib.h>

/*
* A simple generic implementation of Stack
*/

struct stack_gen{
    void* data;
    struct stack_gen *next;
};

/*
* Only returns NULL
*/
struct stack_gen* initialize_stack();

/*
* Returns and removes the top of the stack, 
* if empty returns NULL
*/
void* pop(struct stack_gen **s);

/*
* Adds element to the top of the stack
* Returns 1 on success, 0 if malloc fails
*/
int push(struct stack_gen **s, void *e);

/*
* Returns the top of the stack, 
* if empty returns NULL. 
* Does not remove top of stack
*/
void* peek(struct stack_gen *s);

/*
*   Checks if stack is empty 
*/
int empty(struct stack_gen *s);

/*
* Free the entire stack
*  void (*f)(void*) is the function to free the data type
*/
void free_stack(struct stack_gen *s, void (*f)(void*));

#endif