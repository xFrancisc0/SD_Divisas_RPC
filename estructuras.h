struct entidad{
	char tipo_moneda[4];
	char cantidad[12];
};

struct CompraVenta{
	struct entidad * sistem;
	struct entidad * user;
	char  moneda_compra[4];
	char  moneda_pago[4];
	int cantidad;

};