#! /bin/bash

if [ $# -ne 2 ]
then
	echo "Error al introducir los argumentos. La ejecucion es ./ejercicio4.sh ficheroIPs segundos"
	exit 1
fi

if [ ! -f $1 ]; then
	echo "$1 no es un fichero"
	exit 2
fi

f [ $2 -lt 1 ]
then
	echo "El numero de segundos debe ser mayor o igual que 1"
	exit 3
fi

pings=$(mktemp)
noresponde=$(mktemp)
$Responde=$(mktemp)

for x in $(cat $1) #para leer las IPs del fichero
do
	ping -w $2 -c 1 $x > $pings #Guarda todas aqui

	if [ $? -eq 0]; then
		cat $pings | sed -nre 's/(.+from )(.+)(:.+ )(time=)(.+)( ms)/La ip \2 ha tardado \5 milisegundos/p' >> $Responde #guardo las buenas
	else
		echo "La IP $x no ha respondido en $2 ms" >> $noresponde #malas
	fi
done

cat $Responde | sort -nk 6 
cat $noresponde
