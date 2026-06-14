#ifndef MALLOC_H
# define MALLOC_H
# include <stdlib.h>
# include <stdio.h>
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

    int free; //indica si el chunk esta libre

    struct Chunk *next; //puntero al siguiente chunk
    struct Chunk *prev; //puntero al chunk anterior

}               Chunk;

void            *malloc(size_t size);

#endif