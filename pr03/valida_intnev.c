#include <stdio.h>
#include <stdlib.h>
#include <math.h>
#include "intnev.h"

/**
 * Aquest programa prova la funció `intnev_avald` per avaluar un polinomi interpolador i la seva derivada
 * utilitzant el mètode de Neville. Es generen tres funcions diferents (lineal, quadràtica, i trigonometrica),
 * es calculen els valors de suport `xi` i `yi`, i després es crida la funció `intnev_avald` per avaluar
 * el polinomi interpolador i la seva derivada en un punt donat.
 *
 * Les funcions de suport generen valors `xi` a intervals regulars i calculen els valors corresponents `yi`
 * per a cada funció de prova. A continuació, es crida `intnev_avald` per calcular el polinomi interpolador
 * i la seva derivada en un punt específic i es mostren els resultats.
 * 
 * Per executar aquest programa utilitzar la comanda: make valida_intnev
 * 
 * Aquest requereix 4 paràmetres: 
 * n = nombre de punts de suport 'xi' i 'yi'.
 * x = punt on avaluarem el polinomi i la seva derivada
 * pas = pas entre els punts xi
 * ixrr: 1 si es vol que la utilitat escrigui els punts de suport generats per cada funció; 0 en cas contrari
 */

/**
 * Funció per generar valors xi i yi
 * @param func Funció a avaluar
 * @param xi Array per als valors de suport xi
 * @param yi Array per als valors de suport yi
 * @param n Nombre de punts de suport
 * @param pas Pas entre els punts xi
 */
void genera_valors(double (*func)(double), double xi[], double yi[], int n, double pas) {
    for (int i = 0; i < n; i++) {
        xi[i] = i * pas;
        yi[i] = func(xi[i]);
    }
}

void print_p_suport(double *xi, double *yi, int n){
    printf("Punts de suport:\n");
    for(int i = 0; i < n; i++){
        printf("%.16g = %.16g\n", xi[i], yi[i]);
    }
}

 // Funcions per ser avaluades
double lineal(double x) {return 2.0 * x + 3.0;}
double quadratica(double x) {return x * x - 4.0 * x + 6.0;}
double trigonometrica(double x) {return sin(x);}

int main(int argc, char *argv[]) {
    int n, ixrr;
    double x, pas, p, dp;

    if (argc < 5 
        || sscanf(argv[1], "%d", &n) != 1
        || sscanf(argv[2], "%lf", &x) != 1
        || sscanf(argv[3], "%lf", &pas) != 1 
        || sscanf(argv[4], "%d", &ixrr) != 1) {
        fprintf(stderr, "%s Es requereixen els paràmetres n, x, pas, ixrr\n", argv[0]);
        return -1;
    }

    double xi[n], yi[n];
    // Prova amb funció lineal
    genera_valors(lineal, xi, yi, n, pas);
    intnev_avald(x, n, xi, yi, &p, &dp);
    printf("Funció lineal: 2x + 3\n\n");
    if (ixrr == 1) print_p_suport(xi, yi, n);
    printf("x = %.16g: p = %.16g, dp = %.16g dif = %.16g\n\n", x, p, dp, fabs(lineal(x) - p));

    // Prova amb funció quadràtica
    genera_valors(quadratica, xi, yi, n, pas);
    intnev_avald(x, n, xi, yi, &p, &dp);
    printf("Funció quadràtica: x² - 4x + 6\n\n");
    if (ixrr == 1) print_p_suport(xi, yi, n);
    printf("x = %.16g: p = %.16g, dp = %.16g dif = %.16g\n\n", x, p, dp, fabs(quadratica(x) - p));

    // Prova amb funció trigonomètrica
    genera_valors(trigonometrica, xi, yi, n, pas);
    intnev_avald(x, n, xi, yi, &p, &dp);
    printf("Funció trigonomètrica: sin(x)\n\n");
    if (ixrr == 1) print_p_suport(xi, yi, n);
    printf("x = %.16g: p = %.16g, dp = %.16g dif = %.16g\n\n", x, p, dp, fabs(trigonometrica(x) - p));
    
    return 0;
}