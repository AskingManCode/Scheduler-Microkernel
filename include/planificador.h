
/**
 * @file planificador_h
 * 
 * Round Robin = "Turno Rotativo"
 * - Cada proceso recibe un "quantum" (porcion de tiempo) de CPU
 * - Si no termina, se reubica al final de la cola
 * - Se repite hasta que todos terminan.
 */

#ifndef PLANIFICADOR_H
#define PLANIFICADOR_H


// -------------------------------------------------------------
// IMPORTACIONES
// -------------------------------------------------------------

#include "proceso.h"


// -------------------------------------------------------------
// CONSTANTES
// -------------------------------------------------------------

#define QUANTUM_DEFECTO 4 // Unidades de tiempo


// -------------------------------------------------------------
// FUNCIONES (Contratos)
// -------------------------------------------------------------

void planificador_RoundRobin(PCB *tabla_PCB, int total_procesos, int quantum, long *esperas, long *respuestas, long *retornos, int pausa_ms);

#endif // PLANIFICADOR_H