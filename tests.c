#include <stdio.h>
#include <stdlib.h>    // only used in Test 7 for direct malloc
#include "memoryManager.h"  // defines malloc, calloc, realloc, free

void testCalloc()
{
    printf("Running calloc() Tests...\n");

    // Test 1: Allocate memory and check if initialized to zero
    int *arr = (int *)calloc(5, sizeof(int));
    if (!arr)
    {
        printf("Test 1 Failed: calloc() returned NULL\n");
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
    printf("Test 1 %s: Memory initialized to zero\n",
           initialized ? "Passed" : "Failed");

    // Test 2: calloc with zero size or typeSize should return NULL
    void *zeroAlloc1 = calloc(0, sizeof(int));
    void *zeroAlloc2 = calloc(5, 0);
    if (!zeroAlloc1 && !zeroAlloc2)
    {
        printf("Test 2 Passed: calloc(0, X) and calloc(X, 0) returned NULL\n");
    }
    else
    {
        printf("Test 2 Failed: Expected NULL but got allocated memory\n");
    }

    // Test 3: free allocated memory
    if (free(arr))
        printf("Test 3 Passed: free() successfully freed allocated memory\n");
    else
        printf("Test 3 Failed: free() failed to free memory\n");

    printf("calloc() Tests Completed.\n\n");
}

void testRealloc()
{
    printf("Running realloc() Tests...\n");

    // Test 1: Expand allocation
    int *ptr = (int *)malloc(sizeof(int) * 2);
    if (!ptr)
    {
        printf("Test 1 Failed: malloc() initial allocation failed.\n");
        return;
    }
    ptr[0] = 10;
    ptr[1] = 20;
    int *newPtr = (int *)realloc(ptr, sizeof(int) * 4);
    if (!newPtr)
    {
        printf("Test 1 Failed: realloc() expand failed.\n");
        return;
    }
    newPtr[2] = 30;
    newPtr[3] = 40;
    printf("Test 1 Passed: realloc() expand – Values: %d, %d, %d, %d\n",
           newPtr[0], newPtr[1], newPtr[2], newPtr[3]);
    free(newPtr);

    // Test 2: Shrink allocation
    ptr = (int *)malloc(sizeof(int) * 4);
    if (!ptr) { printf("Test 2 Failed: malloc() failed.\n"); return; }
    ptr[0] = 1; ptr[1] = 2; ptr[2] = 3; ptr[3] = 4;
    newPtr = (int *)realloc(ptr, sizeof(int) * 2);
    if (!newPtr)
    {
        printf("Test 2 Failed: realloc() shrink failed.\n");
    }
    else
    {
        printf("Test 2 Passed: realloc() shrink – Values: %d, %d\n",
               newPtr[0], newPtr[1]);
        free(newPtr);
    }

    // Test 3: realloc(NULL, size) behaves like malloc()
    int *nullPtr = (int *)realloc(NULL, sizeof(int) * 2);
    if (nullPtr)
    {
        printf("Test 3 Passed: realloc(NULL, size) worked.\n");
        free(nullPtr);
    }
    else
    {
        printf("Test 3 Failed: realloc(NULL, size) returned NULL.\n");
    }

    // Test 4: realloc(ptr, 0) frees and returns NULL
    ptr = (int *)malloc(sizeof(int) * 2);
    if (!ptr) { printf("Test 4 Failed: malloc() failed.\n"); return; }
    int *zeroPtr = (int *)realloc(ptr, 0);
    if (!zeroPtr)
        printf("Test 4 Passed: realloc(ptr, 0) correctly freed memory.\n");
    else
    {
        printf("Test 4 Failed: realloc(ptr, 0) did not free.\n");
        free(zeroPtr);
    }

    printf("realloc() Tests Completed.\n\n");
}

int main()
{
    // Test 1: Basic Allocation and Deallocation
    printf("Test 1: Basic Allocation and Deallocation\n");
    int *p1 = (int *)malloc(sizeof(int));
    *p1 = 42;
    printf("  Allocated value: %d\n", *p1);
    printf("  free() Status code: %d (1=success, 0=failure)\n", free(p1));

    // Test 2: Double free (Should return 0 on second free)
    printf("\nTest 2: Double free\n");
    int *p2 = (int *)malloc(sizeof(int));
    *p2 = 84;
    printf("  Allocated value: %d\n", *p2);
    printf("  First free(): %d\n", free(p2));
    printf("  Second free(): %d (expected 0)\n", free(p2));

    // Test 3: Memory Leak Check (only even allocations freed)
    printf("\nTest 3: Memory Leak Check\n");
    for (int i = 0; i < 10; i++)
    {
        int *p = (int *)malloc(sizeof(int));
        *p = i;
        printf("  Allocated %d -> free(): %d\n", i, (i % 2 == 0) ? free(p) : 0);
    }

    // Test 4: Zero-byte Allocation (Edge Case)
    printf("\nTest 4: Zero-byte Allocation\n");
    void *zeroPtr = malloc(0);
    if (zeroPtr == NULL)
        printf("  Passed: malloc(0) returned NULL\n");
    else
        printf("  Failed: malloc(0) did not return NULL\n");

    // Test 5: Large Allocation
    printf("\nTest 5: Large Allocation\n");
    int *pLarge = (int *)malloc(1000000 * sizeof(int));
    if (pLarge)
        printf("  Passed: Successfully allocated large block\n");
    else
        printf("  Failed: Large allocation returned NULL\n");
    free(pLarge);

    // Test 6: Allocate After free
    printf("\nTest 6: Allocate After free\n");
    int *prealloc = (int *)malloc(sizeof(int));
    *prealloc = 123;
    free(prealloc);
    prealloc = (int *)malloc(sizeof(int));
    *prealloc = 456;
    printf("  Allocated after free: %d\n", *prealloc);
    free(prealloc);

    // Run the more specific tests
    testRealloc();
    testCalloc();

    // Final cleanup: free any remaining blocks
    printf("MfreeAll() Status code: %d (1=success, 0=failure)\n", MFreeAll());

    return 0;
}
