#! bin/bash

echo "Lineas con la duracion de las peliculas"
cat peliculas.txt | grep '^[0-9]'
echo "*********"

echo "Lineas con el pais de las peliculas"
cat peliculas.txt | grep -E '[0-9]\/'
echo "*********"

echo "Solo el pais de las peliculas"
cat peliculas.txt | grep -oE '\-.*\-' | tr -d "-"
echo "**********"

lineas6=cat peliculas.txt | grep -E '2016' | wc -l
lineas7=cat peliculas.txt | grep -E '2017' | wc -l

echo "Hay $lineas6 de 2016 y $lineas7 de 2017"

echo "Todo sin lineas vacias"
cat peliculas.txt | grep -oE '.*' 
#cat peliculas.txt | grep -vE '^ *$' #todo menos espàcios

echo "Empiezan por E con o sin espacios"
cat peliculas.txt  | grep -E '^ *E'

echo "Contiene d l o t, una vocal y la misma letra"
cat peliculas.txt  | grep -E '([d,l,t])[aeiou]\1'  #\1 es lo del parentesis

echo "Lineas que contienen ocho aes o mas"
cat peliculas.txt  | grep -iE '(.*a.*){8,}'

echo "lineas que terminan con tres puntos y no empiezan con espacio"
cat peliculas.txt  | grep -E '(\.\.\.)$' | grep -vE '^ '

echo "Vocales con tilde"
#sed -r -e 's/á/\"á\"/' peliculas.txt | sed -r -e 's/é/\"é\"/' | sed -r -e 's/í/\"í\"/' | sed -r -e 's/ó/\"ó\"/' | sed -r -e 's/ú/\"ú\"/' | sed -r -e 's/Á/\"Á\"/' | sed -r -e 's/É/\"É\"/' | sed -r -e 's/Í/\"Í\"/' | sed -r -e 's/Ó/\"Ó\"/' | sed -r -e 's/Ú/\"Ú\"/'
sed -rei 's/[áéíóú]/"\1"/'