Las instrucciones cargadas en la Instruction Memory corresponden a las propuestas en la lectura 9, diapositiva 49:
36   sub $10, $4, $8
40   beq $1,  $3, 7
44   and $12, $2, $5
48   or    $13, $2, $6
52   add $14, $4, $2
56   slt $15, $6, $7
...
72   lw $4,  50($7)

Cuyo ensamblaje corresponde a:

00885022
10230007
00456024
00466825
00827020
0067782a
8ce40032

En caso de que no se encuentren cargadas en memoria, pueden cargarse directamente desde la imagen "Instrucciones" en la Instruction Memory, o bien insertarlas desde la posición cero, dejando tres espacios entre las instrucciones 0067782a y 8ce40032.
Con respecto en los registros, debe de colocarse una f(hexadecimal) y una a(hexadecimal) en los registros 4 y 8 respectivamente y un 0 en el registro 7.
Por otro lado, con respecto a los valores en memoria, en la posición 50 debe de insertarse el valor ffffffff(Hexadecimal), esto, en caso de que no este cargado en memoria.