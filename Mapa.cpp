#include "Mapa.h"

void Mapa::adicionarSqm(string conteudo) {
    caminho.push(conteudo);
}

string Mapa::proximoSqm() {
    string sqm = caminho.front();
    caminho.pop();
    return sqm;
}

bool Mapa::mapaVazio() {
    return caminho.empty();
}
