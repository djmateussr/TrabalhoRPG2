#include "Heroi.h"

Heroi::Heroi(string nome, int vida) : nome(nome), vida(vida), capacidadeCinto(30), pesoAtualCinto(0) {}

void Heroi::adicionarAoCinto(Elemento* e) {
    if (pesoAtualCinto + e->peso <= capacidadeCinto) {
        cinto.push_back(e);
        pesoAtualCinto += e->peso;
        cout << e->nome << " foi adicionado ao cinto." << endl;
    } else {
        adicionarAMochila(e);
    }
}

void Heroi::adicionarAMochila(Elemento* e) {
    mochila.push(e);
    cout << e->nome << " foi adicionado a mochila." << endl;
}

void Heroi::usarPocao() {
    if (!mochila.empty()) {
        Pocao* p = dynamic_cast<Pocao*>(mochila.top());
        if (p) {
            vida += p->cura;
            cout << "Voce usou uma pocao e recuperou " << p->cura << " pontos de vida." << endl;
            mochila.pop();
            delete p;
        } else {
            cout << "O item no topo da mochila nao e uma pocao." << endl;
        }
    } else {
        cout << "Sua mochila esta vazia!" << endl;
    }
}

void Heroi::mostrarStatus() {
    cout << "Nome: " << nome << " | Vida: " << vida << endl;
    cout << "Cinto: ";
    for (Elemento* e : cinto) {
        cout << e->nome << " ";
    }
    cout << endl;
    cout << "Peso no cinto: " << pesoAtualCinto << "/" << capacidadeCinto << endl;

    if (!mochila.empty()) {
        cout << "Mochila: " << mochila.top()->nome << endl;
    } else {
        cout << "Mochila esta vazia!" << endl;
    }
}

Heroi::~Heroi() {
    for (Elemento* e : cinto) {
        delete e;
    }
    while (!mochila.empty()) {
        delete mochila.top();
        mochila.pop();
    }
}
