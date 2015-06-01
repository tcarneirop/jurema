#include "global.h"
#include "little_et_al.h"



int little_et_al(){

	int menorValor = INFINITY;
	int max_constant_value = ZERO;
	int aux = ZERO;

	/*Laco responsavel por localizar e subtrair o menor elemento de cada linha*/
	for(int i = 1; i<=dimension; ++i){
            menorValor = INFINITY;

			for(int j = 1; j<=dimension; ++j){
  	          	if(custo(i,j)<menorValor){
                    menorValor = custo(i,j);
                }
			}
			max_constant_value += menorValor;


			/*Subtrair, de todos os elementos da linha i, o menor valor
			encontrado no laco passado. */
			for(int k = 1; k<=dimension; ++k){
                custo(i,k)-= menorValor;
			}
	}
	aux = max_constant_value;

	/*Laco responsavel por subtrair o menor valor das colunas*/
	for(int i = 1; i<=dimension; ++i){
        menorValor = INFINITY;
        for(int j = 1; j<=dimension; ++j){
            if(custo(j,i)<menorValor){
                menorValor = custo(j,i);
            }//if
        }

        max_constant_value += menorValor;

        /*Subtrair, de todos os elementos de Cij, o menor valor
        encontrado no laco passado. */
        for(int k = 1; k<=dimension; ++k){
            custo(k,i)-= menorValor;
        }//for

    }//for


    return max_constant_value;
}//
