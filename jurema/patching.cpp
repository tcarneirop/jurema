
#include <stdlib.h>
#include <stdio.h>
#include "assig.h"
#include "global.h"
#include "patching.h"
#include <string.h>
#include <iostream>
#include <queue>
#include <vector>
#include <algorithm>



using namespace std;

typedef struct ciclo{

    int qtd_nodos;
    int grafo[500];
    int qtd_arestas;
    int peso;

} ciclo_t;


struct compareCicles { //maior
  bool operator()(const ciclo_t *c1, const ciclo_t *c2) {
    return ((c1->qtd_nodos) < (c2->qtd_nodos));
  }
};

struct compareCicles_minor {
  bool operator()(const ciclo_t *c1, const ciclo_t *c2) {
    return ((c1->qtd_nodos) < (c2->qtd_nodos));
  }
}mySortingObjetc;


priority_queue<ciclo_t*, vector<ciclo_t*>, compareCicles> heap_de_ciclos; //para patching geral

/*karps (79) modified patching*/

vector<ciclo_t*> myvector;

vector<ciclo_t*>::iterator it;

/********************************************************/

ciclo_t* create_cicle(){

    ciclo_t* c = (ciclo_t*)malloc(sizeof(ciclo_t));

    return c;
}




int main_patching(int heuristica){

	N = dimension;

	int assigment[N];
	int assignmentVolta[N];
	int dualU[N], dualV[N];
	int p_ciclo;

    int contador = ZERO;
    int qtd_ciclos = ZERO;
    int valor_atual;
    int posicao = ZERO;

    int ciclo[MAX+1];
    int checados[MAX+1];

	int i, j;
	double assCost;

    ciclo_t *c; //ciclo que sera usado nas operacoes
    int ctd = 1;

	assCost = apc_michele(N,cost_matrix,assigment,assignmentVolta,dualU, dualV, 1);

//////////////////////////////////////////////////////////////////////////////////////////////////////
    for(i = 0; i<N; ++i)
        checados[i] = FALSE;

    while(contador<N){

        for(i = 0; i<N; ++i){
            if(checados[i]==FALSE){
                posicao = i;
                valor_atual = i;

                p_ciclo = 1;
                c = create_cicle();

                c->grafo[p_ciclo] = posicao;
                c->qtd_nodos++;
                c->qtd_nodos = ZERO;
                c->peso =  ZERO;

                break;
            }
        }

        while(assigment[posicao]!=valor_atual){
            checados[posicao] = TRUE;
            ++contador;
            posicao = assigment[posicao];

            ++p_ciclo;
            c->grafo[p_ciclo] = posicao;
            c->peso+= cost(c->grafo[anterior(p_ciclo)],c->grafo[p_ciclo]);
            c->qtd_nodos++;
        }

        ++qtd_ciclos;
        ++contador;
        checados[posicao] = TRUE;

        ++p_ciclo;


        c->grafo[p_ciclo] = c->grafo[1];

        c->peso += cost_p(c->grafo[anterior(p_ciclo)],c->grafo[1]);
        c->qtd_nodos++;
        c->qtd_arestas = c->qtd_nodos;

        /*inserir arestas e nodos*/
        heap_de_ciclos.push(c); //general patching procedure
        myvector.push_back(c);

    }

    
    if(myvector.size()==1){
        printf("\n\nAssignment e' o otimo de valor %d.\n\n", (int)assCost);
		puts("\tTOUR: ");
		for(int i = 1; i<=c->qtd_nodos;++i)
			printf("%d - ", c->grafo[i]+1);
		printf("1\n");
		exit(0);
        return ZERO;

    }

	switch(heuristica){
		case _GENERAL_PATCHING_:
			return patching(solucaoGuia);
			break;
		case _KARPS_MODIFIED_PATCHING_:
			return karps_modified_patching(solucaoGuia);
			break;
		default:
			printf("\n\nERRO DE PARAMETROS DE UPPER BOUNDING.\n\n");
			exit(1);
	}

    free(c);
   
}

