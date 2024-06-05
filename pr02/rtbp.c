#include <stdio.h>
#include <math.h>
#include <string.h>
#include <assert.h>

#define N 4

#ifdef __GNUC__
   #define MIN(i,j) ({ typeof(i) ti=(i); typeof(j) tj=(j); ti<=tj?ti:tj; })
#else /* defined(__GNUC__) */
   #define MIN(i,j) ((i)<=(j)?(i):(j))
#endif /* defined(__GNUC__) */
#define SIGNE(x) ((x)>=0?1:-1)

/*
 * RTBP pla en sinÃ²diques (posicions + velocitats) i variacionals
 * primeres
 */

#define X x[0]
#define Y x[1]
#define U x[2]
#define V x[3]

int rtbp (int kv, int nv[], void *prm, double t, double x[], double f[]) {
   double mu, xmmu, xmmup1, y2, td1, td2, rh12, rh22, rh1, rh2,
          rh13, rh23, pot3, potx3, onemmu;
   mu=*((double *)prm);
   onemmu=1-mu;
   xmmu=X-mu; xmmup1=xmmu+1;
   y2=Y*Y;
   rh12=xmmu*xmmu+y2; rh22=xmmup1*xmmup1+y2;
   rh1=sqrt(rh12); rh2=sqrt(rh22);
   rh13=rh12*rh1; rh23=rh22*rh2;
   td1=-onemmu/rh13; td2=-mu/rh23;
   pot3=td1+td2;
   potx3=td1*xmmu+td2*xmmup1;
/* Equacions */
   f[0]=U; f[1]=V;
   f[2]=2*V+X+potx3;
   f[3]=-2*U+Y*(1+pot3);
/* Variacionals primeres */
   if (kv>=1) {
#define VARX(i,j) x[(1+(j))*N+(i)]
#define VARF(i,j) f[(1+(j))*N+(i)]
      double pot5, potx5, omgxx, omgxy, omgyy;
      int j;
      td1=onemmu/(rh13*rh12); td2=mu/(rh23*rh22);
      pot5=td1+td2;
      td1*=xmmu; td2*=xmmup1;
      potx5=td1+td2;
      omgxx=1+pot3+3*(td1*xmmu+td2*xmmup1);
      omgxy=3*Y*potx5;
      omgyy=1+pot3+3*y2*pot5;
      for (j=0; j<nv[0]; j++) {
         VARF(0,j)=VARX(2,j);
         VARF(1,j)=VARX(3,j);
         VARF(2,j)=omgxx*VARX(0,j)+omgxy*VARX(1,j)+2*VARX(3,j);
         VARF(3,j)=omgxy*VARX(0,j)+omgyy*VARX(1,j)-2*VARX(2,j);
      }
#undef VARX
#undef VARF
   }
   return 0;
}

#undef W
#undef V
#undef U

