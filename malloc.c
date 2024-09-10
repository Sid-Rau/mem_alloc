#include <stdio.h>
#include <assert.h>
#include <sys/types.h>
#include <unistd.h>
#include <string.h>
#include "malloc.h"
#define CHUNK_SIZE sizeof(chunk)
chunk* chunkListHead = NULL;
/* The purpose of this project is to implement my own version of malloc, realloc, calloc,
 * and free based on a tutorial by danluu (danluu.com/malloc-tutorial/).
 */


 // finds free chunk with valid size and returns it 
 //(also finds the last element of the list if a chunk can't be found)
 // Does not split chunk to right size, so could allocate excess
 // Should write a chunk split function
chunk* find_freechunk(size_t size, chunk** last) {
    chunk* current = chunkListHead;
    while (current && !(current->free && current->size >= size)) {
        *last = current;
        current = current->next;
    }
    return current;
}
//Adds more memory to the heap using sbrk and then initializes and adds chunk to list
chunk* alloc_new(size_t size, chunk* last) {
    chunk* newchunk = sbrk(0);
    void* newbreak = sbrk(size + CHUNK_SIZE);
    assert(newbreak == newchunk);
    assert(sbrk(0) == ((char*)newbreak + size + CHUNK_SIZE));
    if (newbreak == (void*)-1) {
        return NULL;
    }
    if (last) {
        last->next = newchunk;
    }
    newchunk->size = size;
    newchunk->free = 0;
    newchunk->next = NULL;
    newchunk->prev = last;

    return newchunk;
}

chunk* getChunk(void* ptr) {
    return (chunk*)ptr - 1;
}

// void mergeFreeChunks(chunk* input) {
//     return;
// }

//allocates a given amount of memory, diy malloc. Uses a linked list to 
//keep track of the memory chunks. 
void* mem_alloc(size_t size) {
    chunk* newchunk;
    if (size <= 0) { return NULL; } // invalid size

    if (!chunkListHead) { //first call, chunkListHead of list is null
        newchunk = alloc_new(size, NULL);
        if (!newchunk) { return NULL; }
        chunkListHead = newchunk;
    }
    else { //if list exists
        //first check if a free chunk big enough exists
        chunk* last = chunkListHead;
        newchunk = find_freechunk(size, &last);
        // If no new chunk exists, allocate new chunk, append to list
        if (!newchunk) {
            newchunk = alloc_new(size, last);
            last->next = newchunk;
        }
        else {
            newchunk->free = 0;
        }
    }
    return (newchunk + 1);
}

//frees memory by marking chunks in the list as free. Combines neighboring chunks if they are all free
void mem_free(void* ptr) {
    if (!ptr) { return; }
    chunk* input = getChunk(ptr);
    // chunk* current = chunkListHead;
    // while (current && (current != input)) {
    //     current = current->next;
    // }
    // assert(current);
    assert(input->free == 0);
    //current->free = 1;
    //mergeFreeChunks(current);
    //merges neighboring free chunks to prevent fragmentation. not implemented yet
}
//Implements calloc, just mem_allocs then sets memory to 0
void* mem_calloc(size_t num, size_t size) {
    size_t total = num * size;
    void* ptr = mem_alloc(total);
    memset(ptr, 0, size);
    return ptr;
}
/*
void* mem_realloc(void* ptr, size_t size) {

}
*/

