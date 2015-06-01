#ifndef UPPER_BOUNDS_H
#define UPPER_BOUNDS_H

#ifndef ERRO
    #define ERRO             -1
#endif

#ifndef SUCESSO
    #define SUCESSO           1
#endif

#ifndef INFINITO
    #define INFINITO 999999
#endif

#define _FITSP_ 0

#ifndef _GENERAL_PATCHING_
	#define _GENERAL_PATCHING_ 1
#endif

#ifndef  _KARPS_MODIFIED_PATCHING_
	#define _KARPS_MODIFIED_PATCHING_ 2
#endif 



int upperBound();
int FITSP(int);
int tourImprovement();
int twoOpt();
int ub(int heuristica);

#endif

