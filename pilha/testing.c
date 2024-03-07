#include "generic_stack.h"
#include <stdlib.h>
#include <stdio.h>

/* Simple test of the stack implementation */

#define RED     "\x1b[31m"
#define GREEN   "\x1b[32m"
#define RESET   "\x1b[0m"

void print_ok(char *str){
    printf("[" GREEN "OK" RESET "]" " %s\n",str);
}

void print_no(char *str){
    printf("[" RED "NO" RESET "]"  " %s\n",str);
}

int main(){
    int **n = malloc(sizeof(int*) * 5);
    int *m;

    /* Initialize*/
    struct stack_gen *stack  = initialize_empty_stack();
    if (!is_empty(stack))
        print_no("Empty Stack Created");
    else
        print_ok("Empty Stack Created");
    
    /* Push */
    for (size_t i = 0; i < 5; i++){
        n[i] = malloc(sizeof(int));
        n[i][0] = i;
        push(&stack,n[i]);
        if ((int*)peek(stack) != n[i])
            print_no("Push error");
    }
    print_ok("Push :: [0,1,2,3,4]");
    
    /* PoP */
    for (size_t i = 5; i > 0; i--){
        m = pop(&stack); 
        if (*m != i-1 )
            print_no("Pop error");
    }
    print_ok("Pop  :: [4,3,2,1,0]");

    /* Empty*/
    if(is_empty(stack))
        print_ok("Stack is empty");

    /* Free all memory*/
    for (size_t i = 0; i < 5; i++)
        free(n[i]);
    free(n);

    /* Free_Stack() */
    for (size_t i = 0; i < 100; i++)
        push(&stack,malloc(sizeof(int)));
    free_stack(stack,free);

    return 0;
}