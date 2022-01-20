#ifndef __dnode_h__
#define __dnode_h__

#include <stdint.h>
#include <stdlib.h>

/** Double-Linked Node */
typedef struct Dnode {
    int8_t* value;
    struct Dnode* prev; 
    struct Dnode* next;
} Dnode;

/** Creates new dnode. 
 * @esize: size of data type to be stored in dnode, in bytes. */
static Dnode* dnode_create(size_t esize, Dnode* next, Dnode* prev)
{
    Dnode* n = (Dnode*) malloc(sizeof(Dnode));
    n->value = (int8_t*) malloc(esize);
    n->next = next;
    n->prev = prev; 
    
    return n;
}

/** Destroys Dnode from memory. 
 * @node: Dnode to be destroyed. */
static inline void dnode_destroy(Dnode *node)
{
    free(node->value);
    free(node);
}

/** Inserts newnode between prevnode and nextnode. 
 * @newnode: node to be inserted
 * @prevnode: node before newnode, can be NULL
 * @nextnode: node after newnode, can be NULL */
static inline void dnode_insert(Dnode *newnode, Dnode *prevnode, Dnode* nextnode)
{
    if(prevnode) prevnode->next = newnode;
    newnode->prev = prevnode;

    if(nextnode) nextnode->prev = newnode;
    newnode->next = nextnode;
}

/** Removes node, connecting node->prev and node->next together. */
static inline Dnode* dnode_remove(Dnode *node)
{
    Dnode* temp = node->next;
    if (temp) temp->prev = node->prev;
    temp = node->prev;
    if (temp) temp->next = node->next;

    return node;
}

/** Returns pointer to node value. 
 * @node: dnode to be read from.
 * @type: type of the data. */
#define DNODE_READ(node, type) ((type*) (node->value)) 

/** Copies node's value to dest.
 * @node: dnode to be read from
 * @dest: data container (ex: variable) to hold value. */
#define DNODE_READCOPY(node, dest) memcpy(&dest, node->value, sizeof(dest));

/** Writes data to node's value. 
 * @node: dnode to be written into
 * @data: data to write. Requires: sizeof(data) is same as sizeof(node->value) */
#define DNODE_WRITE(node, data) memcpy(node->value, &data, sizeof(data));

/** Creates dnode at node with a value. 
 * @node: new dnode will be written here, so should be type DNode *
 * @value: value of new dnode
 * @next: next dnode of new dnode
 * @prev: prev dnode of new dnode */
#define DNODE_EMPLACE(node, value, next, prev)  \
    node = dnode_create(sizeof(value), next, prev); \
    DNODE_WRITE(node, value);

#endif // dnode.h
