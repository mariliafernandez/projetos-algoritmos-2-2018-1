#ifndef _FUNCOES_ADICIONAIS_H_
#define _FUNCOES_ADICIONAIS_H_

/* ASSINATURA DAS FUNCOES ADICIONAIS */
void limpaTela();
FILMES *criarVetorFilmes(int);
BILHETES *criarVetorBilhetes(int);
void desalocarVetorFilmes(FILMES *); //somente desaloca vetores dinamicos do tipo FILMES
void desalocarVetorBilhetes(BILHETES *); //somente desaloca vetores dinamicos do tipo BILHETES

#endif