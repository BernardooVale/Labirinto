#include "Trilha.h"
#include <iostream>

Trilha::Trilha(int id) {
	this->id_destino = id;
	this->prox = nullptr;
}

Trilha::~Trilha() {
	
		delete this->prox;
		this->prox = nullptr;
}

bool Trilha::verificaDuplicada(Trilha* nova) {
	Trilha* aux = this;
	bool duplicada = false;

	while (aux != nullptr) {

		if (nova->id_destino == aux->id_destino) duplicada = true;

		aux = aux->prox;
	}

	return duplicada;
}

void Trilha::adTrilha(Trilha* prox) {

	if (this->prox == nullptr) {
		this->prox = prox;
	}
	else {
		this->prox->adTrilha(prox);
	}
}