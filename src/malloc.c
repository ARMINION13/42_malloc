#include "../headers/malloc.h"

static Heap *TINY = NULL;
static Heap *SMALL = NULL;

Heap *create_zone(size_t nbr_pages)
{
    Heap *ptr_h;
    Chunk *ptr_c;
    size_t page_size;

    page_size = sysconf(_SC_PAGESIZE); // tamaño de la pagina de mi sistema operativo
    ptr_h = mmap(NULL, page_size * nbr_pages, PROT_READ | PROT_WRITE, MAP_PRIVATE | MAP_ANONYMOUS, -1, 0);
    if (ptr_h == MAP_FAILED)
        return NULL;
    // Inicializacion del header del heap o zona
    ptr_h->size = page_size * nbr_pages;
    ptr_h->free_bin = (Chunk *)(ptr_h + 1);
    ptr_h->fwd = NULL;
    ptr_h->bck = NULL;
    // Inicializacion del header del chunk
    ptr_c = (Chunk *)(ptr_h + 1);
    ptr_c->prev_size = 0;
    ptr_c->size = set_flags(0x2, (ptr_h->size - HEAP_HEADER_SIZE));
    ptr_c->fwd = NULL;
    ptr_c->bck = NULL;

    return ptr_h;
}

Chunk *ft_split(Chunk *ptr_c, size_t size)
{
    Chunk *unused;

    unused = NULL;
    if ((unflag_size(ptr_c->size) - size) > MIN_CHUNK_SIZE)
    {
        unused = (Chunk *)((char *)ptr_c + size);
        unused->prev_size = size;
        unused->size = ptr_c->size - size;
        unused->fwd = ptr_c->fwd;
        unused->bck = ptr_c->bck;
        if (unused->fwd)
            unused->fwd->bck = unused;
        if (unused->bck)
            unused->bck->fwd = unused;
        ptr_c->fwd = unused;
    }
    else
    {
        if (ptr_c->fwd)
            ptr_c->fwd->bck = ptr_c->bck;
        if (ptr_c->bck)
            ptr_c->bck->fwd = ptr_c->fwd;
    }
    ptr_c->size = size;

    return ptr_c;
}

Chunk *find_free_chunk(size_t size)
{
    Heap *ptr_h = NULL;
    Chunk *ptr_c = NULL;

    if (size <= TINY_CHUNK)
        ptr_h = TINY;
    else if (size <= SMALL_CHUNK)
        ptr_h = SMALL;
    ptr_c = ptr_h->free_bin;
    while (ptr_h)
    {
        ptr_c = ptr_h->free_bin;
        while (ptr_c && size < unflag_size(ptr_c->size))
            ptr_c = ptr_c->fwd;
        if (ptr_c)
            break;
        ptr_h = ptr_h->fwd;
    }
    if (!ptr_h)
    {
        if (size <= TINY_CHUNK)
        {
            ptr_h = create_zone(TINY_HEAP);
            link_heap(ptr_h, TINY);
        }
        else if (size <= SMALL_CHUNK)
        {
            ptr_h = create_zone(SMALL_HEAP);
            link_heap(ptr_h, SMALL);
        }
        ptr_c = ptr_h->free_bin;
    }
    ptr_c = ft_split(ptr_c, size);
    fix_free_bin(ptr_h);

    return ptr_c;
}

void *malloc(size_t size)
{
    Chunk *ptr_c = NULL;
    int it = 0;

    if (!size)
        return NULL;
    size = parse_size(size);
    if (size <= TINY_CHUNK && TINY == NULL)
        TINY = create_zone(TINY_HEAP);
    else if (size <= SMALL_CHUNK && SMALL == NULL)
        SMALL = create_zone(SMALL_HEAP);

    //TODO: IMPLEMENTAR LOS LARGE CHUNKS

    ptr_c = find_free_chunk(size);     
    //heap_visualize();

    return (void *)(ptr_c + 1);
}