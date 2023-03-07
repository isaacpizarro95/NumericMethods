// Problema 3 - Práctica 1 - Métodos Numéricos
// Autores: Isaac Pizarro Contreras y Júlia Marı́n Méndez
// NIU: 1636421 y 1604251

#include <stdio.h>
#include <math.h>

/**
 * Función que calcula la varianza muestral de los valores de un vector de dimensión n con la fórmula (3) en precisión simple.
 * @param vector vector de tipo float que contiene los valores de los cuales hay que calcular la varianza muestral.
 * @param n entero (tipo int) que define la dimensión del vector.
 * @return la variable 'varianza' de tipo float que contiene el resultado de aplicar la fórmula (3) a los valores del vector.
 */
float varianza_muestral_simple(float vector[], int n){
    float media = 0;
    float varianza = 0;

    for(int i = 0; i < n; i++){
        media += vector[i];
    }
    media = media / n;
    for(int i = 0; i < n; i++){
        varianza += ((vector[i] - media)*(vector[i] - media));
    }
    varianza = varianza / (n-1);
    return varianza;
}

/**
 * Función que calcula la varianza muestral de los valores de un vector de dimensión n con la fórmula (3) en precisión doble.
 * @param vector vector de tipo double que contiene los valores de los cuales hay que calcular la varianza muestral.
 * @param n entero (tipo int) que define la dimensión del vector.
 * @return la variable 'varianza' de tipo double que contiene el resultado de aplicar la fórmula (3) a los valores del vector.
 */
double varianza_muestral(double vector[], int n){
    double media = 0;
    double varianza = 0;

    for(int i = 0; i < n; i++){
        media += vector[i];
    }
    media = media / n;
    for(int i = 0; i < n; i++){
        varianza += ((vector[i] - media)*(vector[i] - media));
    }
    varianza = varianza / (n-1);
    return varianza;
}

/**
 * Función que calcula la varianza muestral de los valores de un vector de dimensión n con la fórmula (4) en precisión simple.
 * @param vector vector de tipo float que contiene los valores de los cuales hay que calcular la varianza muestral.
 * @param n entero (tipo int) que define la dimensión del vector.
 * @return la variable 'varianza' de tipo float que contiene el resultado de aplicar la fórmula (4) a los valores del vector.
 */
float varianza_muestral_simple_2(float vector[], int n){
    float suma_cuadrados = 0;
    float media_cuadrado = 0;
    float varianza = 0;

    for(int i = 0; i < n; i++){
        suma_cuadrados += vector[i]*vector[i];
        media_cuadrado += vector[i];
    }
    varianza = (suma_cuadrados-(media_cuadrado*media_cuadrado)/n)/(n-1);
    return varianza;
}

/**
 * Función que calcula la varianza muestral de los valores de un vector de dimensión n con la fórmula (4) en precisión doble.
 * @param vector vector de tipo double que contiene los valores de los cuales hay que calcular la varianza muestral.
 * @param n entero (tipo int) que define la dimensión del vector.
 * @return la variable 'varianza' de tipo double que contiene el resultado de aplicar la fórmula (4) a los valores del vector.
 */
double varianza_muestral_2(double vector[], int n){
    double suma_cuadrados = 0;
    double media_cuadrado = 0;
    double varianza = 0;

    for(int i = 0; i < n; i++){
        suma_cuadrados += vector[i]*vector[i];
        media_cuadrado += vector[i];
    }
    varianza = (suma_cuadrados-(media_cuadrado*media_cuadrado)/n)/(n-1);
    return varianza;
}


