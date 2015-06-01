#!/bin/bash

time ./jurema.out -s -jp < helsgaun/br17.tour > saidaBR17.txt &
sleep 30 # Roda o sleep por 5 segundos (ou seja, espera 5 segundos)
kill `pidof -o %PPID jurema.out`

time ./jurema.out -s -jp < helsgaun/ft53.tour > saidaFT53.txt &
sleep 30 # Roda o sleep por 5 segundos (ou seja, espera 5 segundos)
kill `pidof -o %PPID jurema.out`



