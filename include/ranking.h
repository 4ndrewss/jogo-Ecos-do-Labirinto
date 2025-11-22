#ifndef RANKING_H
#define RANKING_H

#define eventoPerguntaAcerto 1
#define eventoPerguntaErro   2
#define eventoTempoEsgotado  3

void iniciarPontuacao();

long pegarPontuacao();
void atualizarPontuacao(int evento, int tempoRestante);
long calcularBonusTempo(int segundos);
#endif