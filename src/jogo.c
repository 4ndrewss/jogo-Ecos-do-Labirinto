#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "jogo.h"
#include "mapa.h"
#include "screen.h"
#include "keyboard.h"
#include "timer.h"
#include "ranking.h"

Jogador player;
Mapa* mapaAtual;
EstadoJogo estado;
int tempoRestante;
Pergunta perguntaAtual;

void carregarPergunta() {
    if (player.faseAtual == 1) {
        strcpy(perguntaAtual.pergunta,
        "Se eu não encontrar a saída rápido, vou falhar.\n"
        "Se eu falhar... nunca vou conseguir sair daqui.\n"
        "Logo, eu preciso correr ou estou perdido para sempre.\n"
        "Este argumento é um exemplo de:");

        strcpy(perguntaAtual.opcoes[0], "1) Um Modus Tollens valido");
        strcpy(perguntaAtual.opcoes[1], "2) Um Sofisma / Falacia");
        strcpy(perguntaAtual.opcoes[2], "3) Um Silogismo Aristotelico bem formado");
        strcpy(perguntaAtual.opcoes[3], "4) Uma Deducao Correta");

        perguntaAtual.respostaCorreta = '2';
    }
    else if (player.faseAtual == 2) {
        strcpy(perguntaAtual.pergunta,
        "Se nunca errei antes, então não estou errado agora.\n"
        "Se estou certo... não preciso questionar nada.\n"
        "Logo, questionar e perda de tempo.\n"
        "Este argumento é um exemplo de:");

        strcpy(perguntaAtual.opcoes[0], "1) Um Modus Tollens valido");
        strcpy(perguntaAtual.opcoes[1], "2) Um Sofisma / Falacia");
        strcpy(perguntaAtual.opcoes[2], "3) Um Silogismo Aristotelico bem formado");
        strcpy(perguntaAtual.opcoes[3], "4) Uma Deducao Correta");

        perguntaAtual.respostaCorreta = '2';
    }
    else if (player.faseAtual == 3) {
        strcpy(perguntaAtual.pergunta,
        "Se o labirinto tem uma saida, então ela é visível.\n"
        "A saída não é visível.\n"
        "Logo... talvez não exista nenhuma saída.\n"
        "Este argumento é um exemplo de:");

        strcpy(perguntaAtual.opcoes[0], "1) Um Modus Tollens valido");
        strcpy(perguntaAtual.opcoes[1], "2) Um Sofisma / Falacia");
        strcpy(perguntaAtual.opcoes[2], "3) Uma Deducao por analogia");
        strcpy(perguntaAtual.opcoes[3], "4) Uma Falacia por negacao absoluta");

        perguntaAtual.respostaCorreta = '1';
    }
}

void resetarFaseJogo() {
    for(int y = 0; y < mapaAtual->altura; y++) {
        for(int x = 0; x < mapaAtual->largura; x++) {
            if(mapaAtual->dados[y][x] == 'S') {
                player.x = GAME_MINX + x;
                player.y = GAME_MINY + y;
                break;
            }
        }
    }
    tempoRestante = 60; 
}

void desenharTexto(int y, char* texto) {
    int len = strlen(texto);
    int x = (MAXX - len) / 2;
    if (x < GAME_MINX) x = GAME_MINX;
    screenGotoxy(x, y);
    printf("%s", texto);
}

void desenharHUD() {
    screenSetColor(YELLOW, BLACK);
    screenGotoxy(GAME_MINX, GAME_MAXY);
    
    printf("Fase: %d | Tempo: %02d s | Score: %06ld | Pos: %02d,%02d     ", 
            player.faseAtual, 
            tempoRestante, 
            pegarPontuacao(),
            player.x, player.y);
}

void desenharPergunta() {
    screenInit(1); 
    screenSetColor(WHITE, BLACK);
    
    int yAtual = (GAME_MAXY/2) - 6;
    
    desenharTexto(yAtual, "=== GUARDIAO DA FASE ===");
    yAtual += 2;

    char bufferTexto[300];
    strcpy(bufferTexto, perguntaAtual.pergunta);
    
    char linhaParaImprimir[80] = ""; 
    char *palavra = strtok(bufferTexto, " \n"); 
    
    while(palavra != NULL) {
        if (strlen(linhaParaImprimir) + strlen(palavra) + 1 > 60) {
            desenharTexto(yAtual, linhaParaImprimir);
            yAtual++; 
            strcpy(linhaParaImprimir, ""); 
        }
        strcat(linhaParaImprimir, palavra);
        strcat(linhaParaImprimir, " ");
        palavra = strtok(NULL, " \n");
    }
    
    if (strlen(linhaParaImprimir) > 0) {
        desenharTexto(yAtual, linhaParaImprimir);
        yAtual++;
    }

    yAtual += 2; 
    
    int maiorTamanho = 0;
    for(int i=0; i<4; i++) {
        int len = strlen(perguntaAtual.opcoes[i]);
        if (len > maiorTamanho) maiorTamanho = len;
    }

    int xOpcoes = (MAXX - maiorTamanho) / 2;
    if (xOpcoes < GAME_MINX + 2) xOpcoes = GAME_MINX + 2;

    for(int i=0; i<4; i++) {
        screenGotoxy(xOpcoes, yAtual + i);
        printf("%s", perguntaAtual.opcoes[i]);
    }
    
    yAtual += 6;
    char textoInput[] = "Escolha (1, 2, 3, 4): ";
    int xInput = (MAXX - strlen(textoInput)) / 2;
    screenGotoxy(xInput, yAtual);
    printf("%s", textoInput);
    screenGotoxy(xInput + strlen(textoInput), yAtual);
}

