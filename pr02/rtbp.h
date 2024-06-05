int rtbp (int kv, int nv[], void *prm, double t, double x[], double f[]);
int rkf78 (int n, int kv, int nv[], void *prm,
      int (*camp)(int,int[],void *,double,double [],double []),
      double *t, double x[], double *h,
      double hmin, double hmax, double tol, double *eerr, int ivb);
int proptraj (double mu, int nt, double c, int isgn, double x,
      double *u, double *du, double pmax, FILE *fp);
double ctJac (double mu, double x[]);