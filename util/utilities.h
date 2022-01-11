#ifndef __utilities_h__
#define __utilities_h__ 

/* Edits (I) to be its next highest power of 2. */
#define NEXTPOWOF2(I) {(I)--; (I) |= (I) >> 1; (I) |= (I) >> 2; \
                        (I) |= (I) >> 4; (I) |= (I) >> 8; \
                        (I) |= (I) >> 16; (I)++; }

/* Is (a) mod (b). (b) must be power of 2. */
#define MODPOW2(a, b) ((a) & (b-1))

#endif
