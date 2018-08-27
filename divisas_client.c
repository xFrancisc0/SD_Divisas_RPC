/*
 * This is sample code generated by rpcgen.
 * These are only templates and you can use them
 * as a guideline for developing your own functions.
 */

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "divisas.h"
#include "funciones_client.h"

void
divisas_1(char *host)
{
	system(CLEAR);
	CLIENT *clnt;
	char * *result_1;
	struct EstructuraDatos  comprar_divisas_1_arg;
	char * *result_2;
	struct EstructuraDatos  vender_divisas_1_arg;
	char * *result_3;
	char *listar_divisas_1_arg;
	char * *result_4;
	struct EstructuraDatos  buscar_info_divisa_1_arg;

#ifndef	DEBUG
	clnt = clnt_create (host, DIVISAS, DIVISAS_VER, "udp");
	if (clnt == NULL) {
		clnt_pcreateerror (host);
		exit (1);
	}
#endif	/* DEBUG */

//	result_1 = comprar_divisas_1(&comprar_divisas_1_arg, clnt);
//	if (result_1 == (char **) NULL) {
//		clnt_perror (clnt, "call failed");
//	}
//	result_2 = vender_divisas_1(&vender_divisas_1_arg, clnt);
//	if (result_2 == (char **) NULL) {
//		clnt_perror (clnt, "call failed");
//	}
//	result_3 = listar_divisas_1((void*)&listar_divisas_1_arg, clnt);
//	if (result_3 == (char **) NULL) {
//		clnt_perror (clnt, "call failed");
//	}
//	result_4 = buscar_info_divisa_1(&buscar_info_divisa_1_arg, clnt);
//	if (result_4 == (char **) NULL) {
//		clnt_perror (clnt, "call failed");
//	}
#ifndef	DEBUG
	clnt_destroy (clnt);
#endif	 /* DEBUG */
}


int
main (int argc, char *argv[])
{
	char *host;

	if (argc < 2) {
		printf ("usage: %s server_host\n", argv[0]);
		exit (1);
	}
	host = argv[1];

char opcion;
do{ system(CLEAR);
	printf("MENU\n");
	printf("==================\n");
	printf("Bienvenido al sistema de gestion de divisas.\n");
	printf("Ingrese una opcion para continuar:\n");
	printf("1) Compra de divisas.\n");
	printf("2) Venta de divisas.\n");
	printf("3) Listar divisas.\n");
	printf("4) Buscar una divisa y desplegar su informacion.\n");
	printf("5) Salir.\n");
	fflush(stdin);
	scanf("%c",&opcion);

	divisas_1 (host);
}while(opcion!='9');


exit (0);
}