void desenharResultado(char* titulo, char* msg1, char* msg2, int corTitulo) {
    screenClear(); 
    
    screenSetColor(corTitulo, BLACK);
    screenDrawBorders();
    
    int xTitulo = (MAXX - strlen(titulo)) / 2;
    if (xTitulo < 1) xTitulo = 1;
    screenGotoxy(xTitulo, GAME_MAXY / 2 - 3);
    printf("%s", titulo);
    
    screenSetColor(WHITE, BLACK);
    int xMsg1 = (MAXX - strlen(msg1)) / 2;
    if (xMsg1 < 1) xMsg1 = 1;
    screenGotoxy(xMsg1, GAME_MAXY / 2 - 1);
    printf("%s", msg1);

    if (strlen(msg2) > 0) {
        int xMsg2 = (MAXX - strlen(msg2)) / 2;
        if (xMsg2 < 1) xMsg2 = 1;
        screenGotoxy(xMsg2, GAME_MAXY / 2);
        printf("%s", msg2);
    }
    
    char* continueMsg = "[ Pressione qualquer tecla para continuar ]";
    int xCont = (MAXX - strlen(continueMsg)) / 2;
    screenGotoxy(xCont, GAME_MAXY / 2 + 4);
    screenSetColor(LIGHTGRAY, BLACK);
    printf("%s", continueMsg);
    
    screenUpdate();
    
    while(keyhit()) readch(); 
    while(!keyhit());         
    readch();                 
}

void desenharMenu() {
    screenClear();
    screenDrawBorders();
    
    int centroY = GAME_MAXY / 2;

    screenSetColor(GREEN, BLACK);
    desenharTexto(centroY - 6, "Ecos do Labirinto");
    
    screenSetColor(CYAN, BLACK); 
    desenharTexto(centroY - 3, "Onde a pressa parece razão,");
    desenharTexto(centroY - 2, "o orgulho parece certeza,");
    desenharTexto(centroY - 1, "e até a lógica pode esconder a verdadeira ilusão.");
    
    screenSetColor(LIGHTGRAY, BLACK);
    desenharTexto(centroY + 3, "[ Pressione qualquer tecla para entrar ]");
    
    screenSetColor(DARKGRAY, BLACK); 
    desenharTexto(GAME_MAXY - 3, "Feito por: Andrews Queiroz, Arthur Marques, Hilton Resende,");
    desenharTexto(GAME_MAXY - 2, "Pedro Henrique Cavalcanti, Enzo Amorim & Gustavo Veloso");
    
    screenUpdate();
    
    while(keyhit()) readch();
    while(!keyhit());
    readch();
}

void inicializarJogo() {
    screenInit(1);
    keyboardInit();
    timerInit(100);
    iniciarPontuacao(); 

    player.faseAtual = 1;
    mapaAtual = criarMapa(76, 21);
    carregarFase(mapaAtual, player.faseAtual);
    
    resetarFaseJogo(); 
    
    estado = estadoJogando;
}

