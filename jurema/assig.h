 #ifndef ASSIGNEMT_H_
 #define ASSIGNEMT_H_
 #define INF (999999)
 #define MAXOP (36)
 static int *uc; /* set of unalabelled columns */
 static int *lr; /* set of labelled rows */
 static int *pi; /* min (a[i,j]-u[i]-v[j]; such that row i
                              is labelled and not equal to fb[j]) */
 static int *p,*rc;

void incrm(int *f,int j,int *fb,int *rc);
double init(int n,int *a,int *f,int *u,int *v,int *fb,int *p);
int path(int n,int *a,int i,int *f,int *u,int *v,int *fb,int *rc);
double apc_michele (int n,int *a,int *f,int *fb,int * dualU,int *dualV,int fl_ini);
#endif /*ASSIGNEMT_H_*/

