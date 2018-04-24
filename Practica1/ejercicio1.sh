#! /bin/bash

if [ ! $# 1 ]
	echo "Introduzca directorio"
	exit 1
fi

cd $1
h=0
c=0

if [ -d $1 ] 
then
	for x in $(find -name "*.h")
	do
		y=$(wc -l $x )
		z=$(wc -m $x)
		h=$[$h+1]
		echo"$x tiene $y lineas y $z caracteres"
	done | sort -nk 8

	for x in $(find -name "*.c") 
	do
		y=$(wc -l $x) 
		z=cat $x | wc -m 
		c=$[$c+1]
		echo"$x tiene $y lineas y $z caracteres"
	done | sort -nk 8

	echo "El fichero tiene $h .h y $c .c"
else
	echo "Carpeta no existe"
	exit 1
fi
