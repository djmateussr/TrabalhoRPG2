#ifndef INIMIGO_H
#define INIMIGO_H

#include <string>

using namespace std;

class Inimigo {
public:
    string nome;
    int vida;
    int ataque;

    Inimigo(string nome, int vida, int ataque);
};

#endif
