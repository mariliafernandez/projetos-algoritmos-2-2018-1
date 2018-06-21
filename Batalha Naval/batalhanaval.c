#ifdef _WIN32
#include <Windows.h>
#else
#include <unistd.h>
#endif

#include <stdio.h>
#include <stdlib.h>
#include <locale.h>
#include <time.h>
#include <string.h>

typedef struct {
  int linha[6];
  int coluna[6];
  int tamanho;
  int direcao; //0 - Horizontal, 1 - Vertical
  int tiros;
  char* nome;
} Navio;

typedef struct {
  int linha;
  int coluna;
  char simbolo; //AGUA, ERROU, ACERTOU
  int temNavio;
} Posicao;

typedef struct {
  int ultimoTiro[2];
  int naviosAfundados;
  int virtual;
  int tipo;
  int tentativas;
  char nome[25];
  Navio navios[10];
  Posicao mapa[10][10];
} Jogador;

enum simbolos_mapa {AGUA=1, ACERTOU, ERROU} simbolo;
Navio navios[10];
Jogador jogador[2];

int qtdNavios=3, qtdJogadores;

// Limpa a tela do terminal
void clear (){
  #ifdef WIN32
    system("cls");
  #else
    system("clear");
  #endif
}

// Imprime o nome do jogo
void printBatalhaNaval() {
  clear();
  printf("\n\n\n\n\tXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXX\n");
  printf("\tXX\t\t\t\t\t\t\t\tXX\n");
  printf ("\tXX\tXXXXX    XXXX  XXXXXX   XXXX   XX     XX  XX   XXXX\tXX\n");
  printf ("\tXX\tXX  XX  XX  XX   XX    XX  XX  XX     XX  XX  XX  XX\tXX\n");
  printf ("\tXX\tXXXXX   XX  XX   XX    XX  XX  XX     XXXXXX  XX  XX\tXX\n");
  printf ("\tXX\tXX  XX  XXXXXX   XX    XXXXXX  XX     XX  XX  XXXXXX\tXX\n");
  printf ("\tXX\tXXXXX   XX  XX   XX    XX  XX  XXXXXX XX  XX  XX  XX\tXX\n");
  printf("\tXX\t\t\t\t\t\t\t\tXX\n");
  printf("\tXX\tXX    XX   XXXX   XX       XX   XXXX   XX\t\tXX\n");
  printf("\tXX\tXXXX  XX  XX  XX   XX     XX   XX  XX  XX\t\tXX\n");
  printf("\tXX\tXX XX XX  XX  XX    XX   XX    XX  XX  XX\t\tXX\n");
  printf("\tXX\tXX  XXXX  XXXXXX     XX XX     XXXXXX  XX\t\tXX\n");
  printf("\tXX\tXX    XX  XX  XX      XXX      XX  XX  XXXXXX\t\tXX\n");
  printf("\tXX\t\t\t\t\t\t\t\tXX\n");
  printf("\tXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXX\n\n");
}

// Gera o mapa inicial do jogo com as posições em branco
void inicializarMapa(int jogador_id) {
    int linha, coluna;
        for(linha=0 ; linha < 10 ; linha++ )
            for(coluna=0 ; coluna < 10 ; coluna++)
            {
              jogador[jogador_id].mapa[linha][coluna].linha = linha;
              jogador[jogador_id].mapa[linha][coluna].coluna = coluna;
              jogador[jogador_id].mapa[linha][coluna].simbolo = AGUA;
              jogador[jogador_id].mapa[linha][coluna].temNavio = 0;
            }
}

// Imprime o tabuleiro do jogador
void mostrarMapa(int jogador_id) {
    int linha, coluna;
        printf("\n\n\t\t1 \t2 \t3 \t4 \t5 \t6 \t7 \t8 \t9 \t10\n");
        for(linha=0 ; linha < 10 ; linha++ ){
            printf("\n\t%d",linha+1);
            for(coluna=0 ; coluna < 10; coluna++ ){
                if(jogador[jogador_id].mapa[linha][coluna].simbolo == AGUA){
                    printf("\t~");
                }else if(jogador[jogador_id].mapa[linha][coluna].simbolo == ERROU){
                    printf("\t*");
                }else if(jogador[jogador_id].mapa[linha][coluna].simbolo == ACERTOU){
                    printf("\tX");
                }
            }
            printf("\n");
        }
}

