#include "Jogo.h"
#include <cstdlib>
#include <ctime>

Jogo::Jogo(Heroi* h) : heroi(h), nivelAtual(1) {
    srand(time(0)); // Inicializa a semente para números aleatórios
}

void Jogo::iniciar() {
    while (heroi->vida > 0) {
        Mapa* mapa = new Mapa();
        gerarNovoNivel(mapa);

        while (!mapa->mapaVazio()) {
            string sqm = mapa->proximoSqm();
            cout << "Você encontrou: " << sqm << endl;
            if (sqm == "inimigo") {
                // Aumenta a força dos inimigos a cada nível
                Inimigo* inimigo = new Inimigo("Inimigo", 5 * nivelAtual, 2 * nivelAtual);
                cout << "Deseja usar uma poção antes da batalha? (s/n): ";
                char resposta;
                cin >> resposta;
                if (resposta == 's' || resposta == 'S') {
                    heroi->usarPocao();
                }
                batalhar(inimigo);
                delete inimigo;
            } else if (sqm == "arma" || sqm == "pocao") {
                interagirComElemento(sqm);
            } else {
                cout << "Caminho vazio..." << endl;
            }
            heroi->mostrarStatus();
        }

        cout << "Parabéns, você terminou o nível " << nivelAtual << "!" << endl;
        nivelAtual++;
        delete mapa;
    }
    salvarPontuacao();
}

void Jogo::batalhar(Inimigo* inimigo) {
    cout << "Uma batalha começou!" << endl;

    Arma* armaAtual = heroi->escolherArma();
    if (!armaAtual) {
        cout << "Você não tem uma arma válida para usar. Fuga forçada." << endl;
        return;
    }

    while (inimigo->vida > 0 && heroi->vida > 0) {
        cout << "\nEscolha sua ação:" << endl;
        cout << "1. Atacar com a arma atual (" << armaAtual->nome << ")" << endl;
        cout << "2. Trocar de arma" << endl;
        cout << "3. Usar poção" << endl;

        int escolha;
        cin >> escolha;

        switch (escolha) {
            case 1: // Atacar com a arma atual
                inimigo->vida -= armaAtual->ataque;
                heroi->vida -= inimigo->ataque;
                cout << "Você atacou o inimigo! Inimigo HP: " << inimigo->vida << ", Seu HP: " << heroi->vida << endl;
                break;

            case 2: // Trocar de arma
                armaAtual = heroi->escolherArma();
                if (!armaAtual) {
                    cout << "Você não tem uma arma válida para usar. Fuga forçada." << endl;
                    return;
                }
                break;

            case 3: // Usar poção
                heroi->usarPocao();
                break;

            default:
                cout << "Escolha inválida, você perdeu a vez!" << endl;
                break;
        }

        if (heroi->vida <= 0) {
            cout << "Você foi derrotado!" << endl;
            exit(0);
        } else if (inimigo->vida <= 0) {
            cout << "Você derrotou o inimigo!" << endl;
        }
    }
}

void Jogo::interagirComElemento(string tipo) {
    Elemento* novoItem = nullptr;

    if (tipo == "arma") {
        novoItem = new Arma("Espada", 5, 10 + 5 * nivelAtual);
        cout << "Você encontrou uma arma: " << novoItem->nome << endl;
    } else if (tipo == "pocao") {
        novoItem = new Pocao("Poção de Vida", 2, 10 + 10 * nivelAtual);
        cout << "Você encontrou uma poção!" << endl;
    }

    if (novoItem != nullptr) {
        cout << "Deseja pegar o item? (s/n): ";
        char escolha;
        cin >> escolha;

        if (escolha == 's' || escolha == 'S') {
            heroi->alocarItem(novoItem);
        } else {
            cout << "Você decidiu não pegar o item." << endl;
            delete novoItem;
        }
    }
}

void Jogo::salvarPontuacao() {
    ofstream arquivo("high_scores.txt", ios::app);
    if (arquivo.is_open()) {
        arquivo << "Jogador: " << heroi->nome << " | Nível atingido: " << nivelAtual << endl;
        arquivo.close();
    } else {
        cout << "Não foi possível abrir o arquivo de pontuação." << endl;
    }
}

void Jogo::gerarNovoNivel(Mapa* mapa) {
    int tamanhoMapa = 5 + nivelAtual * 2; // Aumenta o tamanho do mapa a cada nível

    for (int i = 0; i < tamanhoMapa; i++) {
        int randomEvent = rand() % 100; // Gera um número entre 0 e 99

        // Reduz as chances de encontrar armas e poções conforme o nível aumenta
        int chanceInimigo = min(30 + nivelAtual * 2, 50);   // Aumenta a chance de encontrar inimigos, max 50%
        int chanceArma = max(20 - nivelAtual, 5);           // Diminui a chance de encontrar armas, min 5%
        int chancePocao = max(30 - nivelAtual, 5);          // Diminui a chance de encontrar poções, min 5%
        int chanceVazio = 100 - chanceInimigo - chanceArma - chancePocao; // Resto da chance é para espaços vazios

        if (randomEvent < chanceInimigo) {
            mapa->adicionarSqm("inimigo");
        } else if (randomEvent < chanceInimigo + chanceArma) {
            mapa->adicionarSqm("arma");
        } else if (randomEvent < chanceInimigo + chanceArma + chancePocao) {
            mapa->adicionarSqm("pocao");
        } else {
            mapa->adicionarSqm("vazio");
        }
    }
}
