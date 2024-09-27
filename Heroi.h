#ifndef HEROI_H
#define HEROI_H

#include <iostream>
#include <string>
#include "Elemento.h"

using namespace std;

const int MAX_ITEMS_CINTO = 10;  // Máximo de itens no cinto
const int MAX_ITEMS_MOCHILA = 20;  // Máximo de itens na mochila

class Heroi {
public:
    string nome;
    int vida;
    Elemento* cinto[MAX_ITEMS_CINTO];      // Array para o cinto
    int pesoAtualCinto;                    // Peso atual dos itens no cinto
    int numItensCinto;                     // Número atual de itens no cinto
    Elemento* mochila[MAX_ITEMS_MOCHILA];  // Array para a mochila
    int numItensMochila;                   // Número atual de itens na mochila

    Heroi(string nome, int vida);
    void adicionarAoCinto(Elemento* e);
    void adicionarAMochila(Elemento* e);
    void alocarItem(Elemento* e);
    void usarPocao();
    void mostrarStatus();
    Arma* escolherArma();
    ~Heroi();
};

#endif
