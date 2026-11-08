#include "../headers/malloc.h"


void    ft_coalesce(Chunk *ptr_c)
{
    Chunk *bck;
    Chunk *fwd;

    bck = ptr_c;
    fwd = ptr_c;
    if (is_free((Chunk *)((char *)bck - bck->prev_size)))
    {
        bck = (Chunk *)((char *)bck - bck->prev_size);
        bck->size = bck->size + unflag_size(ptr_c->size);
        unlink_chunk(ptr_c);
    }
    if (is_free((Chunk *)((char *)fwd + unflag_size(fwd->size))))
    {
        fwd = (Chunk *)((char *)fwd + unflag_size(fwd->size));
        bck->size = bck->size + unflag_size(fwd->size);
        unlink_chunk(fwd);
    }
}

void    free(void *ptr)
{
    Chunk *ptr_c = ((Chunk *)ptr) - 1;

    link_free_chunk(ptr_c);
    ptr_c->size = set_flags(0x2, ptr_c->size);

    ft_coalesce(ptr_c); 
}