int rkf78 (int n, int kv, int nv[], void *prm,
      int (*camp)(int,int[],void *,double,double [],double []),
      double *t, double x[], double *h,
      double hmin, double hmax, double tol, double *eerr, int ivb) {
/* Coeficients RK (estatics) */
   static double alfa[13] = {
              0.,     2./27.,      1./9.,      1./6.,     5./12.,
              .5,      5./6.,      1./6.,      2./3.,      1./3.,
              1.,         0.,         1.
   };
   static double beta[78] = {
                      2./27.,     1./36.,     1./12.,     1./24.,
              0.,      1./8.,     5./12.,         0.,   -25./16.,
         25./16.,        .05,         0.,         0.,        .25,
              .2,  -25./108.,         0.,         0.,  125./108.,
        -65./27., 2.*(125./108.), 31./300.,       0.,         0.,
              0.,   61./225.,     -2./9.,   13./900.,         2.,
              0.,         0.,    -53./6.,   704./45.,   -107./9.,
         67./90.,         3.,  -91./108.,         0.,         0.,
        23./108., -976./135.,   311./54.,   -19./60.,     17./6.,
         -1./12., 2383./4100.,        0.,         0., -341./164.,
      4496./1025., -301./82., 2133./4100.,   45./82.,   45./164.,
         18./41.,    3./205.,         0.,         0.,         0.,
              0.,    -6./41.,   -3./205.,    -3./41.,     3./41.,
          6./41.,         0., -1777./4100.,       0.,         0.,
      -341./164., 4496./1025., -289./82., 2193./4100.,   51./82.,
        33./164.,    12./41.,         0.,          1.
   };
   static double  c[11] = {
        41./840.,         0.,         0.,         0.,         0.,
        34./105.,     9./35.,     9./35.,    9./280.,    9./280.,
        41./840.
   };
   static double cp[13] = {
              0.,         0.,         0.,         0.,         0.,
        34./105.,     9./35.,     9./35.,    9./280.,    9./280.,
              0.,   41./840.,   41./840.
   };
/* Variables locals */
   int ib, j, k, l, nn=n*(1+( kv>=1?nv[0]:0 )), iret;
   double tt, bet, d, dd, e3, wksp[15*nn], *r=wksp, *b=wksp+13*nn,
          *f=wksp+14*nn;
/* Bucle en el pas */
   do {
   /* Fem RK7 -> b[] i RK8 -> f[]
    * Mitjana per coordenades de RK7-RK8 -> d
    * Norma sub-1 de RK7-RK8 -> dd */
      ib=0;
      for (j=0; j<13; j++) {
         memcpy(b, x, nn*sizeof(double));
         tt=(*t)+alfa[j]*(*h);
         for (k=0; k<j; k++, ib++) {
            bet=beta[ib]*(*h);
            for (l=0; l<nn; l++)
               b[l]+=bet*r[nn*k+l];
         }
         iret=camp(kv,nv,prm,tt,b/*x*/,r+nn*j/*f*/);
         if (iret) return iret;
      }
      dd=d=0;
      for (l=0; l<nn; l++) {
         b[l]=f[l]=x[l];
         for (k=0; k<11; k++) {
            bet=(*h)*r[k*nn+l];
            b[l]+=bet*c[k];
            f[l]+=bet*cp[k];
         }
         f[l]+=(*h)*(cp[11]*r[11*nn+l]+cp[12]*r[12*nn+l]);
         d+=fabs(f[l]-b[l]);
         dd+=fabs(f[l]);
      }
      d/=nn;    /* No es la norma sub-1, sino la mitjana dels errors    */
                /*    comesos a cada coordenada. dd si que es la norma  */
                /*    sub-1, pero no s'usa per mesurar errors sino per  */
                /*    relativitzar la tolerancia.                       */
      e3=tol*(1.+.01*dd); /* Es una tolerancia absoluta per valors    */
                          /* petits de les coordenades, relativa      */
                          /* "retardada dos digits" per valors grans. */
   /* Pleguem si O.K. o pas minim. */
      if (d<e3 || fabs(*h)<=hmin) break;
   /* Corregim pas per a reintegrar. */
      (*h)*=.9*pow(e3/d,.125);
      if (fabs((*h))<hmin) (*h)=SIGNE(*h)*hmin;
   /* Torno a fer RK78 */
   } while (1);
/* Guardem temps final. */
   (*t)+=(*h);
/* Guardem punt final. */
   memcpy(x, f, nn*sizeof(double));
/* Fem correccio de pas */
   if (d<e3) { double tmp=e3/256; if (d<tmp) d=tmp; }
                                /* Si l'error ha estat molt petit         */
                                /*    no volem que el nou pas es dispari. */
   (*h)*=.9*pow(e3/d,.125);  /* Correccio Fehlberg (Stoer 2a ed (7.2.5.16), */
                             /*   noti's que NO es la (7.2.5.17)).          */
   if (fabs(*h)<hmin) {      /* Fem que estigui dins */
      (*h)=SIGNE(*h)*hmin;
      if (ivb>=1)
         fprintf(stderr,"rkf78():: t %G : ajusto a pasmin %G !!\n", *t, hmin);
   }
   else if (fabs(*h)>hmax) { /* els limits permesos. */
      (*h)=SIGNE(*h)*hmax;
      if (ivb>=2)
         fprintf(stderr,"rkf78():: t %G : ajusto a pasmax %G\n", *t, hmax);
   }
/* Tornem l'estimaciÃ³ de l'error */
   if (eerr!=NULL) *eerr=d;
   return 0;
}

