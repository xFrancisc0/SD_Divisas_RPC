#include "estructuras.h"
program CV_DIVISAS{
  version CV_DIVISAS_VER{
    int compra_divisas(struct CompraVenta)=1;
    int venta_divisas(struct CompraVenta)=2;
    void listar_divisas(struct CompraVenta)=3;
    void listardetalles_divisas(struct CompraVenta)=4;
  }=1;
}=1;
