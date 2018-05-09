#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include <sys/stat.h>
#include <sys/types.h>
#include <mqueue.h>
#include <time.h>
#include <errno.h>
#include "common.h"

#include <unistd.h>
#include <regex.h>
#include <getopt.h>


int main(int argc, char **argv)
{
	int c;
	// Cola del servidor
	mqd_t mq_server;
	// Atributos de la cola
	struct mq_attr attr;
	// Buffer para intercambiar mensajes
	char buffer[MAX_SIZE + 1];
	// flag que indica cuando hay que parar. Se escribe palabra exit
	int must_stop = 0;
	// Inicializar los atributos de la cola
	attr.mq_maxmsg = 10;        // Maximo número de mensajes
	attr.mq_msgsize = MAX_SIZE; // Maximo tamaño de un mensaje

	char* rex = NULL;
	regex_t regex;	//Comprobar si empareja o no
    int reti;//lo mismo de arriba
	struct option long_options[]={

		{"regex",	 required_argument,	   0, 'r'}
		{0,0,0,0}
	
	};

	FILE *fLog = NULL;

	// Crear la cola de mensajes del servidor. La cola CLIENT_QUEUE le servira en ejercicio resumen
	mq_server = mq_open(SERVER_QUEUE, O_CREAT | O_RDONLY, 0644, &attr);	
	if(mq_server == (mqd_t)-1 )
	{
   	perror("Error al abrir la cola del servidor");
      exit(-1);
	}

	mq_grep = mq_open(GREP_QUEUE, O_CREAT, 0644, &attr);
	if(mq_grep == ((mqd_t) -1))
	{
		perror("Error al abrir la cola del grep")
		exit(-1);
	}

	while ((c = getopt_long (argc, argv, "r:", long_options, &option_index))!=-1)
	{
		/* El usuario ha terminado de introducir opciones */
		if (c == -1)
			break;
		switch (c)
		{
			case 'r':
				rex=optarg;
				break;
			case '?':
				fprintf(stderr, "La opcion %c requiere un argumento.",optopt);
				break;

			default:
				abort ();
		}
		printf("optind: %d, optarg: %s, optopt: %c\n", optind, optarg, optopt);
	}

	if(rex != NULL)//para saber si le ha pasado la opcion de introducir una cadena si no no ha introducido nada y rex da null 
	{
		
        reti = regcomp(&regex, rex, 0);//preparamos la expresion regular
        //Compilar la expresion regular
        if( reti )//Que es distinto de 0
    	{ 
    		sprintf(msgBuff,"Error al crear la expresion regular");
    		perror("Error al crear la expresion regular.\n"); 
    		// funcionLog(msgBuff);

    		
    		if(mq_send(mq_server, MSG_STOP, MAX_SIZE, 0) != 0)//Si se ha producido algun error algun expresion se escribe un mensaje de error en la cola para desconectar en la cola
    		{
    			perror("Error en el envío.");
    			// funcionLog("Error en el envío");
    		}

    		exit(-1); 
    	}
	}

    else
	{
		printf("No ha introducido expresion regular\n");
		// funcionLog("No ha introducido expresion regular");
		exit(-1);
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