static double v (double x, int isgn, double c, double mu, double *dv) {
   double xmmu, xmmup1, r1, r2, r12, r22, r13, r23, /*y2, */onemmu, ret;
   onemmu=1-mu; xmmu=x-mu; xmmup1=xmmu+1; /* y2=y*y; */
   r12=xmmu*xmmu; r1=fabs(xmmu);
   r22=xmmup1*xmmup1; r2=fabs(xmmup1);
   ret=isgn*sqrt(-c+x*x/*+y2*/+2*(onemmu/r1+mu/r2)+mu*onemmu);
   if (dv!=NULL) {
      r13=r12*r1; r23=r22*r2;
      *dv=(x-onemmu*xmmu/r13-mu*xmmup1/r23)/ret;
   }
   return ret;
}

#define P0 .01
#define PMIN 1e-4
#define TOL 1e-14
#define TOLS 1e-12
#define IX 0
#define IY 1
#define IU 2
#define IV 3
#define IVB 1
// #define XLI -0.8369151257723572

int proptraj (double mu, int nt, double c, int isgn, double x,
      double *u, double *du, double pmax, FILE *fp) {
   int kv, nv, nn=(du==NULL)?N:3*N, j, it;
   double t, xx[nn], h, dv, f[N], ta, xxa[nn];
   if (du==NULL) kv=0;
   else { kv=1; nv=2; }
/* InicialitzaciÃ³ int num */
//    isgn=(x>XLI)?-1:1;
   xx[IX]=x; xx[IY]=0; xx[IU]=0; xx[IV]=v(x,isgn,c,mu,du!=NULL?&dv:NULL);
   if (du!=NULL) {
      xx[4]=1; xx[5]=0; xx[6]=0; xx[7]=0; 
      xx[8]=0; xx[9]=0; xx[10]=0; xx[11]=1; 
   }
   t=0; h=PMIN;
/* Vol lliure */
   for (it=0; it<nt; it++) {
      do {
         if (fp!=NULL)
            fprintf(fp,"%.16g %.16g %.16g %.16g %.16g\n",
                  t, xx[0], xx[1], xx[2], xx[3]);
         ta=t; memcpy(xxa,xx,nn*sizeof(double));
         rkf78(N,kv,&nv,&mu,rtbp,&t,xx,&h,PMIN,pmax,TOL,NULL/*eerr*/,IVB);
      } while (isgn*xx[IY]>=0);
      isgn=-isgn;
   }
/* Ajustar a secciÃ³ */
   t=ta; memcpy(xx,xxa,nn*sizeof(double));
   while (fabs(xx[IY])>TOLS) {
      rtbp(0/*kv*/,NULL/*nv*/,&mu,t,xx,f);
      h=-xx[IY]/f[IY];
      rkf78(N,kv,&nv,&mu,rtbp,&t,xx,&h,
            MIN(PMIN,fabs(h))/*hmin*/,fabs(h)/*hmax*/,TOL,NULL/*eerr*/,IVB);
   }
   if (fp!=NULL)
      fprintf(fp,"%.16G %.16G %.16G %.16G %.16G\n\n",
            t, xx[0], xx[1], xx[2], xx[3]);
/* Avaluo f */
   if (u!=NULL) *u=xx[IU];
   if (du!=NULL) {
      double dp[2];
#define VAR(i,j) xx[(1+(j))*N+(i)]
   /* Avaluo DP (nomÃ©s la fila IU) */
      rtbp(0/*kv*/,NULL/*nv*/,&mu,t,xx,f);
      for (j=0; j<2; j++)
        dp[j]=VAR(IU,j)-f[IU]*VAR(IY,j)/f[IY];
   /* Avaluo f' */
      *du=dp[0]+dp[1]*dv;
#undef VAR
   }
   return 0;
}

#undef XLI
#undef IVB
#undef TOLS
#undef TOL
#undef PMIN
#undef P0

double ctJac (double mu, double x[]) {
   double xmmu, xmmup1, y2, onemmu, r1, r2, ret;
   onemmu=1-mu; xmmu=x[IX]-mu; xmmup1=xmmu+1; y2=x[IY]*x[IY];
   r1=sqrt(xmmu*xmmu+y2); r2=sqrt(xmmup1*xmmup1+y2);
   ret=-x[IU]*x[IU]-x[IV]*x[IV]+x[IX]*x[IX]+x[IY]*x[IY]
      +2*(onemmu/r1+mu/r2)+mu*onemmu;
   return ret;
}

#undef IV
#undef IU
#undef IY
#undef IX