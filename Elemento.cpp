#include "Elemento.h"

Elemento::Elemento(string nome, int peso) : nome(nome), peso(peso) {}
Elemento::~Elemento() {}

Arma::Arma(string nome, int peso, int ataque) : Elemento(nome, peso), ataque(ataque) {}
Pocao::Pocao(string nome, int peso, int cura) : Elemento(nome, peso), cura(cura) {}