// Imprime o tabuleiro com os navios do jogador
void meuMapa(int jogador_id) {
    int linha, coluna;

        printf("\n\n");
        printf("\t\t1 \t2 \t3 \t4 \t5 \t6 \t7 \t8 \t9 \t10");
        printf("\n");

        for(linha=0 ; linha < 10 ; linha++ ){
            printf("\n\t%d",linha+1);
            for(coluna=0 ; coluna < 10; coluna++ ){
                if(jogador[jogador_id].mapa[linha][coluna].temNavio == 1){
                    printf("\t#");
                }else
                    printf("\t.");
            }
            printf("\n");
        }
}

// Classifica os navios de acordo com o tamanho
void setTipoNavio(int navio_id, int jogador_id) {
  jogador[jogador_id].navios[navio_id].nome = malloc(20*sizeof(char));
  int tamanho = jogador[jogador_id].navios[navio_id].tamanho;
  switch (tamanho) {
    case 2:
      strcpy(jogador[jogador_id].navios[navio_id].nome, "Submarino");
      break;
      case 3:
        strcpy(jogador[jogador_id].navios[navio_id].nome, "Contratorpedeiro");
        break;
        case 4:
          strcpy(jogador[jogador_id].navios[navio_id].nome, "Navio-tanque");
          break;
          case 5:
            strcpy(jogador[jogador_id].navios[navio_id].nome, "Porta-aviões");
            break;
            default:
              printf("Erro, tamanho nao definido\n");
  }
}

// Posiciona os navios no mapa
int posicionarNavio(int navio_id, int jogador_id) {
  int i, j;
  int linha = jogador[jogador_id].navios[navio_id].linha[0];
  int col = jogador[jogador_id].navios[navio_id].coluna[0];
  int tam = jogador[jogador_id].navios[navio_id].tamanho;

  if(jogador[jogador_id].navios[navio_id].direcao == 0) // HORIZONTAL
  {
    if(col+tam >= 10) { //  DIREITA OU ESQUERDA
      jogador[jogador_id].navios[navio_id].coluna[0]=col-tam+1;
      col = jogador[jogador_id].navios[navio_id].coluna[0];
    }
      for(i=col; i<col+tam; i++) {
        if((jogador[jogador_id].mapa[linha][i].temNavio == 0) & (i < 10)){
          jogador[jogador_id].mapa[linha][i].temNavio = 1;
          jogador[jogador_id].navios[navio_id].coluna[i-col] = i;
        }
        else // Desfaz as mudandas feitas no mapa
        {
          for(j=i-1; j>=col; j--) {
            jogador[jogador_id].mapa[linha][j].temNavio = 0;
            jogador[jogador_id].navios[navio_id].coluna[j-col] = -1;
          }
          return 0;
        }
      }
      return 1;
    }

  else { // jogador[jogador_id].navios[i].direcao = 1 --> VERTICAL
    if(linha+tam >= 10) { //DIREITA OU ESQUERDA
      jogador[jogador_id].navios[navio_id].linha[0]=linha-tam+1;
      linha = jogador[jogador_id].navios[navio_id].linha[0];
    }
    for(i=linha; i<linha+tam; i++)
    {
      if((jogador[jogador_id].mapa[i][col].temNavio == 0) & (i < 10)){
        jogador[jogador_id].mapa[i][col].temNavio = 1;
        jogador[jogador_id].navios[navio_id].linha[i-linha] = i;
      }
      else /* Desfaz as mudandas feitas no mapa */
      {
        for(j=i; j>=linha; j--) {
          jogador[jogador_id].mapa[j][col].temNavio = 0;
          jogador[jogador_id].navios[navio_id].linha[j-linha] = -1;
        }
        if(!jogador[jogador_id].virtual)
          printf("\nOs navios não podem se sobrepor. Escolha novamente.\n");
        return 0;
      }
    }
    return 1;
  }
}

// Gera coordenadas aleatórias para os navios
void iniciarNavios() {
        srand(time(NULL));
        int i, j, linha, col;

        for(i=0 ; i<qtdNavios; i++) {
          do {
            jogador[0].navios[i].direcao = rand()%2;
            jogador[0].navios[i].linha[0] = rand()%10;
            jogador[0].navios[i].coluna[0] = rand()%10;
            jogador[0].navios[i].tamanho = i+2; //  2 a 5
            jogador[0].navios[i].tiros=0;
            setTipoNavio(i, 0);
          } while(!posicionarNavio(i, 0)); // Jogador 2 = PC

          printf("%d %d, %s\n", jogador[0].navios[i].linha[0]+1, jogador[0].navios[i].coluna[0]+1, jogador[0].navios[i].nome);
        }
}

