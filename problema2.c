// Problema 2 - Práctica 1 - Métodos Numéricos
// Autores: Isaac Pizarro Contreras y Júlia Marı́n Méndez
// NIU: 1636421 y 1604251

#include <stdio.h>
#include <math.h>

/*
* Las siguientes funciones son void porque no tienen valores de retorno. Eso es así porque los parámetros son vectores y al llamar a la función
* desde el main enviamos la dirección de memória del primer valor del vector de forma que lo que modificamos en las funciones es el mismo vector
* que hemos enviado desde el main.
*/

/**
 * Función que utiliza la ecuación cuadrática usual para calcular sus raíces en precisión doble.
 * @param ct vector de tipo double que contiene los coeficientes de la ecuación.
 * @param x vector de tipo double que guardará las raíces de la ecuación.
 */
void ecuacion_cuadratica(double ct[], double x[]){
    x[0] = (-ct[1] + sqrt(ct[1]*ct[1] - 4*ct[0]*ct[2])) / (2*ct[0]);
    x[1] = (-ct[1] - sqrt(ct[1]*ct[1] - 4*ct[0]*ct[2])) / (2*ct[0]);
}

/**
 * Función que utiliza la ecuación cuadrática usual para calcular sus raíces en precisión simple.
 * @param ct vector de tipo float que contiene los coeficientes de la ecuación.
 * @param x vector de tipo float que guardará las raíces de la ecuación.
 */
void ecuacion_cuadratica_simple(float ct[], float x[]){
    x[0] = (-ct[1] + sqrtf(ct[1]*ct[1] - 4*ct[0]*ct[2])) / (2*ct[0]);
    x[1] = (-ct[1] - sqrtf(ct[1]*ct[1] - 4*ct[0]*ct[2])) / (2*ct[0]);
}

/**
 * Función que utiliza la ecuación cuadrática alternativa para calcular sus raíces en precisión doble.
 * @param ct vector de tipo double que contiene los coeficientes de la ecuación.
 * @param x vector de tipo double que guardará las raíces de la ecuación.
 */
void ecuacion_cuadratica_alt(double ct[], double x[]){
    // Distinguimos los casos entre b positivo y b negativo para modificar la ecuación dependiendo del signo y reducir el error de cancelación.
    if(ct[1] < 0){
        x[0] = (-ct[1] + sqrt(ct[1]*ct[1] - 4*ct[0]*ct[2])) / (2*ct[0]);
        x[1] = (-2*ct[2]) / (ct[1] - sqrt(ct[1]*ct[1] - 4*ct[0]*ct[2]));
    }
    else {
        x[0] = (-2*ct[2]) / (ct[1] + sqrt(ct[1]*ct[1] - 4*ct[0]*ct[2]));
        x[1] = (-ct[1] - sqrt(ct[1]*ct[1] - 4*ct[0]*ct[2])) / (2*ct[0]);
    }
}

/**
 * Función que utiliza la ecuación cuadrática alternativa para calcular sus raíces en precisión simple.
 * @param ct vector de tipo float que contiene los coeficientes de la ecuación.
 * @param x vector de tipo float que guardará las raíces de la ecuación.
 */
void ecuacion_cuadratica_alt_simple(float ct[], float x[]){
    // Distinguimos los casos entre b positivo y b negativo para modificar la ecuación dependiendo del signo y reducir el error de cancelación.
    if(ct[1] < 0){
        x[0] = (-ct[1] + sqrtf(ct[1]*ct[1] - 4*ct[0]*ct[2])) / (2*ct[0]);
        x[1] = (-2*ct[2]) / (ct[1] - sqrtf(ct[1]*ct[1] - 4*ct[0]*ct[2]));
    }
    else {
        x[0] = (-2*ct[2]) / (ct[1] + sqrtf(ct[1]*ct[1] - 4*ct[0]*ct[2]));
        x[1] = (-ct[1] - sqrtf(ct[1]*ct[1] - 4*ct[0]*ct[2])) / (2*ct[0]);
    }
}

