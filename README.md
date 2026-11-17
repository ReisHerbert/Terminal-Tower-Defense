# 🏰 Tower Defense no Terminal

Jogo **sem fim** em que o objetivo é fazer o máximo de pontos defendendo o castelo dos inimigos. Tudo roda no terminal: o mapa é lido de um arquivo texto e exibido como uma matriz de caracteres.

> **Tema 2** — Projeto da disciplina de _[nome da disciplina]_ · _[Instituição]_
> **Autor(es):** _[nomes]_ · **Linguagem:** C (C99 ou superior) · **Extra:** interface gráfica com [raylib](https://www.raylib.com/)

---

## 📑 Sumário

1. [Visão geral](#-visão-geral)
2. [Requisitos funcionais](#-requisitos-funcionais)
3. [Regras do jogo](#-regras-do-jogo)
4. [Especificação do mapa](#-especificação-do-mapa-f1)
5. [Torres](#-torres-f2)
6. [Inimigos e fases](#-inimigos-e-fases-f3-f6)
7. [Economia e pontuação](#-economia-e-pontuação-f4-f5)
8. [Ranking persistente](#-ranking-persistente-f7)
9. [Estrutura do projeto](#-estrutura-sugerida-do-projeto)
10. [Estruturas de dados sugeridas](#-estruturas-de-dados-sugeridas)
11. [Fluxo do jogo](#-fluxo-do-jogo)
12. [Extra: interface gráfica com raylib](#-extra-interface-gráfica-com-raylib)
13. [Como compilar e executar](#-como-compilar-e-executar)
14. [Como jogar (controles)](#-como-jogar-controles)
15. [Casos de teste e validações](#-casos-de-teste-e-validações)
16. [Checklist de entrega](#-checklist-de-entrega)

---

## 🎯 Visão geral

O jogador defende um castelo posicionando torres em terrenos livres. A cada fase, uma nova onda de inimigos percorre o caminho até o castelo. Inimigos mortos geram pontos e moedas; inimigos que chegam ao castelo causam dano. O jogo só termina quando a vida do castelo chega a **zero**, e a pontuação final entra em um **ranking salvo em arquivo**.

---

## ✅ Requisitos funcionais

| ID | Requisito | Descrição |
|----|-----------|-----------|
| **F1** | Mapa | Lido de arquivo texto e exibido em matriz de caracteres, com caminhos, terrenos livres e o castelo |
| **F2** | Torres | O jogador compra e posiciona torres em terrenos livres; **no mínimo 3 tipos**, com dano, alcance e custo distintos |
| **F3** | Inimigos | Cada fase gera **mais inimigos e com mais vida**; seguem até o castelo e **nunca atacam as torres** |
| **F4** | Dano ao castelo | Ao chegar, o inimigo causa dano **igual à vida que ainda tinha**; a vida do castelo **não se recupera** |
| **F5** | Economia e pontuação | Cada inimigo morto dá **1 ponto** de ranking e **100 moedas** para comprar torres |
| **F6** | Fases | O jogo avança **sem limite de fases** e termina somente quando a vida do castelo chega a zero |
| **F7** | Ranking persistente | A pontuação final é gravada em arquivo e as melhores são exibidas em **ordem decrescente** |

---

## 📜 Regras do jogo

- O jogo é **infinito**: não existe vitória, apenas a melhor pontuação possível.
- Inimigos **ignoram as torres** — apenas seguem o caminho até o castelo.
- Inimigo que chega ao castelo **some** e causa dano = sua vida atual (um inimigo ferido causa menos dano).
- A vida do castelo **nunca aumenta**.
- Moedas só são obtidas matando inimigos (100 por inimigo). Defina e documente as **moedas iniciais** (ex.: 300).
- Torres só podem ser colocadas em **terreno livre** (nunca no caminho, no castelo ou sobre outra torre).
- Fim de jogo: vida do castelo ≤ 0 → registrar pontuação → exibir ranking.

---

## 🗺️ Especificação do mapa (F1)

O mapa é carregado de um arquivo `.txt` (ex.: `mapas/mapa1.txt`) e mostrado como matriz de caracteres.

### Legenda sugerida

| Caractere | Significado |
|-----------|-------------|
| `#` | Caminho dos inimigos |
| `.` | Terreno livre (pode receber torre) |
| `C` | Castelo |
| `E` | Entrada/ponto de spawn dos inimigos |
| `1` `2` `3` | Torres (tipos 1, 2 e 3) |
| `*` | Inimigo (exibido durante a fase) |

### Exemplo de arquivo de mapa

```
10 20
E###................
...#................
...#######..........
.........#..........
.........#..........
.........#####......
.............#......
.............#######C
....................
....................
```

- A primeira linha informa **linhas e colunas** (ou defina outro formato e documente).
- **Validações obrigatórias ao carregar:**
  - arquivo existe e pôde ser aberto;
  - dimensões coerentes com o conteúdo;
  - existe exatamente **um castelo** e **uma entrada**;
  - existe **caminho contínuo** da entrada ao castelo;
  - não há caracteres inválidos.
- O caminho deve ser extraído do mapa como uma **lista ordenada de coordenadas**, usada para mover os inimigos.

---

## 🗼 Torres (F2)

Mínimo de **três tipos**, com atributos distintos. Sugestão (ajuste o balanceamento como preferir):

| Tipo | Nome | Custo | Dano | Alcance | Característica |
|------|------|-------|------|---------|----------------|
| 1 | Arqueira | 100 | 10 | 3 | Barata e equilibrada |
| 2 | Canhão | 200 | 30 | 2 | Alto dano, curto alcance |
| 3 | Mago | 300 | 15 | 5 | Longo alcance |

**Regras:**
- Posicionar = informar linha e coluna em terreno livre, com moedas suficientes.
- Alcance medido por distância (ex.: Manhattan ou Euclidiana) — **escolha uma e documente**.
- A cada tick, cada torre ataca um inimigo ao alcance (ex.: o mais avançado no caminho).
- Torres **não são destruídas** (inimigos nunca as atacam).

---

## 👾 Inimigos e fases (F3, F6)

- Cada fase gera uma onda com **mais inimigos e mais vida** que a anterior.
- Fórmula sugerida (documente a sua):
  - `quantidade = 5 + 2 * (fase - 1)`
  - `vida = 20 + 10 * (fase - 1)`
- Inimigos são gerados de forma escalonada (um a cada _n_ ticks) a partir da entrada.
- A fase termina quando **todos** os inimigos foram mortos ou chegaram ao castelo.
- Entre as fases, o jogador pode **comprar e posicionar torres** antes de iniciar a próxima.
- Não há limite de fases.

---

## 💰 Economia e pontuação (F4, F5)

| Evento | Efeito |
|--------|--------|
| Inimigo morto | **+1 ponto** de ranking e **+100 moedas** |
| Inimigo chega ao castelo | Castelo perde vida **igual à vida restante do inimigo** |
| Vida do castelo ≤ 0 | Fim de jogo |

- Defina a **vida inicial do castelo** (ex.: 100) e as **moedas iniciais** no código como constantes.

---

## 🏆 Ranking persistente (F7)

- Ao fim do jogo, pedir o **nome do jogador** e gravar `nome pontuação` em arquivo (ex.: `ranking.txt`).
- Se o arquivo não existir, criá-lo.
- Exibir as **melhores pontuações em ordem decrescente** (ex.: top 10).
- Tratar empates (ex.: manter ordem de inserção ou ordenar por nome).
- Tratar arquivo corrompido/vazio sem travar o programa.

Exemplo de `ranking.txt`:

```
Ana 42
Joao 37
Maria 15
```

Exibição:

```
=== RANKING ===
1. Ana ........ 42
2. Joao ....... 37
3. Maria ...... 15
```

---

## 📁 Estrutura sugerida do projeto

```
tower-defense/
├── README.md
├── Makefile
├── mapas/
│   └── mapa1.txt
├── ranking.txt           # gerado automaticamente
├── include/
│   ├── mapa.h  torre.h  inimigo.h  jogo.h  ranking.h
│   └── render.h          # interface de renderização (terminal ou raylib)
├── src/
│   ├── main.c            # menu e loop principal
│   ├── mapa.c            # leitura, validação e exibição (F1)
│   ├── torre.c           # tipos, compra e ataque (F2)
│   ├── inimigo.c         # geração, movimento e vida (F3, F4)
│   ├── jogo.c            # fases, economia, fim de jogo (F5, F6)
│   ├── ranking.c         # gravação, leitura e ordenação (F7)
│   ├── render_terminal.c # saída em ASCII (obrigatório)
│   └── render_raylib.c   # saída gráfica (extra, opcional)
└── docs/
    └── relatorio.pdf     # (se exigido)
```

> **Boa prática:** mantenha a **lógica do jogo separada da renderização**. Assim, o mesmo núcleo (`mapa`, `torre`, `inimigo`, `jogo`, `ranking`) serve ao terminal e ao raylib sem duplicar código.

---

## 🧱 Estruturas de dados sugeridas

```c
// Exemplo em C
typedef struct { int linha, coluna; } Posicao;

typedef struct {
    int tipo, custo, dano, alcance;
    Posicao pos;
} Torre;

typedef struct {
    int vida;
    int indiceCaminho;   // posição atual na lista do caminho
    int ativo;
} Inimigo;

typedef struct {
    char **grade;
    int linhas, colunas;
    Posicao *caminho;    // do spawn até o castelo
    int tamCaminho;
    Posicao castelo;
} Mapa;

typedef struct {
    int vidaCastelo, moedas, pontos, fase;
} Estado;

typedef struct { char nome[50]; int pontos; } RegistroRanking;
```

---

## 🔁 Fluxo do jogo

```
Menu principal
 ├── Jogar
 │    ├── Carregar mapa (F1)
 │    └── Loop de fases (F6)
 │         ├── Fase de preparação: comprar/posicionar torres (F2)
 │         ├── Fase de combate: tick a tick
 │         │     ├── gerar inimigos (F3)
 │         │     ├── mover inimigos pelo caminho
 │         │     ├── torres atacam
 │         │     ├── mortes → +1 ponto, +100 moedas (F5)
 │         │     └── chegada ao castelo → dano (F4)
 │         └── vida do castelo > 0 ? próxima fase : fim de jogo
 ├── Ver ranking (F7)
 └── Sair
```

Dica: use um **loop por ticks** (ex.: `sleep`/`usleep` de ~300 ms) e limpe/redesenhe o terminal a cada tick.

---

## ✨ Extra: interface gráfica com raylib

A versão em **terminal é a entrega principal** e deve cumprir F1–F7 sozinha. O raylib é um **bônus**: uma segunda forma de exibir o mesmo jogo.

**Regras para não comprometer a entrega:**
- O jogo **deve compilar e rodar sem raylib** (versão terminal). Use compilação condicional (`#ifdef USE_RAYLIB`) ou alvos separados no Makefile.
- A lógica (F1–F7) **não pode depender** de funções do raylib.
- O mapa continua sendo **lido do arquivo texto** (F1) e o ranking continua **gravado em arquivo** (F7).

**Ideias para a versão gráfica:**
- Desenhar o mapa em grade com `DrawRectangle` (cores para caminho, terreno livre e castelo).
- Torres e inimigos como formas/sprites; barra de vida sobre cada inimigo.
- Círculo de alcance ao posicionar/selecionar uma torre (`DrawCircleLines`).
- Posicionar torres com o **mouse** (`GetMousePosition` + `IsMouseButtonPressed`) convertendo pixel → célula da grade.
- HUD com vida do castelo, moedas, pontos e número da fase (`DrawText`).
- Tela de ranking e de _game over_.
- Efeitos: projéteis, sons (`InitAudioDevice`), animações simples.

**Esqueleto do loop principal (raylib):**

```c
#include "raylib.h"

int main(void) {
    InitWindow(960, 640, "Tower Defense");
    SetTargetFPS(60);

    // carregar mapa e iniciar estado do jogo aqui

    while (!WindowShouldClose()) {
        float dt = GetFrameTime();
        // atualizar_jogo(&estado, dt);   // mesma lógica do terminal

        BeginDrawing();
            ClearBackground(RAYWHITE);
            // desenhar_mapa(...); desenhar_torres(...); desenhar_inimigos(...); desenhar_hud(...);
        EndDrawing();
    }

    CloseWindow();
    return 0;
}
```

---

## ⚙️ Como compilar e executar

**Requisitos:** `gcc` (ou `clang`), `make`, terminal com suporte a ASCII (e ANSI, se usar cores). Para o extra: biblioteca **raylib** instalada.

### Versão terminal (principal)

```bash
gcc -std=c99 -Wall -Wextra -o tower src/*.c   # ajuste para excluir render_raylib.c
./tower mapas/mapa1.txt
```

### Versão gráfica (extra, com raylib)

```bash
# Linux
gcc -std=c99 -Wall -Wextra -DUSE_RAYLIB -o tower_gui src/*.c -lraylib -lm -lpthread -ldl -lrt -lX11

# Windows (MinGW)
gcc -std=c99 -DUSE_RAYLIB -o tower_gui.exe src/*.c -lraylib -lopengl32 -lgdi32 -lwinmm

# macOS
gcc -std=c99 -DUSE_RAYLIB -o tower_gui src/*.c -lraylib -framework IOKit -framework Cocoa -framework OpenGL
```

### Exemplo de Makefile

```make
CC      = gcc
CFLAGS  = -std=c99 -Wall -Wextra -Iinclude
CORE    = src/main.c src/mapa.c src/torre.c src/inimigo.c src/jogo.c src/ranking.c

all: tower

tower: $(CORE) src/render_terminal.c
	$(CC) $(CFLAGS) -o $@ $^

gui: $(CORE) src/render_raylib.c
	$(CC) $(CFLAGS) -DUSE_RAYLIB -o tower_gui $^ -lraylib -lm -lpthread -ldl -lrt -lX11

clean:
	rm -f tower tower_gui
```

> Instalação do raylib: veja o guia oficial em <https://github.com/raysan5/raylib>.

---

## 🎮 Como jogar (controles)

| Ação | Entrada |
|------|---------|
| Comprar torre | Escolher tipo (1, 2 ou 3) |
| Posicionar torre | Informar `linha coluna` |
| Iniciar fase | Tecla/opção "iniciar" |
| Sair | Opção no menu |

_(Ajuste conforme a sua interface.)_

**Versão raylib:** clique com o mouse na célula desejada para posicionar a torre; teclas `1`, `2` e `3` selecionam o tipo; `ESPAÇO` inicia a fase.

---

## 🧪 Casos de teste e validações

- [ ] Mapa inexistente ou inválido → mensagem de erro, sem travar
- [ ] Mapa sem castelo, sem entrada ou sem caminho contínuo → rejeitado
- [ ] Torre em caminho, castelo ou posição ocupada → recusada
- [ ] Torre fora dos limites do mapa → recusada
- [ ] Compra sem moedas suficientes → recusada
- [ ] Inimigo morto dá exatamente **+1 ponto** e **+100 moedas**
- [ ] Inimigo ferido causa dano = vida restante (não a vida inicial)
- [ ] Vida do castelo nunca aumenta
- [ ] Fase seguinte tem mais inimigos e mais vida
- [ ] Jogo só termina com vida do castelo = 0
- [ ] Ranking criado se não existir, gravado ao fim e ordenado do maior para o menor
- [ ] Sem vazamento de memória (`valgrind`) e sem estouro de buffer na leitura do mapa
- [ ] Versão terminal compila e roda **sem** raylib instalado
- [ ] _(Extra)_ Versão raylib exibe o mesmo comportamento da versão terminal

---

## 📦 Checklist de entrega

- [ ] Código-fonte organizado e comentado
- [ ] Todos os requisitos **F1–F7** implementados
- [ ] Pelo menos **um mapa** de exemplo em `mapas/`
- [ ] README atualizado (compilação, controles)
- [ ] Programa compila sem _warnings_ (`-Wall -Wextra`)
- [ ] _(Extra)_ Versão raylib funcionando e instruções de instalação documentadas
- [ ] Ranking funcionando entre execuções
- [ ] _(Se exigido)_ relatório / vídeo de demonstração

---

## 👥 Autores

- _[Nome 1]_ — _[matrícula]_
- _[Nome 2]_ — _[matrícula]_