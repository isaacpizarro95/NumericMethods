#include <stdio.h>
#include <math.h>
#include "zeros.h"

double fnc_bis_exp (double x, void *prm) {
   return exp(x)-2;
}

int main (int argc, char *argv[]) {
   double a, b, tol, alf;
   int ixrr;

   if (argc<5
         || sscanf(argv[1], "%lf", &a)!=1
         || sscanf(argv[2], "%lf", &b)!=1
         || sscanf(argv[3], "%lf", &tol)!=1
         || sscanf(argv[4], "%d", &ixrr)!=1
      ) {
      fprintf(stderr,"%s a b tol ixrr \\n\
      ", argv[0]);
      return -1;
   }

   alf=biseccio(&a,&b,tol,fnc_bis_exp,NULL/*prm*/,ixrr);
   printf("alf %.16g\n", alf);
   return 0;
}