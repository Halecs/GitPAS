#! /bin/bash

var=$(find -type f | wc -l)
echo "El numero de archivos en la carpeta es $var"

a=$(users)
echo "Esta sería la lista de usuarios conectados:"
echo $a | tr '''\n' | sort -u

carac=0
read -s -t5 -p "Que caracter quieres contar" carac

if [ -z $carac ]; then
	carac="a"
fi


veces=find . -name "*$carac*" | wc -l
#n=$(find . -name "$carac" | wc -c )

echo "El caracter $carac aparece $veces" 