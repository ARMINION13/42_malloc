#include "../headers/malloc.h"

static Heap *TINY = NULL;
static Heap *SMALL = NULL;

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

void  link_heap(Heap *new, Heap *list)
{
    Heap *it;

    it = list;

    if (new == NULL)
        return;
    while (it->next != NULL)
        it = it->next;

    it->next = new;
    new->prev = list;

    return;
}

void unlink_heap(Heap *old)
{
    Heap *prev;
    Heap *next;

    prev = old->prev;
    next = old->next;

    prev->next = next;
    next->prev = prev;

    return;
}

Chunk *create_chunk(Chunk *ptr)
{

}

Heap *create_zone(size_t nbr_pages)
{
    Heap *ptr_h;
    Chunk *ptr_c;
    size_t page_size;

    page_size = sysconf(_SC_PAGESIZ); // tamaño de la pagina de mi sistema operativo
    ptr_h = mmap(NULL, page_size * nbr_pages, PROT_READ | PROT_WRITE, MAP_PRIVATE | MAP_ANONYMOUS, -1, 0);

    if (ptr_h == MAP_FAILED)
        return NULL;

    // Inicializacion del header del heap o zona
    ptr_h->size = page_size * nbr_pages;
    ptr_h->free_size = ptr_h->size - HEAP_HEADER_SIZE;
    ptr_h->next = NULL;
    ptr_h->prev = NULL;

    // Inicializacion del header del chunk
    ptr_c = ptr_h + 1;
    ptr_c->prev_size = 0;
    ptr_c->size = ptr_h->free_size - CHUNK_HEADER_SIZE;
    ptr_c->next = NULL;
    ptr_c->prev = NULL;


    return ptr_h;
}

void *ft_malloc(size_t size)
{
    Chunk *ptr = NULL;
    int it = 0;

    if (!size)
        return NULL;

    if (size <= TINY_CHUNK && TINY == NULL)
        TINY = create_zone(TINY_HEAP);
    else if (size <= SMALL_CHUNK && SMALL == NULL)
        SMALL = create_zone(SMALL_HEAP);

    if (!(ptr = find_free_chunk(size)))
        link_heap(create_zone(size), TINY);
    
    heap_visualize();
    return (void *)(ptr + 1);
}