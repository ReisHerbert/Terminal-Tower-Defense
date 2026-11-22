#include <stdio.h>
#include "mapa.h"

int main() {
    //*--------------------------------F1--------------------------------*//

    Mapa mapa;  //criar a variavel que vai guardar o mapa

    int opcao;
    printf("\nEscolha o mapa (1 para Mapa 1, 2 para Mapa 2, 3 para Mapa 3): ");
    scanf("%d", &opcao);

    char caminho[50];
    sprintf(caminho, "../mapas/mapa%d.txt", opcao);

    //aqui roda a funcao ao msm tempo q verifica se ela vai ser mesmo rodada
    if (!carregarMapa(&mapa, caminho)) {
        printf("\nerro ao carregar o mapa!");
        return 1;
    }

    exibirMapa(&mapa);

    liberarMapa(&mapa);
//*------------------------------------------------------------------------*//
    return 0;
}