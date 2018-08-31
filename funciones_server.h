#include <stdio.h>
#include <stdlib.h>
#include <string.h>

typedef struct{
	char tipo_moneda[4];
	char cantidad[12];	
}entidad;


char** prueba(char tipo_moneda[]){
	static char * result;
	char resultado[1000];
	strcpy(resultado, "hola asdasdsdaasd");
	result = resultado;
	return &result;
}

//Es muy parecida a la funcion imprime_datos_conversion. Sin embargo hay dos diferencias.

//Esta funcion recibe como entrada un string, el cual se utiliza para comparar.

char** imprime_datos_conversion_filtrado(char tipo_moneda[]){
	FILE * f;
	static char * result;
	char resultado[1000];

	f=fopen("./datos/conversion.txt","a+");
	
	printf("======================================\nC O N V E R S I O N E S\n");
	strcpy(resultado, "======================================\nC O N V E R S I O N E S\n");

	printf("======================================\n");

	char origen[4],destino[4],conversion[12];
	while(fscanf(f,"%s %s %s\n",destino,origen,conversion)!=EOF){  //Mientras el archivo no se haya acabado de leer
		if(strcmp(destino, tipo_moneda)==0){                       //Si la entrada de la funcion es igual al tipo de moneda leido en la linea
		printf("1 %s corresponde a %s de la moneda %s\n",destino,conversion,origen); //Desplegar en pantalla su informacion acerca de su conversion con otros tipos de moneda.
		
		strcat(resultado, "1 ");
		strcat(resultado, destino);
		strcat(resultado, " corresponde a ");
		strcat(resultado, conversion);
		strcat(resultado, " de la moneda ");
		strcat(resultado, origen);
		strcat(resultado, ".\n");
		}
	}
	fclose(f);

	result=resultado;
		
	return &result;

}


// Se quiere listar la informacion completa de un tipo de divisa.
char** listar_informacion_moneda(char tipo_moneda[]){
	FILE * f;
	static char * result;
	f=fopen("./datos/informacion_moneda.txt","a+"); // Se abre informacion_moneda.txt. Este archivo contiene informacion en detalle de la moneda.
	
	char *tipo_monedaaux, *nombre_moneda, *localidad_moneda, *anio_moneda, str[1000];
	char resultado[1000];

	strcpy(resultado, "================================\n");
	while(fgets(str, 1000, f)!=NULL){  // Mientras que la lectura del archivo no sea EOF
		tipo_monedaaux=strtok(str,"|"); // Se obtiene Tipomoneda| del archivo. Este puede ser CLP EUR USD.
		
		if(strcmp(tipo_monedaaux,tipo_moneda)==0){  //Si en una fila llegara a ocurrir que el tipo de moneda que se quiere listar es el tipo de moneda de la linea actual
		nombre_moneda=strtok(NULL,"|");             //Se hace un split (Strtok) por cada " | " dentro de la linea. Ejemplo: CLP|10|Hola seria CLP  10  Hola mediante strtok.
		localidad_moneda=strtok(NULL,"|");
		anio_moneda=strtok(NULL,"|");

		strcat(resultado, "La moneda representada por ");
		strcat(resultado, tipo_monedaaux);
		strcat(resultado, " es el ");
		strcat(resultado, nombre_moneda);
		strcat(resultado, ".\nEsta moneda es usada por ");
		strcat(resultado, localidad_moneda);
		strcat(resultado, " y esta vigente desde el anio ");
		strcat(resultado, anio_moneda);
		}
	}
	
	fclose(f);

	result=resultado;
		
	return &result;
}

int rescata_dinero(entidad ent[], FILE * f){
	int i=0;
	if(f==NULL){
		printf("no existe el archivo");
	}else{
		while(fscanf(f,"%s %s\n",ent[i].tipo_moneda,ent[i].cantidad)!=EOF){
			//printf("%s %s\n",ent[i].tipo_moneda,ent[i].cantidad);
			i++;
		}
	}
	return i;
}

