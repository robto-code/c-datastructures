#include "stack.h"
#include "node.h"

Stack* stack_create()
{
    Stack* mystack = (Stack*) malloc(sizeof(Stack));
    mystack->length = 0;
    mystack->head = NULL;
    return mystack;
}

void stack_push(Stack* stack, Node* newnode)
{
    newnode->next = stack->head;
    stack->head = newnode;
    stack->length++;
}

Node* stack_pop(Stack* stack)
{
    Node* dest = stack->head;
    if(dest) 
    {
        stack->length--;
        stack->head = dest->next;
        dest->next = NULL;
    }
    return dest;
}

void stack_destroy(Stack* stack) 
{
    while(!(stack_isempty(stack))) 
    {
        struct Node *temp = stack_pop(stack);
        node_destroy(temp);
    }
    free(stack);
}

