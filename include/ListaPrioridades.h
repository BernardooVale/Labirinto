#ifndef LISTAPRIORIDADES_HEADER
#define LISTAPRIORIDADES_HEADER

class ListaPrioridades{

public:

	int idOrigem, idDestino;
	float dist, distTotal;
	bool ePortal;
	ListaPrioridades* prox;

	ListaPrioridades(int n_idOrigem, int n_idDestino,float n_distTotal, float n_dist, bool n_ePortal);
	~ListaPrioridades();
	void adPrioridades(ListaPrioridades* nova);
};

#endif