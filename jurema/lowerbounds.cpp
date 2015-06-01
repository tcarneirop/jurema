#include "global.h"
#include "lowerbounds.h"
#include "upperbounds.h"
#include "assig.h"
#include "little_et_al.h"
#include <cstdlib>
#include <stdio.h>
#include <string.h>



int assigment[MAX];
int assignmentVolta[MAX];
int dualU[MAX], dualV[MAX];

extern int lambda;

int i, j;


int lowerBound(int metodo){

    switch(metodo){
        case NO_LB:
            printf("\n\nNO LOWER BOUND");
            return ZERO;
            break;
        case LITTLE_ET_AL:
            printf("\n\nLITTLE ET AL");
            return little_et_al();
            break;
        case HUNGARIAN_METHOD:
            printf("\n\nHUNGARIAN METHOD");
            return hungarian_method();
            break;
        default:
            printf("\n\nPARAMETROS DE LB INCORRETOS!!\n\n");
            exit(ONE);
    }
}

/*
    Hungarian method: chama o assignment em assig.h, calcula a matriz resultante
    e retorna o lowerbound.

        Matriz reduzida calculada no laco.

*/


int hungarian_method(){


    int lb = apc_michele(dimension,cost_matrix,assigment,assignmentVolta,dualU, dualV, 1);


	for(i = 0; i<dimension; ++i){
		for(j = 0; j<dimension; ++j){
			cost_m(i,j) = cost_m(i,j)-dualU[i]-dualV[j];
		}
	}

	return lb;
}


int grafo_esparso(int *solucaoGuia, int heuristica){

    int lambda = ZERO;
    int valor;
    int v_linha_max = ZERO;
    int ap_inicial;
    int ap_linha;
    int atsp_inicial;
    int atsp_linha;
    int cost_matrix_aux[MAX*MAX];
    int qtd_arestas_descartadas;
    int qtd_vezes = ZERO;
    bool flag = false;
    bool while_flag = false;

    puts("MATRIZ INICIAL: ");
    for(int i = 1; i<=dimension; ++i){
        for(int j  = 1; j<=dimension; ++j){
            printf("%d  ", custo(i,j));
        }

        puts("\n");
    }


    memcpy(cost_matrix_aux,cost_matrix,sizeof(cost_matrix));


    atsp_inicial = FITSP(0);
    ap_inicial = (int)(apc_michele(dimension,cost_matrix,assigment,assignmentVolta,dualU, dualV, 1));

    printf("\nATSP INICIAL: %d. \nAP INICIAL: %d.\n\n", atsp_inicial, ap_inicial);

    puts("\nSOLUCAO GUIA INICIAL: ");
    for(int i = 1; i<=dimension+1; ++i)
        printf("%d - ", solucaoGuia[i]);

    puts("\n");

    for(int i = 1; i<=dimension; ++i){
        if(custo(solucaoGuia[i],solucaoGuia[proximo(i)])>lambda)
            lambda = custo(solucaoGuia[i],solucaoGuia[proximo(i)]);
    }

    printf("\n\n\tLAMBDA ENCONTRADO: %d\n", lambda);



    do{
        ++qtd_vezes;
        printf("\n\n%d", qtd_vezes);
        if(flag == true){
            lambda = (2*lambda);
            puts("\nBOOOOL");
            memcpy(cost_matrix,cost_matrix_aux,sizeof(cost_matrix));
        }

        qtd_arestas_descartadas = ZERO;
        for(int i = 1; i<=dimension; ++i){
            for(int j = 1; j<=dimension; ++j){
                if(custo(i,j)>lambda){
                    ++qtd_arestas_descartadas;
                    custo(i,j) = INFINITO;
                }
            }
        }



        atsp_linha = FITSP(1);
        ap_linha = (int)(apc_michele(dimension,cost_matrix,assigment,assignmentVolta,dualU, dualV, 1));


        for(int i = 0; i<dimension; ++i){
            if(v_linha_max > dualV[i])
                v_linha_max > dualV[i];
        }



        for(int i = 0; i<dimension; ++i){

            valor = (lambda + 1 - dualU[i] - v_linha_max);

            if(!((atsp_linha-ap_inicial<=valor)&&(valor>=ZERO))){
                while_flag = true;
                break;
                //nao satisfeita --> dobrar o valor de lambda
            }

        }//deve checar para todo i

        flag = true;

    }while(!while_flag);


    puts("\nMATRIZ FINAL:\n ");
    for(int i = 1; i<=dimension; ++i){
        for(int j  = 1; j<=dimension; ++j){
            printf("%d  ", custo(i,j));
        }

        puts("\n");
    }
    printf("\nATSP FINAL: %d. \nAP FINAL: %d.", atsp_inicial, ap_inicial);
    printf("\n\tPROCEDIMENTO EXECUTADO %d VEZES.", qtd_vezes);
    printf("\n\tQUANTIDADE DE ARESTAS DESCARTADAS: %d, %.2f POR CENTO DO TOTAL DE ARESTAS.", qtd_arestas_descartadas, 100*((double)((double)qtd_arestas_descartadas/((double)((dimension*dimension)-dimension)))));

   /* ///COLOCAR AQUI O CALCULO DE MATRIZ RESULTANTE.
    for(int i = 0; i<dimension; ++i){
		for(int j = 0; j<dimension; ++j){
			cost_m(i,j) = cost_m(i,j)-dualU[i]-dualV[j];
		}
	}

    puts("\nMATRIZ REDUZIDA:\n ");
    for(int i = 1; i<=dimension; ++i){
        for(int j  = 1; j<=dimension; ++j){
            printf("%d  ", custo(i,j));
        }

        puts("\n");
    }*/


    //limiteSuperior = atsp_linha;
    limiteInferior = ap_linha;
	//return atsp_linha;

    return atsp_linha;
}
