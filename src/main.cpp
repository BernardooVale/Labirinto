#include <iostream>
#include "Clareira.h"
#include "ListaPrioridades.h"

int main() {

    Clareira* lista_cla = nullptr;
    int num_clareiras, num_trilhas, num_portais;

    std::cin >> num_clareiras >> num_trilhas >> num_portais;

    float x, y;

   for (int i = 0; i < num_clareiras; i++) {

       std::cin >> x >> y;

       Clareira* aux = new Clareira(i, x, y);

        if (lista_cla == nullptr){
            lista_cla = aux;
        }
        else {
            if (!lista_cla->verificaDuplicada(aux)) {
                lista_cla->adProx(aux);
            }
            else{
                std::cout << "dados inválidos, escreva novamente" << std::endl;
                i--;
            }
        }
    }

   int id_partida, id_destino;

   for (int i = 0; i < num_trilhas; i++) {
       std::cin >> id_partida >> id_destino;

        if(lista_cla->existe(id_partida) && lista_cla->existe(id_destino)){
            Trilha* trilha = new Trilha(id_destino);
            Clareira* aux = lista_cla->achaClareira(id_partida);

            if(!aux->trilhas->verificaDuplicada(trilha)) {
                aux->adTrilha(trilha);
            } else {
                std::cout << "dados inválidos, escreva novamente" << std::endl;
                i--;
            }
        } else {
            std::cout << "dados inválidos, escreva novamente" << std::endl;
            i--;
        }
   }

   for (int i = 0; i < num_portais; i++) {

       std::cin >> id_partida >> id_destino;

        if(lista_cla->existe(id_partida) && lista_cla->existe(id_destino)){
            Portal* portal = new Portal(id_destino);
            Clareira* aux = lista_cla->achaClareira(id_partida);

            if(!aux->portais->verificaDuplicada(portal)) {
                aux->adPortal(portal);
            } else {
                std::cout << "dados inválidos, escreva novamente" << std::endl;
                i--;
            }
        } else {
            std::cout << "dados inválidos, escreva novamente" << std::endl;
            i--;
        }
   }

   int quant_portais;
   float energia;

   std::cin >> energia >> quant_portais;

   if(energia >=0){

    int* percorridos = new int[num_clareiras];
    bool* achou = new bool(false);

    for (int i = 0; i < num_clareiras; ++i) {
       percorridos[i] = 0;
    }

    lista_cla->Dijkstra_rev(lista_cla, percorridos, num_clareiras - 1, 0, quant_portais, energia, achou);

    std::cout << (*achou ? "1" : "0") << std::endl;

    *achou = false;
    bool *NA = new bool(false);

    for (int i = 0; i < num_clareiras; ++i) percorridos[i] = 0;

    Clareira* dest = lista_cla->achaClareira(num_clareiras - 1);
    ListaPrioridades* listaPrioridades = nullptr;

    lista_cla->A(lista_cla, percorridos, dest, listaPrioridades, 0, quant_portais, energia, achou, NA);

    if (*achou && !*NA) {
        std::cout << "1" << std::endl;
    }
    else{
        std::cout << "0" << std::endl;

    }

    delete listaPrioridades;
    listaPrioridades = nullptr;
    delete achou;
    achou = nullptr;
    delete[] percorridos;
    percorridos = nullptr;
   } else {
    std::cout << "0" << std::endl;
    std::cout << "0" << std::endl;
   }

   delete lista_cla;
   lista_cla = nullptr;

    return 0;
}