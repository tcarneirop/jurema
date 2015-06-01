#include "global.h"
#include <string.h>
#include <stdio.h>
#include "aux.h"
#include "upperbounds.h"

int grafo_esparso(int *solucaoGuia, int heuristica, int b){

    int lambda = ZERO;
    int v_linha_max = ZERO;
    int ap_inicial;
    int ap_linha;
    int atsp_inicial;
    int atsp_linha;
    int cost_matrix_aux[MAX*MAX];
    bool flag = false;

    int dU[MAX], dV[MAX], assign[MAX], assignVolta[MAX];

    for(int i = 1; i<=dimension; ++i){
        for(int j  = 1; j<=dimension; ++j){
            printf("%d", custo(i,j));
        }

        puts("\n");
    }


    memcpy(cost_matrix_aux,cost_matrix,sizeof(cost_matrix));
    atsp_inicial = FITSP(1);
  //  ap_inicial = (int)(apc_michele(dimension,cost_matrix,assign,assignVolta,dU, dV, 1));

    for(int i = 1; i<=dimension; ++i){
        if(solucaoGuia[i]>lambda)
            lambda = solucaoGuia[i];
    }


    do{
        if(flag == true){
            lambda = (int)(1.5*lambda);
            memcpy(cost_matrix,cost_matrix_aux,sizeof(cost_matrix));
        }

        for(int i = 1; i<=dimension; ++i){
            for(int j = 1; j<=dimension; ++j){
                if(custo(i,j)>lambda){
                    custo(i,j) = INFINITO;
                }
            }
        }

        atsp_linha = FITSP(1);
      //  ap_linha = (int)(apc_michele(dimension,cost_matrix,assign,assignVolta,dU, dV, 1));

        for(int i = 0; i<dimension; ++i){
            if(v_linha_max > dV[i])
                v_linha_max > dV[i];
        }



    }while(!((atsp_linha-ap_inicial <= lambda + 1 - dU[1] - v_linha_max)&&(lambda + 1 - dU[1] - v_linha_max >= ZERO)));


    return ZERO;
}
