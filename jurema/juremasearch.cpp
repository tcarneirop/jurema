#include "global.h"
#include <stdio.h>
#include <string.h>
#include <ctime>
#include <cstdlib>
#include "buscas.h"
#include "aux.h"
#include "juremasearch.h"

void jurema(int level){

	 register int i;
	 int nodoAtual;
	 int branchingNode;
	 register int contador = ZERO;

    /*
        Manipulacao da matriz de ciclo. A priori o ciclo seria a solucao guia.
	 */
     memcpy(ciclo,solucaoGuia,sizeof(solucaoGuia));
     for(int i = 1; i<=dimension; ++i){
            activeSet[i] = TRUE;
     }
	 printf("\nINICIANDO O METODO JUREMA DE %d A %d\n", dimension, level);


     printf("\nSolucao inicial: ");
     for(int i = 1; i<=dimension+1; ++i){
        printf("%d ", solucaoGuia[i]);
     }
	 /*Tempo Comeca a ser contado*/
	 tempoInicial = clock();

	 custo = limiteSuperior; /*Custo da solucao guia*/

	 custo -= lbound(solucaoGuia[dimension],INICIO);
	 custo -= lbound(solucaoGuia[anterior(dimension)],solucaoGuia[dimension]);

	 activeSet[solucaoGuia[dimension]] = FALSE;

	 for(nivel = (dimension - 2); nivel>=level; --nivel){

            memset( lbOrder , 0 , sizeof( lbOrder ) ) ;

            custo -= lbound(solucaoGuia[nivel],solucaoGuia[proximo(nivel)]);
			nodoAtual = solucaoGuia[nivel];

            contador = 0; /*Para lbOrder[x]*/

            for(int i =1; i<=dimension; ++i){

                if(i == nodoAtual) continue;

                    if(activeSet[i]!=TRUE && (custo + lbound(nodoAtual, i)< limiteSuperior)){
                        lbOrder[contador] = i;
                        ++contador;
                    }//if

            }//for

            /*Ordenando o BFS de acordo com o peso do limiteInferior
              Passo necessario para verificar a forma mais eficiente de, a partir
              de nodoAtual, percorrer o espaco de solucoes.
            */
            qsort( lbOrder, contador, sizeof( int ), lb_cmp2);
	        activeSet[solucaoGuia[proximo(nivel)]] = FALSE;
            ciclo[nivel] = nodoAtual;

	        for(int i = 0; i<contador; ++i){

                branchingNode = lbOrder[i];
              // if(  custo+lbound(nodoAtual,branchingNode) < limiteSuperior){

                custo+=lbound(nodoAtual,branchingNode);
                ++qtdNodosExpandidos;

                branch(branchingNode);
                custo-=lbound(nodoAtual,branchingNode);
                //}

            }//for /*Branching part*/


    }//for

   	/*Tempo para de ser computado*/
	tempoFinal = clock();
	tempoNecessario = (tempoFinal - tempoInicial); /*Tempo Necessario em minutos*/

}//jurema



