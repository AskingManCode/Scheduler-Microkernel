#include "planificador.h"

/**
 * @file planificador.c
 *
 * IMPLEMENTACION del algoritmo Round Robin.
 * 
 * Responsable de decidir en todo momento que proceso
 * de la cola de listos recibe la CPU, durante
 * cuanto tiempo, y que ocurre cuando este tiempo se
 * agota o cuando el proceso concluye
 */

#define _DEFAULT_SOURCE

#include <stdio.h>
#include <unistd.h> // Sirve para pausar con unsleep
#include "planificador.h"
#include "cola.h"

/**
 * Funcion "privada" (static)
 * 
 * Hace una pausa para que la ejecucuon 
 * se vea paso a paso.  
 */
static void pausa_visual(int pausa_ms) {
    
    if (pausa_ms > 0) 
    {
        usleep((unsigned int) pausa_ms * 1000);
    }
}

/**
 * PASO A PASO DEL ALGORITMO:
 * 1. Crear cola vacia
 * 2. Agregar todos los procesos a la cola (llegan en tiempo 0)
 * 3. Mientras haya procesos sin terminar:
 *   - Sacar el proceso del frente de la cola
 *   - Darle el CPU (cambiar estado a EJECUTANDO)
 *   - Si es su primera vez, registrar tiempo de respuesta
 *   - Ejecutar por 'quantum' unidades O hasta que termine
 *   - Si termino: marcar como TERMINADO, registrar finalizacion
 *   - Si no termino: restar quantum, volver a LISTO, re-agregar
 * 4. Calcular metricas finales
 */
void planificador_RoundRobin(PCB *tabla_PCB, int total_procesos, int quantum, long *esperas, long *respuestas, long *retornos, int pausa_ms)
{
    // Crear cola de procesos listos
    ColaListos listos;
    iniciar_cola(&listos);

    // Reloj virtual
    long tiempo_actual = 0;

    // Contador de procesos ya terminados
    int terminados = 0;

    for (int i = 0; i < total_procesos; i++)
    {
        agregar_cola(&listos, i);
    }

    printf("\n--- Iniciando planificacion Round Robin (quantum = %d) ---\n\n", quantum);

    /**
     * Bucle principal, mientras ninguno haya terminado
     */
    
    while (terminados < total_procesos) 
    {
        // Sacar el proceso que esta al frente de la cola
        int idx = sacar_cola(&listos);

        PCB *p = &tabla_PCB[idx]; // puntero al proceso en la tabla

        p->estado = EJECUTANDO; // Cambio de estado
        
        // Primer turno de CPU
        if (p -> primera_ejecucion == -1) 
        {
            p -> primera_ejecucion = tiempo_actual;
        }

        imprimir_evento_proceso(p, tiempo_actual, "recibe el CPU.");
        pausa_visual(pausa_ms);

        /**
         * Decicion: terminar este quantum o no?
         */
        if (p -> tiempo_restante <= quantum)
        {
            /**
             * Caso: EL proceso termina dentro de este quantum
             */
            tiempo_actual += p -> tiempo_restante;

            tiempo_actual += p -> tiempo_restante;

            p -> tiempo_restante = 0;

            p -> estado = TERMINADO; // Cambiod e estado

            p -> finalizacion = tiempo_actual;

            terminados++;

            imprimir_evento_proceso(p, tiempo_actual, "termina su ejecucion.");
        }
        else
        {
            /**
             * Caso: El proceso aun no termina (se agota el quantum)
             */
            tiempo_actual += quantum;

            p->tiempo_restante -= quantum;

            p->estado = LISTO; // Camvio de estado

            imprimir_evento_proceso(p, tiempo_actual, "quantum agotado, vuelve a LISTO.");

            agregar_cola(&listos, idx);
        }

        pausa_visual(pausa_ms);
    }

    /**
     * Todos los procesos termiandos
     */
    printf("\n--- Planificacion finalizada en tiempo = %ld ---\n\n", tiempo_actual);

    /**
     * Calculod e Metricas
     */
    for (int i = 0; i < total_procesos; i++) 
    {
        /* Tiempo de retorno = cuando termino - cuando llego */
        retornos[i] = tabla_PCB[i].finalizacion - tabla_PCB[i].llegada;
        
        /* Tiempo de espera = retorno - cuanto trabajo tenia */
        esperas[i] = retornos[i] - tabla_PCB[i].rafaga_total;
        
        /* Tiempo de respuesta = primer turno - cuando llego */
        respuestas[i] = tabla_PCB[i].primera_ejecucion - tabla_PCB[i].llegada;
    }
}