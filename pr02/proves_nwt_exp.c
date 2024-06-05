#include <stdio.h>
#include <math.h>
#include "zeros.h"

void fnc_nwt_exp (double x, double *fx, double *dfx, void *prm) {
   *dfx=exp(x);
   *fx=*dfx-2;
}

int main (int argc, char *argv[]) {
   double x, tolf, tolx, ln2=log(2.);
   int maxit, ixrr, iret;
/*
 * LÃ­nia de comandes:
   double x double tolf double tolx int maxit int ixrr
 */
   if (argc<6
         || sscanf(argv[1], "%lf", &x)!=1
         || sscanf(argv[2], "%lf", &tolf)!=1
         || sscanf(argv[3], "%lf", &tolx)!=1
         || sscanf(argv[4], "%d", &maxit)!=1
         || sscanf(argv[5], "%d", &ixrr)!=1
      ) {
      fprintf(stderr,"%s x tolf tolx maxit ixrr \
\n\
", argv[0]);
      return -1;
   }
/*
 * Fi lÃ­nia de comandes
 */
   iret=newton(&x,tolf,tolx,maxit,fnc_nwt_exp,NULL/*prm*/,ixrr);
   printf("iret %d x %.16g ln(2) %.16g dif %g\n", iret, x, ln2, x-ln2);
   return 0;
}