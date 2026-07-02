
/**
 * @file io_archivo.h
 * 
 * Este modulo maneja TRES tareas:
 *  1. Leer un archivo binario que contiene "procesos simulados"
 *  2. Generar un archivo binario de prueba (para probar sin datos externos)
 *  3. Guardar resultados en un archivo de texto (acumulativo)
 */

#ifndef IO_ARCHIVO_H
#define IO_ARCHIVO_H


// -------------------------------------------------------------
// IMPORTACIONES
// -------------------------------------------------------------
#include "proceso.h"


// -------------------------------------------------------------
// FUNCIONES (Contratos)
// -------------------------------------------------------------

int io_leer_procesos(const char *ruta, PCB *tabla_PCB, int max_procesos);

int io_generar_archivo(const char *ruta, int cantidad_procesos, int rafaga_min, int rafaga_max);

void io_guardar_resultados(const char *ruta, const PCB *tabla_PCB, int total_procesos, const long *esperas, const long *respuestas, const long *retornos, int quantum);

#endif // IO_ARCHIVO_H