#ifndef __stack_h__
#define __stack_h__

#include <stdint.h>
#include <stdlib.h>
#include "node.h"

typedef struct Stack {
    struct Node* head;
    int32_t length;
} Stack;

/** Stack Constructor */
Stack* stack_create();

/** Stack Destructor
 * @stack: stack to be destroyed */
void stack_destroy(Stack* stack);

/** Pops top node from stack. 
 * If stack is empty, returns NULL. */
Node* stack_pop(Stack* stack);

/** Pushes newnode onto top of stack. */
void stack_push(Stack* stack, Node* newnode);

/** 1 if stack is empty, 0 otherwise */
static inline int stack_isempty(Stack* stack)
{
    return (stack->head == NULL);
}

/** Returns amount of nodes in stack */
static inline int32_t stack_size(Stack* stack)
{
    return stack->length;
}

static inline Node* stack_peek(Stack* stack)
{
    return stack->head;
}

#endif //stack.h
