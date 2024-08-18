#ifndef CLAREIRA_HEADER
#define CLAREIRA_HEADER

#include "Trilha.h"
#include "Portal.h"
#include "ListaPrioridades.h"


class Clareira{

public:
	int id;
	float x, y;
	Trilha *trilhas;
	Portal *portais;
	Clareira* prox;

	Clareira(int id, float x, float y);
	~Clareira();
	void adProx(Clareira* prox);
	void adTrilha(Trilha* novaT);
	void adPortal(Portal* novoP);
	Clareira* achaClareira(int id_dest);
	float cal_distancia(Clareira* destino);
	int cont_trilhas();
	int cont_portais();
	bool verificaDuplicada(Clareira* nova);
	bool existe(int idChecar);
	void Dijkstra_rev(Clareira* lista, int* percorridos, int dest, float distTotal, int portais, float energia, bool* achou);
	void A(Clareira* lista, int* percorridos, Clareira* dest, ListaPrioridades* listaPrioridades, float distTotal, int portais, float energia, bool* achou, bool* NA);

};

#endif