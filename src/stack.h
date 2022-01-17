#ifndef __stack_h__
#define __stack_h__

#include <stdint.h>
#include <stdlib.h>
/** 
 * Stack datastructure.
 *
 * The user must supply their own node structure of type struct Node
 * The Node must have a 'next' property and a deconstructor function. 
 */

typedef struct Stack {
    struct Node* head;
    int32_t length;
} Stack;

/** Stack Constructor */
inline Stack* Stack_create()
{
    Stack* mystack = (Stack*) malloc(sizeof(Stack));
    mystack->length = 0;
    mystack->head = NULL;
    return mystack;
}

/** Returns if stack is empty */
inline int Stack_isempty(Stack* stack)
{
    return (stack->head == NULL);
}

/** Returns amount of nodes in stack */
inline int32_t Stack_size(Stack* stack)
{
    return stack->length;
}

/** Stack Destructor
 * @stack: stack to be destroyed
 * @node_destroy: function with 1 argument of type node 
 * that desconstructs the node */
#define STACK_DESTROY(stack, node_destroy)      \
    while(!(Stack_isempty(stack))) {            \
        struct Node* temp;                      \
        STACK_POP(stack, temp);                 \
        node_destroy(temp); }                   \
    free(stack);

/** Pushes node n in stack
 * @n: Node to be pushed into stack */
#define STACK_PUSH(stack, n)    \
    n->next = stack->head;      \
    stack->head = n;            \
    stack->length++;

/** Pops top node from stack, writing it to dest. 
 * If stack is empty, dest is NULL. 
 * @dest: Node pointer; will be overwritten with popped node */
#define STACK_POP(stack, dest)          \
    dest = stack->head;                 \
    if(dest) {                          \
        stack->length--;                \
        stack->head = dest->next;       \
    }

/** Returns pointer to head of stack */
#define STACK_PEEK(stack) stack->head 

#endif //stack.h
