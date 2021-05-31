## Primer Examen Parcial 
 - Estudiante: Emmanuel Zúñiga Chaves
 - Carné: B98729
 - Fecha de Entrega: 1 de Junio, 2021
 
# Resumen de la solución
  En la carpeta raíz "Examenes/Primer Parcial/" puede encontrar la solución a los ejercicios B, C y D en formato pdf. Por otro lado las soluciones del
  ejercicio A se encuentran en la carpeta "Examenes/Primer Parcial/Respuesta A" donde se encuentran los tres entregables, tanto en formato .circ como en pdf para la parte escrita
  
# Notas importantes sobre el circuito de la memoria Cache
  La memoria cache fue implementada usando memorias RAM para representar las 16 lineas de la cache, estas memorias RAM por defecto traen todas sus entradas en 0
  es decir para obtener resultados óptimos los mejor es trabajar con tags que no sean cero, ya que si no la cache podria dar un Hit.
  Por otro lado, la memoria cache realiza todas las operaciones en el flanco positivo, por lo tanto lo más adecuado seria cambiar la dirección de 16 bits con el reloj en 0.
