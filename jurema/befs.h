#ifndef BEFS_H
#define BEFS_H


extern int dimension;
extern int custo;
extern int limiteSuperior;
extern int limiteInferior;
extern int nivel;
extern int qtdFolhas;
extern unsigned long long int qtdNodosExpandidos;


extern int cost_matrix[MAX*MAX];
extern int activeSet[MAX+1];
extern int ciclo[MAX+1];


int best_first_search();

#endif
