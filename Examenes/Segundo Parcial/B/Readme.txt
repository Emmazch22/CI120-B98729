Las instrucciones cargadas en memoria son las siguientes:
0. sw $1, 32($0)
1. lh $2, 32($0)
2. sb $1, 100($10)
3. lw $3, 100($10)

cuyo ensamblaje es el siguiente;
0. ac010020
1. 84020020
3. a1410064
4. 8d430064

Para realizar las pruebas, en el registro 1 debe de colocarse un 22334455(Hexadecimal) y en registro 10 un 7(Hexadecimal). En la Data Memory no hace falta cargar datos. Los valores esperados en los registros son los siguientes:
r1 = 22334455, r2 = 00004455, r3 = 55, r10 = 7.
