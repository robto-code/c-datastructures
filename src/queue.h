#ifndef __queue_h__
#define __queue_h__ 

#include <stdint.h>
#include "dnode.h"

typedef struct Queue {
    int32_t length;
    Dnode* head;
    Dnode* tail;
} Queue;

/** Creates empty queue. 
 * Length is 0, head and tail are NULL. */
Queue* queue_create();

/** Queue Destructor. 
 * Removes queue and all nodes within from memory. */
void queue_destroy(Queue* queue);

void queue_push(Queue* queue, Dnode* node);

Dnode* queue_pop(Queue* queue);

Dnode* queue_peek(Queue* queue);

static inline int32_t queue_length(Queue* queue)
{
    return queue->length;
}

static inline int queue_isempty(Queue* queue)
{
    return (queue->head == NULL);
}

#endif // queue.h
