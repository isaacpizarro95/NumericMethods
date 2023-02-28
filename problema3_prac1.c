#include <stdio.h>
#include <math.h>

/*
DUDAS: 
- Mejor separar en ficheros diferentes las funciones en float y en double?
- Hay algo a mejorar en este fichero?
*/

//////////////** VARIANZA MUESTRAL FÓRMULA 1 **//////////////
//Problema en precisión simple
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

//Problema en precisión doble
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

//////////////** VARIANZA MUESTRAL FÓRMULA 2 **//////////////
//Problema en precisión simple
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

//Problema en precisión doble
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
    for(int i = 0; i < n; i++){
        printf("Inserte la %i coordenada del vector: ", i+1);
        scanf("%lf", &vector[i]);
        vectorf[i] = (float)vector[i];
    }

    // Precisión doble
    printf("La varianza muestral en precisión doble es = %.16G\n", varianza_muestral(vector, n));
    printf("La varianza muestral_2 en precisión doble es = %.16G\n", varianza_muestral_2(vector, n));

    // Precisión simple
    printf("La varianza muestral en precisión simple es = %.8G\n", varianza_muestral_simple(vectorf, n));
    printf("La varianza muestral_2 en precisión simple es = %.8G\n", varianza_muestral_simple_2(vectorf, n));    

    return 0;
}