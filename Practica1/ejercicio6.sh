#!/bin/bash 

if [ $# -lt 1 ] || [ $# -gt 1 ] ; then
	echo -e "Numero de argumentos pasado invalido"
	exit 1
fi

a="aadsfgasfafd"
k=""

function recorre() {
	
		for x in $(find -L $1); do
			if [ $x != $u ] ;then	
				if [ -d $x ]; then
					if [ $a != $x ]; then
						k=$(grep "<ul><li><strong>$(readlink -f $x)</strong></li>" $name)
						if [ -z $k ]; then
							echo "<ul><li><strong>$(readlink -f $x)</strong></li>">>$name			
							echo "<ul>">>$name				
						fi
						a=$x
						recorre $x
						echo "</ul>">>$name
					fi
				else
					k=$(grep "<li>$(readlink -f $x)</li>" $name)
					if [ -z $k ]; then
						echo "<li>$(readlink -f $x)</li>">>$name
					fi
				fi
			fi
		done
		echo "</ul>">>$name
}


name="$1.html"

if [ -e $name ]; then
	rm $name
	echo "$name anterior borrado."

fi

echo "Creando un nuevo archivo html. . ."


touch $name 

echo "<html>">>$name
echo "<head>">>$name
echo "<title>Listado del directorio $1</title>">>$name
echo "</head>">>$name
echo "<body>">>$name
echo "<style type="text/css">">>$name
echo "	body { font-family: sans-serif;}">>$name
echo "</style>">>$name
echo "<h1>Listado del directorio $1</h1>">>$name

u=$1
recorre $1


echo "</body>">>$name
echo "</html>">>$name

echo "$name creado con exito."