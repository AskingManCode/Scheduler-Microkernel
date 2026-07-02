/**
 * @file cola.h
 * 
 * Cola circular de procesos listos
 * - Los procesos entran por un lado "Agregar"
 * - Los procesos salen por otro "Sacar"
 * - Si un proceso no termina, se vuelve a Ingresar
 */

#ifndef COLA_H
#define COLA_H


// -------------------------------------------------------------
// IMPORTACIONES
// -------------------------------------------------------------
#include "proceso.h" // para usar MAX_PROCESOS


// -------------------------------------------------------------
// CONSTANTES
// -------------------------------------------------------------

#define CAPACIDAD_COLA (MAX_PROCESOS * 50)
/**
 *  ¿Por que MAX_PROCESOS * 50?
 *  Un proceso puede re-encolarse MUCHAS veces.
 *  Ejemplo: si un proceso tiene rafaga 100 y quantum 4,
 *  se encolara 100/4 = 25 veces.
 *  Debido a esto se decidio multiplicar por 50 para tener margen de sobra.
 */


// -------------------------------------------------------------
// ESTRUCTURAS DE DATOS
// -------------------------------------------------------------

/**
 * Arreglo de enteros, cada elemento es el indice 
 * de un proceso en la tabla PCB. 
 * No se guarda el proceso completo, solo su 
 * posicion en el arreglo como referencia.
 */
typedef struct 
{
    int datos[CAPACIDAD_COLA];

    int head; 

    int tail;

    int cantidad; // cantidad de elementos en cola.

} ColaListos;


// -------------------------------------------------------------
// FUNCIONES (Contratos)
// -------------------------------------------------------------

void iniciar_cola(ColaListos *cola);

int agregar_cola(ColaListos *cola, int indice_proceso);

int sacar_cola(ColaListos *cola);

int cola_vacia(const ColaListos *cola);

#endif // COLA_H