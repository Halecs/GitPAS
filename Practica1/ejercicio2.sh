#! /bin/bash


if [ $# -eq 1 ]
then
	echo "Introduzca directorio y numero de bytes"
	byte=0c;
	exit 1
fi


if [ -d $1 ]; then
	for x in $(find $1 -type f -size +$(byte)   #"$byte"c
	do
		nombre=$(basename $x)
		user=$(stat -c%U $x | wc -m)
		fecha=$(stat -c%y $x)
		acceso=$(stat -c%x $x)
		bytes=$(stat -c%s $x)
		permisos=$(stat -c%a $x)

	if [ -x $x ]; then
		exe=1
	else
		exe=0

		echo "$nombre;$user;$fecha;$acceso;$bytes;$permisos;$exe"
	fi

	done | sort -t ";"
else
	echo "No existe el directorio"
	exit 1
fi



# find $1 -type f -size $(byte)