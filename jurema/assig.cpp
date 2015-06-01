#include "assig.h"
#include <stdlib.h>
#include <assert.h>


/* ROUTINES DI ASSEGNAMENTO */
void incrm(int *f,int j,int *fb,int *rc)
  /* the procedure increments the assignment starting from column j */
 // int *f,*fb,*rc;
 // int j;
  {
    register int i,jj;
    do {
      i=rc[j];
	fb[j]=i;
	jj=f[i];
	f[i]=j;
      j=jj;
    } while (j!=-1);
  } /* procedure incrm */
double init(int n,int *a,int *f,int *u,int *v,int *fb,int *p)
/* initial dual and primal solutions */
//int n;
//int *a,*u,*v;
//int *f,*fb,*p;
{
  /* it returns the number of initially assigned rows */
  register int i,j,k1;
  int *pv,*pu,*pa,*pa1;
  int *pfb,*pf;
  int min,ia;
  int r; /* index */
  int m; /* number of assigned rows */
  int assign;
  /* Phase 1 */
  m=0;
  for (j=0,pf=f,pfb=fb;j<n;j++,pf++,pfb++)
  {
    *(pfb)=(-1);
    *(pf)=(-1);
  }
 /* scanning of the columns and initialization of v */
  for (j=0,pfb=fb,pv=v;j<n;j++,pfb++,pv++)
  {
    min=INF;
    pf=f;
    pa=a+j;
    for (i=0;i<n;i++)
    {
      ia=(*pa);   /* ia=a[i][j] */
      if (ia<min)
      {
        min=ia;
        r=i;
      }
      else if ((ia==min) && ((*pf)==-1)) r=i;
      pf++;
      pa=pa+n;
    }
    *pv=min;
   if (f[r]==-1)
    {
      /* assignment of column j to row r */
      m++;
      *(pfb)=r;
      f[r]=j;
      u[r]=0;
      p[r]=j+1;
    }
  } /*for j */
  /* Phase 2 */
  /* scanning of the unassigned rows */
  for (i=0,pf=f,pu=u,pa1=a;i<n;i++,pf++,pu++,pa1=pa1+n)
  {
    if((*pf)==-1)
    {
      pa=pa1;
      min=INF;
      j=(-1);
      for (k1=0,pv=v,pfb=fb;k1<n;k1++,pv++,pfb++)
      {
        ia=(*(pa)-(*(pv)));
        pa++;
       if (ia<min)
        {
          min=ia;
          j=k1;
        }
        else if ((ia==min)&&(*pfb==-1)&&(j==-1))
        j=k1;
        else if ((ia==min)&&(*pfb==-1)&&(fb[j]!=-1)) j=k1;
      } /*for k1*/
      *(pu)=min;
      pfb=fb+j;
      if (*(pfb)==-1) assign=1; else assign=0;
      while ((!assign)&&(j<n))
      {
        if (abs((*(pa1+j)-(*pu)-v[j]))<=0)   /* a[i][j]-u[i]-v[j]==0 */
        {
          r=(*(pfb));   /* r=fb[j] */
          k1=p[r];
         while ((!assign)&&(k1<n))
          {
            if ((fb[k1]==-1)&&((abs(*(a+n*r+k1)-u[r]-v[k1]))<=0))
            { /* reassignment of row r and column k1 */
              assign=1;
              f[r]=k1;
              fb[k1]=r;
              /* p[r]=k1+1 */
            }
            else k1++;
          }
          p[r]=k1+1;
        } /* if */
        if (!assign)
        j++;
      } /* while */
      if (assign)
      {
        /* new assignment */
        m++;
        *(pf)=j;
        fb[j]=i;
        p[i]=j+1;
      }
    } /* if */
  } /* for i */
  return(m);
} /* procedure init */
int path(int n,int *a,int i,int *f,int *u,int *v,int *fb,int *rc)
/* determination of an augmenting path starting from unassigned row i and
terminating returning an unassigned column, with updating the dual variables
u[i] and v[i] */
//int n;
//int *a;
//int i;
//int *u,*v;
//int *f,*fb,*rc;
{
// static int uc[MAXOP]; /* set of unalabelled columns */
 //static int lr[MAXOP]; /* set of labelled rows */
// static int pi[MAXOP]; /* min (a[i,j]-u[i]-v[j]; such that row i
                     //         is labelled and not equal to fb[j]) */
 register int j,l,k1;
 int ia,ui,min; /* auxiliary variables */
 int found, nuc,nlr,r;
 int *pa,*ppi,*pv,*pu;
 int *puc,*plr,*prc;
 /* initialization */
 *lr=i;
 nlr=1;
 ui=u[i];
 for (k1=0,ppi=pi,pa=(a+i*n),puc=uc,prc=rc,pv=v;
      k1<n;
      k1++,ppi++,pa++,puc++,prc++,pv++)
 {
   *puc=k1;
   *prc=i;
   *ppi=(*pa)-ui-(*pv);
 }
 nuc=n;
 do
 {
   /* search for a zero element in an unlabelled column */
   l=0;
   found=0;
   puc=uc;
   do
   {
      j=(*puc);
      if (abs(pi[j])<=0) found=1;
      else
      {
        puc++;
        l++;
      }
    } while ((l<nuc)&&(found==0));
    if (found==0)
    {
      /* uptating of the dual variables */
      min=INF;
      for (l=0,puc=uc;l<nuc;l++,puc++)
      {
        j=(*puc);
        if(pi[j]<min) min=pi[j];
      }
      for (l=0,plr=lr;l<nlr;l++,plr++)
      {
        r=(*plr);
        u[r]=u[r]+min;
      }
      for (l=0,pv=v,ppi=pi;l<n;l++,pv++,ppi++)
      {
        if (abs(*ppi)>0) *ppi=(*ppi)-min; /* *ppi!=0 */
        else *pv=(*pv)-min;
      }
    }
    else
    {
      /* determination of an unassigned column j */
      if (fb[j]==-1) return(j);
      else
      {
        /* labelling of row fb[j] and removal of the label of column j */
        lr[nlr]=fb[j];
        nlr++;
        nuc--;
        *puc=uc[nuc];
        /* scanning of the labelled rows */
        r=lr[nlr-1];
        pa=(a+r*n);
        ui=u[r];
        for (l=0,puc=uc;l<nuc;puc++,l++)
        {
           j=(*puc);
           ia=(*(pa+j))-ui-v[j];
           if (ia<pi[j])
           {
             pi[j]=ia;
             rc[j]=r;
           }
        }
      }
    }
  } while (1);
};
double apc_michele (int n,int *a,int *f,int *fb,int * dualU,int *dualV,int fl_ini)  /* assignment function */
//int n;
//int *a;
//int *f,*fb;

