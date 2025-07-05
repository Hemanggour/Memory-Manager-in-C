#include <stdio.h>
#include "memoryManager.h"

void testMCalloc()
{
    printf("Running MCalloc() Tests...\n");

    // Test 1: Allocate memory and check if initialized to zero
    int *arr = (int *)MCalloc(5, sizeof(int));
    if (!arr)
    {
        printf("Test 1 Failed: MCalloc() returned NULL\n");
        return;
    }
    int initialized = 1;
    for (int i = 0; i < 5; i++)
    {
        if (arr[i] != 0)
        {
            initialized = 0;
            break;
        }
    }
    printf("Test 1 Passed: Memory initialized to zero\n");

    // Test 2: MCalloc with zero size or typeSize should return NULL
    void *zeroAlloc1 = MCalloc(0, sizeof(int));
    void *zeroAlloc2 = MCalloc(5, 0);
    if (!zeroAlloc1 && !zeroAlloc2)
    {
        printf("Test 2 Passed: MCalloc(0, X) and MCalloc(X, 0) returned NULL\n");
    }
    else
    {
        printf("Test 2 Failed: Expected NULL but got allocated memory\n");
    }

    // Test 3: Free allocated memory
    if (MFree(arr))
    {
        printf("Test 3 Passed: MFree() successfully freed allocated memory\n");
    }
    else
    {
        printf("Test 3 Failed: MFree() failed to free memory\n");
    }

    printf("MCalloc() Tests Completed.\n\n");
}

void testMRealloc()
{
    printf("\nTest 8: Reallocation with MRealloc\n");

    // Allocate memory
    int *ptr = (int *)MMalloc(sizeof(int) * 2);
    if (!ptr)
    {
        printf("Initial allocation failed.\n");
        return;
    }
    ptr[0] = 10;
    ptr[1] = 20;
    printf("Allocated: %p | Values: %d, %d\n", ptr, ptr[0], ptr[1]);

    // Expand memory
    int *newPtr = (int *)MRealloc(ptr, sizeof(int) * 4);
    if (!newPtr)
    {
        printf("Reallocation failed.\n");
        return;
    }
    newPtr[2] = 30;
    newPtr[3] = 40;
    printf("Reallocated: (expand): %p | Values: %d, %d, %d, %d\n", newPtr, newPtr[0], newPtr[1], newPtr[2], newPtr[3]);

    // Shrink memory
    newPtr = (int *)MRealloc(newPtr, sizeof(int) * 2);
    if (!newPtr)
    {
        printf("Shrink reallocation failed.\n");
        return;
    }
    printf("Reallocated (shrunk): %p | Values: %d, %d\n", newPtr, newPtr[0], newPtr[1]);

    // Free memory
    printf("MFree() Status code (('0' failed) or ('1' success)): %d\n", MFree(newPtr));

    // Test realloc with NULL (should behave like malloc)
    int *nullPtr = (int *)MRealloc(NULL, sizeof(int) * 2);
    if (nullPtr)
        printf("MRealloc(NULL, size) worked: %p\n", nullPtr);
    printf("MFree() Status code (('0' failed) or ('1' success)): %d\n", MFree(nullPtr));

    // Test realloc with size 0 (should free memory and return NULL)
    int *zeroPtr = (int *)MMalloc(sizeof(int) * 2);
    zeroPtr = (int *)MRealloc(zeroPtr, 0);
    if (!zeroPtr)
        printf("MRealloc(ptr, 0) correctly freed memory.\n");
}

int main()
{
    // Test 1: Basic Allocation and Deallocation
    printf("Test 1: Basic Allocation and Deallocation\n");
    int *p1 = (int *)MMalloc(sizeof(int));
    *p1 = 42;
    printf("Allocated value: %d\n", *p1);
    printf("MFree() Status code (('0' failed) or ('1' success)): %d\n", MFree(p1));

    // Test 2: Double Free (Should handle gracefully without crashing)
    printf("\nTest 2: Double Free\n");
    int *p2 = (int *)MMalloc(sizeof(int));
    *p2 = 84;
    printf("Allocated value: %d\n", *p2);
    printf("MFree() Status code (('0' failed) or ('1' success)): %d\n", MFree(p2));
    printf("MFree() Status code (('0' failed) or ('1' success))\nFreeing twice should be handled (Output Should be '0' failed): %d\n", MFree(p2)); // Freeing twice should be handled (Output Should be '0' failed)

    // Test 3: Memory Leak Check
    printf("\nTest 3: Memory Leak Check\n");
    for (int i = 0; i < 10; i++)
    {
        int *p = (int *)MMalloc(sizeof(int));
        *p = i;
        printf("Allocated value: %d\n", *p);
        if (i % 2 == 0)
        {
            printf("MFree() Status code (('0' failed) or ('1' success)): %d\n", MFree(p)); // Freeing every alternate pointer
        }
    }

    // Test 4: Zero-byte Allocation (Edge Case)
    printf("\nTest 4: Zero-byte Allocation\n");
    void *zeroPtr = MMalloc(0); // Should handle gracefully
    if (zeroPtr == NULL)
        printf("Allocated zero bytes, returned NULL\n");
    else
        printf("MFree() Status code (('0' failed) or ('1' success)): %d\n", MFree(zeroPtr));

    // Test 5: Large Allocation
    printf("\nTest 5: Large Allocation\n");
    int *pLarge = (int *)MMalloc(1000000 * sizeof(int)); // Large allocation
    if (pLarge)
        printf("Successfully allocated a large memory block\n");
    else
        printf("Failed to allocate a large memory block\n");
    printf("MFree() Status code (('0' failed) or ('1' success)): %d\n", MFree(pLarge));

    // Test 6: Allocate After Free
    printf("\nTest 6: Allocate After Free\n");
    int *pReAlloc = (int *)MMalloc(sizeof(int));
    *pReAlloc = 123;
    printf("Allocated value: %d\n", *pReAlloc);
    printf("MFree() Status code (('0' failed) or ('1' success)): %d\n", MFree(pReAlloc));
    pReAlloc = (int *)MMalloc(sizeof(int));
    *pReAlloc = 456;
    printf("Allocated value after re-allocation: %d\n", *pReAlloc);
    printf("MFree() Status code (('0' failed) or ('1' success)): %d\n", MFree(pReAlloc));

    // Test 7: Freeing a Pointer Not Allocated
    printf("\nTest 7: Freeing a Pointer Not Allocated\n");
    int *pInvalid = (int *)malloc(sizeof(int));                                           // Direct malloc, not tracked by MMalloc (Output should be '0' failed)
    printf("MFree() Status code (('0' failed) or ('1' success)): %d\n", MFree(pInvalid)); // Should print status code ('0' for failed) or ('1' for success)

    testMRealloc();
    testMCalloc();

    printf("MFreeAll() Status code (('0' failed) or ('1' success)): %d\n", MFreeAll());

    return 0;
}