// Retorna qual o indice do navio que ocupa a posicao informada
int getNavioID(int coord[2], int jogador_id) {
    int nav=0, i;
    while(nav < qtdNavios) {
      if((jogador[jogador_id].navios[nav].direcao == 1) && (jogador[jogador_id].navios[nav].coluna[0] == coord[1])) { // VERTICAL
        for(i=0; i<jogador[jogador_id].navios[nav].tamanho; i++) {
          if(jogador[jogador_id].navios[nav].linha[i] == coord[0])
            return nav;
        }
      }
      else if((jogador[jogador_id].navios[nav].direcao == 0) && (jogador[jogador_id].navios[nav].linha[0] == coord[0])) { // HORIZONTAL
        for(i=0; i<jogador[jogador_id].navios[nav].tamanho; i++) {
          if(jogador[jogador_id].navios[nav].coluna[i] == coord[1])
            return nav;
        }
      }
      nav++;
    }
}

/* Verifica se a coordenada é válida para posicionar o navio.
  retorna 1 se é válida e está livre e 0 se for inválida ou
  estiver ocupada por outro navio. */
int checkPosicao(int linha, int coluna, int navio_id, int jogador_id) {
  if((linha >= 0) && (linha < 10) && (coluna >= 0) && (coluna < 10)) {
    if(jogador[jogador_id].mapa[linha][coluna].temNavio == 0) {
      jogador[jogador_id].navios[navio_id].linha[0] = linha;
      jogador[jogador_id].navios[navio_id].coluna[0] = coluna;
      return 1;
    }
    else {
      printf("\n\n\tEssa posição já está ocupada, escolha novamente\n");
      return 0;
    }
  }
  else {
    printf("\n\n\tPosição inválida, escolha novamente.\n");
    return 0;
  }
}

// Lê a coordenada do navio informada pelo jogador.
void posicionarManualmente(int jogador_id) {
  srand(time(NULL));
  int i;
  for(i=0; i<qtdNavios; i++) {
      do {
        clear();
        printf("\n\n\n\tComandante %s,\n\tposicione os seus navios:\n", jogador[jogador_id].nome);
        meuMapa(jogador_id);
        jogador[jogador_id].navios[i].tamanho = rand()%4+2;
        setTipoNavio(i, jogador_id);
        printf("\n\tNavio %d: %s (%d posiçẽes)\n", i+1, jogador[jogador_id].navios[i].nome, jogador[jogador_id].navios[i].tamanho);
        do {
          printf("\n\tLinha: ");
          scanf("%d", &jogador[jogador_id].navios[i].linha[0]);
          printf("\n\tColuna: ");
          scanf("%d", &jogador[jogador_id].navios[i].coluna[0]);
          jogador[jogador_id].navios[i].linha[0]--;
          jogador[jogador_id].navios[i].coluna[0]--;
        } while(!checkPosicao(jogador[jogador_id].navios[i].linha[0], jogador[jogador_id].navios[i].coluna[0], i, jogador_id));

        printf("\n\tPosição:\n\t[0]HORIZONTAL\n\t[1]VERTICAL\n\t");
        scanf("%d", &jogador[jogador_id].navios[i].direcao);
      }while(!(checkPosicao(jogador[jogador_id].navios[i].linha[0], jogador[jogador_id].navios[i].coluna[0], i, jogador_id)) & !(posicionarNavio(i, jogador_id)));
  }
  clear();
  printf("\n\n\n\tNavios posicionados.\n\tEste é o seu mapa:\n");
  meuMapa(jogador_id);
}

// Lê a coordenada do tiro informada pelo jogador e verifica se é válida.
void atirar(int tiro[2], int jogador_id) {
  if(qtdJogadores == 1)
    printf("\n\n\tComandante %s, ATIRAR!\n", jogador[0].nome);
  else if(jogador_id == 0)
      printf("\n\n\tComandante %s, ATIRAR!\n", jogador[1].nome);
    else
      printf("\n\n\tComandante %s, ATIRAR!\n", jogador[0].nome);

    do{
        mostrarMapa(jogador_id);
        do {
          printf("\n\n\tLinha de tiro: ");
          scanf("%d",&tiro[0]);
          fflush(stdin);
          if(tiro[0]<1 || tiro[0]>10)
            printf("\n\n\tLinha %d inexistente! Tente novamente.\n", tiro[0]);
        } while(tiro[0]<1 || tiro[0]>10);

      }while(tiro[0]<1 || tiro[0]>10);

        tiro[0]--;

        do {
          printf("\n\n\tColuna de tiro: ");
          scanf("%d",&tiro[1]);
          if(tiro[1]<1 || tiro[1]>10)
            printf("\n\n\tColuna %d inexistente! Tente novamente.\n", tiro[1]);
        } while(tiro[1]<1 || tiro[1]>10);

        tiro[1]--;

}

