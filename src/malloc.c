#include "../headers/malloc.h"

static Chunk *start = NULL;

Chunk *get_start_chunck()
{
    return start;
}

void ft_coalesce()
{
    Chunk *curr = start;
    while (curr != NULL && curr->next != NULL)
    {
        
    }

}

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

Chunk *find_free_chunk(size_t size)
{
    Chunk *curr = start;
    while (curr != NULL && curr->next != NULL)
    {
        if (curr->free == 0)
        {
            curr->free = 1;
            return curr;
        }
        curr = curr->next;
    }
    
    return NULL;
}

Chunk *create_chunk(Chunk *ptr)
{
    ptr = mmap(NULL, size + sizeof(Chunk), PROT_READ | PROT_WRITE, MAP_PRIVATE | MAP_ANONYMOUS, -1, 0);
    
    if (ptr == MAP_FAILED)
        return NULL;

    ptr->prev_size = 0;
    ptr->size = size;
    ptr->free = 1;
    ptr->next = NULL;
    ptr->prev = NULL;

    return ptr;
}

void add_chunk(Chunk *new)
{
    if (!start)
    {
        start = new;
        return;
    }

    Chunk *curr = start;
    while (curr != NULL && curr->next != NULL) 
        curr = curr->next;
    
    new->prev_size = curr->size;
    new->prev = curr;
    curr->next = new;

    return;
}

void *ft_malloc(size_t size)
{
    Chunk *ptr = NULL;

    if (!size)
        return NULL;

    if (!(ptr = find_free_chunk(size)))
        ptr = create_chunk(ptr);

    if (ptr == NULL)
        return ptr;
    
    add_chunk(ptr);
    heap_visualize();
    return (void *)(ptr + 1);
}