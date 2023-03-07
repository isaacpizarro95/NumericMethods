#include <stdio.h>
#include <math.h>

double sumatorio_decreciente(double n){
    double sum = 0;
    double j = 1;
    for(int i = 1; i < n; i++){
        sum += (1./(j*j));
        j++;
    }
    return sum;
}

float sumatorio_decreciente_simple(float n){
    float sum = 0;
    float j = 1;
    for(int i = 1; i < n; i++){
        sum += (1./(j*j));
        j++;
    }
    return sum;
}

double sumatorio_creciente(double n){
    double sum = 0;
    double j = n;
    for(int i = n; i > 0; i--){
        sum += (1./(j*j));
        j--;
    }
    return sum; 
}

float sumatorio_creciente_simple(float n){
    float sum = 0;
    float j = n;
    for(int i = n; i > 0; i--){
        sum += (1./(j*j));
        j--;
    }
    return sum;   
}

int main(){
    double n1 = 5000;
    float n1_simple = 5000;
    double n2 = 10000;
    double n2_simple = 10000;

    double s = 1.644934066848226;
    float s_simple = 1.644934066848226;

    // Precisión doble
    printf("PRECISIÓN DOBLE:\n");
    printf("Con n = 5000 en el sumatorio creciente con precisión doble = %.16G \n", sumatorio_creciente(n1));
    printf("Con n = 10000 en el sumatorio creciente con precisión doble = %.16G \n", sumatorio_creciente(n2));
    printf("Con n = 5000 en el sumatorio decreciente con precisión doble = %.16G\n", sumatorio_decreciente(n1));
    printf("Con n = 10000 en el sumatorio decreciente con precisión doble = %.16G\n\n", sumatorio_decreciente(n2));

    // Precisión simple
    printf("PRECISIÓN SIMPLE:\n");
    printf("Con n = 5000 en el sumatorio creciente con precisión simple = %.8G\n", sumatorio_creciente_simple(n1_simple));
    printf("Con n = 10000 en el sumatorio creciente con precisión simple = %.8G \n", sumatorio_creciente_simple(n2_simple));
    printf("Con n = 5000 en el sumatorio decreciente con precisión simple = %.8G\n", sumatorio_decreciente_simple(n1_simple));
    printf("Con n = 10000 en el sumatorio decreciente con precisión simple = %.8G\n\n", sumatorio_decreciente_simple(n2_simple));

    // Comparación resultado
    printf("Imprimiremos las diferencias con los anteriores resultados siguiendo el mismo orden anterior, de forma que:\n");
    printf("La diferencia entre 1,644934066848226 - sumatorio_creciente(5000) = %.16G\n", s-sumatorio_creciente(n1));
    printf("La diferencia entre 1,644934066848226 - sumatorio_creciente(10000) = %.16G\n", s-sumatorio_creciente(n2));
    printf("La diferencia entre 1,644934066848226 - sumatorio_decreciente(5000) = %.16G\n", s-sumatorio_decreciente(n1));
    printf("La diferencia entre 1,644934066848226 - sumatorio_decreciente(10000) = %.16G\n", s-sumatorio_decreciente(n2));
    printf("La diferencia entre 1,644934066848226 - sumatorio_creciente_simple(5000) = %.8G\n", s_simple-sumatorio_creciente_simple(n1_simple));
    printf("La diferencia entre 1,644934066848226 - sumatorio_creciente_simple(10000) = %.8G\n", s_simple-sumatorio_creciente_simple(n2_simple));
    printf("La diferencia entre 1,644934066848226 - sumatorio_decreciente_simple(5000) = %.8G\n", s_simple-sumatorio_decreciente_simple(n1_simple));
    printf("La diferencia entre 1,644934066848226 - sumatorio_decreciente_simple(10000) = %.8G\n", s_simple-sumatorio_decreciente_simple(n2_simple));

    return 0;
}