char** div_comprar( entidad * sistem,  entidad * user, char moneda_compra[], char moneda_pago[], int cantidad, FILE * f, FILE * f2){
	static char * result;
	FILE * conversor = fopen("./datos/conversion.txt","a+");
	char resultado[1000], resultado2[1000];

	int i=0,j=0,i_aux=0, j_aux=0, l, cantidad_usuario_cambio, cantidad_usuario_origen, cantidad_sistema,cantidad_sistema_pago,tipo_cambio_aux ;
	char tipo_aux[4],tipo_aux2[4],tasa_cambio[15];
	float conversion;
	//Buscamos en la  estructura user de tipo entidad la posicion del tipo de moneda_pago ingresado con la que se pagará
	while(strcmp(user[i].tipo_moneda, moneda_pago)!=0){
		i++;	
	}
	//buscamos en la estructura sistem de tipo entidad la posicion de moneda_compra ingresado que se comprará
	while(strcmp(sistem[j].tipo_moneda, moneda_compra)!=0){
		j++;
	}
	
		while(fscanf(conversor,"%s %s %s",tipo_aux,tipo_aux2,tasa_cambio)!=EOF){ 
					//buscamos en el archivo conversion.txt los tipos de moneda que se utilizaran y su tasa de cambio y lo guardamos en tasa_cambio
						if(strcmp(tipo_aux2,moneda_pago)==0 && strcmp(tipo_aux,moneda_compra)==0){
							//printf(" %s==%s && %s==%s\n",tipo_aux2,moneda_pago,tipo_aux,moneda_compra);
							break;
						}
						strcpy(tipo_aux,"");
				}
		//realizamos la  conversion de divisas		
	conversion=cantidad*atof(tasa_cambio);
			fclose(conversor);

	if(conversion>atof(user[i].cantidad)){ //comparamos si es que disponemos con el dinero a pagar, sino desplegamos mensaje
		//printf("Usted dispone de %s de la moneda %s no puede realizar la compra\n\n", user[i].cantidad,user[i].tipo_moneda);
		//system("pause");
		strcpy(resultado,"Usted no dispone del dinero suficiente para realizar la compra\n");
		result=resultado;
		return &result;
	}else{
		
		if(cantidad>=atoi(sistem[j].cantidad)){//comparamos si el sistema dispone de la cantidad suficiente de lo que demandamos, sino despliega mensaje
			
			//printf("Nuestro sistema no dispone de %f de la moneda %s\n",conversion,sistem[j].tipo_moneda);
			strcpy(resultado,"Nuestro Sistema no dispone de la cantidad necesario del tipo solicitado\n");
	
			result=resultado;
			return &result;
		}else{
				
		
			//	printf("tasa cambio %f\n",atof(tasa_cambio));
			
				cantidad_usuario_cambio = atoi(user[j].cantidad)+cantidad; //sumamos la cantidad comprada del tipo deseado al usuario
				cantidad_usuario_origen = atoi(user[i].cantidad)-conversion; //restamos la cantidad que se debe pagar del usuario
				cantidad_sistema = atoi(sistem[j].cantidad)-cantidad;	//restamos la cantidad que se vendio del sistema
				cantidad_sistema_pago = atoi(sistem[i].cantidad)+conversion; //sumamos la cantidad que se recibio por la venta
			}
			//printf("i=%i J=%i\n\n",i,j);
			//cerramos f y f2 para poder realizar la eliminacion de estos
			fclose(f);
			fclose(f2);
			if(remove("./datos/usuario.txt")==0 && remove("./datos/sistema.txt")==0){ 
			//si fueron eliminados usuario.txt y sistema.txt 
			//Los creamos nuevamente con los datos actualizados 
			FILE * nuevo_cliente=fopen("./datos/usuario.txt","a+");
			FILE * nuevo_servidor=fopen("./datos/sistema.txt","a+");
			
			char cantidad_usuario_cambioaux[15];
				char cantidad_usuario_origenaux[15];

				sprintf(cantidad_usuario_cambioaux, "%i", cantidad_usuario_cambio);
				sprintf(cantidad_usuario_origenaux, "%i", cantidad_usuario_origen);

				// Esto se devolvera al cliente
				strcpy(resultado, "================================\nEl usuario antes poseia\n");
				strcat(resultado, user[j].cantidad );
				strcat(resultado, " ");
				strcat(resultado, moneda_compra );
				strcat(resultado, "\n");
				strcat(resultado, user[i].cantidad );
				strcat(resultado, " ");
				strcat(resultado, moneda_pago );
				strcat(resultado, "\n================================\nEl usuario ahora posee\n" );
				strcat(resultado, cantidad_usuario_cambioaux );
				strcat(resultado, " ");
				strcat(resultado, moneda_compra );
				strcat(resultado, "\n");
				strcat(resultado, cantidad_usuario_origenaux );
				strcat(resultado, " ");
				strcat(resultado, moneda_pago );
				strcat(resultado, "\n================================\nIngrese un numero para continuar.\n\n\n" );
				
			for(l=0;l<3;l++){
			
				if(l==j){//buscamos donde sistema entrego la cantidad de monedas compradas y donde el usuario aumenta su saldo de moneda comprada, que estan en la posicion j para actualizarlo en el txt
					fprintf(nuevo_cliente,"%s %i\n",user[l].tipo_moneda,cantidad_usuario_cambio);
					fprintf(nuevo_servidor,"%s %i\n",sistem[l].tipo_moneda,cantidad_sistema);
				
				}else{
					if(l==i){//buscamos donde el sistema gano por la venta y donde el usuario pago con un tipo de moneda que esta almacenado en la posicion i, para escribirlo en el txt
						fprintf(nuevo_cliente,"%s %i\n",user[l].tipo_moneda,cantidad_usuario_origen);
						fprintf(nuevo_servidor,"%s %i\n",sistem[l].tipo_moneda,cantidad_sistema_pago);
						
					}else{//sino, se escribe directamente lo que se tiene almacenado ya que no se ha realizado ninguna modificacion en los demas campos
					
					fprintf(nuevo_cliente,"%s %s\n",user[l].tipo_moneda,user[l].cantidad);
					fprintf(nuevo_servidor,"%s %s\n",sistem[l].tipo_moneda,sistem[l].cantidad);
				
				}
				
			}
		}
			fclose(nuevo_cliente);
			fclose(nuevo_servidor);
			
		}
		}			
		result=resultado;
		
		return &result;
		
}


