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
	// Cola del servidor
	mqd_t mq_server;
	mqd_t mq_grep;
	// Buffer para intercambiar mensajes
	char buffer[MAX_SIZE];
	
	// Abrir la cola del servidor. La cola CLIENT_QUEUE le servira en ejercicio resumen
	mq_server = mq_open(SERVER_QUEUE, O_WRONLY);
	if(mq_server == ((mqd_t)-1 ))
	{
      perror("Error al abrir la cola del servidor");
      exit(-1);
	}

	mq_grep = mq_open(GREP_QUEUE, O_RDONLY);
	if(mq_grep == ((mqd_t) -1))
	{
      perror("Error al abrir la cola del servidor");
      exit(-1);
	}

	printf("Mandando mensajes al servidor (escribir \"%s\" para parar):\n", MSG_STOP);
	do 
	{
		printf("> ");
		fflush(stdout);                  // Limpiar buffer de salida
		memset(buffer, 0, MAX_SIZE);     // Poner a 0 el buffer
		fgets(buffer, MAX_SIZE, stdin);  // Leer por teclado
		buffer[strlen(buffer)-1] = '\0'; // Descartar el salto de línea

		// Enviar y comprobar si el mensaje se manda
		if(mq_send(mq_server, buffer, MAX_SIZE, 0) != 0)
		{
			perror("Error al enviar el mensaje");
			exit(-1);
		}

		if(mq_receive(mq_grep, emparejador, MAX_SIZE, NULL) < 0)
		{
			
			perror("Error al recibir el mensaje.");
			// funcionLog("Error al recibir el mensaje");
			exit(-1);
		}
	// Iterar hasta escribir el código de salida
	}while (strncmp(buffer, MSG_STOP, strlen(MSG_STOP)));

	// Cerrar la cola del servidor
	if(mq_close(mq_server) == (mqd_t)-1)
	{
		perror("Error al cerrar la cola del servidor");
		exit(-1);
	}

	if(mq_close(mq_grep) == (mqd_t)-1)
	{
		perror("Error al cerrar la cola del grep");
		exit(-1);
	}
	return 0;
}
