#include <stdio.h>
#include <assert.h>
#include <sys/types.h>
#include <unistd.h>
#include <string.h>

void* mem_alloc(size_t size);
void mem_free(void* ptr);
void* mem_realloc(void* ptr, size_t size);
void* mem_calloc(size_t num, size_t size);
typedef struct chunk {
    size_t size;
    int free;
    struct chunk* next;
    struct chunk* prev;
}  chunk;



