

if [ $# -lt 1 ] ; then
	echo -e "Numero de argumentos pasado invalido"
	exit 1
fi

if [ -e "Copia" ] ; then #Existe Copia?
	sleep 0
else
	mkdir Copia
fi

for x in $(find "Copia/") ; do
	let aux=$[$(date +%s)-$(stat -c %Y $x)] #tiempo actual - tiempo modf archivo
	
	if [ $x == "Copia/" ]
	then
		sleep 0
	elif [ $aux -gt 200 ]
	then
		rm $x
		echo "copia $(basename $x) de $aux segundos ha sido borrada."
	else
		sleep 0
	fi
done

mkdir acopiar #creamos un directorio, copiamos todo y hacemos el tar.gz

for i in $@ ; done    #recorremos los argumentos
	if [ -d $i ]; then
		cp -r $i acopiar
	else
		cp $i acopiar
	fi
done

name="copia-$USER-$(date +%s).tar.gz"
tar cvf $name acopiar/*

mv $name Copia
rm -R acopiar

echo "La copia de segurida ha sido creada satisfactoriamente"  


