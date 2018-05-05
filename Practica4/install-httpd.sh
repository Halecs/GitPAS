#!/bin/bash
mkdir $HOME/tmp
cd $HOME/tmp

# Si por lo que sea la dirección que hay abajo no dispone del fichero, buscar otra con Google
wget -O httpd-2.4.33.tar.bz2 http://apache.uvigo.es//httpd/httpd-2.4.33.tar.bz2
tar jxvf httpd-2.4.33.tar.bz2

# Bajamos y descomprimimos la última versión de las librerías APR
wget -O apr-1.6.3.tar.bz2 http://ftp.cixug.es/apache//apr/apr-1.6.3.tar.bz2
wget -O apr-util-1.6.1.tar.bz2 http://ftp.cixug.es/apache//apr/apr-util-1.6.1.tar.bz2
tar jxvf apr-1.6.3.tar.bz2
tar jxvf apr-util-1.6.1.tar.bz2

# Movemos las librerías a la carpeta de apache, para que éste las utilice
mv apr-1.6.3 ./httpd-2.4.33/srclib/apr
mv apr-util-1.6.1 ./httpd-2.4.33/srclib/apr-util

# Vamos a la carpeta de apache
cd httpd-2.4.33

# Configurar la compilación, diciendo que el apr lo coja de srclib
# prefix va a indicar el directorio de instalación
./configure --prefix=$HOME/httpd --with-included-apr

# Compilar e instalar en $HOME/httpd
make
make install
make clean

# Configurar bash para que al hacer logout se maten todos los procesos de Apache
if [ ! -f $HOME/.bash_logout ]
then
	echo -e "#!/bin/bash\nkillall -s KILL httpd" > $HOME/.bash_logout
elif [ -z "$(cat $HOME/.bash_logout | grep 'killall -s KILL httpd')" ]
then
	echo "killall -s KILL httpd" >> $HOME/.bash_logout
fi

# Borrar el archivo descargado y la carpeta de compilación
rm $HOME/tmp/httpd-2.4.33.tar.bz2
rm -Rf $HOME/tmp/httpd-2.4.33

# Borrar las carpetas de las librerías y los archivos descargados
rm $HOME/tmp/apr-1.6.3.tar.bz2
rm $HOME/tmp/apr-util-1.6.1.tar.bz2

# Borrar la carpeta temporal
rmdir $HOME/tmp
cd
