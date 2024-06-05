#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <assert.h>
#include "intnev.h"
#include "zeros.h"

struct intext {
    double *x_sup;
    double *y_sup;
    int n;
};

/**
 * Funció per calcular la derivada del polinomi interpolador en un punt x.
 * @param x Punt on es vol calcular la derivada.
 * @param prm Paràmetres addicionals encapsulats en una struct intext.
 * @return Valor de la derivada en el punt x.
 */
double intnev_bis(double x, void *prm) {
    struct intext *params = prm;
    double dp;
    intnev_avald(x, (params->n + 1), params->x_sup, params->y_sup, NULL, &dp);
    return dp;
}

/**
 * Programa principal per a la utilitat `intext`.
 * Aquesta utilitat llegeix un fitxer d'entrada amb dues columnes (xi, yi)
 * i busca el next-èssim extrem de la funció. 
 * Utilitza el mètode de la bisecció per trobar els zeros de la derivada del polinomi interpolador.
 */
int main(int argc, char *argv[]) {
    double tol;
    int n, next, ixrr;

    // Verificar els arguments d'entrada
    if (argc < 5
        || sscanf(argv[1], "%d", &n) != 1
        || sscanf(argv[2], "%d", &next) != 1
        || sscanf(argv[3], "%lf", &tol) != 1
        || sscanf(argv[4], "%d", &ixrr) != 1) {
        fprintf(stderr, "%s n next tol ixrr\n", argv[0]);
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
    double p, dp1, dp2;
    
    // Bucle per llegir els punts i buscar el canvi de signe
    while (scanf("%lf %lf", &xi[n], &yi[n]) == 2) {
        // Calcular les derivades en els punts j i j+1
        intnev_avald(xi[j], (n + 1), xi, yi, &p, &dp1);
        intnev_avald(xi[j + 1], (n + 1), xi, yi, &p, &dp2);
        // Comprovar si hi ha un canvi de signe entre dp1 i dp2
        if (dp1 * dp2 < 0) {
            canvi_de_signe++;
            printf("\n\nS'ha trobat un canvi de signe amb dp1 = %lf, dp2 = %lf, x[%d] = %lf, x[%d] = %lf\n\n", dp1, dp2, j, xi[j], j + 1, xi[j + 1]);
            if (canvi_de_signe == next) break;
        }

        // Moure els valors una posició cap a l'esquerra
        memmove(&xi[0], &xi[1], n * sizeof(double));
        memmove(&yi[0], &yi[1], n * sizeof(double));
    }

    // Verificar si s'ha trobat l'extrem
    if (canvi_de_signe < next) {
        fprintf(stderr, "No s'ha trobat el %dè extrem\n", next);
        return 1;
    }

    // Crear la struct intext per passar els paràmetres a la funció `func`
    struct intext params = {xi, yi, n};

    // Aplicar el mètode de la bisecció per trobar l'extrem
    double a = xi[j];
    double b = xi[j + 1];
    double extrem = biseccio(&a, &b, tol, intnev_bis, &params, ixrr);

    // Mostrar el resultat
    printf("Valor interpolat de x per l'extrem ≈ %.16g: %.16g\n", extrem, intnev_bis(extrem, &params));

    return 0;
}
