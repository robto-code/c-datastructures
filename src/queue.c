#include "queue.h"
#include "dnode.h"

Queue* queue_create()
{
    Queue* queue = (Queue*) malloc(sizeof(Queue));
    
    queue->length = 0;
    queue->head = queue->tail = NULL;

    return queue;
}

Dnode* queue_pop(Queue* queue)
{
    Dnode* temp = queue->tail;
    queue->tail = temp->prev;

    return dnode_remove(queue->tail);
}

void queue_push(Queue* queue, Dnode* node)
{
    node->next = queue->head;
    (queue->head)->prev = node;
    queue->head = node;

    if (!queue->tail) queue->tail = queue->head;

    queue->length++;
}


