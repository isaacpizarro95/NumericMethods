/**
 * Pràctica 1 - Mètodes Numèrics
 * Autors: Isaac Pizarro i Gina Gardenyes
 * NIUS: 1636421; 1638998;
*/

#include <stdio.h>
#include <stdlib.h>
#include <math.h>
#include "trigrec.h"

/**
 * Programa principal per a calcular i escriure els valors de cosinus i sinus
 * per a múltiples d'un angle x fins a k, fent servir diferents algorismes.
 * 
 * @param argc Nombre d'arguments passats al programa.
 * @param argv Arguments passats al programa, on argv[1] és k i argv[2] és x.
 * @return Retorna 0 si s'executa correctament o -1 en cas d'error.
 */
int main (int argc, char *argv[]) {
    int k;
    double x;
        
    // Comprova que s'hagin introduït correctament els arguments necessaris
    if (argc!=3 
        || sscanf(argv[1],"%d",&k)!=1 
        || sscanf(argv[2],"%lf",&x)!=1) {
        fprintf(stderr, "Ús: trigrec_escr k x\n"); // Missatge d'error si els arguments no són vàlids
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

    // Calcula els valors utilitzant els diferents algorismes
    trigrec0(k, x, c[0], s[0]);
    trigrec1(k, x, c[1], s[1]);
    trigrec2(k, x, c[2], s[2]);
    trigrec3(k, x, c[3], s[3]);

    // Escriu els resultats en pantalla
    for(int j=0; j<=k; j++){
        printf("%.16g\t %.16g\t %.16g\t %.16g\t"
            "%.16g\t %.16g\t %.16g\t %.16g\t\n",
            c[0][j], c[1][j], c[2][j], c[3][j],
            s[0][j], s[1][j], s[2][j], s[3][j]);
    }

    // Allibera l'espai de memòria reservat
    free(c);
    free(s);
    return 0;
}