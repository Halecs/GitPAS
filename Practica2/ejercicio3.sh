#! /bin/bash

if [ $# != 1 ]; then
	echo "Mal ejecutado, introduzca /ejercicio3.sh <nombrefichero>"
	exit 1
fi

if [ ! -f $1 ]; then
	echo "$1 no es un fichero"
	exit 2
fi

fichero=$(mktemp)
for x in $(ls -a $HOME | grep -E '^\.')
do 
	a=$(echo "$x" | wc -c)
	echo "$x $a" >> $fichero
done
cat $fichero | sort -nk 2 | sed -re 's/(.*) (.*)/\1/'


f="$1.sinLineasVacias"
if [ -e $f ]; then
	rm -f $f
fi

echo "El fichero a procesar es $1"
touch $f
cat $1 | grep -oE '.*' >> $f
echo "Fichero guardado"

echo "Listado de procesos"
#ps -ef | grep -E '^i62rejia' | sed -re 's/[^ ]+[ ]+([^ ]+)[ ]+[^ ]+[ ]+[^ ]+[ ]+[^ ]+[ ]+[^ ]+[ ]+[^ ]+[ ]+[^ ]+[ ]+([^ ]+)[ ]+[^ ]+[ ]+([^ ]+)[ ]+/PID: \1 Hora: \2 Ejecucion: \3/'
ps -o pid,start_time,cmd | sed -r -e '/PID.*CMD$/d' | sed -r -e 's/^(.*) ([0-9]{1,2}:[0-9]{2,2}) (.*)$/PID: "\1" Hora: "\2" Ejecutable: "\3"/'