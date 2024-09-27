#include "Heroi.h"
#include "Jogo.h"
#include "Mapa.h"
#include "Elemento.h"
#include "Inimigo.h"

int main() {
    srand(time(0)); // Inicializa a semente para números aleatórios

    string nomeJogador;
    cout << "Digite o nome do heroi: ";
    getline(cin, nomeJogador);

    Heroi* heroi = new Heroi(nomeJogador, 100);

    Jogo jogo(heroi);
    jogo.iniciar();

    delete heroi;
    return 0;
}
