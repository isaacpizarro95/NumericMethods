#include <stdio.h>
#include <math.h>

/**
 * Funció de bisecció per trobar les arrels d'una funció.
 *
 * @param a Punter al valor inicial de l'interval a.
 * @param b Punter al valor inicial de l'interval b.
 * @param tol Tolerància per a la solució.
 * @param f Funció de la qual es vol trobar l'arrel.
 * @param prm Paràmetres addicionals per a la funció f.
 * @param ixrr Indicador per imprimir les iteracions.
 * @return Aproximació de l'arrel de la funció dins l'interval donat.
 *
 * Aquesta funció aplica el mètode de bisecció per trobar l'arrel d'una funció
 * dins d'un interval [a, b] amb una precisió especificada per tol.
 */
double biseccio (double *a, double *b, double tol, double (*f)(double,void*), void *prm, int ixrr) {
    double fa = f(*a, prm);
    double fb = f(*b, prm);

    if (fa * fb > 0){
        fprintf(stderr, "\nError: Es requereixen a i b inicials en bisecció tals que f(a)f(b) < 0\n\n");
        return -1; // La funció ha de tenir signes oposats als extrems de l'interval escollit
    }

    if (fabs((*b - *a))/2.0 <= tol) return (*a + *b)/2.0;

    int iter = 1;
    double m, fm;
    while ((fabs(*b - *a))/2.0 > tol) {
        m = (*a + *b) / 2.0; // Punt mig de l'últim interval
        fm = f(m, prm);
        
        // Si ixrr és superior a 0, imprimiu els detalls de la iteració actual a stderr
        if (ixrr > 0) fprintf(stderr, "Iteració %d: a = %.16g, b = %.16g, m = %.16g, f(m) = %.16g\n", iter,*a, *b, m, fm);
        
        if (fa * fm < 0) { // L'arrel està a [a, m]
            *b = m;
            fb = fm;
        } else { // L'arrel està a [m, b]
            *a = m;
            fa = fm;
        }
        iter++;
    }

    // Retorna el punt mitjà de l'interval final.
    return m;       
}

/**
 * Funció de Newton per trobar les arrels d'una funció.
 *
 * @param x Punter al valor inicial de l'aproximació de l'arrel.
 * @param tolf Tolerància per al valor de la funció.
 * @param tolx Tolerància per al canvi en x.
 * @param maxit Nombre màxim d'iteracions.
 * @param fdf Funció que calcula f(x) i f'(x).
 * @param prm Paràmetres addicionals per a la funció fdf.
 * @param ixrr Indicador per imprimir les iteracions.
 * @return Nombre d'iteracions realitzades si es troba l'arrel, -1 en cas contrari.
 *
 * Aquesta funció aplica el mètode de Newton per trobar l'arrel d'una funció
 * donada una aproximació inicial.
 */
int newton(double *x, double tolf, double tolx, int maxit, void (*fdf)(double, double*, double*, void*), void *prm, int ixrr) {
    double fx, dfx, xnew;
    int iter;

    for (iter = 0; iter < maxit; iter++) {
        // Calcular f(x) i f'(x)
        fdf(*x, &fx, &dfx, prm);

        // Evitar divisió per zero
        if (dfx == 0.0) {
            fprintf(stderr, "\nError: Derivada zero a x = %.16g\n\n", *x);
            return -1;
        }

        // Actualitzar x
        xnew = *x - fx / dfx;

        if (ixrr > 0) {
            fprintf(stderr, "Iteració %d: x = %.16g, f(x) = %.16g, f'(x) = %.16g\n", iter+1, *x, fx, dfx);
        }

        // Verificar tolerància
        if (fabs(fx) <= tolf && fabs(xnew - *x) <= tolx) {
            *x = xnew;
            if (ixrr > 0) {
                fprintf(stderr, "\nConvergència assolida a la iteració %d: x = %.16g\n\n", iter+1, *x);
            }
            return iter+1;
        }

        *x = xnew;
    }

    fprintf(stderr, "\nError: No s'ha assolit la convergència després de %d iteracions\n\n", maxit);
    return -1;
}