#include "linkedlist.h"
#include "debug.h"
#include "node.h"
#include <stdlib.h>

LinkedList* List_create(int32_t esize) 
{
    LinkedList* l_list = malloc(sizeof(LinkedList));
    l_list->esize = esize;
    l_list->length = 0;
    l_list->head = NULL;

    return l_list;
}

void List_destroy(LinkedList* list)
{
    Node* destroy = list->head;
    while (list->length--)
    {
        Node* temp = destroy->next;
        Node_destroy(destroy);
        destroy = temp;
    }
    free(list);
}

void List_append(LinkedList* list, Node* n)
{
    if(list->length == 0)
    {
        list->head = list->tail = n;
    }
    else 
    {
        list->tail->next = n;
        list->tail = n;
    }
    list->length++;
}

void List_push(LinkedList *list, Node* n)
{
    if(list->length == 0)
    {
        list->head = list->tail = n;
    }
    else 
    {
        n->next = list->head;
        list->head = n;
    }
    list->length++;
}

void List_insert(LinkedList* list, Node* n, uint32_t pos)
{
    DBG_check(pos < list->length || list->length == 0, "pos surpasses size of list", error);
    
    if (list->length == 0)
    {
        list->head = list->tail = n;
    }
    else 
    {   
        Node** dest = &(list->head);
        while(pos--)
        {
            dest = &((*dest)->next);
        }
        n->next = *dest; // new node's next becomes previous node at pos
        *dest = n;      // node at pos is now new node.
    }

    list->length++;
    return;

error:
    return;
}

Node* List_decapitate(LinkedList* list)
{
    DBG_check(list->length != 0, "empty list", error);
    
    Node** denode = &(list->head);
    *denode = (*denode)->next;
    list->length--;
    
    return *denode;

error:
    return NULL;
}

Node* List_pop(LinkedList* list)
{
    DBG_check(list->length != 0, "empty list", error);
    
    uint32_t i = list->length; 
    Node** popnode = &(list->head);
    while (--i)
    {
        popnode = &((*popnode)->next);
    }
    Node* retnode = (*popnode)->next;
    (*popnode)->next = NULL;
    list->tail = *popnode;
    list->length--;
    
    return retnode;

error:
    return NULL;
}

Node* List_remove(LinkedList* list, uint32_t pos)
{
    DBG_check(list->length < pos, "pos surpasses list bounds", error);

    if (pos == 0) return List_decapitate(list);
    else if (pos == list->length-1) return List_pop(list);

    Node** dest = &(list->head);
    while(--pos)
    {
        dest = &((*dest)->next);
    }
    Node* remnode = (*dest)->next;
    (*dest)->next = ((*dest)->next)->next;
    list->length--;

    return remnode;

error:
    return NULL;
}

Node* List_get(LinkedList* list, uint32_t pos)
{
    DBG_check(list->length < pos, "pos surpasses list bounds", error);
    
    Node** dest = &(list->head);
    while(pos--)
    {
        dest = &((*dest)->next);   
    }
    return *dest;

error:
    return NULL;
}

void List_delete(LinkedList* list, uint32_t pos)
{
    Node_destroy(List_remove(list, pos));
}
