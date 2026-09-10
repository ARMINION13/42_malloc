#include "../headers/malloc.h"




void    ft_free(void *ptr)
{
    Chunk *chunk_pointer = ((Chunk *)ptr) - 1;

    Chunk->free = 1;
    ft_coalesce(); 
}