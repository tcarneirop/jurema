#ifndef LOWERBOUNDS_H
#define LOWERBOUNDS_H


#ifndef NO_LB
#define NO_LB 1
#endif


#ifndef HUNGARIAN_METHOD
#define HUNGARIAN_METHOD 2
#endif

#ifndef LITTLE_ET_AL
#define LITTLE_ET_AL 3
#endif

#ifndef ZERO
#define ZERO 0
#endif

#ifndef UM
#define UM 1
#endif

#define cost_m(x,y) cost_matrix[(dimension)*(x)+(y)]

extern int cost_matrix[MAX*MAX];
extern int dimension;

extern int limiteInferior;

/**/

int lowerBound(int);
int hungarian_method();
int grafo_esparso(int *, int);
#endif
