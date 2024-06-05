#include <stdio.h>
#include "rtbp.h"

#define PMAX .5
#define MU 1.215058560962404e-2

/* 
 * EXECUCIÓ PER VALIDAR LA UTILITAT:
 * ./rtbp_lyap_csig 3.196255396314419=c -1=isgn -0.830=xi -0.829=xf \100=nx > u.txt
 */

/**
 * @param argc Nombre d'arguments passats per línia de comandament.
 * @param argv Arguments passats per línia de comandament.
 * @return 0 si l'execució ha estat correcta, -1 en cas d'error.
 *
 * Aquest programa aplica la funció proptraj per propagar una trajectòria del RTBP
 * i detecta un canvi de signe de u com a funció de x, per tal de localitzar una arrel
 * que doni lloc a una òrbita de Lyapunov plana.
 */
int main (int argc, char *argv[]) {
    double c, x0, xf;
    int isgn, n;

    // Comprovar si els arguments de la línia de comandament són correctes.
    if (argc < 6
            || sscanf(argv[1], "%lf", &c) != 1
            || sscanf(argv[2], "%d", &isgn) != 1
            || sscanf(argv[3], "%lf", &x0) != 1
            || sscanf(argv[4], "%lf", &xf) != 1
            || sscanf(argv[5], "%d", &n) != 1
        ) {
        // Si hi ha un error en els arguments, mostra un missatge d'error i finalitza.
        fprintf(stderr, "%s c isgn x0 xf n \n", argv[0]);
        return -1;
    }

    double xi, ui;

    // Bucle per calcular la trajectòria per a cada valor xi i detectar el canvi de signe de u.
    for (int i = 0; i <= n; i++) {
        xi = x0 + i * (xf - x0) / n;
        // Si la trajectòria es calcula correctament, imprimir xi i ui.
        if (proptraj(MU, 1, c, isgn, xi, &ui, NULL, PMAX, NULL) == 0) 
            printf("%lf %lf\n", xi, ui);
        else 
            // Si hi ha un error en la propagació, mostrar un missatge d'error.
            fprintf(stderr, "Error en la propagació de la trajectòria per a xi = %lf\n", xi);
    }

    return 0;
}


