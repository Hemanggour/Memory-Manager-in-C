# Memory Management System

## Overview
This project implements a simple memory management system in C, providing custom memory allocation and deallocation functions to track allocated memory blocks. It includes the following functionalities:

- `MMalloc(size_t size)`: Allocates memory and tracks it.
- `MCalloc(size_t size, size_t typeSize)`: Allocates zero-initialized memory and tracks it.
- `MRealloc(void* ptr, size_t size)`: Reallocates a previously allocated memory block.
- `MFree(void* ptr)`: Frees a specific allocated memory block.
- `MFreeAll()`: Frees all allocated memory blocks.
- `MGetLeaks()`: Returns an array of `LeakInfo` structures containing information about memory leaks.

## File Structure
```
Memory-Manager/
│── global.h           # Contains global structures and variables
│── memoryManager.h    # Header file with function declarations
│── memoryManager.c    # Contains memory management functions
│── tests.c           # Contains test cases for memory management
│── README.md         # Documentation
```

## Implementation Details
### global.h
This file contains global structures and variables:
- `MemoryBlock` struct: Stores metadata about allocated memory blocks
- `LeakInfo` struct: Stores information about memory leaks
- Global pointers for managing the memory block list

### memoryManager.h
Header file containing function declarations and necessary includes:
- Function prototypes for all memory management functions
- Required standard library includes

### memoryManager.c
This file contains the implementation of memory management functions:
- `MemoryBlock` struct: Stores metadata about allocated memory.
- `getMemoryBlock()`: Allocates memory for a new block.
- `MMalloc(size_t size)`: Custom memory allocation function.
- `MCalloc(size_t size, size_t typeSize)`: Custom memory allocation function for zero-initialized memory.
- `MRealloc(void* ptr, size_t size)`: Resizes an existing allocated memory block.
- `MFree(void* ptr)`: Frees a specific memory block.
- `MFreeAll()`: Frees all allocated memory blocks.
- `MGetLeaks()`: Returns an array of `LeakInfo` structures containing information about memory leaks.

### tests.c
This file contains test cases to validate the functionality of the memory manager.

## Usage
To use the memory manager in your program:
```c
#include "memoryManager.h"
```
Compile and run:
```sh
gcc tests.c -o tests
./tests
```

## Example Usage
```c
#include "memoryManager.h"

int main() {
    int *arr = (int *)MMalloc(5 * sizeof(int));
    if (arr) {
        for (int i = 0; i < 5; i++)
            arr[i] = i + 1;
    }
    MFree(arr);

    arr = (int *)MMalloc(10 * sizeof(int));
    arr = (int *)MMalloc(10 * sizeof(int));
    MFree(arr);

    arr = (int *)MMalloc(10 * sizeof(int));
    for (int i = 5; i < 10; i++)
        arr[i] = i + 1;

    LeakInfo *leaks = MGetLeaks();

    for (size_t i = 0; i < leaks->leakCount; i++)
        printf("Leak %zu: Address: %p, Size: %zu bytes\n", i + 1, leaks[i].address, leaks[i].size);

    free(leaks); // Don't forget to free the array when done

    MFreeAll();
    return 0;
}
```

## Notes
- Ensure proper use of `MFree()`, `MRealloc()`, and `MFreeAll()` to prevent memory leaks.
- The `MFree()` and `MFreeAll()` functions return a status code __0__ and __1__.
- _0_ for failed to free memory and _1_ for successfully freed memory.
- `MCalloc()` ensures memory is initialized to zero before use.
- `MRealloc()` resizes an existing memory block while preserving its contents.
- `MGetLeaks()` helps in detecting memory leaks by providing information about unfreed memory blocks.
- Remember to free the leaks array using `free()` after use to avoid memory leaks.

## License
This project is open-source and free to use under the MIT License.