
/**
 * @file proceso.h
 * 
 * Define la estructura PCB (Process Control Block) que representa un proceso en el sistema operativo, 
 * junto con sus posibles estados y las funciones para crearlo, destruirlo e imprimir su informacon.
 */

#ifndef PROCESO_H
#define PROCESO_H

 
// -------------------------------------------------------------
// CONSTANTES
// -------------------------------------------------------------

/**
 * Cantidad de procesos que el simulador va a manejar.
 */
#define MAX_PROCESOS 50

/**
 * Ultimo Byte del proceso, al ser leido del archivo binario de entrada,
 * indica que ya finalizó la lectura del procesos.
 */
#define BYTE_FIN_PROCESO 0xFF


// -------------------------------------------------------------
// ESTRUCTURAS DE DATOS
// -------------------------------------------------------------

/**
 * Estados de un Proceso: NUEVO, LISTO, EJECUTANDO, BLOQUEADO, TERMINADO.
 */
typedef enum 
{    
    NUEVO,       /* El proceso fue creado pero aun no entra a la cola */
    LISTO,       /* Espera turno de CPU en la cola circular */
    EJECUTANDO,  /* Tiene actualmente el CPU asignado */
    BLOQUEADO,   /* Reservado para futuras extensiones (E/S) */
    TERMINADO    /* Ya consumio toda su rafaga de CPU */

} EstadoProceso;

/** 
 * PCB = Process Control Block
 * Es la "ficha" que el sistema operativo mantiene por cada proceso
 * Contiene toda la informacion relevante del proceso para gestionarlo.
 */
typedef struct 
{
    int pid;                // pid = identificador unico del proceso
    long rafaga_total;      // rafaga_total = cuantos "bytes" de CPU necesita el proceso para terminar su ejecucion
    long tiempo_restante;   // tiempo_restante = cuanto tiempo le falta por ejecutar (igual a rafaga_total al inicio, y va disminuyendo a medida que se ejecuta)
    long llegada;           // llegada = instante de tiempo en que el proceso fue creado y agregado a la cola de procesos
    long primera_ejecucion; // primera_ejecucion = instante de tiempo en que el proceso fue ejecutado por primera vez (Para calcular el tiempo de respuesta)
    long finalizacion;      // finalizacion = instante de tiempo en que el proceso terminó su ejecucion (Para calcular el tiempo de retorno)
    EstadoProceso estado;   // estado = estado actual del proceso (NUEVO, LISTO, EJECUTANDO, BLOQUEADO, TERMINADO)

} PCB;


// -------------------------------------------------------------
// FUNCIONES (Contratos)
// -------------------------------------------------------------

void inicializar_proceso(PCB *proceso, int pid, long rafaga_total, long llegada);

void imprimir_evento_proceso(const PCB *proceso, long tiempo_actual, const char *evento);

void imprimir_resultado_proceso(const PCB *proceso, long tiempo_espera, long tiempo_respuestas, long tiempo_retorno);

const char *nombre_estado_proceso(EstadoProceso estado);

#endif // PROCESO_H 