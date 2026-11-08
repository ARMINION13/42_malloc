#include "../headers/malloc.h"

// void heap_visualize(Heap *TINY, Heap *SMALL) 
// {
//     Heap    *heap;
//     Chunk   *chunk;

//     heap = TINY;
//     while (heap != NULL && heap->next != NULL)
//     {
//         printf("\n--- ESTADO DEL TINY %i ---\n", it++);
//         chunk = (heap + 1);
//         while (chunk->next != NULL)
//         {
//             printf("[%s | flags: %zu bytes | addr: %p]\n", get_flags(chunk->size), unflag_size(curr->size), (void*)curr);
//             curr = curr->next;
//         }
//         printf("------------------------\n");
//         heap = heap->next;
//     }
// }

bool is_free(Chunk *chunk)
{
    size_t flags;

    flags = get_flags(chunk->size);
    if (flags != 2 && flags != 3 && flags != 6 && flags != 7)
        return false;
    return true;
}

size_t unflag_size(size_t size)
{
    return size & ~0x7; // Tamaño sin flags
}

size_t set_flags(size_t hex, size_t size)
{
    size = size & ~0x7;
    size = size | hex;

    return size; 
}

size_t get_flags(size_t size)
{
    return size - (size & ~0x7); // Tamaño con flags
}

void fix_free_bin(Heap *ptr_h)
{
    Chunk *aux;
    size_t flags;

    aux = ptr_h->free_bin;
    flags = get_flags(aux->size);
    while (!is_free(aux))
        aux = aux->fwd;
    ptr_h->free_bin = aux;
}

void  link_heap(Heap *new, Heap *list)
{
    Heap *it;

    it = list;
    if (!new || !list)
        return;
    while (it->fwd != NULL)
        it = it->fwd;
    it->fwd = new;
    new->bck = list;
}

void  link_free_chunk(Chunk *new)
{
    Chunk *ptr_c;
    size_t flags;
    size_t real_size;

    ptr_c = new;
    flags = get_flags(ptr_c->size);
    while (ptr_c->prev_size > 0 && !is_free(ptr_c))
    {
        ptr_c = (Chunk *)((char *)ptr_c - ptr_c->prev_size);
        flags = get_flags(ptr_c->size);
    }
    if (ptr_c->prev_size == 0)
        ptr_c = ((Heap *)(ptr_c - 1))->free_bin;
    new->bck = ptr_c->bck;
    if (ptr_c->bck)
        ptr_c->bck->fwd = new;
    new->fwd = ptr_c;
    ptr_c->bck = new;
}

void unlink_chunk(Chunk *old)
{
    Chunk *bck;
    Chunk *fwd;

    if (!old)
        return;
    bck = old->bck;
    fwd = old->fwd;
    if(bck)
        bck->fwd = fwd;
    if(fwd)
        fwd->bck = bck;
}

void unlink_heap(Heap *old)
{
    Heap *bck;
    Heap *fwd;

    if (!old)
        return;
    bck = old->bck;
    fwd = old->fwd;
    if(bck)
        bck->fwd = fwd;
    if(fwd)
        fwd->bck = bck;
}

// void ft_putnbr_size_t(size_t n)
// {
//     char    buffer[32];
//     int     i;

//     i = 31;
//     buffer[i] = '\0';

//     if (n == 0)
//     {
//         buffer[--i] = '0';
//     }
//     else
//     {
//         while (n > 0)
//         {
//             buffer[--i] = (n % 10) + '0';
//             n /= 10;
//         }
//     }

//     // Usamos el descriptor 2 (stderr) para impresión inmediata sin búfer
//     write(2, &buffer[i], 31 - i);
// }

size_t parse_size(size_t size)
{
    size_t aux;

    aux = size / 16;
    if (size % 16)
        aux = (aux + 1);
    aux = (aux * 16) + CHUNK_HEADER_SIZE;

    return (aux);
}