char ** vender_divisa( entidad * sistem,  entidad * user, char moneda_venta[], char moneda_recibo[], int cantidad, FILE * f, FILE * f2){
	static char * result;
	FILE * conversor = fopen("./datos/conversion.txt","a+");
	char resultado[1000], resultado2[1000];
	int i=0,j=0,i_aux=0, j_aux=0, l, cantidad_usuario_cambio, cantidad_usuario_origen, cantidad_sistema,cantidad_sistema_pago,tipo_cambio_aux ;
	char tipo_aux[4],tipo_aux2[4],tasa_cambio[15];
	float conversion;
	//Buscamos en la  estructura user de tipo entidad la posicion del tipo de moneda_recibo que es lo que se recibira
	while(strcmp(sistem[i].tipo_moneda, moneda_recibo)!=0){
		i++;	
	}
	//buscamos en la estructura sistem de tipo entidad la posicion de moneda_venta que es la que se vendera
	while(strcmp(user[j].tipo_moneda, moneda_venta)!=0){
		j++;
	}
	
		while(fscanf(conversor,"%s %s %s",tipo_aux,tipo_aux2,tasa_cambio)!=EOF){ 
					//buscamos en el archivo conversion.txt los tipos de moneda que se utilizaran y su tasa de cambio y lo guardamos en tasa_cambio
						if(strcmp(tipo_aux2,moneda_recibo)==0 && strcmp(tipo_aux,moneda_venta)==0){
							printf(" %s==%s && %s==%s\n",tipo_aux2,moneda_recibo,tipo_aux,moneda_venta);
							system("pause");
							break;
						}
						strcpy(tipo_aux,"");
				}
		//realizamos la  conversion de divisas		
	conversion=cantidad*atof(tasa_cambio);
			fclose(conversor);

	if(conversion>atof(sistem[i].cantidad)){ //comparamos si es que el sistema dispone con el dinero que se recibiria por la venta, sino desplegamos mensaje
		//printf("El sistema no dispone de %s de la moneda %s no puede realizar la transaccion\n\n", conversion,sistem[i].tipo_moneda);
		//system("pause");
		strcpy(resultado,"El sistema no dispone de suficiente de la moneda que desea, por lo que no se puede realizar la transaccion\n");
		result=resultado;
		return &result;
	}else{
		
		if(cantidad>atoi(user[j].cantidad)){//comparamos si se dispone de la cantidad suficiente de lo que vendemos, sino despliega mensaje
			
			//printf("Usted no dispone de %i de la moneda %s, no se puede realizar la transaccion\n",cantidad,user[j].tipo_moneda);
			//return 0;
			strcpy(resultado, "Usted no dispone de la cantidad que desea vender, intentelo de nuevo mas tarde\n");
			result=resultado;
			return &result;
		}else{
				
		
			//	printf("tasa cambio %f\n",atof(tasa_cambio));
			
				cantidad_usuario_cambio = atoi(user[j].cantidad)-cantidad; //restamos la cantidad vendida del tipo deseado al usuario
				cantidad_usuario_origen = atoi(user[i].cantidad)+conversion; //sumamos la cantidad que se recibe por el usuario
				cantidad_sistema = atoi(sistem[j].cantidad)+cantidad;	//sumamos la cantidad que el sistema compro
				cantidad_sistema_pago = atoi(sistem[i].cantidad)-conversion; //restamos la cantidad que se dio por la venta
			/*
			printf("usuario despues de la venta %i\n",cantidad_usuario_cambio);
			printf("usuario recibio %i\n",cantidad_usuario_origen);
			printf("cantidad sistema recibio %i\n",cantidad_sistema);
			printf("cantidad sistema pago %i\n",cantidad_sistema_pago);
			system("pause");
			*/
			//printf("i=%i J=%i\n\n",i,j);
			//cerramos f y f2 para poder realizar la eliminacion de estos
			fclose(f);
			fclose(f2);
		
			if(remove("./datos/usuario.txt")==0 && remove("./datos/sistema.txt")==0){ 
			//si fueron eliminados usuario.txt y sistema.txt 
			//Los creamos nuevamente con los datos actualizados 
			FILE * nuevo_cliente=fopen("./datos/usuario.txt","a+");
			FILE * nuevo_servidor=fopen("./datos/sistema.txt","a+");
			
				
			char cantidad_usuario_cambioaux[15];
				char cantidad_usuario_origenaux[15];

				sprintf(cantidad_usuario_cambioaux, "%i", cantidad_usuario_cambio);
				sprintf(cantidad_usuario_origenaux, "%i", cantidad_usuario_origen);

				// Esto se devolvera al cliente
				strcpy(resultado, "================================\nEl usuario antes poseia\n");
				strcat(resultado, user[j].cantidad );
				strcat(resultado, " ");
				strcat(resultado, moneda_venta);
				strcat(resultado, "\n");
				strcat(resultado, user[i].cantidad );
				strcat(resultado, " ");
				strcat(resultado, moneda_recibo );
				strcat(resultado, "\n================================\nEl usuario ahora posee\n" );
				strcat(resultado, cantidad_usuario_cambioaux );
				strcat(resultado, " ");
				strcat(resultado, moneda_venta );
				strcat(resultado, "\n");
				strcat(resultado, cantidad_usuario_origenaux );
				strcat(resultado, " ");
				strcat(resultado, moneda_recibo );
				strcat(resultado, "\n================================\nIngrese un numero para continuar.\n\n\n" );
				
			for(l=0;l<3;l++){
			
				if(l==j){//buscamos donde sistema recibio la cantidad de monedas al venderle y donde se encuentra el tipo moneda que vendio el usuario, que estan en la posicion j para actualizarlo en el txt
				
					fprintf(nuevo_cliente,"%s %i\n",user[l].tipo_moneda,cantidad_usuario_cambio);
					fprintf(nuevo_servidor,"%s %i\n",sistem[l].tipo_moneda,cantidad_sistema);
				
				}else{
					if(l==i){//buscamos donde el usuario gano por la venta y donde el sistema pago con un tipo de moneda que esta almacenado en la posicion i, para escribirlo en el txt
					
						fprintf(nuevo_cliente,"%s %i\n",user[l].tipo_moneda,cantidad_usuario_origen);
						fprintf(nuevo_servidor,"%s %i\n",sistem[l].tipo_moneda,cantidad_sistema_pago);
						
					}else{//sino, quiere decir que no se realizo  modificacion alguna en la posicion que se encuentra
					
					fprintf(nuevo_cliente,"%s %s\n",user[l].tipo_moneda,user[l].cantidad);
					fprintf(nuevo_servidor,"%s %s\n",sistem[l].tipo_moneda,sistem[l].cantidad);
				
				}
				
			}
		}
			fclose(nuevo_cliente);
			fclose(nuevo_servidor);
			
		}
		
	}
		}			
		result=resultado;
		
		return &result;
		
		
	}



