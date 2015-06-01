#include "global.h"
#include <stdio.h>
#include <string.h>
#include <ctime>
#include <cstdlib>
#include "aux.h"
#include "buscas.h"
#include "jurematronco.h"
#include "juremasearch.h"


void jurema_tronco(){

     register int i;
	 int nodoAtual;
	 int branchingNode;
	 int retorno;
	 register int contador = ZERO;
	 int custo_aux;
	 int aSetAux[MAX+1];


     //Manipulacao da matriz de ciclo. A priori o ciclo seria a solucao guia.

	 printf("\nINICIANDO UMA JUREMA TRONCO\n");

     memcpy(ciclo,solucaoGuia,sizeof(solucaoGuia));

     for(int i = 1; i<=dimension; ++i){
            activeSet[i] = TRUE;
     }

     printf("\nSolucao guia inicial: ");
     for(int i = 1; i<=dimension+1; ++i){
        printf("%d ", solucaoGuia[i]);
     }
     puts("\n");


	 /*Tempo Comeca a ser contado*/
	 tempoInicial = time(NULL);

	 custo = limiteSuperior; /*Custo da solucao guia*/

	 custo -= lbound(solucaoGuia[dimension],INICIO);
	 custo -= lbound(solucaoGuia[anterior(dimension)],solucaoGuia[dimension]);

	 activeSet[solucaoGuia[dimension]] = FALSE;

	 for(nivel = (dimension - 2); nivel>=INICIO; --nivel){

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

                custo+=lbound(nodoAtual,branchingNode);

                ++qtdNodosExpandidos;
                dive(branchingNode);
                custo-=lbound(nodoAtual,branchingNode);



               // memcpy(solucaoGuiaDois, solucaoGuia, sizeof(solucaoGuia));
                if(diving_flag == true){

                   custo_aux = custo;
                   memcpy(aSetAux, activeSet, sizeof(activeSet));

                   jurema_de_juremas(proximo(nivel));

                   custo = custo_aux;
                   memcpy(activeSet, aSetAux, sizeof(activeSet));

                } //Se ele tiver encontrado uma solucao no diving, expanda-o na moda j_d_j
               // memcpy(solucaoGuia, solucaoGuiaDois, sizeof(solucaoGuiaDois));



            }//for
    }//for

   	/*Tempo para de ser computado*/
	tempoFinal = time(NULL);
	tempoNecessario = (double)(tempoFinal - tempoInicial)/MINUTO; /*Tempo Necessario em minutos*/
}


void jurema_de_juremas(int ultimo_nivel_busca){

	 register int i;
	 int nodoAtual;
	 int branchingNode;
	 register int contador = ZERO;


     //Manipulacao da matriz de ciclo. A priori o ciclo seria a solucao guia.

     //memcpy(ciclo,solucaoGuia,sizeof(solucaoGuia)); ?? tirou ou nao?
     for(int i = 1; i<=dimension; ++i){
            activeSet[i] = TRUE;
     }

	 printf("\nINICIANDO UMA JUREMA DE JUREMAS de %d a %d\n", dimension, ultimo_nivel_busca);

     printf("\nSolucao guia: ");
     for(int i = 1; i<=dimension+1; ++i){
        printf("%d ", solucaoGuia[i]);
     }
     puts("\n");

	 /*Tempo Comeca a ser contado*/

     custo = limiteSuperior;
	 custo -= lbound(solucaoGuia[dimension],INICIO);
	 custo -= lbound(solucaoGuia[anterior(dimension)],solucaoGuia[dimension]);

	 activeSet[solucaoGuia[dimension]] = FALSE;

	 for(nivel = (dimension - 2); nivel>=ultimo_nivel_busca; --nivel){

            memset( lbOrder , 0 , sizeof( lbOrder ) ) ;

            custo -= lbound(solucaoGuia[nivel],solucaoGuia[proximo(nivel)]);
			nodoAtual = solucaoGuia[nivel];

            contador = 0; /*Para lbOrder[x]*/

            for(int i =1; i<=dimension; ++i){ //MODIFICACAO Para evitar repeticoes de branches

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

	        for(int i = 0; i<contador; ++i){

                branchingNode = lbOrder[i];

                custo+=lbound(nodoAtual,branchingNode);
                ++qtdNodosExpandidos;
                ciclo[nivel] = nodoAtual;
                branch_jj(branchingNode);
                custo-=lbound(nodoAtual,branchingNode);


            }//for
    }//for

}
