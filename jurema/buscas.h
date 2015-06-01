#ifndef BUSCAS_H
#define BUSCAS_H

#ifndef MAX
    #define MAX 500
#endif

#ifndef TRUE
    #define TRUE 1
#endif

#ifndef FALSE
    #define FALSE 0
#endif

#ifndef ONE
    #define ONE 1
#endif

#ifndef ZERO
    #define ZERO 0
#endif

#ifndef INFINITY
    #define INFINITY 999999
#endif

#ifndef INFINITO
    #define INFINITO 999999
#endif

#ifndef INICIO
    #define INICIO 1
#endif

#ifndef custo
    #define custo(x,y) cost_matrix[x][y]
#endif

#ifndef lbound
    #define lbound(x,y) cost_matrix[x][y]
#endif

#ifndef anterior
    #define anterior(x) (x-1)
#endif

#ifndef proximo
   #define proximo(x) (x+1)
#endif



extern int dimension;
extern int custo;
extern int limiteSuperior;
extern int limiteSuperiorDois;
extern int limiteInferior;
extern int nivel;
extern int qtdFolhas;
extern unsigned long long int qtdNodosExpandidos;

extern clock_t tempoInicial;
extern clock_t tempoFinal;
extern clock_t tempo;
extern int a;
extern double tempoNecessario;


extern int cost_matrix[MAX*MAX];
extern int activeSet[MAX+1];
extern int solucaoGuia[MAX+1];
extern int ciclo[MAX+1];

extern bool diving_flag;

void branch(int);
void branch_jj(int);
void  dive(int);
#endif
