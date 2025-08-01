typedef struct MemoryBlock
{
    size_t size;
    void *memory;
    struct MemoryBlock *next;
} MemoryBlock;

typedef struct LeakInfo
{
    void *address;
    size_t size;
} LeakInfo;

MemoryBlock *MemoryBlockHead = NULL, *MemoryBlockTail = NULL;