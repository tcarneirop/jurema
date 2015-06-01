/*****************************************************************************
*                                                                            *
* 			    FUNCOES AUXILIARES                               *
*****************************************************************************/
#include "global.h"
#include "aux.h"
#include <stdio.h>
#include <stdlib.h>

/*Funcao auxiliar responsavel por imprimit qualquer matriz*/
void print_any_matrix(int msize, int nsize, int A[MAX+1][MAX+1]) {
	int i, j;
	for (i = 1; i <= msize; i++) {
		for (j = 1; j <= nsize; j++)
			printf("%d ", A[i][j]);
		printf("\n");
	}
	return;
}

/*Funcao auxiliar responsavel por receber a matriz de adjacencias*/
void read(){

	scanf("%d", &dimension);

	for( int i = 0 ; i < (dimension*dimension) ; i++ ){
        scanf("%d", &cost_matrix[ i ] ) ;
    }

    for(int i = 1; i<=dimension;++i)
        for(int j = 1; j<=dimension;++j){
            if(i==j)
                cost(i,j) = INFINITO;
        }

}

//para ser utilizada quando a solguia e dada
void read_v2(){
    int i , j,s ;
	scanf("%d", &dimension);
	for(s = 1; s<=dimension+1; ++s){
        scanf("%d", &solucaoGuia[s]);
    }
	for( i = 0 ; i < (dimension*dimension) ; i++ ){
        scanf("%d", &cost_matrix[ i ] ) ;
	}

	for(int i = 1; i<=dimension; ++i){
		for(int j = 1; j<=dimension; ++j){
			if(i==j)
				cost(i,j) = INFINITO;
		}
	}
}

int calcularPesoSolGuia(){

	int soma = 0;
	for(int i = 1; i<=dimension; ++i){
		soma += original_matrix(solucaoGuia[i],solucaoGuia[proximo(i)]);
	}
	return soma;
}

int calcularPesoSolucao(int *A){
    int soma = limiteInferior;
    for(int i = 1; i<=dimension; ++i){
        soma+=custo(A[i], A[proximo(i)]);
    }
    return soma;
}



int calcularPesoSolucao(int inicio, int fim, int A[]){
    int soma = 0;
    for(int i = inicio; i<=fim; ++i){
        soma+= custo(A[i], A[proximo(i)]);
    }
    return soma;
}
int lb_cmp2(const void *a, const void *b){
    int idx1 = *(int*)a,
		idx2 = *(int*)b;
	if( lbound(solucaoGuia[nivel], idx1 ) == lbound(solucaoGuia[nivel], idx2 ) ) return 0;
	if( lbound(solucaoGuia[nivel], idx1 ) < lbound( solucaoGuia[nivel], idx2 ) ) return -1;
	if( lbound(solucaoGuia[nivel], idx1 ) > lbound( solucaoGuia[nivel], idx2 ) ) return 1;
}

