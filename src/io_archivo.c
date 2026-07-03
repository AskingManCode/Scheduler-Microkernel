
/**
 * @file io_archivo.c
 * 
 * Implementacion de las funciones de E/S de archivos.
 * - Abre archivos
 * - Genera numeros aleatorios
 * - Trabaja con fechas y horas
 */

#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include "io_archivo.h"

/**
 * Lee byte por byte un archivo binario y crea los procesos.
 */
int io_leer_procesos(const char *ruta, PCB *tabla_PCB, int max_procesos)
{
    FILE *archivo = fopen(ruta, "rb");

    if (archivo == NULL)
    {
        perror("Error abriendo el archivo de procesos.");
        return -1;
    }

    int total_procesos = 0;     /* Cantidad de procesos creados */
    int pid_actual = 1;         /* valor del siguiente proceso */
    long bytes_proceso = 0;     /* Acumulado de bytes del proceso actual */
    unsigned char byte_leido;   /* By=uffer para leer un byte */

    /**
     * BUcle principal, para leer byte por byte
     */
    while (fread(&byte_leido, sizeof(unsigned char), 1, archivo) == 1)
    {
        if (byte_leido == BYTE_FIN_PROCESO)
        {
            if (bytes_proceso > 0 && total_procesos < max_procesos)
            {
                inicializar_proceso(&tabla_PCB[total_procesos], pid_actual, bytes_proceso, 0);

                total_procesos++;
                pid_actual++;
            }
        }
        else
        {
            bytes_proceso++;
        }

        if (total_procesos >= max_procesos)
        {
            break;
        }
    }

    fclose(archivo);

    return total_procesos;
}


int io_generar_archivo(const char *ruta, int cantidad_procesos, int rafaga_min, int rafaga_max)
{
    FILE *archivo = fopen(ruta, "wb");

    if (archivo == NULL)
    {
        perror("Error creando el archivo de prueba.");
        return -1;
    }

    srand((unsigned int) time(NULL));

    /** 
     * Bluque principal para generar cada proceso
     */
    for (int i = 0; 1 < cantidad_procesos; i++)
    {
        // Tamanio aleatorio de la rafaga
        int tamanio = rafaga_min + (rand() % (rafaga_max - rafaga_min + 1));

        for (int x = 0; x < tamanio; x++)
        {
            // bytes aleatorios entre 0 y 253
            unsigned char dato = (unsigned char) (rand() % 0xFE); // Evita usar el byte que es fin de proceso
            fwrite(&dato, sizeof(unsigned char), 1, archivo);
        }

        unsigned char fin = BYTE_FIN_PROCESO; // Escribe el byte de fin de proceso
        fwrite(&fin, sizeof(unsigned char), 1, archivo);
    }

    fclose(archivo);
    return 0;
}


void io_guardar_resultados(const char *ruta, const PCB *tabla_PCB, int total_procesos, const long *esperas, const long *respuestas, const long *retornos, int quantum)
{
    FILE *archivo = fopen(ruta, "a");

    if (archivo == NULL) {
        perror("Error abriendo el archivo de resultados.");
        return;
    }

    // Fecha y hora
    time_t ahora = time(NULL);                  // Tiempo actual en segundos
    struct tm *desglosado = localtime(&ahora);  // Desglosado de componentes
    char fecha_hora[64];                        // buffer para el string formateado
    strftime(fecha_hora, sizeof(fecha_hora), "%d/%m/%Y %H:%M:%S", desglosado);

    fprintf(archivo, "==================================================\n");
    fprintf(archivo, "Ejecucion: %s | Algoritmo: Round Robin | Quantum: %d\n", fecha_hora, quantum);
    fprintf(archivo, "==================================================\n");

    /* Encabezados de la tabla */
    fprintf(archivo, "%-6s %-10s %-10s %-12s %-10s\n",
            "PID", "Rafaga", "Espera", "Respuesta", "Retorno");

    // Variable apra calcular promedio
    long suma_espera = 0, suma_respuesta = 0, suma_retorno = 0;

    // UNa fila por cada proceso
    for (int i = 0; i < total_procesos; i++) {
        fprintf(archivo, "%-6d %-10ld %-10ld %-12ld %-10ld\n",
                tabla_PCB[i].pid, tabla_PCB[i].rafaga_total,
                esperas[i], respuestas[i], retornos[i]);
        
        // Acumulado de promedios
        suma_espera += esperas[i];
        suma_respuesta += respuestas[i];
        suma_retorno += retornos[i];
    }

    // Guardado de promedios
    if (total_procesos > 0) {
        fprintf(archivo, "--------------------------------------------------\n");
        fprintf(archivo, "Promedios -> Espera: %.2f | Respuesta: %.2f | Retorno: %.2f\n\n",
                (double) suma_espera / total_procesos,
                (double) suma_respuesta / total_procesos,
                (double) suma_retorno / total_procesos);
    }

    fclose(archivo);
}