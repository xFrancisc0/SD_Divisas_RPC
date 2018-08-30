#include "estructuras.h"
program CV_DIVISAS{
  version CV_DIVISAS_VER{
    string compra_divisas(struct CompraVenta)=1;
    string venta_divisas(struct CompraVenta)=2;
    string listar_divisas(int opcion)=3;
    string listardetalles_divisas(struct CompraVenta)=4;
  }=1;
}=1;
