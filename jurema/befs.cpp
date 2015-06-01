#include <iostream>
#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <list>
#include <queue>
#include <ctime>

#include "global.h"
#include "befs.h"
#include "aux.h"

using namespace std;

class Node{
	//@TODO:\
		sei que que as variaveis nao devem ser public. dps mudarei

    public:
        int flag[MAX+1];
        int nivel;
        int custo;
        int indice;
        Node(int cost, int index, int* flagPai,int _nivel);

};

Node::Node(int cost, int index, int*flagPai,int _nivel){

    nivel = _nivel+1;
    custo = cost;
    indice = index;

    memcpy(flag, flagPai, sizeof(flag));

    if(nivel <= dimension) //se nao for uma solucao
        flag[indice] = TRUE;

}


struct compareNodes { //maior
  bool operator()(const Node *n1, const Node *n2) {
    return ((n1->custo) > (n2->custo));
  }
};


int best_first_search(){

    printf("\n\n##################BEST-FIRTS SEARCH INICIADA#######################\n\n");
    priority_queue<Node*, vector<Node*>, compareNodes> active_set_befs; //para o bnb
    Node* rootNode;
    Node* branching_node;
    register int bnode_cost;
    register int i;
    register int bnode_index;
    register int better_solution;
    register int bnode_nivel;
    memset( activeSet , ZERO , sizeof( activeSet ) ) ; //inicializacao do vetor de flags.

	activeSet[INICIO]=TRUE;

    rootNode = new Node(limiteInferior, INICIO,activeSet,ZERO);


    if(rootNode->custo>limiteSuperior)
        return _ERRO_;

    active_set_befs.push(rootNode); //nodo inicial colocado no conjunto ativo

    while(!active_set_befs.empty()){ /*Busca se dara como em papadimitriou e steinglitz (1998)*/

        branching_node = active_set_befs.top();


        bnode_cost = branching_node->custo;
        bnode_index = branching_node->indice;
        bnode_nivel = branching_node->nivel;



        //printf("\n\nNODO DA VEZ: indice: %d, custo:%d , nivel: %d",bnode_index,bnode_cost,bnode_nivel);

      //  printf("\n\nANTES DO POP:\n");
       // for(int k = 1; k<=dimension;++k)
       //     printf("- %d -", branching_node->flag[k]);

        active_set_befs.pop(); //remove esse nodo

       // printf("\n\nDEPOIS DO POP:\n ");
        //for(int k = 1; k<=dimension;++k)
          // printf("- %d -", branching_node->flag[k]);


        if(bnode_nivel == (dimension+1)){
            ++qtdFolhas;
            printf("\nSolucao de CUSTO %d, INDICE do nodo %d, NIVEL %d.\n", bnode_cost, bnode_index, bnode_nivel);
            limiteSuperior = bnode_cost;
            return SUCESSO;
        }
        else
            if(bnode_nivel==dimension){
                    if(bnode_cost+cost(bnode_index,INICIO)<limiteSuperior){
                        active_set_befs.push(new Node(bnode_cost+cost(bnode_index,INICIO), INICIO,branching_node->flag,bnode_nivel));
                    }
            }
            else
                for(i = 1; i<=dimension; ++i){
                    if(bnode_cost+cost(bnode_index,i)<limiteSuperior && branching_node->flag[i]==FALSE){
                        active_set_befs.push(new Node(bnode_cost+cost(bnode_index,i), i,branching_node->flag,bnode_nivel));
                        ++qtdNodosExpandidos;
                }//fi
            }//rof
    }//while

    return -1;
}
