#ifndef JOGO_H
#define JOGO_H
#include "screen.h"

typedef enum {
    estadoJogando,
    estadoPergunta,
    estadoVitoria,
} EstadoJogo;

typedef struct {
    int x, y;
    int startX, startY;
    int faseAtual;
} Jogador;

typedef struct {
    char pergunta[256];
    char opcoes[4][256];
    char respostaCorreta;
} Pergunta;

#define GAME_MINX (MINX + 1)
#define GAME_MINY (MINY + 1)
#define GAME_MAXX (MAXX - 1)
#define GAME_MAXY (MAXY - 1)

void desenharMenu();

void inicializarJogo();
void rodarJogo();
void finalizarJogo();

#endif