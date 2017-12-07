//
//  ctestsbill.c
//  
//
//  Created by Bill Addo on 5/6/17.
//
//

#include "ctestsbill.h"
#include <stdlib.h>
#include <stdio.h>
#include <stdbool.h>
#include <string.h>
#include "heaplib.h"

#define HEAP_SIZE 1024
#define ARRAY_LEN 16

// TODO: Add test descriptions as you add more tests...
const char* testDescriptions[] = {
    "init: heap should be created when enough space",
    "init: heap should not be created when not enough space",
    "alloc: block should be allocated when enough space",
    "alloc: block should not be allocated when not enough space",
    "alloc: block returned is aligned",
    "release: Do nothing if blockptr is 0",
    "resize: block should be allocated when enough space",
    "resize: block should not be allocated when not enough space",
    "resize: block returned is aligned",
    "resize: contents of block must be preserved",
    "release: released memory can be allocated to",
    "init: multiple heaps can coexist and be allocated to separately",
    "init: an overlapping heap cannot be created"
};

/* Checks whether a "heap" is created when there IS enough space.
 * THIS TEST IS COMPLETE.
 */
int test01() {
    
    char heap[HEAP_SIZE];
    
    int heap_created_f = hl_init(heap, HEAP_SIZE);
    
    if (heap_created_f) {
        return SUCCESS;
    }
    return FAILURE;
}

/* Checks whether a "heap" is created when there IS NOT enough space.
 * THIS TEST IS NOT COMPLETE. heaplame.c does not pass this test. Feel free to fix it!
 * Lab 12 TODO: COMPLETE THIS TEST!
 */
int test02() {
    char heap[HEAP_SIZE];
    
    int heap_created_f = hl_init(heap, 0);
    if (heap_created_f) {
        return FAILURE;
    }
    return SUCCESS;
}

/* Checks whether a block can be allocated when there is enough space.
 * THIS TEST IS NOT COMPLETE.
 * Lab 12 TODO: COMPLETE THIS TEST!
 */
int test03() {
    char heap[HEAP_SIZE];
    hl_init(heap,HEAP_SIZE);
    void *block = hl_alloc(heap,0);
    if (block==NULL) {
        return FAILURE;
    }
    return SUCCESS;
}

/* Checks whether a block can be allocated when there is NOT enough space.
 * THIS TEST IS COMPLETE. heaplame.c does not pass this test. Feel free to fix it!
 */
int test04() {
    
    char heap[HEAP_SIZE];
    
    hl_init(heap, HEAP_SIZE);
    
    // should NOT work
    void *block = hl_alloc(heap, ARRAY_LEN * HEAP_SIZE);
    
    if (block == NULL) {
        return SUCCESS;
    }
    return FAILURE;
}

/* Checks whether hl_alloc returns a pointer that has the correct
 * alignment.
 * THIS TEST IS NOT COMPLETE. heaplame.c does not pass this test. Feel free to fix it!
 * LAB 12 TODO: COMPLETE THIS TEST! (it is not robust)
 */
int test05() {
    
    char array[HEAP_SIZE];
    void *block;
    bool aligned_f;
    hl_init(&array, HEAP_SIZE-1);
    block=hl_alloc(&array, ARRAY_LEN);
    
    for(int i=1;i<8;i++) {
        aligned_f = (unsigned long)block % ALIGNMENT;
        if (aligned_f) {
            return FAILURE;
        }
        block=hl_alloc(&array, ARRAY_LEN+i);
    }
    return SUCCESS;
    
    //hl_init(&array, HEAP_SIZE - 1);
    
    //block = hl_alloc(&array, ARRAY_LEN); // doesn't really matter how much we allocate here
    
    // you may find this helpful. feel free to remove
    //#ifdef PRINT_DEBUG
    //  printf("blockptr = %16lx\n", (unsigned long)block);
    //  printf("mask =     %16lx\n", (unsigned long)(ALIGNMENT -1));
    //  printf("---------------------------\n");
    //  printf("ANDED =    %16lx\n", (unsigned long)block & (ALIGNMENT - 1));
    //  printf("!ANDED (ALIGNED) =   %6d\n", !((unsigned long)block & (ALIGNMENT - 1)));
    //#endif
    //should equal 0 if aligned
    //aligned_f = ((unsigned long)block) % ALIGNMENT;
    //if (aligned_f>0) {
    //	return FAILURE;
    //   }
    //  return SUCCESS;
}

/* Your test.
 * hl_release should do nothing if blockptr has the value 0 (NULL)
 */
