Primera Prueba:
En la Instruction Memory deben de estar cargadas las siguientes instrucciones:
 add $2, $1, $1 // r2 = 20
 add $3, $5, $2 // r3 = 30
 add $4, $2, $6 // r4 = 30
 add $5, $4, $4 // r5 = 60
 sw $5, 100($4) // Guarda 60 en la posición 130 de la memoria

 Cuyo ensamblaje corresponde a:
 00211020
 00a21820
 00462020
 00852820
 ac850050

Debe de colocarse una a(Hexadecimal) en los registros 1,2,3,4,5 y 6. Por otro lado en la Data Memory, posición 32 debe de colocarse un 23(Decimal) o 17(Hexadecimal).

Segunda Prueba:
En la instruction memory deben de cargarse las siguientes instrucciones:
• lw $2, 22($1) // se carga de la posición de memoria 22 + 10 (tiene un 23)
• add $4, $2, $3 // r4 = 23 + 10
• add $5, $2, $3 // r5 = 23 + 10
• add $6, $4, $2 // r6 = 33 + 23
• slt $1, $4, $2 // r4 = 33, r2 = 23, r1 = 0

Cuyo ensamblaje es el siguiente:
8c220016
00432020
00432820
00823020
0082082a

Debe de colocarse una a(Hexadecimal) en los registros 1,2,3,4,5 y 6. Por otro lado en la Data Memory, posición 32 debe de colocarse un 23(Decimal) o 17(Hexadecimal).