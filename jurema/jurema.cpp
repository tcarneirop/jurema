#include <iostream>
#include <stdio.h>
#include <string.h>
#include <ctime>
#include <cstdlib>

#include "global.h"
#include "aux.h"
#include "upperbounds.h"
#include "lowerbounds.h"
#include "juremasearch.h"
#include "jurematronco.h"
#include "dfs_bnb.h"
#include "buscas_omp.h"
#include "befs.h"

//#include "jurematronco.h"



using namespace std;



#define   JUREMA        "-j"
#define   DFSBNB        "-d"
#define   SGUIA         "-s"
#define   JUREMADUPLO   "-jd"
#define   JUREMACORTE   "-jc"
#define   JUREMATRONCO  "-jt"
#define   JUREMAPARARELO "-jp"
#define   DFSPARALELO    "-dp"
#define   BESTFSEARCH    "-be"


#define NO_LB 1
#define HUNGARIAN_METHOD 2
#define LITTLE_ET_AL 3

#define NL_LB_CHAR "-nlb"
#define LITTLE_ET_AL_CHAR "-lea"
#define HUNGUARIAN_METHOD_CHAR "-hm"

#define CORTE (int)(dimension/2)
/*************************************************************************************************
*                                     VARIAVELS GLOBAIS
*************************************************************************************************/

/*Matriz de adjacencias.*/
int cost_matrix[MAX*MAX];
int original_matrix[MAX*MAX];
int zeroes_matrix[MAX*MAX];
int lbVector[MAX*MAX]; /*Vetor utilizado para encontar o limite inferior*/
int lbOrder[MAX+1]; /*Vetor que guardara os indices de acordo com a ordem crescente de seus limites inferiores*/

/* No vetor activeSet, se activeSet[X]==TRUE, significa que X já foi expandido
e nao pertence ao activeSet; */
int activeSet[MAX+1];
int ciclo[MAX+1];
int solucaoGuia[MAX+1]; /*Vetor que guardara a solucao guia utilizada pelo metodo Jurema.*/
int solucaoGuiaDois[MAX+1];
//int solucaoGuiaDois[MAX+1];
/*
  Variaveis globais utilizadas pelas funcoes que compoe o metodo Branch-n-Bound.
*/
int dimension = ZERO; /*Tamanho do ciclo hamiltoniano*/
int custo = ZERO;       /*Custo atual da rota*/
int limiteSuperior = INFINITO;
int limiteSuperiorDois = INFINITO;
int limiteInferior = INFINITO ;
int nivel = ZERO; /*Nivel da arvore no qual a busca se encontra*/
int qtdFolhas = ZERO;
unsigned long long int qtdNodosExpandidos = ZERO; /*Qtd de nodos expandidos pelo bnb*/

bool diving_flag;

//USADO NO PATCHING
int N;
int usados[MAX*MAX];

/*
  Variaveis utilizadas no calculo do tempo gasto na busca pelo otimo.
*/
clock_t tempoInicial;
clock_t tempoFinal;
clock_t tempo;
int a = CLOCKS_PER_SEC/1000;
double tempoNecessario;




int main(int argc, char *argv[]){


	memset( cost_matrix , INFINITO, sizeof( cost_matrix ) );


    //@TODO: Ajeitar isso e botar um switch case.
    if(argc == 2){

        //Atividade comum a qualquer uma das
        read();
        memcpy(original_matrix,cost_matrix,sizeof(cost_matrix));

		//limiteSuperior = ub(_KARPS_MODIFIED_PATCHING_);
		//printf("\n\n\t\n UB KARPS:%d\n\t",ub(_KARPS_MODIFIED_PATCHING_));
		limiteSuperior = ub(_GENERAL_PATCHING_);

        limiteInferior = lowerBound(NO_LB); //pode ser feito so uma vez, neh?

        printf("\n\n\n#############################################\n\n\n");
        printf("\nQuantidade de vertices: %d", dimension);
        printf("\nLimite superior inicial: %d.\n", limiteSuperior);
        printf("\nLimite inferior inicial: %d. \n", limiteInferior);
		printf("\n\n\n#############################################\n\n\n");
        if( !strcmp(argv[1],JUREMA) ){
            jurema(INICIO);
        }
        if(!strcmp(argv[1],DFSBNB)){
            dfs();
        }
        if(!strcmp(argv[1],BESTFSEARCH)){
            best_first_search();
        }
        if(!strcmp(argv[1],JUREMAPARARELO)){
            jurema_paralela();
        }//
		if(!strcmp(argv[1],DFSPARALELO)){
            dfs_paralelo();
        }//
    }
    else{
        if(argc == 3){ //de 0-2. 0: nome, 1: buscap, 2: solucao retornada.

            read_v2();
            memcpy(original_matrix,cost_matrix,sizeof(cost_matrix));
            limiteSuperior = calcularPesoSolGuia();
            limiteInferior = lowerBound(HUNGARIAN_METHOD);

            printf("\n\n\n#############################################\n\n\n");
            printf("\nQuantidade de vertices: %d", dimension);
            printf("\nLimite superior inicial: %d.\n", limiteSuperior);
            printf("\nLimite inferior inicial: %d. \n", limiteInferior);

            if( !strcmp(argv[2],JUREMA)){
                jurema(INICIO);
            }
            if(!strcmp(argv[2],DFSBNB)){
                dfs();
             }
            if(!strcmp(argv[1],BESTFSEARCH)){
                best_first_search();
            }
            if(!strcmp(argv[2],JUREMAPARARELO)){
                jurema_paralela();
            }
            if(!strcmp(argv[2],DFSPARALELO)){
                dfs_paralelo();
            }
        }//if
	else{
              printf("\n\nATENCAO. Parametros incorretos.\nLeia a documentacao para maiores detalhes.\n\n");
              exit(1);
            }
    }//else


	printf("\n\n\n\tLimite Superior Final (Otimo): %d\n",limiteSuperior);
	printf("\tTEMPO NECESSARIO(ms): %d", (int)(tempoNecessario/a));
	printf("\n\tTamanho da arvore: %llu\n", qtdNodosExpandidos);

	return 0;
}

