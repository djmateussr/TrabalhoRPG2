#ifndef ELEMENTO_H
#define ELEMENTO_H

#include <string>

using namespace std;

class Elemento {
public:
    string nome;
    int peso;

    Elemento(string nome, int peso);
    virtual ~Elemento();
};

class Arma : public Elemento {
public:
    int ataque;

    Arma(string nome, int peso, int ataque);
};

class Pocao : public Elemento {
public:
    int cura;

    Pocao(string nome, int peso, int cura);
};

#endif
