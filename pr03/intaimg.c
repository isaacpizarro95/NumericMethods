#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <assert.h>
#include "intnev.h"

/**
 * Programa principal per a la utilitat `intaimg`.
 * Aquesta utilitat llegeix un fitxer d'entrada amb dues columnes (xi, yi)
 * i busca el nimg-èssim canvi de signe de yi - vimg.
 * A continuació, troba el valor de x tal que f(x) ≈ vimg mitjançant
 * interpolació inversa amb un polinomi interpolador de grau n.
 * També calcula i mostra el valor del polinomi interpolador en x.
 */
int main(int argc, char *argv[]) {
    double vimg;
    int n, nimg;

    // Verificar els arguments d'entrada
    if (argc < 4
        || sscanf(argv[1], "%d", &n) != 1
        || sscanf(argv[2], "%d", &nimg) != 1
        || sscanf(argv[3], "%lf", &vimg) != 1) {
        fprintf(stderr, "%s n nimg vimg\n", argv[0]);
        return -1;
    }

    // Llegir els primers n punts
    double xi[n+1];
    double yi[n+1]; 
    
    for (int i = 0; i < n; i++) {
        if (scanf("%lf %lf", &xi[i], &yi[i]) != 2) {
            fprintf(stderr, "Error en la lectura de dades\n");
            return -1;
        }
    }

    // Variables per al control del canvi de signe
    int canvi_de_signe = 0;
    int j = n / 2;

    // Bucle per llegir els punts i buscar el canvi de signe
    while (scanf("%lf %lf", &xi[n], &yi[n]) == 2) {
        // Comprovar si hi ha un canvi de signe entre els punts j i j+1
        if ((yi[j] - vimg) * (yi[j + 1] - vimg) < 0) {
            canvi_de_signe++;
            printf("S'ha trobat un canvi de signe entre yi[%d] = %lf i yi[%d] = %lf\n\n", j, yi[j], j + 1, yi[j + 1]);
            if (canvi_de_signe == nimg) break;
        }

        // Moure els valors una posició cap a l'esquerra
        memmove(&xi[0], &xi[1], n * sizeof(double));
        memmove(&yi[0], &yi[1], n * sizeof(double));
    }

    // Verificar si s'ha trobat el canvi de signe
    if (canvi_de_signe < nimg) {
        fprintf(stderr, "No s'ha trobat el %dè canvi de signe\n", nimg);
        return 1;
    }

    // Interpolació inversa per trobar x tal que f(x) ≈ vimg
    double x, dp;
    intnev_avald(vimg, (n + 1), yi, xi, &x, &dp);
    printf("Interpolació inversa: f(x) ≈ %.16g, x = %.16g\n", vimg, x);

    // Calcular el valor del polinomi interpolador en x
    double y;
    intnev_avald(x, (n + 1), xi, yi, &y, NULL);
    printf("Interpolació: x = %.16g, y = %.16g\n", x, y);

    return 0;
}