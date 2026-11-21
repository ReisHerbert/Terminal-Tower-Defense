#include <stdio.h>
#include <stdlib.h>
#include "mapa.h"

//Mapa *m recebe o endereco do struct; const garante que apenas estamos lendo o nome do arquivo sem altera-lo
int carregarMapa(Mapa *m, const char *caminho_arquivo) {

    //aqui tentamos abrir o arquivo no modo leitura (r)
    FILE *arquivo = fopen(caminho_arquivo, "r");
    if (arquivo == NULL) return 0;

    //aqui ele le a primeira linha do arquivo, onde ta o tamanho do mapa e guarda em qt_linhas e qt_colunas
    fscanf(arquivo, "%d %d", &m->qt_linhas, &m->qt_colunas);

    //aqui estamos alocando a matriz (comeca pela alocacao da coluna e depois das linhas a partir da coluna)
    m->matriz = malloc(m->qt_linhas * sizeof(char *));
    if (m->matriz == NULL) {
        fclose(arquivo);
        return 0;
    }
    for (int i = 0; i < m->qt_linhas; i++) {
        m->matriz[i] = malloc((m->qt_colunas + 1) * sizeof(char));
        if (m->matriz[i] == NULL) {
            for (int j = 0; j < i; j++) {
                free(m->matriz[j]);
            }
            free(m->matriz);
            fclose(arquivo);
            return 0;
        }
    }

    //aqui ele ta lendo o arquivo e armazenando na matriz alocada, alem de verificar e armazenar as posicoes da entrada e do castelo
    for (int i = 0; i < m->qt_linhas; i++) {
        fscanf(arquivo, "%s", m->matriz[i]);
        for (int j = 0; j < m->qt_colunas; j++) {
            if (m->matriz[i][j] == 'E') {
                m->posicao_entrada.linha = i;
                m->posicao_entrada.coluna = j;
            }
            if (m->matriz[i][j] == 'C') {
                m->posicao_castelo.linha = i;
                m->posicao_castelo.coluna = j;
            }
        }
    }
    fclose(arquivo);
    return 1;
}

//falta criar exibirMapa e liberarMapa

