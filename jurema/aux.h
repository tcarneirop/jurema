#ifndef AUX_H
#define AUX_H

#ifndef MAX
	#define MAX 600
#endif

extern int cost_matrix[MAX*MAX];
extern int original_matrix[MAX*MAX];
extern int activeSet[MAX+1];
extern int solucaoGuia[MAX+1];
extern int solucaoGuiaDois[MAX+1];


extern int dimension;
extern int custo;
extern int limiteSuperior;
extern int limiteInferior;
extern int nivel;




void print_any_matrix(int msize, int nsize, int A[MAX+1][MAX+1]);
int calcularPesoSolucao(int *);
int calcularPesoSolGuia();

void organizarSolucaoGuia(int i, int j, int k, int *A,int contador);
void read();
void read_v2();
int lb_cmp2( const void *a, const void *b );

#endif
