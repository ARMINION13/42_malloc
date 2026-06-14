#include "./headers/malloc.h"

Chunk *start = NULL;

void heap_visualize() 
{
    printf("\n--- ESTADO DEL HEAP ---\n");
    Chunk *curr = start;
    while (curr != NULL) 
    {
        printf("[%s | size: %zu bytes | addr: %p]\n", curr->free ? "FREE" : "USED", curr->size, (void*)curr);
        curr = curr->next;
    }
    printf("------------------------\n");
}

int main ()
{
    heap_visualize();
    return 0;
}