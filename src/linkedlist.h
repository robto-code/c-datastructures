
#ifndef __linkedlist_h__
#define __linkedlist_h__ 

#include <stdint.h>
#include "node.h"

typedef struct {
    uint32_t length; 
    uint32_t esize;
    Node* head;
    Node* tail;
} LinkedList; /* Single-Linked List */

/* Creates empty linked list. Element size of list is esize. 
 * head and tail are NULL. */
LinkedList* List_create(uint32_t esize);

/* Removes list and all nodes within it from memory. */
void List_destroy(LinkedList* list);

/* Appends newnode to end of linked list. Use this to add a node 
 * to an empty list. O(1) time. */
void List_append(LinkedList* list, Node* newnode); 

/* Inserts newnode at position (pos). If list is empty, then pos 
 * is not considered. O(pos) time. 
 * Requires: pos < list->length if list->length != 0 */
void List_insert(LinkedList* list, Node* newnode, uint32_t pos);

/* Removes node at position pos from the list and from memory.
 * O(pos) time.
 * Requires: pos < list->length; list->length != 0 */
void List_delete(LinkedList* list, uint32_t pos); 

/* Removes and returns tail from list. O(list->length) time. */
Node* List_pop(LinkedList* list);

/* Removes and returns head from list. O(1) time. */
Node* List_decapitate(LinkedList* list);

/* Removes and returns node at position pos from list. O(pos) time. */
Node* List_remove(LinkedList* list, uint32_t pos);

/* Returns node at position pos from list. O(pos) time. */
Node* List_get(LinkedList* list, uint32_t pos);

#endif // linkedlist.h
