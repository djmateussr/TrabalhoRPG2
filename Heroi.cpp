#include "Heroi.h"

Heroi::Heroi(string nome, int vida) : nome(nome), vida(vida), pesoAtualCinto(0), numItensCinto(0), numItensMochila(0) {
    for (int i = 0; i < MAX_ITEMS_CINTO; i++) {
        cinto[i] = nullptr;
    }
    for (int i = 0; i < MAX_ITEMS_MOCHILA; i++) {
        mochila[i] = nullptr;
    }
}

void Heroi::adicionarAoCinto(Elemento* e) {
    if (pesoAtualCinto + e->peso <= 30 && numItensCinto < MAX_ITEMS_CINTO) {
        cinto[numItensCinto] = e;
        pesoAtualCinto += e->peso;
        numItensCinto++;
        cout << e->nome << " foi adicionado ao cinto." << endl;
    } else {
        adicionarAMochila(e);
    }
}

void Heroi::adicionarAMochila(Elemento* e) {
    if (numItensMochila < MAX_ITEMS_MOCHILA) {
        mochila[numItensMochila] = e;
        numItensMochila++;
        cout << e->nome << " foi adicionado à mochila." << endl;
    } else {
        cout << "Mochila cheia! Não foi possível adicionar " << e->nome << endl;
    }
}

void Heroi::usarPocao() {
    if (numItensMochila > 0) {
        Pocao* p = dynamic_cast<Pocao*>(mochila[numItensMochila - 1]);
        if (p) {
            int cura = min(p->cura, 100 - vida);  // Evita ultrapassar o máximo de 100 pontos de vida
            vida += cura;
            cout << "Você usou uma poção e recuperou " << cura << " pontos de vida." << endl;
            delete mochila[numItensMochila - 1];
            mochila[numItensMochila - 1] = nullptr;
            numItensMochila--;
        } else {
            cout << "O item no topo da mochila não é uma poção." << endl;
        }
    } else {
        cout << "Sua mochila está vazia!" << endl;
    }
}

void Heroi::mostrarStatus() {
    cout << "Nome: " << nome << " | Vida: " << vida << endl;
    cout << "Cinto: ";
    for (int i = 0; i < numItensCinto; i++) {
        if (cinto[i] != nullptr) {
            cout << cinto[i]->nome << " ";
        }
    }
    cout << endl;
    cout << "Peso no cinto: " << pesoAtualCinto << "/30" << endl;

    if (numItensMochila > 0 && mochila[numItensMochila - 1] != nullptr) {
        cout << "Mochila: " << mochila[numItensMochila - 1]->nome << endl;
    } else {
        cout << "Mochila está vazia!" << endl;
    }
}

Arma* Heroi::escolherArma() {
    if (numItensCinto == 0) {
        cout << "Você não tem armas no cinto." << endl;
        return nullptr;
    }

    int index = 1;
    cout << "Escolha uma arma:" << endl;
    for (int i = 0; i < numItensCinto; i++) {
        Arma* arma = dynamic_cast<Arma*>(cinto[i]);
        if (arma) {
            cout << index << ". " << arma->nome << " (Ataque: " << arma->ataque << ")" << endl;
            index++;
        }
    }

    int escolha;
    cout << "Digite o número da arma que deseja usar: ";
    cin >> escolha;

    index = 1;
    for (int i = 0; i < numItensCinto; i++) {
        Arma* arma = dynamic_cast<Arma*>(cinto[i]);
        if (arma && index == escolha) {
            return arma;
        }
        index++;
    }

    cout << "Escolha inválida." << endl;
    return nullptr;
}

Heroi::~Heroi() {
    for (int i = 0; i < MAX_ITEMS_CINTO; i++) {
        delete cinto[i];
    }
    for (int i = 0; i < MAX_ITEMS_MOCHILA; i++) {
        delete mochila[i];
    }
}
