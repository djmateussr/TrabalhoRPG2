#ifndef HEROI_H
#define HEROI_H

#include <list>
#include <stack>
#include <iostream>
#include <string>
#include "Elemento.h"

using namespace std;

class Heroi {
public:
    string nome;
    int vida;
    list<Elemento*> cinto;      // Lista para o cinto
    stack<Elemento*> mochila;   // Pilha para a mochila
    int capacidadeCinto;        // Capacidade máxima de peso do cinto
    int pesoAtualCinto;         // Peso atual dos itens no cinto

    Heroi(string nome, int vida);
    void adicionarAoCinto(Elemento* e);
    void adicionarAMochila(Elemento* e);
    void usarPocao();
    void mostrarStatus();
    Arma* escolherArma();
    ~Heroi();
};

#endif
