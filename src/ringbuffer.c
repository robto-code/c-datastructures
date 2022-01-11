#include "debug.h"
#include "utilities.h"
#include "ringbuffer.h"
#include <stdlib.h>


/* Returns a pointer to a ringbuffer. 
 --------------------------------------
 * Size of Ringbuffer is either capacity or closest power of 2 larger than
 * capacity.
 * 
 * esize: size of element in ringbuffer, in bytes
 * capacity: minimum size (in elements) of ringbuffer */
RingBuffer *RB_create(unsigned int esize, unsigned int capacity)
{
    NEXTPOWOF2(capacity)
    
    RingBuffer *ring = (RingBuffer *) malloc(sizeof(RingBuffer));

    DBG_check(ring, "Problem allocating space for ring", error)
    
    ring->capacity = capacity;
    ring->buffer = malloc(ring->capacity * esize);
    ring->start = ring->end = 0;
    ring->esize = esize;

    return ring;

error:
    exit(1);
}

/* Frees ringbuffer from memory.
 --------------------------------------
 * ring: ringbuffer to be destroyed */
void RB_destroy(RingBuffer *ring)
{   
    DBG_check(ring, "No ring to be destroyed", error);
    
    free(ring->buffer);
    free(ring);

error:
    return;

}

/* Posts to ring using reader's index.
 --------------------------------
 * ring: ringbuffer to be posted to
 * reader: dr's index is used to be new read pointer. Requires: index >= ring's read pointer. */
void RB_postReader(RingBuffer *ring, DataRead *reader)
{
    DBG_check(reader->index >= ring->start, "New Index is less than current read pointer", error);
    ring->start = reader->index;

error:
    return;
}

/* Posts to ring using smallest index in reader list.
 -------------------------------
 * ring: ringbuffer to be posted to
 * readers: smallest index in readers list will be used to post 
 * n: length of readers array. */
void RB_postListReader(RingBuffer *ring, DataRead **readers, unsigned int n)
{
    DataRead *min = readers[0];
    for (int i = 0; i < n; i++)
    {
        if (readers[i]->index < min->index) min = readers[i];
    }
    RB_postReader(ring, min);
}



