#include "Jogo.h"

Jogo::Jogo(Heroi* h) : heroi(h), nivelAtual(1) {
    srand(time(0)); // Inicializa a semente para números aleatórios
}

void Jogo::iniciar() {
    while (heroi->vida > 0) {
        Mapa* mapa = new Mapa();
        gerarNovoNivel(mapa);

        while (!mapa->mapaVazio()) {
            string sqm = mapa->proximoSqm();
            cout << "Voce encontrou: " << sqm << endl;
            if (sqm == "inimigo") {
                Inimigo* inimigo = new Inimigo("Inimigo", 5 * nivelAtual, 2 * nivelAtual);
                batalhar(inimigo);
                delete inimigo;
            } else if (sqm == "arma" || "pocao") {
                interagirComElemento(sqm);
            } else {
                cout << "Caminho vazio..." << endl;
            }
            heroi->mostrarStatus();
        }

        cout << "Parabens, voce terminou o nivel " << nivelAtual << "!" << endl;
        nivelAtual++;
        delete mapa;
    }
    salvarPontuacao();
}

void Jogo::batalhar(Inimigo* inimigo) {
    cout << "Uma batalha comecou!" << endl;
    while (inimigo->vida > 0 && heroi->vida > 0) {
        inimigo->vida -= 2;
        heroi->vida -= inimigo->ataque;
        cout << "Inimigo HP: " << inimigo->vida << " | Heroi HP: " << heroi->vida << endl;
    }

    if (heroi->vida <= 0) {
        cout << "Voce foi derrotado!" << endl;
        exit(0);
    } else {
        cout << "Voce derrotou o inimigo!" << endl;
    }
}

void Jogo::interagirComElemento(string tipo) {
    if (tipo == "arma") {
        Arma* arma = new Arma("Espada", 5, 10 + 5 * nivelAtual);
        heroi->adicionarAoCinto(arma);
        cout << "Voce encontrou uma arma: " << arma->nome << endl;
    }if (tipo == "arma") {
        Arma* arma = new Arma("Arco e Flecha", 3, 7 + 5 * nivelAtual);
        heroi->adicionarAoCinto(arma);
        cout << "Voce encontrou uma arma: " << arma->nome << endl;
    }if (tipo == "arma") {
        Arma* arma = new Arma("Lanca", 10, 15 + 5 * nivelAtual);
        heroi->adicionarAoCinto(arma);
        cout << "Voce encontrou uma arma: " << arma->nome << endl;
    }else if (tipo == "pocao") {
        Pocao* pocao = new Pocao("Pocao de Vida", 2, 10 + 10 * nivelAtual);
        heroi->adicionarAMochila(pocao);
        cout << "Voce encontrou uma pocao!" << endl;
    }
}

void Jogo::salvarPontuacao() {
    ofstream arquivo("high_scores.txt", ios::app);
    if (arquivo.is_open()) {
        arquivo << "Jogador: " << heroi->nome << " | Nivel atingido: " << nivelAtual << endl;
        cout << "Arquivo gerado com sucesso" << endl;
        arquivo.close();
    } else {
        cout << "Nao foi possivel abrir o arquivo de pontuacao." << endl;
    }
}

void Jogo::gerarNovoNivel(Mapa* mapa) {
    int tamanhoMapa = 5 + nivelAtual * 2; // Aumenta o tamanho do mapa a cada nível
    for (int i = 0; i < tamanhoMapa; i++) {
        int randomEvent = rand() % 3;
        if (randomEvent == 0) {
            mapa->adicionarSqm("inimigo");
        } else if (randomEvent == 1) {
            mapa->adicionarSqm("arma");
        } else if (randomEvent == 2) {
            mapa->adicionarSqm("pocao");
        } else {
            mapa->adicionarSqm("vazio");
        }
    }
}
