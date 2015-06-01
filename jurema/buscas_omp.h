#ifndef BUSCAS_OMP_H
#define BUSCAS_OMP_H

extern int cost_matrix[MAX*MAX];
extern int solucaoGuia[MAX+1];
extern int activeSet[MAX+1];
extern int dimension;
extern int custo;
extern int limiteSuperior;
extern int limiteInferior;
extern int nivel;
extern int lbOrder[MAX+1];
extern int custo ;
extern unsigned long long int qtdNodosExpandidos;






/*guardara a melhor solucao de cada thread*/


void jurema_paralela();
void dfs_paralelo();


#endif
