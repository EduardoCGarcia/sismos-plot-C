
#include <string.h>
#include <unistd.h>
#include <sys/socket.h>
#include <sys/types.h>
#include <netinet/in.h>
#include <arpa/inet.h>
#include <time.h>
#include "bmp_plot.h"

#define PORT 4444

/**
 * @brief
 * Usando la funcion gaussiana redondea hacia abajo el numero que recibe
 * @param n
 */
int redondeo(float n)
{
	return (int)n;
}

int main()
{
	int op = 0;

	int clientSocket, ret;
	struct sockaddr_in serverAddr;
	char buffer[1024];
	char nameCity[50];
	char t[20];
	float num;
	char dato[10];
	int time_value;

	char file_vector[15];
	int vec[100];
	char nameCityFile[50];

	char *token;
	time_t t1 = 0;
	time_t *pt1 = &t1;

	clientSocket = socket(AF_INET, SOCK_STREAM, 0);
	if (clientSocket < 0)
	{
		printf("[-]Error in connection.\n");
		exit(1);
	}
	printf("[+]Client Socket is created.\n");

	memset(&serverAddr, '\0', sizeof(serverAddr));
	serverAddr.sin_family = AF_INET;
	serverAddr.sin_port = htons(PORT);
	serverAddr.sin_addr.s_addr = inet_addr("127.0.0.1");

	ret = connect(clientSocket, (struct sockaddr *)&serverAddr, sizeof(serverAddr));
	if (ret < 0)
	{
		printf("[-]Error in connection.\n");
		exit(1);
	}
	printf("[+]Connected to Server.\n");

	printf("Nombre de la ciudad: ");
	scanf("%s", &nameCity[0]);
	send(clientSocket, nameCity, strlen(nameCity), 0);
	int bandera = 1;
	while (bandera == 1)
	{
		printf("\n1) Introducir dato");
		printf("\n2) Solicitar grafica");
		printf("\n3) Terminar conexion");
		printf("\nSelecciona una opcion: ");
		scanf("%d", &op);

		switch (op)
		{
		case 1:
			printf("\nIngresa la magnitud del sismo en escala de Richter");
			printf("\nDato: ");
			scanf("%f", &num);
			num *= 10;
			int nume = redondeo(num);
			sprintf(dato, "%d", nume);

			time(pt1);
			sprintf(t, "%ld", *pt1);
			strcat(t, "|");
			strcat(t, dato);
			strcat(t, "|");

			printf("JSON: %s\n", t);

			send(clientSocket, t, strlen(t), 0);
			break;
		case 2:
			strcpy(buffer, "grafica");
			send(clientSocket, buffer, strlen(buffer), 0);
			int j = 0;
			while (1)
			{
				recv(clientSocket, file_vector, 14, 0);
				//printf("Vec [%ld]: %s\n", strlen(file_vector), file_vector);

				token = strtok(file_vector, "|");
				//printf("token 1: %s\n", token);

				token = strtok(NULL, "|");
				//printf("token 2: %s\n", token);

				if (strcmp(file_vector, ":exit") == 0)
				{
					break;
				}
				else
				{
					vec[j] = atoi(token);
					j++;
				}
			}
			for (int i = 0; i < j; i++)
			{
				printf("%d\n", vec[i]);
			}
			strcpy(nameCityFile,nameCity);
			strcat(nameCityFile,".pgm");
			
			generaGrafica(nameCityFile,vec,j);
			printf("Grafica creada satisfactoriamente \nBuscala como: %s", nameCityFile);
			break;
		case 3:
			bzero(buffer, sizeof(buffer));
			strcpy(buffer, ":exit");
			send(clientSocket, buffer, strlen(buffer), 0);
			printf("\nSaliendo...\n");
			bandera = 0;
			break;
		default:
			printf("La opcion no es valida...");
			break;
		}
	}

	return 0;
}

/**

						token = strtok(file_vector,"|");
						printf("token 1: %s\n",token);

						token = strtok(NULL,"|");
						printf("token 2: %s\n",token);
 */