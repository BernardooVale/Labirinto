#include "ListaPrioridades.h"
#include <iostream>

ListaPrioridades::ListaPrioridades(int n_idOrigem, int n_idDestino,float n_distTotal, float n_dist, bool n_ePortal) {
	this->idDestino = n_idDestino;
	this->idOrigem = n_idOrigem;
	this->dist = n_dist;
	this->prox = nullptr;
	this->ePortal = n_ePortal;
	this->distTotal = n_distTotal;
}

ListaPrioridades::~ListaPrioridades() {
	delete this->prox;
	this->prox = nullptr;
}

void ListaPrioridades::adPrioridades(ListaPrioridades* nova) {

	if (this->prox == nullptr){
		this->prox = nova;
	}
	else if (nova->dist < this->prox->dist) {
		nova->prox = this->prox;
		this->prox = nova;
	}
	else {
		this->prox->adPrioridades(nova);
	}
}