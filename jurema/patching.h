#ifndef __PATCHING_H_
#define __PATCHING_H_

#ifndef _GENERAL_PATCHING_
	#define _GENERAL_PATCHING_ 1
#endif

#ifndef  _KARPS_MODIFIED_PATCHING_
	#define _KARPS_MODIFIED_PATCHING_ 2
#endif

#define usados(x,y) usados[(N)*(x)+(y)]
#define cost_p(x,y) cost_matrix[(N)*(x)+(y)]

#ifndef TRUE
	#define TRUE 1
#endif

#ifndef FALSE
	#define FALSE 0
#endif

extern int cost_matrix[MAX*MAX];
extern int solucaoGuia[MAX+1];
extern int dimension;

extern int N;
extern int usados[MAX*MAX];

int main_patching(int heuristica);
int karps_modified_patching(int *solucaoGuia);
int patching(int *solucaoGuia);

#endif
