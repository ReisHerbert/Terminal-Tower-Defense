#ifndef TERMINAL_TOWER_DEFENSE_MAPA_H
#define TERMINAL_TOWER_DEFENSE_MAPA_H

typedef struct _Posicao_ {
//a partir desse struct da p determinar a posicao (coordenada) de qualquer coisa dentro do mapa
    int linha;
    int coluna;

}Posicao;

typedef struct _Mapa_ {
//aqui armazenam informacoes sobre o mapa (matriz) e seus elementos (entrada e castelo)
    int qt_linhas;
    int qt_colunas;
    char **matriz;
    Posicao posicao_castelo;
    Posicao posicao_entrada;

}Mapa;
//declarando funcoes pro mapa rodar
int carregarMapa(Mapa *m, const char *caminho_arquivo);

void exibirMapa(const Mapa *m);

void liberarMapa(Mapa *m);

#endif //TERMINAL_TOWER_DEFENSE_MAPA_H