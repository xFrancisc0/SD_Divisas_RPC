#include <stdio.h>
#include <stdlib.h>
#include <string.h>

typedef struct{
	char tipo_moneda[4];
	char cantidad[12];	
}entidad;

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
	while(strcmp(user[i].tipo_moneda, moneda_pago)!=0){
		i++;	
	}
	while(strcmp(sistem[j].tipo_moneda, moneda_compra)!=0){
		j++;
	}
	if(cantidad>=atoi(user[i].cantidad)){
		printf("Usted dispone de %s de la moneda %s\n\n", user[i].cantidad,user[i].tipo_moneda);
	}else{
		
		if(conversion>=atoi(sistem[j].cantidad)){
			printf("Nuestro sistema no dispone de %f de la moneda %s\n",conversion,sistem[j].tipo_moneda);
		}else{
				while(fscanf(conversor,"%s %s %s",tipo_aux,tipo_aux2,tasa_cambio)!=EOF){
					
						if(strcmp(tipo_aux2,moneda_pago)==0 && strcmp(tipo_aux,moneda_compra)==0){
							//printf(" %s==%s && %s==%s\n",tipo_aux2,moneda_pago,tipo_aux,moneda_compra);
							break;
						}
						strcpy(tipo_aux,"");
				}
				fclose(conversor);
			//	printf("tasa cambio %f\n",atof(tasa_cambio));
				conversion=cantidad*atof(tasa_cambio);
				cantidad_usuario_cambio = atoi(user[j].cantidad)+cantidad;
				cantidad_usuario_origen = atoi(user[i].cantidad)-conversion;
				cantidad_sistema = atoi(sistem[j].cantidad)-cantidad;
				cantidad_sistema_pago = atoi(sistem[i].cantidad)+conversion;
			}
			//printf("i=%i J=%i\n\n",i,j);
			fclose(f);
			fclose(f2);
			if(remove("./datos/usuario.txt")==0 && remove("./datos/sistema.txt")==0){
			
			FILE * nuevo_cliente=fopen("./datos/usuario.txt","a+");
			FILE * nuevo_servidor=fopen("./datos/sistema.txt","a+");
			

				printf("================================\nEl usuario antes poseia\n");
				printf("%i %s\n", atoi(user[j].cantidad), moneda_compra);
				printf("%i %s\n", atoi(user[i].cantidad), moneda_pago);
				printf("\n================================\nEl usuario ahora posee\n");
				printf("%i %s\n", cantidad_usuario_cambio, moneda_compra);
				printf("%i %s\n", cantidad_usuario_origen, moneda_pago);
				printf("\n================================\nIngrese cualquier caracter para continuar\n\n\n");
				


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
			
				if(l==j){
					fprintf(nuevo_cliente,"%s %i\n",user[l].tipo_moneda,cantidad_usuario_cambio);
					fprintf(nuevo_servidor,"%s %i\n",sistem[l].tipo_moneda,cantidad_sistema);
				
				}else{
					if(l==i){
						fprintf(nuevo_cliente,"%s %i\n",user[l].tipo_moneda,cantidad_usuario_origen);
						fprintf(nuevo_servidor,"%s %i\n",sistem[l].tipo_moneda,cantidad_sistema_pago);
						
					}else{
					
					fprintf(nuevo_cliente,"%s %s\n",user[l].tipo_moneda,user[l].cantidad);
					fprintf(nuevo_servidor,"%s %s\n",sistem[l].tipo_moneda,sistem[l].cantidad);
				
				}
				
			}
		}
			fclose(nuevo_cliente);
			fclose(nuevo_servidor);
			result=resultado;
			return &result;
		}
		}	
		result=resultado;		
		return &result;
		
	}