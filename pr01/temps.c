#include <stdlib.h>
#include <sys/time.h>
#include <sys/resource.h>

/*
 * Ãšs tÃ­pic;
 *   double tt0=-1, tt1, tt2, tt3;
 *   tt1=temps(&tt0);
 *   ... codi ...
 *   tt2=temps(&tt0);  el temps transcorregut entre tt1 i tt2 Ã©s tt2-tt1
 *   ... codi ...
 *   tt3=temps(&tt0);  el temps transcorregut entre tt2 i tt3 Ã©s tt3-tt2
 *                     el temps transcorregut entre tt1 i tt3 Ã©s tt3-tt1
 *
 * L'unic objectiu de tt0 Ã©s fixar un origen de temps per tal que,
 * entre els segons des de 1/1/1970 i els nanosegons des dels segons
 * no matxaquem tota la precissiÃ³ doble
 *
 * Si TEMPS_RELLOTGE estÃ  definit, temps() dona wall-clock (gettimeofday())
 * Si TEMPS_RELLOTGE no estÃ  definit, temps() torna user time
 */

double temps (double *t0) {
#ifdef TEMPS_RELLOTGE
    struct timeval tv;
    gettimeofday(&tv,NULL);
    if (*t0<0) *t0=tv.tv_sec;
    return ((double)tv.tv_sec-*t0)+1e-6*tv.tv_usec;
#else  /* TEMPS_RELLOTGE */
    struct rusage ru;
    struct timeval *ptv;
    getrusage(RUSAGE_SELF,&ru);
    ptv=&ru.ru_utime;
    if (*t0<0) *t0=ptv->tv_sec;
    return ((double)ptv->tv_sec-*t0)+1e-6*ptv->tv_usec;
#endif /* TEMPS_RELLOTGE */
}