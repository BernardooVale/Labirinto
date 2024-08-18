#include "Clareira.h"
#include <math.h> 
#include <iostream>
#define FLT_MAX 3.402823466e+38F

Clareira::Clareira(int id, float x, float y) {
	this->id = id;
	this->x = x;
	this->y = y;
	this->trilhas = nullptr;
	this->portais = nullptr;
	this->prox = nullptr;
}

Clareira::~Clareira() {

		delete this->trilhas;
		this->trilhas = nullptr;

		delete this->portais;
		this->portais = nullptr;

		delete this->prox;
		this->prox = nullptr;
}

void Clareira::adProx(Clareira* prox) {

	if (this->prox == nullptr) {
		this->prox = prox;
	}
	else {
		this->prox->adProx(prox);
	}
}

void Clareira::adTrilha(Trilha* novaT) {

	if (this->trilhas == nullptr) {
		this->trilhas = novaT;
	} else {
		this->trilhas->adTrilha(novaT);
	}
}

void Clareira::adPortal(Portal* novoP) {
	
	if (this->portais == nullptr) {
		this->portais = novoP;
	}
	else {
		this->portais->adPortal(novoP);
	}
}

Clareira* Clareira::achaClareira(int id_dest) {
	Clareira* aux = this;

	while (aux->id != id_dest && aux != nullptr) aux = aux->prox;

	return aux;
}

float Clareira::cal_distancia(Clareira* destino) {

	float a = this->x - destino->x;
	float b = this->y - destino->y;

	return sqrt((a * a) + (b * b));
}

int Clareira::cont_trilhas() {
	int num = 0;
	Trilha* trilhas_p = this->trilhas;

	while (trilhas_p != nullptr){
		num++;
		trilhas_p = trilhas_p->prox;
	}
	return num;
}

int Clareira::cont_portais() {
	int num = 0;
	Portal* portais_p = this->portais;

	while (portais_p != nullptr) {
		num++;
		portais_p = portais_p->prox;
	}
	return num;
}

bool Clareira::verificaDuplicada(Clareira* nova) {
	Clareira* aux = this;
	bool duplicada = false;

	while (aux != nullptr){

		if (nova->x == aux->x && aux->y == nova->y) duplicada = true;

		aux = aux->prox;
	}

	return duplicada;
}

bool Clareira::existe(int idChecar){

	Clareira* aux = this;
	bool existe = false;

	while (aux != nullptr){
		if(idChecar == aux->id) return !existe;
		aux = aux->prox;
	}
	
	return existe;
}

void Clareira::Dijkstra_rev(Clareira* lista, int percorridos[], int dest, float distTotal, int portais, float energia, bool* achou) {

	percorridos[this->id] = 1;

	if (!*achou) {

		Clareira* auxC = nullptr;		//auxiliares
		Trilha* auxT = this->trilhas;
		Portal* auxP = this->portais;

		int num_trilhas = this->cont_trilhas();
		int num_portais = portais >= 1 ? this->cont_portais() : 0;
		float dist_min = 0; //menor distancia
		float dist = 0;		// distancia atual
		int dist_id = -1;	// id da clareira com menor distancia
		int tipo_id = -1;   // 0 se for trilha, 1 se for portal
		bool percorrido = false;	// verifica se ja foi percorrido antes
		float distFinal = 0;

		int* percorridosT = new int[num_trilhas];
		for (int i = 0; i < num_trilhas; i++) percorridosT[i] = -1; //preenche todos com -1, depois será povoado com o id

		int* percorridosP = new int[num_portais];
		for (int i = 0; i < num_portais; i++) percorridosP[i] = -1; //preenche todos com -1, depois será povoado com o id

		for (int i = 0; i < (num_trilhas + num_portais); i++) { // passa por todas as conexões

			dist_min = FLT_MAX;
			dist = 0;

			auxT = this->trilhas;

			while (auxT != nullptr){ // passa por todos as trilhas

				for (int i = 0; i < num_trilhas; i++)
					if (percorridosT[i] == auxT->id_destino)
						percorrido = true;

				if(!percorrido) { // se ja foi percorrido nem leva em conta
					auxC = lista->achaClareira(auxT->id_destino); //clareira "apontada" pela trilha

					dist = this->cal_distancia(auxC); //distancia entre as duas
					if (dist < dist_min) { //se for distancia menor, preenche os dados
						dist_min = dist;
						dist_id = auxC->id;
						tipo_id = 0;
					}
				}
				percorrido = false;
				auxT = auxT->prox;
			}

			auxP = this->portais;

			if(portais >= 1){
				while (auxP != nullptr) { // passa por todos as portais

					for (int i = 0; i < num_portais; i++)
						if (percorridosP[i] == auxP->id_destino)
							percorrido = true;

					if(!percorrido){ // se ja foi percorrido nem leva em conta
						auxC = lista->achaClareira(auxP->id_destino); //clareira "apontada" pelo portal

						dist = 0; //distancia entre as duas
						if (dist < dist_min) { //se for distancia menor, preenche os dados
							dist_min = dist;
							dist_id = auxC->id;
							tipo_id = 1;
						}
					}
					percorrido = false;
					auxP = auxP->prox;
				}
			}

			//nesse ponto ja sabemos o caminho mais curto entre o vertice atual e seus adjacentes

			if (tipo_id == 0) {

				int i = 0;
				while (percorridosT[i] != -1) i++;

				percorridosT[i] = dist_id;

				auxC = lista->achaClareira(dist_id);
				if(percorridos[auxC->id] == 0) {

					distFinal = this->cal_distancia(auxC) + distTotal;

					if (auxC->id == dest) { //se for igual destino
						if (distFinal <= energia) {
							*achou = true;
							return;
						}
					}
					else {
						auxC->Dijkstra_rev(lista, percorridos, dest, distFinal, portais, energia, achou); //funcao recursiva, vai fzr a msm coisa pro proximo, sistema de pilha
						if (*achou) return;
					}
				}

			}
			else if (tipo_id == 1) {

				int i = 0;
				while (percorridosP[i] != -1) i++;

				percorridosP[i] = dist_id;

				auxC = lista->achaClareira(dist_id);

				if(percorridos[auxC->id] == 0) {
					if (auxC->id == dest) { //se for igual destino
						if (distTotal <= energia) {
							*achou = true;
							return;
						}
					}
					else {
						auxC->Dijkstra_rev(lista, percorridos, dest, distTotal, portais - 1, energia, achou); //funcao recursiva, vai fzr a msm coisa pro proximo, sistema de pilha
						if (*achou) return;
					}
				}
			}
		}

		delete[] percorridosT;
		delete[] percorridosP;
	}

	percorridos[this->id] = 0;
	return;
}

