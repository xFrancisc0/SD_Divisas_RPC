#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h> // Necesario para isdigit

//si el SO es windows, usar el system("cls")
#ifdef _WIN32
#define CLEAR "cls"
//Si no, usar system("clear");
#else
#define CLEAR "clear"
#endif


//Algoritmos de validacion
int IsNaN_int (char str[]) {

   char *ptr;
   long res;

   res = strtol(str, &ptr, 10); // str es el numero entero
   
   
   if(strcmp(ptr, "")==0){ //ptr es el string
   return(0);
   }

   return(1);
}


int IsNaN_float (char str[]) {

   char *ptr;
   long res;

   res = strtod(str, &ptr); // str es el numero flotante
   
   if(strcmp(ptr, "")==0){ //ptr es el string
   return(0);
   }

   return(1);
}

int IsNaS(char str[]){
   int i;
   
   for(i=0;i<=strlen(str);i++){
   	  
   	  
//A continuacion dentro del isdigit, se puede filtrar que no solo los digitos no sean aceptados si no que simbolos ASCII
//Podria perfectamente escribir if(isdigit(str[i]) && str != "'" && str != "%"

   if(isdigit(str[i])){
   return(1);
   }

   return(0);
   }
	
}