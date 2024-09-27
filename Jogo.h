#ifndef JOGO_H
#define JOGO_H

#include "Heroi.h"
#include "Mapa.h"
#include "Inimigo.h"
#include <iostream>
#include <fstream>
#include <cstdlib>
#include <ctime>

using namespace std;

class Jogo {
private:
    Heroi* heroi;
    int nivelAtual;

public:
    Jogo(Heroi* h);
    void iniciar();
    void batalhar(Inimigo* inimigo);
    void interagirComElemento(string tipo);
    void salvarPontuacao();
    void gerarNovoNivel(Mapa* mapa);
};

#endif
