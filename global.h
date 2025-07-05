typedef struct MemoryBlock
{
    size_t size;
    void *memory;
    struct MemoryBlock *next;
} MemoryBlock;

typedef struct LeakInfo
{
    size_t size;
    size_t leakCount;
    void *address;
} LeakInfo;

MemoryBlock *MemoryBlockHead = NULL, *MemoryBlockTail = NULL;