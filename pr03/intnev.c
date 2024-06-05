#include <string.h>
#include <stdio.h>
#include <stdlib.h>

/**
 * Funció per avaluar el polinomi interpolador i la seva derivada usant el mètode de Neville
 * @param x Punt on es vol avaluar el polinomi i la seva derivada
 * @param n Nombre de punts de suport
 * @param xi Array de longitud n que conté els valors x dels punts de suport
 * @param yi Array de longitud n que conté els valors y dels punts de suport
 * @param p Punter on es guardarà el valor del polinomi interpolador en x (pot ser NULL)
 * @param dp Punter on es guardarà el valor de la derivada del polinomi interpolador en x (pot ser NULL)
 * @return No torna cap valor, els resultats es guarden en els punters p i dp si no són NULL
 */
void intnev_avald(double x, int n, double xi[], double yi[], double *p, double *dp) {
    double nev[n];  // Vector de Neville per al polinomi
    double dnev[n]; // Vector de Neville per a la derivada

    // Inicialització dels vectors amb els valors de y
    for (int i = 0; i < n; i++) {
        nev[i] = yi[i];
        dnev[i] = 0; // La derivada inicial és zero
    }

    double aux_nev;
    // Construcció dels vectors de Neville
    for (int j = 1; j < n; j++) {
        for (int i = 0; i < n - j; i++) {
            aux_nev = nev[i];
            nev[i] = ((x - xi[i + j]) * aux_nev + (xi[i] - x) * nev[i + 1]) / (xi[i] - xi[i + j]);
            dnev[i] = ((x - xi[i + j]) * dnev[i] + aux_nev + (xi[i] - x) * dnev[i + 1] - nev[i + 1]) / (xi[i] - xi[i + j]);
        }
    }

    // El valor del polinomi i la seva derivada en x
    if (p != NULL) *p = nev[0];
    if (dp != NULL) *dp = dnev[0];
}
