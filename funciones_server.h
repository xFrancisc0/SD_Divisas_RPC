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

