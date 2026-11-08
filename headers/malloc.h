#ifndef MALLOC_H
# define MALLOC_H
# include <stdio.h>
# include <unistd.h>
# include <sys/mman.h>

typedef struct  Heap {

    size_t  size; // tamaño total del heap
    
    struct Heap    *fwd;  // puntero al siguiente heap
    struct Heap    *bck;  // puntero al anterior heap
    struct Chunk   *free_bin;  // puntero a la lista de chunks libres

}               Heap;

typedef struct  Chunk {
    
    size_t      prev_size; //tamaño del chunk anterior con header incluido
    size_t      size; //tamaño de este chunk con header incluido

    struct Chunk *fwd; //siguiente puntero libre
    struct Chunk *bck; //anterior puntero libre
    
}               Chunk;

// 0x0 == 000 Previo en uso
// 0x1 == 001 Previo en uso
// 0x2 == 010 Chunk libre
// 0x3 == 011
// 0x4 == 100 Chunk mmap
// 0x5 == 101
// 0x6 == 110
// 0x7 == 111 Todas las flags

// &             |
// 0 & 0 = 0     0 | 0 = 0
// 1 & 0 = 0     1 | 0 = 1
// 0 & 1 = 0     0 | 1 = 1
// 1 & 1 = 1     1 | 1 = 1

#define MALLOC_ALIGNMENT 16
#define MIN_CHUNK_SIZE 48
#define TINY_CHUNK 160
#define SMALL_CHUNK 1024
#define TINY_HEAP 4
#define SMALL_HEAP 26
#define HEAP_HEADER_SIZE 32
#define CHUNK_HEADER_SIZE 32

void            *malloc(size_t size);
void            free(void *ptr);
//void            heap_visualize(Heap *TINY, Heap *SMALL);
size_t          unflag_size(size_t size);
size_t          set_flags(size_t hex, size_t size);
size_t          get_flags(size_t size);
void            fix_free_bin(Heap *ptr_h);
void            link_heap(Heap *new, Heap *list);
void            unlink_chunk(Chunk *old);
void            unlink_heap(Heap *old);
size_t          parse_size(size_t size);
bool            is_free(Chunk *chunk);
void            link_free_chunk(Chunk *new);






#endif