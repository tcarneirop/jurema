all: clean
	g++ -c -O2  aux.cpp assig.cpp befs.cpp buscas.cpp grafo_esparso.cpp dfs_bnb.cpp juremasearch.cpp jurematronco.cpp little_et_al.cpp lowerbounds.cpp patching.cpp upperbounds.cpp
	g++ -c -O2 -fopenmp  buscas_omp.cpp
	g++ jurema.cpp aux.o assig.o befs.o buscas.o buscas_omp.o dfs_bnb.o grafo_esparso.o juremasearch.o jurematronco.o little_et_al.o lowerbounds.o patching.o upperbounds.o -O2 -fopenmp -o jurema.out
clean:
	rm *.o jurema.out
