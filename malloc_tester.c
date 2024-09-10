#include <stdio.h>
#include <assert.h>
#include <sys/types.h>
#include <unistd.h>
#include "malloc.h"

int malloctester() {
    int stack = 1;
    printf("stack address: %p\n", &stack);
    printf("program break: %p\n", sbrk(0));
    char* ar = mem_alloc(sizeof(char[20]));

    ar = "Hello World!";
    printf("%s\n", ar);
    printf("new program break: %p\n", sbrk(0));

    mem_free(ar);

    int* second = mem_alloc(sizeof(int));
    long long* ar2 = mem_alloc(sizeof(long long[3000]));

    mem_free(ar2);
    mem_free(second);
    return 0;
}

int main() {
    printf("start\n");
    malloctester();
    return 0;
}