void Clareira::A(Clareira* lista, int* percorridos, Clareira* dest, ListaPrioridades* listaPrioridades, float distTotal, int portais, float energia, bool* achou, bool* NA) {

	percorridos[this->id] = 1;

		Clareira* auxC = nullptr;		//auxiliares
		Trilha* auxT = this->trilhas;
		Portal* auxP = this->portais;
		ListaPrioridades* auxL = nullptr;
		int prox_portais = 0;
		float dist = 0;		// distancia atual
		float distFinal = 0;

		while (auxT != nullptr) {
			if(percorridos[auxT->id_destino] == 0) {
				auxC = lista->achaClareira(auxT->id_destino);
				dist = this->cal_distancia(auxC) + auxC->cal_distancia(dest);

				ListaPrioridades* nova = new ListaPrioridades(this->id, auxC->id, distTotal, dist, false);
				if (listaPrioridades == nullptr) {
					listaPrioridades = nova;
				}
				else if (nova->dist < listaPrioridades->dist) {
					nova->prox = listaPrioridades;
					listaPrioridades = nova;
				}
				else {
					listaPrioridades->adPrioridades(nova);
				}
			}
			auxT = auxT->prox;
		}
		if(portais >= 1){
			while (auxP != nullptr) {
				if (percorridos[auxP->id_destino] == 0) {
					auxC = lista->achaClareira(auxP->id_destino);
					dist = auxC->cal_distancia(dest);

					ListaPrioridades* nova = new ListaPrioridades(this->id, auxC->id, distTotal, dist, true);
					if (listaPrioridades == nullptr) {
						listaPrioridades = nova;
					}
					else if (nova->dist < listaPrioridades->dist) {
						nova->prox = listaPrioridades;
						listaPrioridades = nova;
					}
					else {
						listaPrioridades->adPrioridades(nova);
					}
				}
				auxP = auxP->prox;
			}
		}
		if (listaPrioridades != nullptr){
			auxL = listaPrioridades; //pega o primeiro da fila
			listaPrioridades = listaPrioridades->prox; //segunda da fila vira o primeiro

			auxC = lista->achaClareira(auxL->idDestino);
			Clareira* origem = lista->achaClareira(auxL->idOrigem); //pega os vertices equivalentes

			distFinal = auxL->distTotal + (auxL->ePortal ? 0 : origem->cal_distancia(auxC)); //calcula distancia entre eles
			auxL->ePortal ? prox_portais = portais : prox_portais = portais - 1;

			if (auxC->id == dest->id) {
				if (distFinal <= energia) {
					*achou = true;
					return;
				}
				else {
					*achou = true;
					*NA = true;
				}
			}
			else {
				percorridos[origem->id] = 1;
				auxC->A(lista, percorridos, dest, listaPrioridades, distFinal, prox_portais, energia, achou, NA);
				delete auxL;
				auxL = nullptr;
				if (*achou) return;
			}
		}

	percorridos[this->id] = 0;
	return;
}