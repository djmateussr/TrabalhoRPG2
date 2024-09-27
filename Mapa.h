#ifndef MAPA_H
#define MAPA_H

#include <queue>
#include <string>

using namespace std;

class Mapa {
public:
    queue<string> caminho; // Fila para gerenciar o caminho

    void adicionarSqm(string conteudo);
    string proximoSqm();
    bool mapaVazio();
};

#endif
