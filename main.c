#include <stdio.h>
#include <stdlib.h>
#include "./headers/malloc.h"

void prueba_char(char *prueba)
{
    prueba[0] = '4';
}

int main ()
{
    char *prueba = NULL;

    //heap_visualize();
    prueba = malloc(sizeof(char) * 2);
    prueba[0] = '0';
    prueba[1] = 0;
    printf("Replica %s\n", prueba);
    prueba_char(prueba);
    printf("Replica %s\n", prueba);
    free(prueba);
    // printf("Replica %i\n", *prueba);
    return 0;
}