int karps_modified_patching(int *solucaoGuia){

    printf("\n\n###### KARP'S 79 MODIFIED PATCHING PROCEDURE ######\n\n");

   // if(myvector.size()==1){
      //  printf("\n\nAssignment e' o otimo.\n\n");
		//exit(0);
      //  return ZERO;

   // }

    ciclo_t *c1,*c2, *novo_ciclo;

    int melhor_ciclo;

    int menor_soma = INFINITO;

    int melhor_i, melhor_j, melhor_k, melhor_l;

    int posicao_melhor_i, posicao_melhor_j, posicao_melhor_k, posicao_melhor_l;

    int posicao_c1, posicao_c2;

    int posicao_novo_ciclo = ZERO;

    int soma = ZERO;
    int soma1;
    int soma2;

    int posicao_ciclo_aux;
    int posicao_i;

    bool flag = false;

    int posicao_solucao_guia = 0;
    int peso_solucao_guia = 0;

    int x,j,l;


    printf("TAMANHO DO VECTOR: %d", myvector.size());

    for(int i = 0; i<N; ++i) //inicializando matriz de arestas usadas
        for(int j = 0; j<N;++j)
            usados(i,j) = FALSE;


    sort(myvector.begin(), myvector.end(), mySortingObjetc); //smallest cicle at mv.front()

    c1 = myvector.front();

    myvector.erase(myvector.begin()); //removing smallest from myvector




    //patching procedure
    while(myvector.size()>0){ //



        if(flag == true)
            c1 = novo_ciclo;

        for(x = 0; x<myvector.size(); ++x){

            menor_soma = INFINITO;

            c2 = myvector[x];              //@ATENCAO: estou botando qtd_nodos no lugar de qtd-1, voltar ao normal
                                            //APARENTEMENTE ERA O ERRO!!!
            for(int i = 1; i<=(c1->qtd_nodos);++i){ //@POSSIVEL ERRO: nao seria qtd nodos?!!!?!?

                j = proximo(i);

                if(usados(i,j) == TRUE) //se a aresta jah tiver participado do patching, desconsiderar
                    continue;

                for(int k = 1; k<=(c2->qtd_nodos);++k){

                    l = proximo(k);

                    if(usados(k,l) == TRUE) //se a aresta jah tiver participado do patching, desconsiderar
                        continue;

                    soma1 = cost_p(c1->grafo[i],c2->grafo[l]) + cost_p(c2->grafo[k],c1->grafo[j]);

                    soma2 = (cost_p(c1->grafo[i],c1->grafo[j] )) + (cost(c2->grafo[k],c2->grafo[l]));

                    soma = soma1 - soma2;


                    if((soma)<menor_soma){


                        menor_soma = soma;

                        melhor_i = c1->grafo[i];
                        posicao_melhor_i = i;

                        melhor_j = c1->grafo[j];
                        posicao_melhor_j = j;

                        melhor_k = c2->grafo[k];
                        posicao_melhor_k = k;

                        melhor_l = c2->grafo[l];
                        posicao_melhor_l = l;

                        melhor_ciclo = x;

                    }//if
                }

            }//for

        }//for


       // printf("\n\nMelhor ciclo: %d", x);

        myvector.erase(myvector.begin()+x-1); //tirando o melhor ciclo do vector
        flag = true; //


      /* printf("\n\n\t POSICAO Melhor i: %d. Melhor i: %d",posicao_melhor_i,c1->grafo[posicao_melhor_i]+1);
       printf("\n\n\t POSICAO Melhor j: %d. Melhor j: %d",posicao_melhor_j,c1->grafo[posicao_melhor_j]+1);
       printf("\n\n\t POSICAO Melhor k: %d. Melhor k: %d",posicao_melhor_k,c2->grafo[posicao_melhor_k]+1);
       printf("\n\n\t POSICAO Melhor l: %d. Melhor l: %d\n",posicao_melhor_l,c2->grafo[posicao_melhor_l]+1);


        printf("\n\tSubciclo c1: ");

        for(int i = 1; i<=(c1->qtd_nodos+1); ++i)
            printf("%d -> ",(c1->grafo[i])+1);


        printf("\n\tSubciclo c2: ");

        for(int i = 1; i<=(c2->qtd_nodos+1); ++i)
            printf("%d -> ",(c2->grafo[i])+1); */

//ligando os ciclos
        posicao_novo_ciclo = ZERO;
        novo_ciclo = create_cicle();
        novo_ciclo->qtd_nodos = (c1->qtd_nodos) + (c2->qtd_nodos);
        novo_ciclo->qtd_arestas = novo_ciclo->qtd_nodos;


        //fase 1
        for(int a = 1; a<=(posicao_melhor_i); ++a){
            ++posicao_novo_ciclo;
            novo_ciclo->grafo[a] = c1->grafo[a];
        }

        //resultado f1
      /*  puts("\nFASE 1");
        for(int i = 1; i<=novo_ciclo->qtd_nodos; ++i){
            printf("%d - ", novo_ciclo->grafo[i]+1);
        }
        puts("\n");*/


        //fase2
        for(int b = posicao_melhor_l; b<=c2->qtd_nodos; ++b){//aqui?
            ++posicao_novo_ciclo;
            novo_ciclo->grafo[posicao_novo_ciclo] = c2->grafo[b];

        }

        for(int b = 1; b<=posicao_melhor_k; ++b){//aqui?
            ++posicao_novo_ciclo;
            novo_ciclo->grafo[posicao_novo_ciclo] = c2->grafo[b];

        }

        //resultado f2
        /*puts("\nFASE 2");
        for(int i = 1; i<=novo_ciclo->qtd_nodos; ++i){
            printf("%d - ", novo_ciclo->grafo[i]+1);
        }
        puts("\n");*/


        //f3
        for(int a = posicao_melhor_j; a<=c1->qtd_nodos+1; ++a){
            ++posicao_novo_ciclo;
            novo_ciclo->grafo[posicao_novo_ciclo] = c1->grafo[a];

        }

        /*//resultado f3
        puts("\nFASE 3");
        for(int i = 1; i<=novo_ciclo->qtd_nodos+1; ++i){
            printf("%d - ", novo_ciclo->grafo[i]+1);
        }
        puts("\n");*/


    }//while


    //reorganizacao de ciclo
    if((novo_ciclo->grafo[1])!=0){//se precisar reorganizar o ciclo

	    for(int i = 1; i<=(novo_ciclo->qtd_nodos-1); ++i){

            if((novo_ciclo->grafo[i]) == 0){
                posicao_i = i;
                break;
            }

        }

        for(int i = posicao_i; i<=(novo_ciclo->qtd_nodos); ++i){

            ++posicao_solucao_guia;
            solucaoGuia[posicao_solucao_guia] = (novo_ciclo->grafo[i]);
        }


        for(int i = 1; i<posicao_i; ++i){
            ++posicao_solucao_guia;
            solucaoGuia[posicao_solucao_guia] = (novo_ciclo->grafo[i]);
        }

    }//if
    else{

        memcpy(solucaoGuia, novo_ciclo->grafo, sizeof(novo_ciclo->grafo));

    }
    //if fim reorganizacao

    //imprimir e calcular peso da SG: 
   // puts("\nSG: \n");
    for(int i = 1; i<=(novo_ciclo->qtd_nodos)+1; ++i){
        if(i == novo_ciclo->qtd_nodos+1){
   			//printf("%d ->", solucaoGuia[i]);
            continue;
        }
        else{
				//printf("\n\tvou ligar %d -> %d: %d\n", solucaoGuia[i], solucaoGuia[i+1],cost_p(solucaoGuia[i],solucaoGuia[i+1])); 
            	peso_solucao_guia+=cost_p(solucaoGuia[i],solucaoGuia[i+1]);
			}
       // printf("%d -> ", (solucaoGuia[i]));

    }//for

	
   // printf("\n\tPeso SG: %d\n\n", peso_solucao_guia);

	for(int i = 1; i<=(novo_ciclo->qtd_nodos)+1; ++i)
			++solucaoGuia[i];

    return peso_solucao_guia;

}



