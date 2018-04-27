#include <stdlib.h>
#include <stdio.h>
#include "estruturas_dados.h"
#include "funcoes_principais.h"
#include "funcoes_adicionais.h"

int main(){
	/* CHAMANDO FUNCOES QUE CRIAM VETORES DINAMICOS */
	//criar vetor "lista de filmes"
	FILMES *lista_filmes;			//criar vetor dinamico do tipo FILMES que vai armazenar a lista de filmes
	int tam_vetor_filmes = 5;
	lista_filmes = criarVetorFilmes(tam_vetor_filmes);	//passar o tamanho do vetor
	if(lista_filmes != NULL){		// verificar se a alocacao foi bem sucedida
		//nao fazer nada, continuar com o programa
	}else{
		printf("Erro ao alocar memoria, saindo do programa...\n");
		return 0;					//sair do programa
	}

	//criar vetor "vetor de bilhetes" 
	BILHETES *vetor_bilhetes;
	int tam_vetor_bilhetes = 5;
	vetor_bilhetes = criarVetorBilhetes(tam_vetor_bilhetes);
	if(vetor_bilhetes != NULL){		// verificar se a alocacao foi bem sucedida
		//nao fazer nada, continuar com o programa
	}else{
		printf("Erro ao alocar memoria, saindo do programa...\n");
		return 0; 					//sair do programa
	}

	/* os ponteiros abaixo servem para contar em que posicao do vetor eu estou
	quando add um novo filme, assim, na primeira vez que add um novo filme ele valera 0,
	depois 1, etc, assim eu sei a partir de que posicao do vetor eu irei add um novo filme */
	int cont_parou_addFilme = 0; 
	int cont_parou_reservarBilhete = 0;

	int op;   //variavel para o menu
	int resp; //variavel para repetir o menu

	do{
		limpaTela();
		printf("   MENU PRINCIPAL \n\n");
		printf("1) Reservar bilhete\n");
		printf("2) Pesquisar bilhete\n");
		printf("3) Verificar poltronas\n");
		printf("4) Adicionar novo filme\n");
		printf("5) Editar filme\n");
		printf("6) Deletar filme\n");
		printf("7) Mostrar lista de filmes\n");
		printf("8) Sair do programa\n\n");

		printf("Escolha uma das opcoes acima: ");
		scanf("%d", &op);

		switch(op){
			case 1: //Reservar bilhete
				limpaTela();
				reservarBilhete(lista_filmes, vetor_bilhetes, &cont_parou_addFilme, &cont_parou_reservarBilhete, &tam_vetor_bilhetes);
			break;

			case 2: //Pesquisar bilhete
				limpaTela();
				buscarBilhete(lista_filmes, vetor_bilhetes, &cont_parou_addFilme, &cont_parou_reservarBilhete, &tam_vetor_bilhetes);
			break;

			case 3: //Verificar poltronas
				printf("Opcao 3\n");
			break;

			case 4: //Adicionar novo filme
				limpaTela();
				addFilme(lista_filmes, &cont_parou_addFilme); //respectivamente: nome do vetor, contador
			break;

			case 5: //Editar filme
				printf("Opcao 5\n");
			break;

			case 6: //Deletar filme
				printf("Opcao 6\n");
			break;

			case 7: //Mostrar lista de filmes
				limpaTela();
				mostrarListaFilmes(lista_filmes, &cont_parou_addFilme);
			break;

			case 8: //sair do programa
				printf("\nSaindo do programa...\n");
				return 0;
			break;

			default:
				printf("Opcao invalida.\n");
		}

	printf("\n--------------------");
	printf("\nDigite 0 para voltar ao Menu Principal e 1 para sair: ");
	scanf("%d", &resp);

	}while(resp == 0);

	/* desacolar blocos de memoria */
	desalocarVetorFilmes(lista_filmes);
	desalocarVetorBilhetes(vetor_bilhetes);

	return 0;
}
