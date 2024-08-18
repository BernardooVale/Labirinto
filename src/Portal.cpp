#include "Portal.h"
#include <iostream>

Portal::Portal(int id) {
	this->id_destino = id;
	this->prox = nullptr;
}

Portal::~Portal() {
	
		delete this->prox;
		this->prox = nullptr;
}

bool Portal::verificaDuplicada(Portal* nova) {
	Portal* aux = this;
	bool duplicada = false;

	while (aux != nullptr) {

		if (nova->id_destino == aux->id_destino) duplicada = true;

		aux = aux->prox;
	}

	return duplicada;
}

void Portal::adPortal(Portal* prox) {

	if (this->prox == nullptr) {
		this->prox = prox;
	}
	else {
		this->prox->adPortal(prox);
	}
}