
#include <stdio.h>
#include "cola.h"

/**
 * Es como un "constructor"  de la cola.
 * Deja la cola vacia, lista para usar.
 */
void iniciar_cola(ColaListos *cola)
{
    cola -> head = 0;
    cola -> tail = 0;
    cola -> cantidad = 0;
}

/**
 * Agrega un elemento al final de la cola.
 */
int agregar_cola(ColaListos *cola, int indice_proceso)
{
    if (cola -> cantidad >= CAPACIDAD_COLA)
    {
        fprintf(stderr, "La cola de listos esta llena (Capacidad = %d)\n",
                CAPACIDAD_COLA);
        
        return -1;
    }

    // Se guarda el indice al final de la cola
    cola -> datos[cola -> tail] = indice_proceso;

    // Se avanza al siguiente espacio para no sobreescribir
    cola -> tail++;

    // Incrementa la cantidad de elementos
    cola -> cantidad++;

    return 0;
}

/**
 * Saca y devuelve el indice de proceso al final de la cola.
 */
int sacar_cola(ColaListos *cola)
{
    if (cola_vacia(cola) == 1)
    {
        fprintf(stderr, "La cola de listos esta vacia.\n");
        return -1;
    }

    int valorHead = cola -> datos[cola -> head];

    cola -> head++;

    cola -> cantidad--;

    return valorHead;
}

/**
 * Devuelve 1 (verdadero) si la cola esta vacia, 0 (false) si tiene elementos.
 */
int cola_vacia(const ColaListos *cola)
{
    return cola -> cantidad == 0;
}