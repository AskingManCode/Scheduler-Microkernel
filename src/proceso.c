/**
 * @file proceso.c
 * 
 * Este archivo implementa las funciones declaradas en proceso.h
 */

#include <stdio.h>
#include "proceso.h"

/**
 * Esta funcion construye un proceso, llenando sus campos.
 */
void inicializar_proceso(PCB *proceso, int pid, long rafaga_total, long llegada)
{
    proceso -> pid = pid;
    proceso -> rafaga_total = rafaga_total;
    proceso -> tiempo_restante = rafaga_total;
    proceso -> llegada = llegada;
    proceso -> primera_ejecucion = -1; // No se ha no ejecutado 
    proceso -> finalizacion = 0; // No se ha ejecutado
    proceso -> estado = LISTO;
}

/**
 * Convierte un estado de proceso a su nombre convertido en texto.
 */
const char *nombre_estado_proceso(EstadoProceso estado) // Devuelve un puntero a una cadena constante.
{
    switch(estado){
        case NUEVO:
            return "NUEVO";
        case LISTO:
            return "LISTO";
        case EJECUTANDO:
            return "EJECUTANDO";
        case BLOQUEADO:
            return "BLOQUEADO";
        case TERMINADO:
            return "TERMINADO";
        default:
            return "DESCONOCIDO";
    }
}

/**
 * Muestra en consola lo que esta sucediendo con un proceso.
 */
void imprimir_evento_proceso(const PCB *proceso, long tiempo_actual, const char *evento)
{
    printf("[reloj] = %4ld | PID = %-3d | Estado = %-10s | Tiempo Restante = %-4ld | Evento = %s\n",
            tiempo_actual, proceso -> pid, nombre_estado_proceso(proceso -> estado), evento);
}

/**
 * Muestra una fila de resultados de un proceso.
 */
void imprimir_resultado_proceso(const PCB *proceso, long tiempo_espera, long tiempo_respuesta, long tiempo_retorno)
{
    printf("PID = %-3d | Rafaga = %-4ld | Tiempo de Espera = %-4ld | Tiempo de Respuesta = %-4ld | Tiempo de Retorno = %-4ld\n",
            proceso -> pid, proceso -> rafaga_total, tiempo_espera, tiempo_respuesta, tiempo_retorno);
}


