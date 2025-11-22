#ifndef MAPA_H
#define MAPA_H

typedef struct {
    char **dados; 
    int largura;
    int altura;
} Mapa;

Mapa* criarMapa(int largura, int altura);
void carregarFase(Mapa* m, int fase);
void destruirMapa(Mapa* m);
void desenharMapa(Mapa* m);
int verificarColisao(Mapa* m, int x, int y);

#endif