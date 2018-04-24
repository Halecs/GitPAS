#! /bin/bash
if [ $# -eq 2 ]; then
	umbral2= 100000
fi
if [ $# -eq 1]; then
	umbral2=100000
	umbral1=10000
fi

if [ -d "medianos" ]; then
	echo "Ya existen las carpetas, procedo a borrarlas"
	rm -R pequenos
	rm -R medianos
	rm -R grandes
fi
	mkdir pequenos
	mkdir medianos
	mkdir grandes


if [ -d $1 ]; then
	for x in $(find $l)
	do
	var=$(stat -c%s $x)

		if [ $var -gt $umbral1 ]; then
			if [ $var -gt $umbral2 ]; then
				cp $x grandes
			else
				cp $x medianos
			fi
		else
			cp $x pequenos
		fi
done


else
	echo "No existe directorio"
	exit 1
fi