int main(){
    double x[2]; // Vector donde guardaremos las raíces de la ecuación cuadrática usual en precisión doble.
    double x_alt[2]; // Vector donde guardaremos las raíces de la ecuación cuadrática alternativa en precisión doble.
    double ct[3]; // Vector donde guardaremos los coeficientes de la ecuación en precisión doble (a,b,c).

    float xf[2]; // Vector donde guardaremos las raíces de la ecuación cuadrática usual en precisión simple.
    float xf_alt[2]; // Vector donde guardaremos las raíces de la ecuación cuadrática alternativa en precisión doble.
    float ctf[3]; // Vector donde guardaremos los coeficientes de la ecuación en precisión doble (a,b,c).

    // Se recogen por pantalla los valores correspondientes a los coeficientes de la ecuación cuadrática.
    for(int i = 0; i < 3; i++){
        // Haciendo uso del tipo 'char' y la tabla ASCII utilizamos la iteración sobre 'i' para imprimir letras (empezando por 'a' cuando i == 0).
        printf("Inserte el valor de '%c': ", 'a'+i); 
        scanf("%lf", &ct[i]);
        // Guardamos en el vector de coeficientes de precisión simple el valor que acabamos de almacenar en el vector de coeficientes de precisión doble.
        ctf[i] = (float)ct[i]; 
    }

    // Si a <= 0 o b² <= 4ac se informa al usuario de que el input introducido no es válido y se detiene el programa.
    if (ct[0] <= 0 || ct[1]*ct[1] <= 4*ct[0]*ct[2]){
        printf("Input no válido, debe cumplirse: a > 0 y b^2 > 4ac\n");
        return 0;
    } 

    // Calculamos las raíces de la ecuación cuadrática con la fórmula usual en precisión doble y simple.
    ecuacion_cuadratica(ct, x);
    ecuacion_cuadratica_simple(ctf, xf);

    // Calculamos las raíces de la ecuación cuadrática con la fórmula alternativa en precisión doble y simple.
    ecuacion_cuadratica_alt(ct, x_alt);
    ecuacion_cuadratica_alt_simple(ctf, xf_alt);

    // Imprimimos por pantalla las raíces de la ecuación cuadrática con la fórmula usual en precisión doble y simple.
    printf("El resultado de la ecuación %lfx² + %lfx + %lf = 0 con precisión doble es: %.16G y %.16G\n",ct[0], ct[1], ct[2], x[0], x[1]);
    printf("El resultado de la ecuación %fx² + %fx + %f = 0 con precisión simple es: %.8G y %.8G\n",ctf[0], ctf[1], ctf[2], xf[0], xf[1]);

    // Imprimimos por pantalla las raíces de la ecuación cuadrática con la fórmula alternativa en precisión doble y simple.
    printf("El resultado de la ecuación %lfx² + %lfx + %lf = 0 alternativa en precisión doble es: %.16G y %.16G\n",ct[0], ct[1], ct[2], x_alt[0], x_alt[1]);
    printf("El resultado de la ecuación %fx² + %fx + %f = 0 alternativa en precisión simple es: %.8G y %.8G\n",ctf[0], ctf[1], ctf[2], xf_alt[0], xf_alt[1]);

    
    /*
    * Definimos dos ejemplos numéricos (uno con b > 0 y otro b < 0) en los que se da error de cancelación tanto en precisión simple
    * como en precisión doble con la fórmula cuadrática usual y se reduce con la fórmula cuadrática alternativa devolviendo valores
    * significativamente diferentes en el cálculo de las raices.
    */ 

    double ct_ex[3] = {2, 1000009714, 3};
    float ctf_ex[3] = {2, 1000009714, 3};
    double ct_ex_2[3] = {2, -1000009714, 3};
    float ctf_ex_2[3] = {2, -1000009714, 3};

    printf("\n\nConstruimos dos ejemplos numéricos donde hayan diferencias significativas entre ambas fórmulas en precisión doble y simple:\n\n");

    // Calculamos las raices en precisión doble y simple con la fórmula usual y alternativa para el caso b > 0.
    ecuacion_cuadratica(ct_ex, x);
    ecuacion_cuadratica_simple(ctf_ex, xf);
    ecuacion_cuadratica_alt(ct_ex, x_alt);
    ecuacion_cuadratica_alt_simple(ctf_ex, xf_alt);

    // Imprimimos por pantalla las raíces en precisión doble y simple con la fórmula usual y alternativa para el caso b > 0.
    printf("Primer ejemplo: b > 0\n");
    printf("El resultado de la ecuación 2x² + 1000009714x + 3 = 0 con precisión doble es: %.16G y %.16G\n", x[0], x[1]);
    printf("El resultado de la ecuación 2x² + 1000009714x + 3 = 0 con precisión simple es: %.8G y %.8G\n", xf[0], xf[1]);
    printf("El resultado de la ecuación 2x² + 1000009714x + 3 = 0 alternativa en precisión doble es: %.16G y %.16G\n", x_alt[0], x_alt[1]);
    printf("El resultado de la ecuación 2x² + 1000009714x + 3 = 0 alternativa en precisión simple es: %.8G y %.8G\n", xf_alt[0], xf_alt[1]);

    // Calculamos las raices en precisión doble y simple con la fórmula usual y alternativa para el caso b < 0.
    ecuacion_cuadratica(ct_ex_2, x);
    ecuacion_cuadratica_simple(ctf_ex_2, xf);
    ecuacion_cuadratica_alt(ct_ex_2, x_alt);
    ecuacion_cuadratica_alt_simple(ctf_ex_2, xf_alt);

    // Imprimimos por pantalla las raíces en precisión doble y simple con la fórmula usual y alternativa para el caso b > 0.
    printf("\nSegundo ejemplo: b < 0\n");
    printf("El resultado de la ecuación 2x² - 1000009714x + 3 = 0 con precisión doble es: %.16G y %.16G\n", x[0], x[1]);
    printf("El resultado de la ecuación 2x² - 1000009714x + 3 = 0 con precisión simple es: %.8G y %.8G\n", xf[0], xf[1]);
    printf("El resultado de la ecuación 2x² - 1000009714x + 3 = 0 alternativa en precisión doble es: %.16G y %.16G\n", x_alt[0], x_alt[1]);
    printf("El resultado de la ecuación 2x² - 1000009714x + 3 = 0 alternativa en precisión simple es: %.8G y %.8G\n", xf_alt[0], xf_alt[1]);

    return 0;
}