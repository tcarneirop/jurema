#include "global.h"
#include "dfs_bnb.h"
#include <stdio.h>
#include <string.h>
#include <ctime>
#include "buscas.h"


/*
    DFS-BNB
*/
void dfs(){

     printf("\n\nBUSCA DFS INICIADA\n\n");
	/*Inicializando o activeSet. Como o DFS() não utiliza a solucao guia, utiliza
	apenas o seu valor, ele pode realizar esta operacao.*/

    memset( activeSet , ZERO , sizeof( activeSet ) ) ;

    tempoInicial = clock(); /*Tempo Comeca a ser contado*/
    activeSet[INICIO]=ONE;
    nivel = INICIO;
    custo += limiteInferior; /*Busca se dara como em papadimitriou e steinglitz (1998)*/

    ciclo[nivel] = INICIO;

	for(int i = 2; i<=dimension; ++i){

			custo+= lbound(INICIO,i);

			if( custo < limiteSuperior ) {
		         ++qtdNodosExpandidos;
  				 branch( i );
   			 }
   			 custo-= lbound(INICIO,i);
	}

	/*Tempo para de ser computado*/
	tempoFinal = clock();
	tempoNecessario = (tempoFinal - tempoInicial); /*Tempo Necessario em minutos*/
}