int test06() {
    char array[HEAP_SIZE];
    hl_init(array, HEAP_SIZE);
    hl_alloc(array, HEAP_SIZE/2);
    char check[HEAP_SIZE];
    int i=0;
    while (i<HEAP_SIZE) {
        check[i]=array[i];
        i++;
    }
    void* emptyBlock=0;
    hl_release(array, emptyBlock);
    i=0;
    while (i<HEAP_SIZE) {
        if (check[i]!=array[i]) {
            return FAILURE;
        }
        i++;
    }
    return SUCCESS;
    
}

/* Your test.
 * hl_resize, block must be allocated if it can (return should
 * be the new ptr)
 */
int test07() {
    char heap[HEAP_SIZE];
    hl_init(heap, HEAP_SIZE);
    void* block = hl_alloc(heap, ARRAY_LEN);
    void* reblock=hl_resize(heap,block,ARRAY_LEN*2);
    if (reblock==NULL) {
        return FAILURE;
    }
    return SUCCESS;
    
}
/*CHANGED
 *Your test.
 * make sure allocate doesn't write to the previoulsy allocated block
 * takes 5 allocs and checks if any lies inside the other
 */
int test08() {
    char heap[HEAP_SIZE];
    hl_init(heap, HEAP_SIZE);
    
    //5 ptrs for allocs
    void *blocks[5];
    
    //5 allocs
    for(int i = 0; i < 5; i++){
        blocks[i] = hl_alloc(heap, 100);
    }
    
    //check if any block lies within the other 4 blocks
    for(int j = 0; j < 5; j++){
        char *singleBlock = (char*)blocks[j];
        for(int k = 0; k < 5; k++){
            if(j == k){
                continue;
            }
            char* checks = (char *)blocks[k];
            if( (singleBlock <= checks) && (checks < singleBlock + 100)){
                return FAILURE;
            }
        }
    }
    return SUCCESS;
}


/* CHANGED
 *shouldn't allocate to pointer that isn't a heapptr
 */
int test09() {
    
    char array[HEAP_SIZE];
    hl_init(array, HEAP_SIZE);
    
    void* block = hl_alloc(&heap[5], ARRAY_LEN);
    if(block){
        return FAILURE;
    }
    return SUCCESS;
    
}

/* Your test.
 * Contents of a block resized by hl_resize should be preserved if
 * blockptr is not NULL.
 */
int test10() {
    char array[HEAP_SIZE];
    int* block;
    hl_init(array, HEAP_SIZE);
    block= (int*) hl_alloc(array, ARRAY_LEN);
    *block=5;
#ifdef PRINT_DEBUG
    printf("Address of block = %p\n",block);
#endif
    hl_alloc(array,HEAP_SIZE/2);
    block = (int*) hl_resize(array, block, ARRAY_LEN*2);
#ifdef PRINT_DEBUG
    printf("Address of block = %p\n",block);
#endif
    if (*block==5) {
        return SUCCESS;
    }
    return FAILURE;
}

/* Your test.
 * A block of memory which has been freed by hl_release must be
 * able to be allocated again by subsequent calls to hl_alloc
 */
int test11() {
    char array[HEAP_SIZE];
    void* block=NULL;
    hl_init(array,HEAP_SIZE);
    int i=0;
    while(block==NULL) {
        block=hl_alloc(array,HEAP_SIZE-i);
        i++;
    }
    hl_release(array, block);
    void* block2 = hl_alloc(array,HEAP_SIZE-i);
    if (block2==NULL) {
        return FAILURE;
    }
    return SUCCESS;
    
}
//alloc shouldn't work if heapptr is incorrect
/* Your test.
 * hl_init supports multiple heaps.
 * after consecutive calls of hl_init to different heapptrs
 * it should still be possible to hl_alloc to either heapptr.
 */
int test12() {
    char heap1[HEAP_SIZE];
    char heap2[HEAP_SIZE];
    hl_init(heap1, HEAP_SIZE);
    hl_init(heap2, HEAP_SIZE);
    void* block1 = hl_alloc(heap1, ARRAY_LEN);
    void* block2 = hl_alloc(heap2, ARRAY_LEN);
    if ((block1==NULL) || (block2==NULL)) {
        return FAILURE;
    }
    return SUCCESS;
    
}

/* Your test.
 * if hl_init is called with a heapptr that is inside another heap
 * then hl_init should fail and return 0.
 */
int test13() {
    char heap[HEAP_SIZE];
    hl_init(heap, HEAP_SIZE);
    
    char* heap2 = &heap[5];
    int result = hl_init(heap2, HEAP_SIZE);
    
    if( result == 0 ){
        return SUCCESS;
    }
    return FAILURE;
}
