// #include <stdio.h>
// #include <math.h>
// #include "rtbp.h"
// #include "zeros.h"

// Comanda per generar l'executable: make exercici7


#include <stdio.h>
#include <math.h>
#include "rtbp.h"
#include "zeros.h"

#define MU 1.215058560962404e-2
#define PMAX .5

struct lyap_ref {
    double c;
    int isgn;
};

void proptraj_nwt(double x, double *u, double *du, void *prm) {
    struct lyap_ref *params = prm;
    proptraj(MU, 1, params->c, params->isgn, x, u, du, PMAX, NULL);
}

int main (int argc, char *argv[]) {
    double c, x, tolfnwt;
    int isgn, maxitnwt, ixrr;

    if (argc < 6
            || sscanf(argv[1], "%lf", &c) != 1
            || sscanf(argv[2], "%d", &isgn) != 1
            || sscanf(argv[3], "%lf", &x) != 1
            || sscanf(argv[4], "%lf", &tolfnwt) != 1
            || sscanf(argv[5], "%d", &maxitnwt) != 1
            || sscanf(argv[6], "%d", &ixrr) != 1
        ) {
        fprintf(stderr, "%s c isgn x tolfnwt maxitnwt ixrr\n", argv[0]);
        return -1;
    }

    struct lyap_ref prm;
    prm.c = c;
    prm.isgn = isgn;

    while (prm.c > 2.85) {
        // Aplicación del método de Newton
        if (ixrr > 0) fprintf(stderr, "\nNewton:\n");
        newton(&x, tolfnwt, 1e-12, maxitnwt, proptraj_nwt, &prm, ixrr);
        
        // Imprimir el resultado para el valor actual de c
        printf("%.16g %.16g\n", prm.c, x);

        // Reducir el valor de c
        prm.c -= 0.001;
    }

    return 0;
}
