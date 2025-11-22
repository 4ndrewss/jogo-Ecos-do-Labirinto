#include "ranking.h"
#include <stdio.h>

static long pontuacaoTotal = 0;

#define BASE_ACERTO 5000
#define PENALIDADE_ERRO -2000
#define PENALIDADE_TEMPO -3000
#define MULTIPLICADOR_TEMPO 100

void iniciarPontuacao() {
    pontuacaoTotal = 0;
}

long pegarPontuacao() {
    return pontuacaoTotal;
}

long calcularBonusTempo(int segundos) {
    if (segundos <= 0) {
        return 0;
    }
    return MULTIPLICADOR_TEMPO + calcularBonusTempo(segundos - 1);
}

void atualizarPontuacao(int evento, int tempoRestante) {
    switch (evento) {
        case eventoPerguntaAcerto:
            pontuacaoTotal += BASE_ACERTO;
            pontuacaoTotal += calcularBonusTempo(tempoRestante);
            break;

        case eventoPerguntaErro:
            pontuacaoTotal += PENALIDADE_ERRO;
            break;

        case eventoTempoEsgotado:
            pontuacaoTotal += PENALIDADE_TEMPO;
            break;
    }
    if (pontuacaoTotal < 1) pontuacaoTotal = 1; 
}

