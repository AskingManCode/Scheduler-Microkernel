
/**
 * @file main.c
 * 
 * Punto de entrada del programa
 */

#include <stdio.h>
#include <stdlib.h>


// -------------------------------------------------------------
// IMPORTACIONES
// -------------------------------------------------------------

#include "proceso.h"
#include "cola.h"
#include "planificador.h"
#include "io_archivo.h"


// -------------------------------------------------------------
// CONSTANTES
// -------------------------------------------------------------

/** Archivo de procesos */
#define ARCHIVO_PROCESOS_DEFECTO "data/procesos.bin"

/** Archivo donde se acumulan los resultados */
#define ARCHIVO_RESULTADOS "data/resultados.txt"

/** Pausea entre eventos de consola */
#define PAUSA_VISUAL_MS 150

/**
 * Main
 */
int main (int argc, char *argv[]) 
{
    const char *ruta_procesos = ARCHIVO_PROCESOS_DEFECTO;
    int quantum = QUANTUM_DEFECTO;

    if (argc >= 2) 
    {
        ruta_procesos = argv[1];
    }

    if (argc >= 3) 
    {

        quantum = atoi(argv[2]);
        
        /* Validacion: el quantum debe ser positivo */
        if (quantum <= 0) 
        {
            fprintf(stderr, "El quantum debe ser un entero positivo. Usando %d por defecto.\n",
                    QUANTUM_DEFECTO);
            quantum = QUANTUM_DEFECTO;
        }
    }

    /**
     * Generacion de un archivo para pruebas
     */
    if (argc < 2) {
        printf("No se indico archivo de procesos: generando uno de prueba en '%s'...\n",
               ARCHIVO_PROCESOS_DEFECTO);
        
        /** Funcion que */
        if (io_generar_archivo(ARCHIVO_PROCESOS_DEFECTO, 6, 5, 30) != 0) 
        {
            fprintf(stderr, "No se pudo generar el archivo de prueba.\n");

            return 1;  // error
        }
    }

    // Declaracion de arreglos
    PCB tabla[MAX_PROCESOS];           /* Los procesos leidos del archivo */
    long esperas[MAX_PROCESOS];        /* Tiempo de espera de cada uno */
    long respuestas[MAX_PROCESOS];     /* Tiempo de respuesta de cada uno */
    long retornos[MAX_PROCESOS];       /* Tiempo de retorno de cada uno */

    /** Lectura de procesos del archivo binario */
    int total_procesos = io_leer_procesos(ruta_procesos, tabla, MAX_PROCESOS);
    
    if (total_procesos < 0) 
    {
        return 1;  // Error
    }

    if (total_procesos == 0) 
    {
        fprintf(stderr, "El archivo '%s' no contiene procesos validos.\n", ruta_procesos);
        return 1;
    }

    printf("Se cargaron %d procesos desde '%s'.\n", total_procesos, ruta_procesos);
    
    /** Round Robin */
    planificador_RoundRobin(tabla, total_procesos, quantum, esperas, respuestas, retornos, PAUSA_VISUAL_MS);

    /**
     * Resultados para mostrar en consola
     */
    printf("--- Resultados (quantum = %d) ---\n", quantum);
    
    long suma_espera = 0, suma_respuesta = 0, suma_retorno = 0;
    
    for (int i = 0; i < total_procesos; i++) 
    {
        imprimir_resultado_proceso(&tabla[i], esperas[i], respuestas[i], retornos[i]);
        
        suma_espera += esperas[i];
        suma_respuesta += respuestas[i];
        suma_retorno += retornos[i];
    }
    
    /* Calcular y mostrar promedios */
    printf("Promedios -> Espera: %.2f | Respuesta: %.2f | Retorno: %.2f\n",
           (double) suma_espera / total_procesos,
           (double) suma_respuesta / total_procesos,
           (double) suma_retorno / total_procesos);

    /**
     * Guardar resultados en archivo de texto
     */
    io_guardar_resultados(ARCHIVO_RESULTADOS, tabla, total_procesos, esperas, respuestas, retornos, quantum);

    printf("\nResultados guardados (acumulados) en '%s'.\n", ARCHIVO_RESULTADOS);

    return 0; // Exito
}