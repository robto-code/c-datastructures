#ifndef __debug_h__
#define __debug_h__

#ifdef DEBUG 
#include <stdio.h>

/* Prints an error with message (M) and goes to error flag (F) */
#define DBG_error(M, F) { fprintf(stderr, "ERROR %d: %s", __LINE__, (M)); goto F;} 

/* Prints error w/ message (M) if condition (C) is false, goto flag (F) */
#define DBG_check(C, M, F) if(!(C)) DBG_error(M, F)

#else

#define DBG_error(M, F) 
#define DBG_check(C, M, F) 

#endif 
#endif
