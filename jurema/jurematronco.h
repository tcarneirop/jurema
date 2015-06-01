#ifndef JUREMA_TRONCO_H
#define JUREMA_TRONCO_H

#ifndef ERRO
#define ERRO -1
#endif

#ifndef SUCESSO
#define SUCESSO 1
#endif

extern int lbVector[MAX*MAX];
extern int lbOrder[MAX+1];

void jurema_tronco();
void jurema_de_juremas(int ultimo_nivel_busca);
//int  dive(int nivel, int peso, int raiz, int *ciclo, int *activeSet, int *solucaoGuia);
#endif
