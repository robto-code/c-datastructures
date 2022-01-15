#ifndef __ringbuffer_h__
#define __ringbuffer_h__ 

#include "debug.h"
#include "utilities.h"
#include <stdint.h>

typedef struct {
    int8_t *buffer;                  /* data stored in bytes; size is esize * capacity */ 
    unsigned int esize;              /* size of element */
    unsigned int capacity;           /* Capacity of ringbuffer in elements, always power of 2 */
    unsigned int start;              /* start of valid data, loc of read pointer */
    unsigned int end;                /* end of valid data, loc of write pointer */
} RingBuffer;

typedef struct {
    //int8_t *data;
    unsigned int index;
} DataRead; /* Used for reading data from ringbuffer */

/* Returns a pointer to a ringbuffer. 
 --------------------------------------
 * Size of Ringbuffer is either capacity, if capacity is a power of 2,
 * or closest power of 2 larger than capacity.
 * 
 * elementSize: size of element in ringbuffer, in bytes
 * capacity: minimum size (in elements) of ringbuffer */
RingBuffer* RB_create(unsigned int elementSize, unsigned int capacity);

/* Frees ringbuffer from memory.
 --------------------------------------
 * ring: ringbuffer to be destroyed */
void RB_destroy(RingBuffer *ring);

/* Increases ring's read pointer by 2. */
void inline RB_post(RingBuffer *ring)
{
    ring->start++;
}

/* Increases ring's read pointer by n. Read pointer should be smallest index of reader threads.  */
void inline RB_postInc(RingBuffer *ring, unsigned int n)
{
    ring->start += n;
}

/* Sets ring's read pointer to dr's index.
 * Requires: reader's index >= ring's reader pointer. */
void RB_postReader(RingBuffer *ring, DataRead *reader);

/* Sets ring's read pointer to smallest index in readers. 
 * n is the size of readers array.
 * Requires: selected reader index >= ring's reader pointer. */
void RB_postListReader(RingBuffer *ring, DataRead **readers, unsigned int n);

/* Space available to write in ring */
unsigned int inline RB_writeSpace(RingBuffer *ring) 
{
    return ring->capacity - (ring->end - ring->start);
}

/* Space available to read in ring */
unsigned int inline RB_readSpace(RingBuffer *ring, DataRead *reader)
{
    return ring->end - reader->index;
}
/* Space left to post in ring */
unsigned int inline RB_postSpace(RingBuffer *ring)
{
    return ring->end - ring->start;
}

/* Writes single unit of data (D) to (R)'s buffer. Updates write pointer in ring.
 * Requires: (D) type has same size as (R)->esize. */
#define RB_WRITE(R, D) memcpy(R->buffer + (MODPOW2(R->end++, R->capacity) * R->esize), &D,  R->esize); 

/* Returns pointer to one element in ringbuffer (R) of type (DS) at index specified in dataread (DR). 
 * Requires: DS is a type (int, char, etc) of same size as (R)->esize */
#define RB_READ(R, DR, DS) (DS *) &(R->buffer[MODPOW2((DR)->index++, R->capacity) * R->esize])  

/* Copies 1 element in ringbuffer at index of dataread (DR) into data (D). D should be a variable of same type
 * as element. */
#define RB_READCOPY(R, DR, D) memcpy(&D, &R->buffer[MODPOW2((DR)->index++, R->capacity) * R->esize], R->esize) 

#endif
