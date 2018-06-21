#ifndef BATALHANAVAL_H_INCLUDED
#define BATALHANAVAL_H_INCLUDED

void clear();
void printBatalhaNaval();
void inicializarMapa(int);
void mostrarMapa(int);
void meuMapa(int);
void tipoNavio(int, int);
int posicionarNavio(int, int);
void iniciarNavios();
int getNavioID(int, int);
int checkPosicao(int, int, int, int);
void posicionarManualmente(int);
void atirar(int, int);
int afundou(int, int);
int acertou(int, int);
void dica(int, int, int);
int verificarTiro(int, int);
void liberar(int);
int timeout (int);
int ganhou(int);
void play(int);
void playTentativas(int);
void instrucoes();
void menu();

#endif // BATALHANAVAL_H_INCLUDED
