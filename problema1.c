// Problema 1 - Práctica 1 - Métodos Numéricos
// Autores: Isaac Pizarro Contreras y Júlia Marı́n Méndez
// NIU: 1636421 y 1604251

#include <stdio.h>
#include <math.h>

/**
 * Función que utiliza una fórmula alternativa ('2*sin^2(x/2)') para el cálculo de '1-cos(x)' en precisión simple para reducir el error de cancelación. 
 * @param x variable de tipo float
 * @return variable de tipo float que devuelve 0.5 si x == 0 o un valor dependiente de x, cuando x != 0
**/
float g_simple(float x){
    float resultado = 1./2;
    if(x != 0) return (2*(sinf(x/2)*sinf(x/2)))/(x*x); 
    else return resultado;
}

/**
 * Función que utiliza una fórmula alternativa ('2*sin^2(x/2)') para el cálculo de '1-cos(x)' en precisión doble para reducir el error de cancelación. 
 * @param x variable de tipo double
 * @return variable de tipo double que devuelve 0.5 si x == 0 o un valor dependiente de x, cuando x != 0
**/
double g(double x){
    if(x != 0) return (2*(sin(x/2)*sin(x/2)))/(x*x); 
    else return 1./2;
} 
   
/**
 * Función que calcula '1-cos(x)/x²' en precisión simple. 
 * @param x variable de tipo float
 * @return variable de tipo float que devuelve 0.5 si x == 0 o un valor dependiente de x, cuando x != 0
**/
float f_simple(float x){
    float resultado = 1./2;
    if(x != 0) return ((1-cosf(x))/(x*x));
    else return resultado;
}

/**
 * Función que calcula '1-cos(x)/x²' en precisión doble. 
 * @param x variable de tipo double
 * @return variable de tipo double que devuelve 0.5 si x == 0 o un valor dependiente de x, cuando x != 0
**/
double f(double x){
    if(x != 0) return ((1-cos(x))/(x*x));
    else return 1./2;
}

int main(){
    double x1 = 1.2 * pow(10,-5);
    float x2 = 1.2 * powf(10,-5);

    // Imprimimos por pantalla f(0.000012) con precisión doble.
    printf("f(%lf) con precisión doble = %.16G\n", x1, f(x1));

    // Imprimimos por pantalla f(0) con precisión doble.
    printf("f(0) con precisión doble = %.16G \n", f(0));

    // Imprimimos por pantalla g(0.000012) con precisión doble donde g(x) contiene la fórmula alternativa para reducir el error de cancelación.
    printf("g(%f) double con error reducido = %.16G\n\n", x1, g(x1));

    // Imprimimos por pantalla f(0.000012) con precisión simple.
    printf("f(%f) con precisión simple = %.8G\n", x2, f_simple(x2));

    // Imprimimos por pantalla f(0) con precisión doble.
    printf("f(0) con precisión simple = %.8G\n", f_simple(0));

    // Imprimimos por pantalla g(0.000012) con precisión doble donde g(x) contiene la fórmula alternativa para reducir el error de cancelación.
    printf("g(%f) simple con error reducido = %.8G\n", x2, g_simple(x2));

    return 0;
}