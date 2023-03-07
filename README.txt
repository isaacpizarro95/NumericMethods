Isaac Pizarro Contreras NIU:1636421
Júlia Marı́n Méndez NIU:1604251

Al realizar esta práctica se ha utilizado el sistema operativo Linux. 
Se ha compilado con el compilador GCC (Gnu C Compiler)

Una vez descomprimida la carpeta MNP1-GR2.zip se introduce la siguiente instrucción en consola para acceder a los ficheros:
cd MNP1-GR2

Una vez ubicados en el directorio donde se han guardado los ficheros se introducen las siguientes instrucciones de compilación en la consola:
gcc -o nombre_fichero -Wall -pedantic nombre_fichero.c -lm

Se pide al compilador que muestre todos los "Warnings" (-Wall), se fuerza la sintaxis del estándar ISO C 90 (-pedantic) y se enlaza con la librería matemática (-lm).

Ejecutamos el código mediante:
./nombre_fichero

Dependiendo del fichero ejecutado la interacción con el usuario será la siguiente:
- En el problema 1 el usuario solamente tiene que ejecutar el código ya que los valores con los que se trabajan estan fijados dentro del código. Si se quiere se pueden modificar los valores en el mismo código.

- En el problema 2 al usuario se le pedirá introducir los valores de los coeficientes de la ecuación cuadrática (a,b y c). Una vez introducidos aparecerá automáticamente el resultado de la ecuación con los coeficientes del usuario calculado en precisión doble y en simple con la fórmula usual y la alternativa. Además, también se imprimiran dos ejemplos en los que el error se produce tanto en precisión doble como en simple en la fórmula usual y se reduce en la alternativa.

- En el problema 3 al usuario se le pedirá introducir la dimensión del vector y sus valores. Después aparecerá el cálculo de la varianza muestral para dichos valores en precisión doble y en simple con las dos fórmulas utilizadas en la práctica. Además se imprimirá el mismo resultado pero para el vector {10000, 10001, 10002} y para dos vectores de dimensión 150 y 200.