// Verifica se o navio afundou, retorna 1 se afundou e 0 se não afundou.
int afundou(int navio_id, int jogador_id, int oponente_id) {
  if(jogador[oponente_id].navios[navio_id].tiros == jogador[oponente_id].navios[navio_id].tamanho)
  {
    jogador[jogador_id].naviosAfundados++;
    return 1;
  }
  else
    return 0;
}

// Verifica se o jogador acertou o tiro, retorna 1 se acertou e 0 se errou.
int acertou(int tiro[2], int jogador_id) {
  int nav_id=getNavioID(tiro, jogador_id);
    if((jogador[jogador_id].mapa[tiro[0]][tiro[1]].temNavio)) {
      jogador[jogador_id].mapa[tiro[0]][tiro[1]].simbolo = ACERTOU;
      jogador[jogador_id].navios[nav_id].tiros++;
      return 1;
    }
    else {
      jogador[jogador_id].mapa[tiro[0]][tiro[1]].simbolo = ERROU;
      return 0;
    }
}

// Imprime na tela quantos navios há na linha e coluna da coordenada de tiro.
void dica(int coord[2], int tentativa, int jogador_id) {
        int linha=0,
            coluna=0,
            naviosNaLinha=0,
            naviosNaColuna=0,
            i, j;

        for(i=0 ; i<qtdNavios; i++){
          if(jogador[jogador_id].navios[i].direcao == 0) { // HORIZONTAL
            if(jogador[jogador_id].navios[i].linha[0] == coord[0])
              linha=1;
            for(j=0; j<jogador[jogador_id].navios[i].tamanho; j++) {
              if(jogador[jogador_id].navios[i].coluna[j] == coord[1])
                coluna=1;
            }
          }
          else { //VERTICAL
            if(jogador[jogador_id].navios[i].coluna[0] == coord[1])
              coluna=1;
            for(j=0; j<jogador[jogador_id].navios[i].tamanho; j++) {
              if(jogador[jogador_id].navios[i].linha[j] == coord[0])
                linha=1;
            }
          }
          if(linha==1) {
            naviosNaLinha++;
          }
          if(coluna==1) {
            naviosNaColuna++;
          }
          linha=0;
          coluna=0;
        }
        printf("\n\n\tDica %d: ", tentativa);
        printf("\n\tO seu último tiro foi em (%d, %d)", coord[0]+1, coord[1]+1);
        printf("\n\tlinha %d -> %d navios\n\tcoluna %d -> %d navios\n", coord[0]+1, naviosNaLinha, coord[1]+1, naviosNaColuna);
}

// Verifica se a coordenada do tiro é posição válida de ataque, retorna 1 se é válida e 0 se é inválida.
int verificarTiro(int tiro[2], int jogador_id) {
	if((jogador[jogador_id].mapa[tiro[0]][tiro[1]].simbolo == ACERTOU) || (jogador[jogador_id].mapa[tiro[0]][tiro[1]].simbolo == ERROU))
		return 0;
	else
		return 1;
}

// Libera a memória alocada.
void liberar(int qtdNavios) {
  int i;
  for(i=0; i<qtdNavios; i++) {
    free(jogador[0].navios[i].nome);
    free(jogador[1].navios[i].nome);
  }
}

// Verifica se o jogador ganhou o jogo, retorna 1 se ganhou e 0 se não ganhou.
int ganhou(int jogador_id) {
  if(jogador[jogador_id].naviosAfundados == qtdNavios)
    return 1;
  else
    return 0;
}

