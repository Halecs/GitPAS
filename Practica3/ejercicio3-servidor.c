#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include <sys/stat.h>
#include <sys/types.h>
#include <mqueue.h>
#include <time.h>
#include <errno.h>
#include "common.h"

int main(int argc, char **argv)
{
	int c;
	// Cola del servidor
	mqd_t mq_server;
	// Atributos de la cola
	struct mq_attr attr;
	struct mq_attr attr2;
	// Buffer para intercambiar mensajes
	char buffer[MAX_SIZE + 1];
	// flag que indica cuando hay que parar. Se escribe palabra exit
	int must_stop = 0;
	// Inicializar los atributos de la cola
	attr.mq_maxmsg = 10;        // Maximo número de mensajes
	attr.mq_msgsize = MAX_SIZE; // Maximo tamaño de un mensaje

	// Crear la cola de mensajes del servidor. La cola CLIENT_QUEUE le servira en ejercicio resumen
	mq_server = mq_open(SERVER_QUEUE, O_CREAT | O_RDONLY, 0644, &attr);	
	if(mq_server == (mqd_t)-1 )
	{
   	perror("Error al abrir la cola del servidor");
      exit(-1);
	}

	mq_grep = mq_open(GREP_QUEUE, O_CREAT, 0644, &attr2);
	if(mq_grep == ((mqd_t) -1))
	{
		perror("Error al abrir la cola del grep")
		exit(-1);
	}
// LEEMOS PARSEANDO LA LINEA DE COMANDOS LA EXPRESION A EMPAREJAR
    opterr = 0; 
    while ((c = getopt (argc, argv, "r:")) != -1)
    {
        // Podemos observar qué pasa con las variables externas que va gestionando
        //   getopt() durante las sucesivas llamadas. 
        //   - optind Indice del siguiente elemento a procesar del vector argv[]
        //   - optarg recoge el valor del argumento obligario de una opcion.
        //   - optopt recoge el valor de la opcion cuando es desconocida (?) o INCOMPLETA respecto a las opciones indicadas.        
        switch (c)
        {
		     case 'r':
		    	cvalue = optarg;
		        break;
		     case '?': //Opcion no reconocida o INCOMPLETA. Probar tambien la diferencia entre ejecutar %$>./a.out m   ó   %$>./a.out -m
		         if (optopt == 'c') //Para el caso de que 'c' no tenga el argumento obligatorio.
		             fprintf (stderr, "La opción %c requiere un argumento. Valor de opterr = %d\n", optopt, opterr);
		         else if (isprint (optopt)) //Se mira si el caracter es imprimible
		             fprintf (stderr, "Opción desconocida \"-%c\". Valor de opterr = %d\n", optopt, opterr);
		         else //Caracter no imprimible o especial
		             fprintf (stderr, "Caracter `\\x%x'. Valor de opterr = %d\n", optopt, opterr);
		         return 1;  //Finaliza el programa
		     default:
		         abort ();
        }
        printf("optind: %d, optarg: %s, optopt: %c, opterr: %d\n", optind, optarg, optopt, opterr);
    }



// 
	do 
	{
		// Número de bytes leidos
		ssize_t bytes_read;
		// ssize_t bytes_send; //Numero bits enviados

		// Recibir el mensaje
		bytes_read = mq_receive(mq_server, buffer, MAX_SIZE, NULL);
		// Comprar que la recepción es correcta (bytes leidos no son negativos)
		if(bytes_read < 0)
		{
			perror("Error al recibir el mensaje");
			exit(-1);
		}
		// Cerrar la cadena
		buffer[bytes_read] = '\0';


		// Comprobar el fin del bucle
		if (strncmp(buffer, MSG_STOP, strlen(MSG_STOP))==0)
			must_stop = 1;
		else
			printf("Recibido el mensaje: %s\n", buffer);
	} while (!must_stop); 	// Iterar hasta que llegue el código de salida, es decir, la palabra exit

///////////////////////////////////COLA SERVER
	// Cerrar la cola del servidor
	if(mq_close(mq_server) == (mqd_t)-1)
	{
		perror("Error al cerrar la cola del servidor");
		exit(-1);
	}

	// Eliminar la cola del servidor
	if(mq_unlink(SERVER_QUEUE) == (mqd_t)-1)
	{
		perror("Error al eliminar la cola del servidor");
		exit(-1);
	}

///////////////////////////////////COLA GREP
	if(mq_close(mq_grep) == (mqd_t)-1)
	{
		perror("Error al cerrar la cola del grep");
		exit(-1);
	}

	// Eliminar la cola del grep
	if(mq_unlink(GREP_QUEUE) == (mqd_t)-1)
	{
		perror("Error al eliminar la cola del grep");
		exit(-1);
	}

	return 0;
}
