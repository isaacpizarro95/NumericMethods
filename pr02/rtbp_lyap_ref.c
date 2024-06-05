#include <stdio.h>
#include <math.h>
#include "rtbp.h"
#include "zeros.h"

#define MU 1.215058560962404e-2
#define PMAX .5

/**
 * EXECUCIÓ PER VALIDAR LA UTILITAT
 * ./rtbp_lyap_ref 3.196255396314419=c -1=isgn -0.830=xa -0.829=xb 1e-4=tolbis 1e-12=tolfnwt 10=maxitnwt 1=ixrr
 */

/**
 * Estructura per emmagatzemar els paràmetres de Lyapunov.
 *
 * @param c Constant de Jacobi.
 * @param isgn Signe de la velocitat inicial.
 *
 * Aquesta estructura s'utilitza per passar els paràmetres necessaris a les funcions
 * de propagació de trajectòries.
 */
struct lyap_ref {
    double c;
    int isgn;
};

/**
 * @param x Valor actual de x.
 * @param prm Punter als paràmetres estructurats de lyap_ref.
 * @return Valor de la funció proptraj.
 *
 * Aquesta funció crida la funció proptraj amb els paràmetres especificats i retorna el
 * valor resultant per a la bisecció.
 */
double proptraj_bis(double x, void *prm) {
    struct lyap_ref *params = prm;
    double u;
    proptraj(MU, 1, params->c, params->isgn, x, &u, NULL, PMAX, NULL);
    return u;
}

/**
 * @param x Valor actual de x.
 * @param u Punter per emmagatzemar el valor de la funció proptraj.
 * @param du Punter per emmagatzemar la derivada de la funció proptraj.
 * @param prm Punter als paràmetres estructurats de lyap_ref.
 *
 * Aquesta funció crida la funció proptraj amb els paràmetres especificats i emmagatzema
 * els resultats en u i du per a la iteració de Newton.
 */
void proptraj_nwt(double x, double *u, double *du, void *prm) {
    struct lyap_ref *params = prm;
    proptraj(MU, 1, params->c, params->isgn, x, u, du, PMAX, NULL);
}

/**
 * @param argc Nombre d'arguments passats per línia de comandament.
 * @param argv Arguments passats per línia de comandament.
 * @return 0 si l'execució ha estat correcta, -1 en cas d'error.
 *
 * Aquest programa aplica els mètodes de bisecció i Newton per trobar una arrel de la
 * funció proptraj amb els paràmetres especificats en la línia de comandament.
 */
int main (int argc, char *argv[]) {
    double c, xa, xb, tolbis, tolfnwt;
    int isgn, maxitnwt, ixrr;

    // Comprovar si els arguments de la línia de comandament són correctes.
    if (argc < 9
            || sscanf(argv[1], "%lf", &c) != 1
            || sscanf(argv[2], "%d", &isgn) != 1
            || sscanf(argv[3], "%lf", &xa) != 1
            || sscanf(argv[4], "%lf", &xb) != 1
            || sscanf(argv[5], "%lf", &tolbis) != 1
            || sscanf(argv[6], "%lf", &tolfnwt) != 1
            || sscanf(argv[7], "%d", &maxitnwt) != 1
            || sscanf(argv[8], "%d", &ixrr) != 1
        ) {
        // Si hi ha un error en els arguments, mostra un missatge d'error i finalitza.
        fprintf(stderr, "%s c isgn xa xb tolbis tolfnwt maxitnwt ixrr\n", argv[0]);
        return -1;
    }

    struct lyap_ref prm;
    prm.c = c;
    prm.isgn = isgn;

    // Aplicació del mètode de Bisecció
    if (ixrr > 0) fprintf(stderr, "\nBisecció\n");
    double alfa = biseccio(&xa, &xb, tolbis, proptraj_bis, &prm, ixrr);
    if (alfa == -1) return -1;

    // Aplicació del mètode de Newton
    if (ixrr > 0) fprintf(stderr, "\nNewton:\n");
    newton(&alfa, tolfnwt, 1e-12, maxitnwt, proptraj_nwt, &prm, ixrr);

    // Arrel trobada
    printf("\nalfa = %.16g\n\n", alfa);

    return 0;
}