// Inicia o jogo.
void play(int qtdJogadores) {
  int jogador_id, tiro[2], espera = 1, nav_id, opcao = -1, oponente, rodadas=0;

  printBatalhaNaval();
  if(qtdJogadores > 1) {
    printf("\n\n\tJogador 1, digite o seu nome:\n\n\t");
    scanf("%s", jogador[0].nome);
    printf("\n\n\tJogador 2, digite o seu nome:\n\n\t");
    scanf("%s", jogador[1].nome);
  }
  else {
    printf("\n\n\tDigite o seu nome:\n\n\t");
    scanf("%s", jogador[0].nome);
  }

  for(jogador_id=0; jogador_id<qtdJogadores; jogador_id++) {
    inicializarMapa(jogador_id);
    if (qtdJogadores > 1){
      posicionarManualmente(jogador_id);
      if(espera) {
        if(jogador_id == 0)
          printf("\n\n\tDigite 0 para Comandante %s posicionar os navios.\n\t", jogador[jogador_id+1].nome);
        else
          printf("\n\n\tDigite 0 para começar a batalha.\n");
        scanf("%d", &espera);
      }
      espera=1;
    }
    else if(qtdJogadores == 1){ // jogadores=1
      jogador[jogador_id].virtual = 1;
      iniciarNavios();
    }
    jogador[jogador_id].naviosAfundados=0;
    jogador[jogador_id].tentativas=0;
  }
  jogador_id=0;
  clear();
  if(qtdJogadores > 1)
    printf("\n\n\n\tAtenção Comandantes");
  else
    printf("\n\n\n\tAtenção Comandante %s", jogador[0].nome);
  sleep(1);
  printf("\n\n\n\tPREPARAR");
  sleep(1);
  printf("\n\n\n\tAPONTAR");
  sleep(1);
  printf("\n\n\n\tFOGO!\n\n\n");
  sleep(1);

  while(ganhou(jogador_id)!=1){
      if(qtdJogadores > 1){ //  Para alternar as jogadas entre os jogadores
        if(rodadas%2 == 0) {
          jogador_id = 0;
          oponente = 1;
        }
        else {
          jogador_id = 1;
          oponente = 0;
        }
      }
      else {
        jogador_id=0;
        oponente=0;
      }

      clear();
      if(jogador[jogador_id].tentativas > 0)
        dica(jogador[jogador_id].ultimoTiro, jogador[jogador_id].tentativas, oponente);
      atirar(tiro, oponente);

      if(verificarTiro(tiro, oponente)) {
         jogador[jogador_id].tentativas++;
        if(acertou(tiro, oponente)) {
          clear();
          printf("\n\n\n\tFOGO! Você acertou o tiro (%d, %d) ", tiro[0]+1, tiro[1]+1);
          nav_id = getNavioID(tiro, oponente);
          if(afundou(nav_id, jogador_id, oponente)==1) {
            printf("\n\te derrubou um %s!\n", jogador[oponente].navios[nav_id].nome);
          }
          mostrarMapa(oponente);
        }
        else {
          clear();
          printf("\n\n\n\tO tiro (%d, %d) acertou o mar\n", tiro[0]+1, tiro[1]+1);
          mostrarMapa(oponente);
        }
        jogador[jogador_id].ultimoTiro[0] = tiro[0];
        jogador[jogador_id].ultimoTiro[1] = tiro[1];
        rodadas++;
        sleep(3);
      }
  }
  printf("\n\n\tParabéns, Comandante %s!\n\n\n\tVocê acertou os %d navios em %d tentativas!\n", jogador[jogador_id].nome, qtdNavios, jogador[jogador_id].tentativas);
  printf("\n\n\t[0] Voltar ao menu\n");
  printf("\t[1] Sair\n\n\t");

  do {
    scanf("%d", &opcao);
    switch (opcao) {
      case 0:
        menu();
      break;
      case 1:
        exit(1);
      break;
      default:
        printf("\nOpção Inválida. Digite novamente\n\n\t");
      break;
    }
  }while(opcao == -1);

  liberar(qtdNavios);
}