//int fl_ini;


/* Hungarian method for complete matrices; algorithm described in
   G.Carpaneto, S.Martello, P. Toth, "Algorithms and codes for the Assignment
   problem", Annals of Operations Research, vol13, 1988
   Complexity O(n**3)
    n = size of the problem
    a = cost matrix
    f = assignment
   the function returns the cost of the min cost assigment
   Note that unassigned rows are labelled by -1
    (in the original code they were labelled by 0 but in the C implementation
     0 is a feasible assignment label)       */
  {
   register int i,j;
   double z;

   int m; /* number of initial assignments */
   int *pf;
   int *u,*v;
   	u=(int*)calloc(sizeof(int),n);
	v=(int*)calloc(sizeof(int),n);
	uc=(int*)malloc(sizeof(int)*n);

	lr=(int*)malloc(sizeof(int)*n);
	pi=(int*)malloc(sizeof(int)*n);
	p=(int*)malloc(sizeof(int)*n);
	rc=(int*)malloc(sizeof(int)*n);


   if ( fl_ini )
     m=init(n,a,f,u,v,fb,p);
   else
     for (m=i=0; i<n; i++) if (f[i]>=0) m++;
   if (m<n)
     for (i=0,pf=f;i<n;i++,pf++)
        if (*(pf)==-1)
        {
          j=path(n,a,i,f,u,v,fb,rc);
          incrm(f,j,fb,rc);
        }
     /* computation of the assignment value */
     z=0;
     for (i=0;i<n;i++,u++,v++){
       z=z+*(u)+*(v);
       dualU[i] = *(u);
       dualV[i] = *(v);
       //printf("u:%2d  v:%2d\n",*(u),*(v));
     }
     //printf("\n");
     return(z);
  } /* function apc */

