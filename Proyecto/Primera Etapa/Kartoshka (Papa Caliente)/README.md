**Primera estapa del proyecto - Juego de la "papa" caliente (Kartoshka)**

Autor: Emmanuel Zúñiga Chaves
Carné: B98729

## Pre requisitos

Para la compilación y ejecución del fichero .c es necesario contar con Pthreads, para ello se puede utilizar el siguiente comando:

```
$ sudo apt-get install libpthread-stubs0-dev 
```

## Compilación

Para la compilación del fichero .c basta con ejecutar el comando: 

```
$ gcc -Wall Kartoshka.c -o kartoshka -pthread
```

o bien, usar el comando:
```
$ make
```

## Ejecución

Para la ejecución del programa se debe de ingresar el siguiente comando:

```
$ ./kartoshka n v s
```
Donde:
- *n* corresponde a la cantidad de hilos.
- *v* el valor de la papa (item).
- *s* sentido de rotación.

Por ejemplo:
```
$ ./kartoshka 5 10 -1
```

En este caso, la simulación del juego se haría con 5 hilos, estableciendo un valor inicial de 10 y un sentido de rotación a la derecha (-1).

## Pruebas

A continuación se presenta una prueba de ejecución:
```
$ ./kartoshka 5 10 1
The item is 1 
Creating a game with 5 players, start player # 0 with item # 1 
Thread # 1 changing the token value to 4 
Thread # 0 changing the token value to 4 
Thread # 4 changing the token value to 4 
Thread # 3 changing the token value to 4 
Thread # 0 changing the token value to 2 
Thread # 1 changing the token value to 2 
Thread # 2 changing the token value to 4 
Thread # 3 changing the token value to 2 
Thread # 0 changing the token value to 1 
Thread # 0 has left the game.
Thread # 2 changing the token value to 2 
Thread # 4 changing the token value to 2 
Thread # 2 changing the token value to 1 
Thread # 2 has left the game.
Thread # 3 changing the token value to 1 
Thread # 3 has left the game.
Thread # 1 changing the token value to 1 
Thread # 1 has left the game.
The winner is thread # 1.
```

NOTA: En este caso el acceso a la salida estandar (printf) no sigue ningún orden en especifico. No obstante, internamente los hilos cambian el valor de la papa siguiendo el sentido de rotación especificado. Por lo tanto, la salida en consola no es un indicativo del orden tomado por los hilos.
