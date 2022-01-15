#ifndef __node_h__
#define __node_h__ 

#include <stdint.h>

typedef struct Node {
    int8_t* value;
    struct Node* next;
} Node;

/* Creates new node, where value is size (esize) and next is (next).
 * If the node has no next node, let next be NULL. */
Node* Node_create(uint32_t esize, Node* next);

/* Removes n from memory. 
 * Make sure to remove 'next' references to n in other nodes. */
void Node_destroy(Node* n);

/* Appends n2 to  n1. 
 * If n1 already has a next node n3, then n3 is removed from n1 and appended to n2. 
 * Requires: n2 does not have a next node. */
void Node_insert(Node* n1, Node* n2);

/* Writes value V of size E (in bytes)to Node N */
#define NODE_WRITE(N, V, E) memcpy(N->value, V, E);

/* Reads value of type T from Node N */
#define NODE_READ(N, T) (T*) N->value;

/* Copies E bytes from node N->value to D. 
 * E should be the element size, in bytes, of the value. */
#define NODE_READCOPY(N, D, E) memcpy(D, N->value, E);

#endif //node.h
