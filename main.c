#include "./headers/malloc.h"

void prueba_int(int *prueba)
{
    *prueba = 42;
}

int main ()
{
    int *prueba = NULL;

    heap_visualize();
    prueba = ft_malloc(100);
    printf("%i\n", *prueba);
    prueba_int(prueba);
    printf("%i\n", *prueba);
    return 0;
}