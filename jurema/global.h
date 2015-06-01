#ifndef __GLOBAL__H
#define __GLOBAL__H


#ifndef MAX
    #define MAX 600
#endif

#ifndef TRUE
    #define TRUE 1
#endif

#ifndef FALSE
    #define FALSE 0
#endif

#ifndef ONE
    #define ONE 1
#endif

#ifndef ZERO
    #define ZERO 0
#endif


#define INFINITY 999999999


#ifndef INICIO
    #define INICIO 1
#endif


#define INFINITO 999999999



#ifndef custo
	#define custo(x,y) cost_matrix[(dimension)*(x-1)+(y-1)]
#endif

#ifndef cost
	#define cost(x,y) cost_matrix[(dimension)*(x-1)+(y-1)]
#endif

#ifndef lbound
	#define lbound(x,y) cost_matrix[(dimension)*(x-1)+(y-1)]
#endif

#ifndef original_matrix
	#define original_matrix(x,y) original_matrix[(dimension)*(x-1)+(y-1)]
#endif

#ifndef zeroes_matrix
	#define zeroes_matrix(x,y) zeroes_matrix[(dimension)*(x-1)+(y-1)]
#endif

#ifndef anterior
    #define anterior(x) (x-1)
#endif

#ifndef proximo
   #define proximo(x) (x+1)
#endif

#ifndef MINUTO
    #define MINUTO 60
#endif

#ifndef MENOSINFINITO
    #define MENOSINFINITO  -999999
#endif

#ifndef _ERRO_
    #define _ERRO_ -1
#endif

#ifndef SUCESSO
    #define SUCESSO 1
#endif

#endif