int patching(int *solucaoGuia){

    printf("\n\n###### GENERAL PATCHING PROCEDURE ######\n\n");
    //if(heap_de_ciclos.size()==1){
       // printf("\n\nAssignment e' o otimo.\n\n");
		//exit(0);
       // return ZERO;
    //}

    ciclo_t *c1,*c2;

    ciclo_t *novo_ciclo;


    int i,j,k,l,menor_soma;

    menor_soma = INFINITO;
    int melhor_i, melhor_j, melhor_k, melhor_l;

    int posicao_melhor_i, posicao_melhor_j, posicao_melhor_k, posicao_melhor_l;

    int posicao_c1, posicao_c2;

    int posicao_novo_ciclo = ZERO;
    int soma = ZERO;

    int counter = 0;
    int soma1;
    int soma2;

    int posicao_ciclo_aux;
    int posicao_i;

    bool flag = false;

    int posicao_solucao_guia = 0;

    int peso_solucao_guia = 0;

    //@ERRO: Acho que tem erro na qtd de arestas

    while(heap_de_ciclos.size()>1){ //quando a solucao guia nao estiver formada



        c1 = heap_de_ciclos.top();
        heap_de_ciclos.pop();
        c2 = heap_de_ciclos.top();
        heap_de_ciclos.pop();


        menor_soma = INFINITO;


        for(int i = 1; i<=(c1->qtd_nodos);++i){ //@DUVIDA: eh qtd_nodos-1 mesmo? TREI NA FUNCAO DO KARP, TIREI NESSA TB


            for(int k = 1; k<=(c2->qtd_nodos);++k){
                ++counter;

                j = proximo(i);


                l = proximo(k);

                soma1 = cost_p(c1->grafo[i],c2->grafo[l]) + cost_p(c2->grafo[k],c1->grafo[j]);

                soma2 = (cost_p(c1->grafo[i],c1->grafo[j] )) + (cost_p(c2->grafo[k],c2->grafo[l]));

                soma = soma1 - soma2;


                if((soma)<menor_soma){


                    menor_soma = soma;

                    melhor_i = c1->grafo[i];
                    posicao_melhor_i = i;

                    melhor_j = c1->grafo[j];
                    posicao_melhor_j = j;

                    melhor_k = c2->grafo[k];
                    posicao_melhor_k = k;

                    melhor_l = c2->grafo[l];
                    posicao_melhor_l = l;

                }
            }

        }



        /*printf("\n\n\t POSICAO Melhor i: %d. Melhor i: %d",posicao_melhor_i,c1->grafo[posicao_melhor_i]+1);
        printf("\n\n\t POSICAO Melhor j: %d. Melhor j: %d",posicao_melhor_j,c1->grafo[posicao_melhor_j]+1);
        printf("\n\n\t POSICAO Melhor k: %d. Melhor k: %d",posicao_melhor_k,c2->grafo[posicao_melhor_k]+1);
        printf("\n\n\t POSICAO Melhor l: %d. Melhor l: %d\n",posicao_melhor_l,c2->grafo[posicao_melhor_l]+1);


        printf("\n\tSubciclo c1: ");

        for(int i = 1; i<=(c1->qtd_nodos+1); ++i)
            printf("%d -> ",(c1->grafo[i])+1);


        printf("\n\tSubciclo c2: ");

        for(int i = 1; i<=(c2->qtd_nodos+1); ++i)
            printf("%d -> ",(c2->grafo[i])+1);

*/

//ligando os ciclos
        posicao_novo_ciclo = ZERO;
        novo_ciclo = create_cicle();
		novo_ciclo->qtd_nodos = (c1->qtd_nodos) + (c2->qtd_nodos);
    	novo_ciclo->qtd_arestas = novo_ciclo->qtd_nodos;

        //fase 1
        for(int a = 1; a<=(posicao_melhor_i); ++a){
            ++posicao_novo_ciclo;
            novo_ciclo->grafo[a] = c1->grafo[a];
        }

        /*//resultado f1
        puts("\nFASE 1");
        for(int i = 1; i<=novo_ciclo->qtd_nodos; ++i){
            printf("%d - ", novo_ciclo->grafo[i]+1);
        }
        puts("\n");

        */
        //fase2
        for(int b = posicao_melhor_l; b<=c2->qtd_nodos; ++b){//aqui?
            ++posicao_novo_ciclo;
            novo_ciclo->grafo[posicao_novo_ciclo] = c2->grafo[b];

        }

        for(int b = 1; b<=posicao_melhor_k; ++b){//aqui?
            ++posicao_novo_ciclo;
            novo_ciclo->grafo[posicao_novo_ciclo] = c2->grafo[b];

        }

        /*//resultado f2
        puts("\nFASE 2");
        for(int i = 1; i<=novo_ciclo->qtd_nodos; ++i){
            printf("%d - ", novo_ciclo->grafo[i]+1);
        }
        puts("\n");
        */

        //f3
        for(int a = posicao_melhor_j; a<=c1->qtd_nodos+1; ++a){
            ++posicao_novo_ciclo;
            novo_ciclo->grafo[posicao_novo_ciclo] = c1->grafo[a];

        }

        /*//resultado f3
        puts("\nFASE 3");
        for(int i = 1; i<=novo_ciclo->qtd_nodos+1; ++i){
            printf("%d - ", novo_ciclo->grafo[i]+1);
        }
        puts("\n");
        */

        heap_de_ciclos.push(novo_ciclo);

    } //while
    //fim do patching

	//printf("\n\tQTD NODOS ANTES DA REORGANIZACAO: %d", novo_ciclo->qtd_nodos);
    //reorganizacao de ciclo
    if((novo_ciclo->grafo[1])!=0){//se precisar reorganizar o ciclo
        for(int i = 1; i<=(novo_ciclo->qtd_nodos-1); ++i){

            if((novo_ciclo->grafo[i]) == 0){
                posicao_i = i;
                break;
            }

        }


        for(int i = posicao_i; i<=(novo_ciclo->qtd_nodos); ++i){

            ++posicao_solucao_guia;
            solucaoGuia[posicao_solucao_guia] = novo_ciclo->grafo[i];
        }


        for(int i = 1; i<posicao_i; ++i){
            ++posicao_solucao_guia;
            solucaoGuia[posicao_solucao_guia] = novo_ciclo->grafo[i];
        }

    }//if
    else{

        memcpy(solucaoGuia, novo_ciclo->grafo, sizeof(novo_ciclo->grafo));

    }
    //if fim reorganizacao

//	puts("\nSG: \n");

	//printf("\n\tQTD NODOS: %d", novo_ciclo->qtd_nodos);
    for(int i = 1; i<=(novo_ciclo->qtd_nodos)+1; ++i){
        if(i == novo_ciclo->qtd_nodos+1){
   			//printf("%d ->", solucaoGuia[i]);
            continue;
        }
        else{
            	peso_solucao_guia+=cost_p(solucaoGuia[i],solucaoGuia[i+1]);
			}
        //printf("%d -> ", (solucaoGuia[i]));

    }//for

	
    //printf("\n\tPeso SG: %d\n\n", peso_solucao_guia);

	for(int i = 1; i<=(novo_ciclo->qtd_nodos)+1; ++i)
			++solucaoGuia[i];

	 return peso_solucao_guia;
}




