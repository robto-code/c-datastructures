
#include "node.h"
#include "debug.h"
#include <stdlib.h>

Node* Node_create(uint32_t esize, Node* next)
{
    Node* n = malloc(sizeof(Node));
    n->value = malloc(esize);
    n->next = next;
    return n;
}

void Node_destroy(Node* n)
{
    free(n->value);
    free(n);
}

void Node_insert(Node* n1, Node* n2)
{
    DBG_check(!(n2->next), "n2 can not have a 'next' node!", error);
    
    n2->next = n1->next;
    n1->next = n2;

error:
    return;
}

