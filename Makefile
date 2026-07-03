# =====================================================================
# Makefile
# ---------------------------------------------------------------------
# Este archivo automatiza la compilacion.
# 
# En C#, Visual Studio hace todo esto automaticamente.
# En C con Linux, usamos Make.
# 
# Como funciona:
#   - make        -> compila todo
#   - make run    -> compila y ejecuta
#   - make clean  -> borra archivos compilados
# 
# SINTAXIS BASICA:
#   objetivo: dependencias
#       comando
#   
#   (El TAB antes del comando es OBLIGATORIO, no espacios)
# =====================================================================

# Compilador a usar. 'gcc' es el compilador estandar de C en Linux.
CC = gcc

# Flags (opciones) del compilador:
#   -Wall      = muestra TODAS las advertencias (Warnings All)
#   -Wextra    = advertencias extra (mas estricto)
#   -std=c11   = usar el estandar C de 2011 (moderno pero estable)
#   -Iinclude   = buscar archivos .h en la carpeta 'include/'
CFLAGS = -Wall -Wextra -std=c11 -Iinclude

# Nombre del ejecutable final
TARGET = bin/simulador_rr

# Archivos fuente (.c)
SRCS = src/main.c src/proceso.c src/cola.c src/io_archivo.c src/planificador.c

# Archivos objeto (.o) - se generan automaticamente de los .c
# $(SRCS:.c=.o) reemplaza .c por .o en cada archivo
# Luego agregamos obj/ al inicio de cada uno
OBJS = $(patsubst src/%.c,obj/%.o,$(SRCS))

# =====================================================================
# REGLAS
# =====================================================================

# 'all' es el objetivo por defecto (se ejecuta con solo 'make')
all: $(TARGET)

# Como crear el ejecutable: necesita todos los .o
$(TARGET): $(OBJS)
	# Crear la carpeta bin/ si no existe
	mkdir -p bin
	# Enlazar (link) todos los .o en un solo ejecutable
	# -o = output (salida)
	$(CC) $(OBJS) -o $(TARGET)

# Como crear cada .o desde su .c correspondiente
# % es un comodin (wildcard)
obj/%.o: src/%.c
	# Crear la carpeta obj/ si no existe
	mkdir -p obj
	# Compilar (-c) el .c a .o, buscando .h en include/
	$(CC) $(CFLAGS) -c $< -o $@

# 'run' compila y ejecuta
run: $(TARGET)
	./$(TARGET)

# 'clean' borra archivos compilados para empezar de cero
clean:
	rm -f obj/*.o $(TARGET)
	rm -f data/procesos.bin data/resultados.txt

# Indica que 'all', 'run', 'clean' no son archivos reales
.PHONY: all run clean
