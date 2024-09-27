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
        cout << "Não foi possível adicionar " << e->nome << " ao cinto. Peso ou espaço insuficiente." << endl;
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

void Heroi::alocarItem(Elemento* e) {
    cout << "Onde deseja alocar o item " << e->nome << "?" << endl;
    cout << "1. Cinto" << endl;
    cout << "2. Mochila" << endl;
    int escolha;
    cin >> escolha;

    if (escolha == 1) {
        adicionarAoCinto(e);
    } else if (escolha == 2) {
        adicionarAMochila(e);
    } else {
        cout << "Escolha inválida. Item alocado na mochila por padrão." << endl;
        adicionarAMochila(e);
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
    cout << "Primeiro item no cinto: ";
    if (numItensCinto > 0 && cinto[0] != nullptr) {
        cout << cinto[0]->nome << endl;
    } else {
        cout << "Cinto vazio." << endl;
    }

    cout << "Último item na mochila: ";
    if (numItensMochila > 0 && mochila[numItensMochila - 1] != nullptr) {
        cout << mochila[numItensMochila - 1]->nome << endl;
    } else {
        cout << "Mochila vazia." << endl;
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
