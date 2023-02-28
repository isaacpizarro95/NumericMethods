#include <stdio.h>
#include <math.h>

/*
DUDAS: 
- Mejor separar en ficheros diferentes las funciones en float y en double?
- Mejor modificar los valores en las variables del main manualmente o introducir los valores por el terminal con scanf?
- Hay algo a mejorar en este fichero?
*/

// Reescribir la función f(x) utilizando fórmulas trigonométricas de manera que se reduzca el error que se produce utilizando la expresión
float reduccion_error_simple(float x){
    float resultado = 1./2;
    if(x != 0) return (2*(sinf(x/2)*sinf(x/2)))/(x*x); 
    else return resultado;
}

double reduccion_error(double x){
    if(x != 0) return (2*(sin(x/2)*sin(x/2)))/(x*x); 
    else return 1./2;
} 

   
//Problema 1a en precisión simple
float problema1_simple(float x){
    float resultado = 1./2;
    if(x != 0) return ((1-cosf(x))/(x*x));
    else return resultado;
}

//Problema 1a en precisión doble
double problema1(double x){
    if(x != 0) return ((1-cos(x))/(x*x));
    else return 1./2;
}

int main(){
    double x1 = 1.2 * pow(10,-5);
    float x2 = 1.2 * powf(10,-5);

    // Precisión doble
    printf("f(%lf) con precisión doble = %.16G\n", x1, problema1(x1));
    printf("f(0) con precisión doble = %.16G \n", problema1(0));
    printf("f(%f) double con error reducido = %.16G\n\n", x1, reduccion_error(x1));

    // Precisión simple
    printf("f(%f) con precisión simple = %.8G\n", x2, problema1_simple(x2));
    printf("f(0) con precisión simple = %.8G\n", problema1_simple(0));
    printf("f(%f) simple con error reducido = %.8G\n", x2, reduccion_error_simple(x2));
    return 0;
}