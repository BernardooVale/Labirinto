#ifndef TRILHA_HEADER
#define TRILHA_HEADER

class Trilha{

public:
	int id_destino;
	Trilha* prox;
	void adTrilha(Trilha* prox);
	bool verificaDuplicada(Trilha* nova);
	Trilha(int id);
	~Trilha();

};

#endif