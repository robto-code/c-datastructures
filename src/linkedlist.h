#ifndef __linkedlist_h__
#define __linkedlist_h__ 

#include <stdint.h>
#include "node.h"

typedef struct {
    int32_t length; 
    int32_t esize;
    struct Node* head;
} LinkedList; /* Single-Linked List */


/* Creates empty linked list. Element size of list is esize. 
 * head and tail are NULL. */
LinkedList* List_create(int32_t esize);

/** Loops through each node in list. 
 * @list: list to be looped through
 * @loopvar: struct Node; loop variable */
#define LIST_FOREACH(list, loopvar) \
    for (loopvar = list->head; loopvar != nullptr; loopvar = loopvar->next) 

/** Loops through each value in list. 
 * @list: list to be looped through
 * @valvar: loop variable for value
 * @nodevar: loop variable for node */
#define LIST_FOREACHVAL(list, valvar, nodevar) \
    for (loopvar = list->head, valvar = NODE_READ(loopvar, typeof(valvar)); loopvar != nullptr; loopvar = loopvar->next) 

/* Removes list and all nodes within it from memory. */
//void List_destroy(LinkedList* list);

/* Appends newnode to end of linked list. Use this to add a node 
 * to an empty list. O(1) time. */
//void List_append(LinkedList* list, Node* newnode); 

/* Inserts newnode at position (pos). If list is empty, then pos 
 * is not considered. O(pos) time. 
 * Requires: pos < list->length if list->length != 0 */
//void List_insert(LinkedList* list, Node* newnode, uint32_t pos);

/* Removes node at position pos from the list and from memory.
 * O(pos) time.
 * Requires: pos < list->length; list->length != 0 */
//void List_delete(LinkedList* list, uint32_t pos); 
#define LIST_DELETE(list, nodeid, member) { \

/* Removes and returns tail from list. O(list->length) time. */
//Node* List_pop(LinkedList* list);

/* Removes and returns head from list. O(1) time. */
//Node* List_decapitate(LinkedList* list);

/* Removes and returns node at position pos from list. O(pos) time. */
//Node* List_remove(LinkedList* list, uint32_t pos);
#define LIST_REMOVE(list, nodeid, member) ({        \
    struct Node* __ptr = list->head                 \
    if (__ptr->member == nodeid) {                  \
        LIST_POPFRONT(list); }                      \
    LIST_FOREACH(list, __ptr) {                     \
        if (__ptr->next && (__ptr->next)->member == nodeid) {   \
            struct Node* __ret = __ptr->next;       \
            __ptr->next = __ret->next;              \
            __ret->next = NULL;                     \
            __ret;}} NULL;})

/* Returns node at position pos from list. O(pos) time. */
//Node* List_get(LinkedList* list, uint32_t pos);

#endif // linkedlist.h
