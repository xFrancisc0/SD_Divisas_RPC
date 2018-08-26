#include "estructuras.h"

program DIVISAS{
	version DIVISAS_VER{
	
	string comprar_divisas(struct Datosentrada)=1;
	string vender_divisas(struct Datosentrada)=2;
	string listar_divisas()=3;
	string buscar_info_divisa(struct Datosentrada)=4;
	}=1;
}=1;
