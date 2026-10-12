#include "../headers/malloc.h"

void heap_visualize(Heap *TINY, Heap *SMALL) 
{
    Heap    *heap;
    Chunk   *chunk;
    int     it;

    it = 0;
    heap = TINY;
    while (heap != NULL && heap->next != NULL)
    {
        printf("\n--- ESTADO DEL TINY %i ---\n", it++);
        chunk = (heap + 1);
        while (chunk->next != NULL)
        {
            printf("[%s | flags: %zu bytes | addr: %p]\n", get_flags(chunk->size), unflag_size(curr->size), (void*)curr);
            curr = curr->next;
        }
        printf("------------------------\n");
        heap = heap->next;
    }
}

size_t unflag_size(size_t size)
{
    return size & ~0x5; // Tamaño sin flags
}

size_t get_flags(size_t size)
{
    return size - (size & ~0x5); // Tamaño con flags
}