int main(){
    int n;

    printf("Inserte la dimensión del vector: ");
    scanf("%i", &n);

    double vector[n];
    float vectorf[n];

    // Se recogen por pantalla los valores del vector.
    for(int i = 0; i < n; i++){
        printf("Inserte la %i coordenada del vector: ", i+1);
        scanf("%lf", &vector[i]);
        // Guardamos en el vector de precisión simple el valor que acabamos de almacenar en el vector de precisión doble.
        vectorf[i] = (float)vector[i];
    }

    // Dado un vector de dimensión n insertado por el usuario se calcula la varianza muestral de sus componentes en precisión simple y doble.
    printf("\nLa varianza muestral en precisión doble es = %.16G\n", varianza_muestral(vector, n)); // precisión doble con fórmula (3)
    printf("La varianza muestral_2 en precisión doble es = %.16G\n", varianza_muestral_2(vector, n)); // precisión doble con fórmula (4)
    printf("La varianza muestral en precisión simple es = %.8G\n", varianza_muestral_simple(vectorf, n)); // precisión simple con fórmula (3)
    printf("La varianza muestral_2 en precisión simple es = %.8G\n\n\n", varianza_muestral_simple_2(vectorf, n)); // precisión simple con fórmula (4)


    // Calculamos la varianza muestral para el vector {10000, 10001, 10002} en precisión simple y doble.
    double vector_b[3] = {10000,10001,10002};
    float vectorf_b[3] = {10000,10001,10002};

    // Calculamos e imprimimos por pantalla la varianza muestral para el vector {10000, 10001, 10002} en precisión simple y doble.
    printf("Calculamos la varianza muestral para el vector {10000, 10001, 10002} en precisión simple y doble:\n\n");
    printf("La varianza muestral en precisión doble es = %.16G\n", varianza_muestral(vector_b, 3)); // precisión doble con fórmula (3)
    printf("La varianza muestral_2 en precisión doble es = %.16G\n", varianza_muestral_2(vector_b, 3)); // precisión doble con fórmula (4)
    printf("La varianza muestral en precisión simple es = %.8G\n", varianza_muestral_simple(vectorf_b, 3)); // precisión simple con fórmula (3)
    printf("La varianza muestral_2 en precisión simple es = %.8G\n\n\n", varianza_muestral_simple_2(vectorf_b, 3)); // precisión simple con fórmula (4)
 

    // Creamos dos vectores de dimensiones de 150 y 200 en precisión doble y simple con unos valores dados en el bucle for.
    n = 150;
    double vector_gran[n];
    float vectorf_gran[n];
    double vector_gran_2[n+50];
    float vectorf_gran_2[n+50];

    for(int i = 0; i < n+50; i++){
        if(i < 150){
            vector_gran[i] = 1000000+i;
            vectorf_gran[i] = 1000000+i;
        }
        vector_gran_2[i] = 3000000+i*0.5;
        vectorf_gran_2[i] = 3000000+i*0.5;
    }

    // Calculamos e imprimimos por pantalla la varianza muestral de los dos vectores en precisión simple y doble.
    printf("Ejemplo con vectores de dimensiones de 150 y 200:\n\n");
    
    // Vector 1
    printf("La varianza muestral en precisión doble con el 1er vector grande es = %.16G\n", varianza_muestral(vector_gran, n)); // precisión doble con fórmula (3)
    printf("La varianza muestral en precisión simple con el 1er vector grande es = %.8G\n", varianza_muestral_simple(vectorf_gran, n)); // precisión doble con fórmula (4)
    printf("La varianza muestral_2 en precisión doble con el 1er vector grande es = %.16G\n", varianza_muestral_2(vector_gran, n)); // precisión simple con fórmula (3)
    printf("La varianza muestral_2 en precisión simple con el 1er vector grande es = %.8G\n\n", varianza_muestral_simple_2(vectorf_gran, n)); // precisión simple con fórmula (4)
    
    // Vector 2
    printf("La varianza muestral en precisión doble con el 2o vector grande es = %.16G\n", varianza_muestral(vector_gran_2, n)); // precisión doble con fórmula (3)
    printf("La varianza muestral en precisión simple con el 2o vector grande es = %.8G\n", varianza_muestral_simple(vectorf_gran_2, n)); // precisión doble con fórmula (4)
    printf("La varianza muestral_2 en precisión doble con el 2o vector grande es = %.16G\n", varianza_muestral_2(vector_gran_2, n)); // precisión simple con fórmula (3)
    printf("La varianza muestral_2 en precisión simple con el 2o vector grande es = %.8G\n", varianza_muestral_simple_2(vectorf_gran_2, n)); // precisión simple con fórmula (4)
    
    return 0;
}