#ifndef _ESTRUTURAS_DADOS_H_
#define _ESTRUTURAS_DADOS_H_

/* STRUCT para Filmes */
typedef struct FILMES
{
	int cod_filme; //codigo do filme
	char nome_filme[50]; //nome do filme
	char gen_filme[20]; //genero do filme
	char form_filme[10]; //formato do filme, e.g. 2D, 3D
	char data_filme[10]; //data do filme, e.g. dd-mm-aaaa
	int hora_filme; //horario do filme
	float valor_bilhete; //valor do bilhete
} FILMES;

/* STRUCT para Bilhetes */
typedef struct BILHETES
{
	//add um codigo_bilhetes
	int cod_bil_filme; //codigo do filme
	char nome_cliente[50]; //nome do cliente
	int tel_cliente; //telefone do cliente
	int poltrona; //alterar? poltrona 11, 12..
	float valor_bil_bilhete; //valor do bilhete
} BILHETES;

#endif