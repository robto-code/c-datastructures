#ifndef __node_h__
#define __node_h__ 

#include <stdint.h>
#include <stdlib.h>

typedef struct Node {
    int8_t* value;
    struct Node* next;
} Node;

/* Creates new node, where value is size (esize) and next is (next).
 * If the node has no next node, let next be NULL. */
static inline Node* node_create(size_t esize, Node* next)
{
    Node* n = (Node*) malloc(sizeof(Node));
    n->value = (int8_t*) malloc(esize);
    n->next = next;
    return n;
}

/* Removes n from memory. 
 * Make sure to remove 'next' references to n in other nodes. */
static inline void node_destroy(Node* n)
{
    free(n->value);
    free(n);
}

/** Writes value V to Node N.
 * @N: node to be written into 
 * @V: value */
#define NODE_WRITE(N, V) memcpy(N->value, &V, sizeof(V));

/** Reads value of type T from Node N.
 * @N: node
 * @T: type of value */
#define NODE_READ(N, T) ((T*) (N->value))

/** Copies value from node N to D. 
 * @N: node
 * @D: data container (ex: variable). N->value is copied into here */
#define NODE_READCOPY(N, D) memcpy(&D, N->value, sizeof(D));

/** Creates Node at N with value V and next NEXT.
 * @N: variable must be of type Node */
#define NODE_EMPLACE(N, V, NEXT) \
    N = node_create(sizeof(V), NEXT); \
    NODE_WRITE(N, V);

#endif //node.h
