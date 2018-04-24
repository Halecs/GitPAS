#! /bin/bash

#sed -re '/^$/d' peliculas.txt | sed -re '/^\=/d'  #elimina las lineas vacias y =
#sed -nre '1s/(.*)/Titulo->\1/p' peliculas.txt #Muestro el titulo
#sed -nre '3s/(\(.*\))/Fecha->\1' peliculas.txt 
#sed -re '/^$/d' peliculas.txt | sed -re '/^\=/d' | sed -nre 's/(^[0-9]hr.*)/Duracion -> \1/p' #Duraciones
#sed -re '/^$/d' peliculas.txt | sed -re '/^\=/d' | sed -re 's/(^[0-9]hr.*)/Duracion -> \1/' | sed -re 's/^Reparto: (.*)$/|-> Reparto: \1/' #reparto
#sed -re '/^$/d' peliculas.txt | sed -re '/^\=/d' | sed -re 's/(^[0-9]hr.*)/Duracion -> \1/' | sed -re 's/^Reparto: (.*)$/|-> Reparto: \1/' | sed  -re 's/^Dirigida por (.*)/|-> Director: \1/' | sed -re 's/^(\(.*)\)/|-> Fecha de estreno: \1/'
sed -re '/^$/d' peliculas.txt | sed -re '/^\=/d' | sed -re 's/(^[0-9]hr.*)/Duracion -> \1/' | sed -re 's/^Reparto: (.*)$/|-> Reparto: \1/' | sed  -re 's/^Dirigida por (.*)/|-> Director: \1/' | sed -re 's/^(\(.*)\)/|-> Fecha de estreno: \1/' | sed -re '/^ +/d' | sed -re 's/(^[^[D(|)])/Titulo: \1/'
#awk 'NF' peliculas.txt