// Inicia o jogo com limite de tentativas.
void playTentativas(int MAX_TENTATIVAS) {
    int tiro[2], espera = 1, nav_id, opcao = -1, rodadas=0;

    printBatalhaNaval();
    printf("\n\n\tDigite o seu nome:\n\n\t");
    scanf("%s", jogador[0].nome);
    strcpy(jogador[1].nome, jogador[0].nome);

    inicializarMapa(0);
    jogador[1].virtual = 1;
    iniciarNavios();

    jogador[0].naviosAfundados=0;
    jogador[0].tentativas=0;

    clear();
    printf("\n\n\n\tAtenção Comandante %s", jogador[0].nome);
    sleep(1);
    printf("\n\n\n\tPREPARAR");
    sleep(1);
    printf("\n\n\n\tAPONTAR");
    sleep(1);
    printf("\n\n\n\tFOGO!\n\n\n");
    sleep(1);
    clear();
    while((ganhou(0)!=1)&(jogador[0].tentativas < MAX_TENTATIVAS)){

      if(jogador[0].tentativas > 0)
        dica(jogador[0].ultimoTiro, jogador[0].tentativas, 0);
      atirar(tiro, 0);

        if(verificarTiro(tiro, 0)) {
           jogador[0].tentativas++;
          if(acertou(tiro, 0)) {
            clear();
            printf("\n\n\n\tFOGO! Você acertou o tiro (%d, %d) ", tiro[0]+1, tiro[1]+1);
            nav_id = getNavioID(tiro, 0);
            if(afundou(nav_id, 0, 0)==1) {
              printf("\n\te derrubou um %s!\n", jogador[0].navios[nav_id].nome);
            }
          }
          else {
            clear();
            printf("\n\n\tO tiro (%d, %d) acertou o mar\n", tiro[0]+1, tiro[1]+1);
          }
          jogador[0].ultimoTiro[0] = tiro[0];
          jogador[0].ultimoTiro[1] = tiro[1];
          rodadas++;
        }
    }
    mostrarMapa(0);
    if(ganhou(0))
      printf("\n\n\tParabéns, Comandante %s!\n\n\n\tVocê acertou os %d navios em %d tentativas!\n", jogador[0].nome, qtdNavios, jogador[0].tentativas);
    else
      printf("\n\n\tVocê esgotou as %d tentativas.\n\tMais sorte da próxima vez, Comandante %s.\n", jogador[0].tentativas, jogador[0].nome);
    printf("\n\n\t[0] Voltar ao menu\n");
    printf("\t[1] Sair\n\n\t");

    do {
      scanf("%d", &opcao);
      switch (opcao) {
        case 0:
          menu();
        break;
        case 1:
          exit(1);
        break;
        default:
          printf("Opção Inválida.\n\n");
        break;
      }
    }while(opcao == -1);

    liberar(qtdNavios);
}

// Imprime as instruções do jogo na tela
void instrucoes() {
  printBatalhaNaval();
  printf("\n\n\tInstruções:\n\n");
  printf("\tO objetivo do jogo consiste em afundar todas as\n\tembarcações presentes no tabuleiro.\n\n");
  printf("\tAo final de cada rodada o jogador recebe uma dica sobre\n\ta presença de embarcações na linha/coluna atirada.\n\n");
  printf("\tNo modo desafiador, o jogador tem um certo numero de\n\ttentativas para derrubar todos os navios.\n\n\n\n");

  printf("\t[0] Voltar ao menu\n\n\t");

  while(getchar() != '0') {}
    menu();
}

void creditos() {
  clear();
  printBatalhaNaval();
  printf("\n\tDesenvolvido por:\n\t\tLarissa Martins\n\t\tMarília Fernandez\n\n\tProjeto final da disciplina de Algoritmos 2\n\tdo curso de Engenharia de Computação\n\n\tJunho, 2018\n\n\n\n");

  printf("\t[0] Voltar ao menu\n\n\t");

  while(getchar() != '0') {}
    menu();
}

// Imprime o menu do jogo na tela e retorna a opção escolhida
void menu() {
  int jogadores;
  int opcao;
  printBatalhaNaval();
  printf("\n\n\tMenu:\n\n");
  printf("\t0 - Instruções\n");
  printf("\t1 - 1 Jogador (modo livre)\n");
  printf("\t2 - 2 Jogadores\n");
  printf("\n\tModos desafiadores (1 jogador)");
  printf("\n\t3 - Fácil (50 tentativas)");
  printf("\n\t4 - Médio (30 tentativas)");
  printf("\n\t5 - Difícil (20 tentativas)");
  printf("\n\t6 - Créditos");
  printf("\n\t7 - Sair\n\n\t");

  do {
    scanf("%d", &opcao);
    fflush(stdin);

    switch(opcao) {
      case 0:
        instrucoes();
        break;
      case 1:
        qtdJogadores=1;
        play(1);
        break;
      case 2:
        qtdJogadores=2;
        play(2);
        break;
      case 3:
          playTentativas(50);
          break;
      case 4:
          playTentativas(30);
          break;
      case 5:
          playTentativas(20);
          break;
      case 6:
          creditos();
          break;
      case 7:
          exit(0);
          break;
        default:
        printf("Opção inválida.\n\t");
        break;
    }
  } while(1);

}
