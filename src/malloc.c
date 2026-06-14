#include "../headers/malloc.h"

void *malloc(size_t size)
{
    void *ptr = NULL;

    if (!size)
        return NULL;
    
    ptr = mmap(NULL, size + sizeof(Chunk), PROT_READ | PROT_WRITE, MAP_PRIVATE | MAP_ANONYMOUS, 0, 0);


    return ptr;
}