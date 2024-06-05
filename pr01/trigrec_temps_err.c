/**
 * Pràctica 1 - Mètodes Numèrics
 * Autors: Isaac Pizarro i Gina Gardenyes
 * NIUS: 1636421; 1638998;
*/

#include <stdio.h>
#include <stdlib.h>
#include <assert.h>
#include <math.h>
#include "trigrec.h"
#include "temps.h"

/**
 * Programa principal per a mesurar el temps d'execució i l'error dels algorismes trigonomètrics.
 * 
 * @param argc Nombre d'arguments passats al programa.
 * @param argv Arguments passats al programa, on argv[1] és k i argv[2] és x.
 * 
 * Aquest programa calcula el cosinus i el sinus de múltiples d'un angle x fins a k
 * utilitzant diferents mètodes, mesura el temps d'execució de cada mètode i estima
 * l'error màxim comès per les funcions trigrec1, trigrec2 i trigrec3 comparant els
 * outputs amb els de trigrec0.
 * 
 * Finalment imprimeix els temps d'execució i els errors màxims.
 */
int main (int argc, char *argv[]){
    int k;
    double x;
    // Comprova que s'hagin introduït els paràmetres correctament
    if (argc!=3
            || sscanf(argv[1],"%d",&k)!=1
            || sscanf(argv[2],"%lf",&x)!=1
            ) {
        fprintf(stderr, "trigrec_temps_err k x\n");
        return -1;
    }

    // Arrays per emmagatzemar els resultats de cosinus i sinus
    double (*c)[k+1], (*s)[k+1]; 
    if((c = (double (*)[k+1]) malloc(4*(k+1)*sizeof(double))) == NULL){
            printf("\n[ERROR] Malloc no ha pogut reservar l'espai de memòria\n\n");
            exit(1);     
    }
    if((s = (double (*)[k+1]) malloc(4*(k+1)*sizeof(double))) == NULL){
            printf("\n[ERROR] Malloc no ha pogut reservar l'espai de memòria\n\n");
            exit(1);     
    }
    double t0 = -1, t1, t2, t3, t4, t5; // Variables per mesurar el temps

    // Calcula el temps d'execució de cada funció trigrec
    t1 = temps(&t0);
    trigrec0(k, x, c[0], s[0]);
    t2 = temps(&t0);
    
    trigrec1(k, x, c[1], s[1]);
    t3 = temps(&t0);
    
    trigrec2(k, x, c[2], s[2]);
    t4 = temps(&t0);
    
    trigrec3(k, x, c[3], s[3]);
    t5 = temps(&t0);

    printf("trigrec0 ha trigat %.16g segons\n", t2-t1);
    printf("trigrec1 ha trigat %.16g segons\n", t3-t2);
    printf("trigrec2 ha trigat %.16g segons\n", t4-t3);
    printf("trigrec3 ha trigat %.16g segons\n", t5-t4);
    
    double e_c, e_s; // Variables per a emmagatzemar l'error
    double max_e_c[3], max_e_s[3]; // Màxims errors calculats

    // Calcula l'error màxim de cada algorisme
    for(int i=0; i<3; i++){
        max_e_c[i] = 0;
        max_e_s[i] = 0;
        for(int j=0; j<=k; j++){
            if(max_e_c[i] < (e_c = fabs(c[i+1][j] - c[0][j]))) max_e_c[i] = e_c;
            if(max_e_s[i] < (e_s = fabs(s[i+1][j] - s[0][j]))) max_e_s[i] = e_s;
        }
    }

    // Imprimeix els errors màxims calculats
    printf("\nerrc1 = %.16g\t errc2 = %.16g\t errc3 = %.16g\nerrs1 = %.16g\t errs2 = %.16g\t errs3 = %.16g\n", 
        max_e_c[0], max_e_c[1], max_e_c[2], max_e_s[0], max_e_s[1], max_e_s[2]);

    // Allibera l'espai de memòria reservat
    free(c);
    free(s);
    return 0;
}