char ** listar_datos_usuario(){
	static char * result;
	char resultado[1000];//resultado acumulara todo lo que se encuentre en usuario.txt 
	strcpy(resultado,"");
	FILE * f;
	f=fopen("./datos/usuario.txt","a+");
	if(f==NULL){
		//printf("no existe archivo");
		strcpy(resultado,"no existe archivo\n");
		result=resultado;
		return &result;
	}else{
	strcpy(resultado,"================================\nUsted actualmente Posee:\n================================\n");	
	char tipo_moneda[4],cantidad[12];
	while(fscanf(f,"%s %s\n",tipo_moneda,cantidad)!=EOF){;
		strcat(resultado,tipo_moneda);
		strcat(resultado," ");
		strcat(resultado,cantidad);
		strcat(resultado,"\n");

	}
	fclose(f);
	result=resultado;
	return &result; //retornaremos lo que acumulamos a listar_divisas_1_scv
}
}

char ** listar_datos_sistema(){
	static char * result;
	char resultado[1000];
	strcpy(resultado,"");
	FILE * f;
	f=fopen("./datos/sistema.txt","a+");
	if(f==NULL){
		//printf("no existe archivo");
		strcpy(resultado,"no existe archivo\n");
		result=resultado;
		return &result;
	}else{
	strcpy(resultado,"================================\nEl Sistema actualmente posee:\n================================\n");
	
	char tipo_moneda[4],cantidad[12];
	while(fscanf(f,"%s %s\n",tipo_moneda,cantidad)!=EOF){;
		strcat(resultado,tipo_moneda);
		strcat(resultado," ");
		strcat(resultado,cantidad);
		strcat(resultado,"\n");

	}
	fclose(f);
	result=resultado;
	return &result;
}
}	

char ** imprime_datos_conversion(){
	static char * result;
	char resultado[1000];
	strcpy(resultado,"");
	FILE * f;
	f=fopen("./datos/conversion.txt","a+");
	if(f==NULL){
		//printf("no existe archivo");
		strcpy(resultado,"no existe archivo");
		result=resultado;
		return &result;
	}else{
	strcpy(resultado,"================================\nLos cambios de divisas son los siguientes\n================================\n");

	char origen[4],destino[4],conversion[12];
	while(fscanf(f,"%s %s %s\n",destino,origen,conversion)!=EOF){
		//printf(" %s corresponde a %s de la moneda %s\n",destino,conversion,origen);
		strcat(resultado,destino);
		strcat(resultado," corresponde a ");
		strcat(resultado,conversion);
		strcat(resultado," de la moneda ");
		strcat(resultado,origen);
		strcat(resultado,"\n");

	}
	fclose(f);
	result=resultado;
	return &result;
}
}			


				