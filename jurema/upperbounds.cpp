#include <stdio.h>
#include <stdlib.h>
#include <string.h>



#include "aux.h"
#include "global.h"
#include "upperbounds.h"
#include "patching.h"



/******************************************************************************
*                                 HEURÍSTICAS                                  *
*******************************************************************************/
/*
  FITSP
  return peso da solucao guia.
*/

int FITSP(int valor){

	int auxSolucaoGuia[MAX+1];
	int vizinhoMaisDistante = INFINITO;
	int custoVizinhoMaisDistante = MENOSINFINITO;
	int pesoFITSP = ZERO;

	int vizinhoMelhorSelecao = INFINITO;
	int custoMelhorSelecao = INFINITO;
	int custoSelecao = INFINITO;
	int melhor_i = ZERO;
	int melhor_j = ZERO;

	int pesoATSP = ZERO;

	int posicaoUltimoVertice = 1; /*Este valor guarda a posicao do ultimo vertice da tour, ou seja, o que leva a tour a origem.*/

	/*Algumas inicializacoes*/
	memset(solucaoGuia, ZERO, sizeof(solucaoGuia));
	memset(auxSolucaoGuia, ZERO, sizeof(auxSolucaoGuia));
	memset(activeSet, FALSE, sizeof(activeSet));

	puts("\n\nHEURISTICA: FITSP\n");



	/*Passo 1: comece com um subgrafo contendo apenas um vertice inicial.*/
	solucaoGuia[INICIO]= INICIO;
	activeSet[INICIO] = TRUE;

	/*Passo 2: Ache um vertice k tal que seja o mais distante do vertice inicial e forme o ciclio i-k-i*/
	for( int k = 1; k<=dimension; ++k){
		if( custo(INICIO,k) > custoVizinhoMaisDistante && activeSet[k]==FALSE && custo(k,INICIO)<INFINITO && custo(INICIO,k)<INFINITO){
			vizinhoMaisDistante = k;
			custoVizinhoMaisDistante = custo(INICIO,k);
		}
	}



	/*Formando a tour i-k-i:*/
	activeSet[vizinhoMaisDistante]=TRUE;
	solucaoGuia[2] = vizinhoMaisDistante;
	solucaoGuia[3] = INICIO;
	++posicaoUltimoVertice;



	memcpy(auxSolucaoGuia, solucaoGuia, sizeof(solucaoGuia)); /*Atualizando a solucao guia auxiliar*/


	/*Tour i-k-i formada*/

	while( posicaoUltimoVertice <dimension){ /*Enquando um ciclio Hamiltoniano nao for formado*/

	       vizinhoMaisDistante = INFINITO;
	       custoVizinhoMaisDistante = MENOSINFINITO;
	       custoMelhorSelecao = INFINITO;


 		   /* Passo 3: selecao. Encontre k tal quer seja o mais distante de qualquer ponto da tour.*/

 		   for( int i = 1; i <= posicaoUltimoVertice; ++i ){
   		   		for( int j = 1; j <= dimension; ++j ){

					 if( custo(solucaoGuia[i],j) > custoVizinhoMaisDistante && activeSet[j] == FALSE){
			 	     	 vizinhoMaisDistante = j;
			 	     	 custoVizinhoMaisDistante = custo(solucaoGuia[i],j);
				     }
			    }
   		   }//for

		   /*Passo 4: insercao. Ache o arco(i,j) dentro da tour, tal que c(i,k) + custo(k,j) - custo(i,j) seja minimo*/
		   for( int i = 1, j=i+1; i<=posicaoUltimoVertice; ++i){

				custoSelecao = ( custo(solucaoGuia[i], vizinhoMaisDistante) + custo(vizinhoMaisDistante, solucaoGuia[j]) - custo(solucaoGuia[i],solucaoGuia[j]) );

				if( custoSelecao < custoMelhorSelecao ){

					vizinhoMelhorSelecao = vizinhoMaisDistante;
					custoMelhorSelecao = custoSelecao;
					melhor_i = i;
					melhor_j = j;

				}

				++j;
           }//for

		   /*Atualizar a solucao guia:*/
   	       solucaoGuia[melhor_j] = vizinhoMelhorSelecao;


		   for( int a = melhor_j+1; a<=posicaoUltimoVertice+2; ++a){

		   		solucaoGuia[a]= auxSolucaoGuia[a-1];
	 	   }
	 	   memcpy(auxSolucaoGuia,solucaoGuia,sizeof(solucaoGuia));

		   /*Atualizar Valores*/
		   ++posicaoUltimoVertice;
		   activeSet[vizinhoMaisDistante] = TRUE;

    }

    for(int i = 1; i<=dimension; ++i){
            pesoATSP += custo(solucaoGuia[i],solucaoGuia[proximo(i)]);
    }
	return pesoATSP;
}//fitsp





int tourImprovement(){
    int contador = 0;

    while(twoOpt()!=ERRO){
        ++contador;
    }

    if(contador>0)
        return contador;
    else
        return ERRO;
}

int twoOpt(){

    int i1, j1, i2, j2;
    int melhorValor = limiteSuperior;
    int indice_melhor_i1, indice_melhor_i2, indice_melhor_j1, indice_melhor_j2;
    int valorSolucao;
    int aux;

    for( i1 = INICIO; i1<=(dimension -2); ++i1 ){
        for( j1 = INICIO + 2; j1<=dimension; ++j1 ){

            i2 = proximo(i1);
            j2 = proximo(j1);

            valorSolucao = limiteSuperior + custo(solucaoGuia[i1],solucaoGuia[j1])
                                              + custo(solucaoGuia[j1], solucaoGuia[proximo(i2)])
                                              + custo(solucaoGuia[anterior(j1)],solucaoGuia[i2])
                                              + custo(solucaoGuia[i2],solucaoGuia[j2])
                                              - custo(solucaoGuia[i1],solucaoGuia[i2])
                                              - custo(solucaoGuia[i2],solucaoGuia[proximo(i2)])
                                              - custo(solucaoGuia[anterior(j1)],solucaoGuia[j1])
                                              - custo(solucaoGuia[j1],solucaoGuia[j2]);
            if( valorSolucao < melhorValor){

                melhorValor = valorSolucao;
                indice_melhor_i1 = i1;
                indice_melhor_i2 = i2;
                indice_melhor_j1 = j1;
                indice_melhor_j2 = j2;

            }

        }//for
    }//for

    if( melhorValor < limiteSuperior){
        limiteSuperior = melhorValor;
        aux = solucaoGuia[indice_melhor_i2];
        solucaoGuia[indice_melhor_i2] = solucaoGuia[indice_melhor_j1];
        solucaoGuia[indice_melhor_j1] = aux;

        return SUCESSO;
    }
    else
        return ERRO;
}



int ub(int heuristica){

	switch(heuristica){
		case _FITSP_:
			return FITSP(0);
			break;
		case _GENERAL_PATCHING_:
			return main_patching(_GENERAL_PATCHING_);
			break;
		case _KARPS_MODIFIED_PATCHING_ :
			return main_patching(_KARPS_MODIFIED_PATCHING_ );
			break;
		default:
			printf("\n\nERRO DE PARAMETROS DE UPPER BOUNDING.\n\n");
			exit(1);
	}

}

int upperBound(){

    limiteSuperior = FITSP(0);
    tourImprovement();
    return limiteSuperior;
}

