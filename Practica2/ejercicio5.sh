#! /bin/bash

#CPUINFO

cat /proc/cpuinfo | sed -n -r -e 's/model name[[:blank:]]*: (.+)/Modelo de procesador: \1/p' | head -1

cat /proc/cpuinfo | sed -n -r -e's/cpu MHz[[:blank:]]*: (.+)/Megahercios: \1/p' | head -1 

cat /proc/cpuinfo | sed -n -r -e 's/cache size[[:blank:]]*: (.+)/Tamaño de cache: \1/p' | head -1

echo "Numero de hilos: $(cat /proc/cpuinfo | grep -E 'processor[[:blank:]]*: .+' | wc -l)"

cat /proc/cpuinfo | sed -n -r -e 's/vendor_id[[:blank:]]*: (.+)/ID vendedor: \1/p'  | head -1

#MOUNTS

echo "Puntos de montaje:"
cat /proc/mounts | sed -r -e  's/([^ ]+) ([^ ]+) ([^ ]+) ([^ ]+) ([^ ]+) ([^ ]+)/->Punto de montaje: \2, Dispositivo: \1, Tipo de dispositivo: \3/' | sort -r -k 2

#Partitions

echo "Particiones y número de bloques:"
cat /proc/partitions | sed -e '1,2d' | sed -n -r -e 's/ *([[:digit:]]+) *([[:digit:]]+) *([[:digit:]]+) *([[:alnum:]]+)/->Particion: \4, Numero de Bloques: \3/p'  | sort -r -k 2