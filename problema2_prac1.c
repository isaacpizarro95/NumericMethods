#include <stdio.h>
#include <math.h>

/*
DUDAS: 
- Mejor modificar los valores en las variables del main manualmente o introducir los valores por el terminal con scanf?
- He utilizado vectores, pero mejor usar una variable independiente para cada valor?
- Hay algo a mejorar en este fichero?
- El apartado d) hay que dejar escritos los ejemplos numéricos en el código? O solo tenemos que apuntar aquellos que hayamos encontrado en el informe.
- Todas las funciones que tengan errores de cancelación en precisión simple tendran también errores de cancelación con 'x' suficientemente grandes en double y long double.
*/

void ecuacion_cuadratica(double ct[], double x[]){
    x[0] = (-ct[1] + sqrt(ct[1]*ct[1] - 4*ct[0]*ct[2])) / (2*ct[0]);
    x[1] = (-ct[1] - sqrt(ct[1]*ct[1] - 4*ct[0]*ct[2])) / (2*ct[0]);
}

void ecuacion_cuadratica_simple(float ct[], float x[]){
    x[0] = (-ct[1] + sqrtf(ct[1]*ct[1] - 4*ct[0]*ct[2])) / (2*ct[0]);
    x[1] = (-ct[1] - sqrtf(ct[1]*ct[1] - 4*ct[0]*ct[2])) / (2*ct[0]);
}

void ecuacion_cuadratica_alt(double ct[], double x[]){
    if(ct[1] < 0){
        x[0] = (-ct[1] + sqrt(ct[1]*ct[1] - 4*ct[0]*ct[2])) / (2*ct[0]);
        x[1] = (-2*ct[2]) / (ct[1] - sqrt(ct[1]*ct[1] - 4*ct[0]*ct[2]));
    }
    else {
        x[0] = (-2*ct[2]) / (ct[1] + sqrt(ct[1]*ct[1] - 4*ct[0]*ct[2]));
        x[1] = (-ct[1] - sqrt(ct[1]*ct[1] - 4*ct[0]*ct[2])) / (2*ct[0]);
    }
}

void ecuacion_cuadratica_alt_simple(float ct[], float x[]){
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
    double x[2];
    double x_alt[2];
    double ct[3];

    float xf[2];
    float xf_alt[2];
    float ctf[3];

    for(int i = 0; i < 3; i++){
        printf("Inserte el valor de '%c': ", 'a'+i);
        scanf("%lf", &ct[i]);
        ctf[i] = (float)ct[i];
    }

    ecuacion_cuadratica(ct, x);
    ecuacion_cuadratica_simple(ctf, xf);
    ecuacion_cuadratica_alt(ct, x_alt);
    ecuacion_cuadratica_alt_simple(ctf, xf_alt);

    if (ct[0] <= 0 || ct[1]*ct[1] <= 4*ct[0]*ct[2]) printf("Input no válido, debe cumplirse: a > 0 y b^2 > 4ac\n");
    else {
        printf("El resultado de la ecuación %lfx² + %lfx + %lf = 0 con precisión doble es: %.16G y %.16G\n",ct[0], ct[1], ct[2], x[0], x[1]);
        printf("El resultado de la ecuación %fx² + %fx + %f = 0 con precisión simple es: %.8G y %.8G\n",ctf[0], ctf[1], ctf[2], xf[0], xf[1]);
        printf("El resultado de la ecuación %lfx² + %lfx + %lf = 0 alternativa en precisión doble es: %.16G y %.16G\n",ct[0], ct[1], ct[2], x_alt[0], x_alt[1]);
        printf("El resultado de la ecuación %fx² + %fx + %f = 0 alternativa en precisión simple es: %.8G y %.8G\n",ctf[0], ctf[1], ctf[2], xf_alt[0], xf_alt[1]);
    }
    return 0;
}