void rodarJogo() {
    int ch = 0;
    int frames = 0;
    int precisaRedesenhar = 1;

    desenharMapa(mapaAtual);
    desenharHUD();

    while (ch != 27) { 
        if (keyhit()) {
            ch = readch();
            
            if (estado == estadoJogando) {
                int nextX = player.x;
                int nextY = player.y;

                if (ch == 'w' || ch == 'W') nextY--;
                if (ch == 's' || ch == 'S') nextY++;
                if (ch == 'a' || ch == 'A') nextX--;
                if (ch == 'd' || ch == 'D') nextX++;

                int colisao = verificarColisao(mapaAtual, nextX, nextY);
                
                if (colisao == 0) { 
                    screenGotoxy(player.x, player.y);
                    printf(" "); 
                    player.x = nextX;
                    player.y = nextY;
                } else if (colisao == 2) { 
                    estado = estadoPergunta;
                    carregarPergunta();
                    precisaRedesenhar = 1;
                }
            } 
            // O ELSE IF das perguntas deve estar alinhado com if(estadoJogando)
            else if (estado == estadoPergunta) {
                if (ch >= '1' && ch <= '4') {
                    if (ch == perguntaAtual.respostaCorreta) {
                        atualizarPontuacao(eventoPerguntaAcerto, tempoRestante);
                        
                        if (player.faseAtual == 3) {
                             desenharResultado("RESPOSTA CORRETA", "Voce enxerga a saida desse lugar...", "Você escapou.", GREEN);
                        } else {
                             desenharResultado("RESPOSTA CORRETA", "Um novo caminho se abre a sua frente...", "", GREEN);
                        }
                        
                        player.faseAtual++;
                        
                        if (player.faseAtual > 3) {
                            estado = estadoVitoria;
                            screenInit(1);
                        } else {
                            carregarFase(mapaAtual, player.faseAtual);
                            resetarFaseJogo(); 
                            estado = estadoJogando;
                            
                            screenInit(1);
                            desenharMapa(mapaAtual);
                            desenharHUD();
                        }
                    } else {
                        atualizarPontuacao(eventoPerguntaErro, 0);
                        desenharResultado("RESPOSTA INCORRETA", "Voce se encontra de volta no inicio do labirinto.", "", RED);
                        
                        resetarFaseJogo(); 
                        estado = estadoJogando;
                        
                        screenInit(1);
                        desenharMapa(mapaAtual);
                        desenharHUD();
                    }
                    precisaRedesenhar = 1;
                }
            }
            else if (estado == estadoVitoria) {
                break;
            }
        }

        if (timerTimeOver()) {
            if (estado == estadoJogando) {
                frames++;
                if (frames >= 10) { 
                    tempoRestante--;
                    frames = 0;
                    if (tempoRestante <= 0) {
                        atualizarPontuacao(eventoTempoEsgotado, 0);
                        desenharResultado("TEMPO ESGOTADO", "Apenas a lua ilumina o labirinto...", "Você se encontra de volta ao inicio.", RED);
                        resetarFaseJogo(); 
                        screenInit(1);
                        desenharMapa(mapaAtual);
                        desenharHUD();
                    }
                }
                screenSetColor(CYAN, BLACK);
                screenGotoxy(player.x, player.y);
                printf("ጸ"); 
                desenharHUD();
            }
            else if (estado == estadoPergunta) {
                if (precisaRedesenhar) { 
                    desenharPergunta();
                    precisaRedesenhar = 0;
                }
                frames++;
            } 
            else if (estado == estadoVitoria) {
                screenClear();
                
                long score = pegarPontuacao();
                int corFinal = WHITE;
                int centroY = GAME_MAXY / 2;
                
                if (score >= 22000) {
                    corFinal = CYAN;
                    screenSetColor(corFinal, BLACK);
                    screenDrawBorders();
                    
                    desenharTexto(centroY - 2, "Quem constrói a saída precisa antes ver as paredes.");
                    desenharTexto(centroY, "Agora eu sei: O rumo sempre foi meu.");
                } 
                else if (score >= 17500) {
                    corFinal = YELLOW;
                    screenSetColor(corFinal, BLACK);
                    screenDrawBorders();
                    
                    desenharTexto(centroY - 2, "O labirinto nunca precisou de paredes...");
                    desenharTexto(centroY, "Ele só precisava de alguém que acreditasse nelas.");
                }
                else if (score >= 10000) {
                    corFinal = YELLOW;
                    screenSetColor(corFinal, BLACK);
                    screenDrawBorders();
                    
                    desenharTexto(centroY - 2, "Respondi aos guardiões nas sombras...");
                    desenharTexto(centroY, "Mas eles só são reflexões de mim mesmo, não são?");
                }
                else {
                    corFinal = RED;
                    screenSetColor(corFinal, BLACK);
                    screenDrawBorders();
                    
                    desenharTexto(centroY - 2, "Meus pés tocaram o lado de fora, mas...");
                    desenharTexto(centroY, "Minha mente nunca saiu de lá.");
                }

                char msgPontos[256];
                sprintf(msgPontos, "PONTUACAO FINAL: %ld", score);
                
                screenSetColor(corFinal, BLACK);
                desenharTexto(centroY + 2, msgPontos);

                screenSetColor(WHITE, BLACK);
                desenharTexto(centroY + 4, "Fim de jogo.");

                screenUpdate();

                while(keyhit()) readch();
                while(!keyhit());
                readch();
                break;
            }
            screenUpdate();
        }
    }
}

void finalizarJogo() {
    destruirMapa(mapaAtual);
    keyboardDestroy();
    screenDestroy();
    timerDestroy();
}
