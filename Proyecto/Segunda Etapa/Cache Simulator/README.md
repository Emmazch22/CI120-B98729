**Segunda etapa del proyecto - Simulador de Memoria Cache**

- Autor: Emmanuel Zúñiga Chaves
- Carné: B98729

## Pre requisitos

Para la compilación y ejecución de los ficheros .cpp es necesario contar con un compilador adecuado, por ejemplo g++.

## Compilación

Para la compilación de los ficheros .cpp es necesario ejecutar el siguiente comando:

```
g++ -O0 -g -Wall main.cpp -o cache_simulator src/Simulator.cpp src/Cache.cpp
```

o bien, usar el comando:
```
$ make
```

## Ejecución

Para la ejecución del simulador se debe de ingresar el siguiente comando:

```
./cache_simulator <sets> <blocks> <bytes> <strategy one> <strategy two> <replacement algorithm> <access time (cycles)> <next level access time(cyles)> <file>
```
A continuación se explica cada parámetro:

	- sets: Cantidad de conjuntos de la cache en potencia de dos.
	- blocks: Cantidad de bloques por conjunto en potencia de dos.
	- bytes: Tamaño en bytes de la cache, mayor o igual a 4.
	- strategy one: Politica de escritura 1 (write-through o no-write allocate).
	- strategy two: Politica de escritura 2 (write-through o no-write allocate).
	- replacement algorithm: Politica de reemplazo en la cache (lru, fifo o random).
	- access time: Tiempo T que tarda en realizar un ciclo.
	- next level acces: Tiempo Tn que tarda en acceder al siguiente nivel de la memoria.
	- file: Archivo de traza (el formato de los archivos se explican más adelante).

Un ejemplo de ejecucíón seria el siguiente:

```
./cache_simulator 256 1 16 write-through no-write-allocate random 13 230 trace_files/tracefile.txt
```
## Requisitos del archivo de traza

El archivo de traza debe de ser en formato .txt (recomendada codificación plain text). Cada instrucción debe de venir en lineas independientes y deben de tener el siguiente formato:

Operador Instrucción,Dato
Ejemplo:
```
L 0111ffff,8
S 0111ffff,6
```

El operador funciona tanto en mayúscula como en minúscula, por otro lado la instrucción debe de ser obligatoriamente de 32 bits, es decir 8 carácteres en hexadecimal de (de 0 hasta F). No obstante el dato de cada linea resulta indiferente.

## Pruebas

A continuación se presenta una prueba de ejecución:
```
$ ./cache_simulator 256 1 16 write-through no-write-allocate random 13 230 trace_files/traza2.txt
Simulated for a Direct Mapped Cache

Instructions 	 Cycles 	 Events
l 00000000,8		243		Miss
l 00000000,8		13		Hit
l 00000000,6		13		Hit
l 00000000,8		13		Hit
s 00000000,5		243		Hit
l 00000000,2		13		Hit
l 00000000,8		13		Hit
l 00000000,6		13		Hit
s 00000000,6		243		Hit
l 00000000,8		13		Hit

==============================
Total Cycles: 820
Total Hits: 9
Total Misses. 1
```
## Notas importantes

En esta etapa del proyecto solo es funcional una memoria cache con las siguientes configuraciones:

1. “direct-mapped”, “write-through” y “no-write allocate”
2. “fully associative”, “write-through” y “no-write-allocate”

Por lo tanto, valores necesarios para el funcionamiento de otras configuraciones no son considerados en esta solución. Por ejemplo evicted o dirty...

Para escoger una cache con configuración direct mapped deben de haber N conjuntos de un bloque cada uno. Por otro lado, para una cache fully associative debe de haber un conjunto de N bloques.

La Cache no simula un nivel en especifico, no obstante sea asume que la cache puede escribir datos en los siguientes niveles por esto se escoge un tiempo de acceso al siguiente nivel.

El simulador no funciona con la instrucción Modify 'M' (pues no fue programada) por lo tanto archivos de traza que presenten dicha instrucción no serviran para el simulador. Por otro lado, como se mencionó anteriormente el Simulador funciona especificamente con instrucciones de 32 bits (8 bytes) con el formato explicado anteriormente, por lo tanto si se presenta alguna instrucción que sobrepase dicha extensión pueden presentarse resultados incoherentes.
