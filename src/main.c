#include <stdio.h>
#include "mapa.h"

int main() {
    //*--------------------------------F1--------------------------------*//

    Mapa mapa;  //criar a variavel que vai guardar o mapa

    int opcao;
    printf("Bem-vindo ao Tower Defense!\n");
    printf(">digite 1 para escolher o mapa 1\n");
    printf(">digite 2 para escolher o mapa 2\n");
    printf(">digite 3 para escolher o mapa 3\n");
    printf(">digite 4 para escolher o mapa 4\n");
    printf(">digite 5 para escolher o mapa 5\n");
    printf("Escolha o mapa: \n");
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