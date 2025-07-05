#include <stdlib.h>

#include "global.h"
#include "memoryManager.c"

MemoryBlock *getMemoryBlock(void);
LeakInfo *MGetLeaks(void);
int MFreeAll(void);
int MFree(void *);
void *MMalloc(size_t);
void *MCalloc(size_t, size_t);
void *MRealloc(void *, size_t);