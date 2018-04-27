#include <stdio.h>
#include <stdlib.h> //exit, rand, srand
#include <unistd.h> //pipe, close, fork, usleep, read, write, getpid, getppid
#include <sys/wait.h> //wait
#include <errno.h> //Control de errores
#include <string.h> //strerror
#include <time.h> //Para la semilla del generador de aleatorios


int main(int argc, char const *argv[])
{
	pid_t flag;

	int tuberia1;
	int tuberia2;
	int numero;
	int status;
	int resultado;
	char retorno[100];

	int fildes[2];
	int fildes2[2];	
	ssize_t nbytes;

	tuberia1 = pipe(fildes);
	if(tuberia1 == -1)
	{
		printf("Error al crear la tuberia 1\n");
		return;
	}

	tuberia2 = pipe(fildes2);
	if(tuberia2 == -1)
	{
		printf("Error al crear la tuberia 2\n");
		return;
	}

	switch(fork())
	{
		case -1:
			perror("No se ha podido crear el proceso hijo...");
			exit(EXIT_FAILURE);
			break;

		//Hijo lee de la tuberia 1 y escribe en la dos
		case 0:
			//No escribimos, la cerramos
			if (close(fildes[1]) == -1) 
			{
				perror("Error en close1"); 
				exit(EXIT_FAILURE);
			}

			nbytes = read(fildes[0],&numero,sizeof(int));
			if(nbytes == -1)
			{
				printf("Error en read\n");
				exit(EXIT_FAILURE);
			}
			printf("[Hijo] He leido %d desde la tuberia1\n",numero);

			if(close(fildes[0]) == -1)
			{
				printf("Error en close1\n");
				exit(EXIT_FAILURE);
			}
			// printf("[Hijo] Tuberia cerrada\n");

			//No leemos, cerramos el 0
			if(close(fildes2[0]) == -1)
			{
				perror("Error en close2");
				exit(EXIT_FAILURE);
			}

			if(numero % 2 == 0)
				// retorno[0] = "par";
			strcpy(retorno,"par");
			else
				// retorno[0] = "impar";
				strcpy(retorno, "impar");

			nbytes = write(fildes2[1],retorno,100);
			if(nbytes == -1)
			{
				printf("Error en read\n");
				exit(EXIT_FAILURE);
			}

			if(close(fildes2[1]) == -1)
			{
				perror("Error en el close2");
				exit(EXIT_FAILURE);
			}

			exit(EXIT_SUCCESS);

		default:
			//No necesitamos leer
			if(close(fildes[0]) == -1)
			{
				printf("Error en close2\n");
				exit(EXIT_FAILURE);
			}
			//Pedimos el numero por pantalla
			printf("Introduzca numero --> ");
			scanf("%d",&numero);
			//Escribimos datos en la tuberia
			resultado = write(fildes[1],&numero,sizeof(int));
			if(resultado != sizeof(int))
			{
				printf("[Padre] Error al escribir\n");
				exit(EXIT_FAILURE);
			}

			//Cerramos donde hemos escrito
			close(fildes[1]);
			printf("Tuberia1 cerrada\n");


			//Cogemos lo que hemos enviado desde el hijo la tuberia 2
			//Cerramos porque no escribimos
			if (close(fildes2[1]) == -1)
			{
				printf("Error en el close2\n");
				exit(EXIT_FAILURE);
			}

			nbytes = read(fildes2[0],retorno,100);
			if(nbytes == -1)
			{
				printf("Error al leer de la tuberia2\n");
				exit(EXIT_FAILURE);
			}

			if(close(fildes2[0]) == -1)
			{
				printf("Error en el close2\n");
				exit(EXIT_FAILURE);
			}
			printf("El numero %d es %s\n",numero,retorno);


			while ( (flag=wait(&status)) > 0 ) 
			{
				if (WIFEXITED(status)) {
					printf("[PADRE]: Hijo con PID %ld finalizado, status = %d\n", (long int)flag, WEXITSTATUS(status));
				} 
				else if (WIFSIGNALED(status)) {  //Para seniales como las de finalizar o matar
					printf("[PADRE]:, Hijo con PID %ld finalizado al recibir la señal %d\n", (long int)flag, WTERMSIG(status));
				} 
			}
			if (flag==(pid_t)-1 && errno==ECHILD)
			{
				printf("[PADRE]: Valor de errno = %d, definido como: %s\n", errno, strerror(errno));
			}
			else
			{
				printf("[PADRE]: Error en la invocacion de wait o la llamada ha sido interrumpida por una señal.\n");
				exit(EXIT_FAILURE);
			}		 

	}
	return 0;
}