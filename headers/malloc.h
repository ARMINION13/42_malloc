#ifndef MALLOC_H
# define MALLOC_H
# include <stdlib.h>
# include <stdio.h>
# include <unistd.h>
# include <sys/mman.h>

typedef struct  Heap {

    size_t size; // tamaño total del heap
    size_t free_size; // espacio libre en el heap

    struct Heap *next;  // puntero al siguiente heap
    struct Heap *prev;  // puntero al anterior heap

}               Heap;

typedef struct  Chunk {
    
    size_t prev_size; //tamaño del chunk anterior
    size_t size; //tamaño de este chunk
    
    struct Chunk *next; //puntero al siguiente chunk libre
    struct Chunk *prev; //puntero al chunk anterior libre
    
}               Chunk;


#define MALLOC_ALIGNMENT 16
#define MIN_CHUNK_SIZE 32
#define TINY_CHUNK 160
#define SMALL_CHUNK 1024
#define TINY_HEAP 4
#define SMALL_HEAP 26
#define HEAP_HEADER_SIZE 32
#define CHUNK_HEADER_SIZE 32

void            *ft_malloc(size_t size);
void            ft_free(void *ptr);
void            heap_visualize();
Chunk           *get_start_chunck();
size_t          unflag_size(size_t size);
void            heap_visualize(Heap *TINY);



#endif