#include <stdio.h>
#include "rtbp.h"

#define PMAX .01

/*
echo "-0.8291710221854511 3.196255396314419 -1 2" | ./rtbp_sim _ _ > orbita_lyapunov.txt
*/

int main (int argc, char *argv[]) {
   double mu=1.215058560962404e-2, x, c, pmax=.01;
   int nt, isgn;

   if (argc<3
         || ( argv[1][0]!='_' && sscanf(argv[1], "%lf", &mu)!=1 )
         || ( argv[2][0]!='_' && sscanf(argv[2], "%lf", &pmax)!=1 )
      ) {
      fprintf(stderr,"%s _mu _pmax \
\n\
", argv[0]);
      return -1;
   }

   while (scanf("%lf %lf %d %d",&x,&c,&isgn,&nt)==4)
      proptraj(mu,nt,c,isgn,x,NULL,NULL,PMAX,stdout);
   return 0;
}