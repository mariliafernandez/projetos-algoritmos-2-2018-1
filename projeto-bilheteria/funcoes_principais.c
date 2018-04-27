#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include "estruturas_dados.h"

/* IMPLEMENTACAO DAS FUNCOES PRINCIPAIS */

void reservarBilhete(FILMES *lista_filmes, BILHETES *vetor_bilhetes, int *p_cont_parou_addFilme, int *p_cont_parou_reservarBilhete, int *qtd_bilhetes){
	// 1) imprimir lista basica dos filmes
	printf("# Lista basica de filmes cadastrados\n\n");
	int ate_onde = *p_cont_parou_addFilme;
	int i;
	for (i = 0; i < ate_onde; i++){
		printf("Codigo do filme: %d \n", lista_filmes[i].cod_filme);
		printf("Nome do filme: %s \n", lista_filmes[i].nome_filme);
		printf("Formato: %s \n", lista_filmes[i].form_filme);
		printf("Data do filme: %s \n", lista_filmes[i].data_filme);
		printf("Horario do filme: %d \n", lista_filmes[i].hora_filme);
		printf("Valor do bilhete: %.2f \n\n", lista_filmes[i].valor_bilhete);
	}

	// 2) entrar com os dados do bilhete
	int j = *p_cont_parou_reservarBilhete;

	printf("--------------------------\n");
	printf("# Reservar um novo bilhete\n\n");

	printf("Entre com o codigo do filme escolhido: ");
	scanf("%d", &vetor_bilhetes[j].cod_bil_filme);
	printf("Entre com o nome do cliente: ");
	scanf("%s", vetor_bilhetes[j].nome_cliente);
	printf("Entre com o telefone do cliente: ");
	scanf("%d", &vetor_bilhetes[j].tel_cliente);

	// 3) mostrar poltronas disponiveis
	printf("\n# Escolher poltrona\n\n");
	printf("Escolha uma poltrona: ");
	scanf("%d", &vetor_bilhetes[j].poltrona);

	// 4) imprimir bilhete
	printf("\n--------------------\n");
	printf("# Imprimindo bilhete\n\n");
	printf("Codigo do filme: %d \n", vetor_bilhetes[j].cod_bil_filme);
	// pesquisando pelo nome, pelo formato e valor do bilhete usando o codigo fornecido
	int k;
    for (k = 0; k < (*qtd_bilhetes); k++){ //varrendo o vetor lista_filmes a procura dos dados
		if (vetor_bilhetes[j].cod_bil_filme == lista_filmes[k].cod_filme){
			printf("Nome do filme: %s \n", lista_filmes[k].nome_filme);
			printf("Formato: %s \n", lista_filmes[k].form_filme);
			printf("Valor do bilhete: %.2f \n", lista_filmes[k].valor_bilhete);
		}
    }
    printf("Poltrona: %d \n", vetor_bilhetes[j].poltrona);

	/* depois de reservar um novo bilhete, incrementar +1 ao contador */
	*p_cont_parou_reservarBilhete = *p_cont_parou_reservarBilhete + 1;
}

void addFilme(FILMES *lista_filmes, int *p_cont_parou_addFilme){
	int i = *p_cont_parou_addFilme;

	printf("# Adicionar um novo filme\n\n");

	lista_filmes[i].cod_filme = i + 100; //o proprio codigo vai definir o codigo do filme
	printf("Entre com o nome: ");
	scanf("%s", lista_filmes[i].nome_filme);
	printf("Entre com o genero: ");
	scanf("%s", lista_filmes[i].gen_filme);
	printf("Entre com o formato: ");
	scanf("%s", lista_filmes[i].form_filme);
	printf("Entre com a data do filme (dd-mm-aaaa): ");
	scanf("%s", lista_filmes[i].data_filme);
	printf("Entre com o horario do filme: ");
	scanf("%d", &lista_filmes[i].hora_filme);
	printf("Entre com o valor do bilhete: ");
	scanf("%f", &lista_filmes[i].valor_bilhete);	

	/* depois de add um novo filme, incrementar +1 ao contador */
	*p_cont_parou_addFilme = *p_cont_parou_addFilme + 1;
}

void mostrarListaFilmes(FILMES *lista_filmes, int *p_cont_parou_addFilme){
	printf("# Lista de filmes cadastrados\n\n");

	int ate_onde = *p_cont_parou_addFilme;
	int i; //contador comum
	for (i = 0; i < ate_onde; i++){
		printf("Codigo do filme: %d \n", lista_filmes[i].cod_filme);
		printf("Nome do filme: %s \n", lista_filmes[i].nome_filme);
		printf("Genero: %s \n", lista_filmes[i].gen_filme);
		printf("Formato: %s \n", lista_filmes[i].form_filme);
		printf("Data do filme: %s \n", lista_filmes[i].data_filme);
		printf("Horario do filme: %d \n", lista_filmes[i].hora_filme);
		printf("Valor do bilhete: %.2f \n\n", lista_filmes[i].valor_bilhete);
	}
}

void buscarBilhete(FILMES *lista_filmes, BILHETES *vetor_bilhetes, int *p_cont_parou_addFilme, int *p_cont_parou_reservarBilhete, int *qtd_bilhetes){
	/* Legenda
	[1] = FOR para percorrer todas as posições que contem os bilhetes reservados
	[2] = imprimindo os bilhetes reservados
	[3] = AUX para garantir que apenas os bilhetes reservado serao impressos
	[4] = TESTE para caso não exista bilhetes reservados */

	int i, cod, tel, op; //variaveis: contador; variavel para teste de busca por codigo; variavel para teste de busca por telefone; variavel para o menu
	int aux;			 //vaiavel aux para testar caso nao haja nenhum bilhete reservado
	char nome[50];		 //variavel para teste de busca por nome do cliente
	
	//menu da funcao buscarBilhete
	printf("# Escolha um dos metodos abaixo para encontrar o bilhete: \n\n");
	printf("1. Codigo do filme \n");
	printf("2. Nome do cliente \n\n");

	printf("# Informe o numero da opcao: ");
	scanf("%d", &op);

	switch(op){
		case 1:
			printf("\n# Voce optou por procurar o bilhete pelo codigo do filme \n\n");
			printf("# Por favor, digite o codigo do filme: ");
			scanf("%d", &cod);

			//[1]
			for(i=0; i < *qtd_bilhetes; i++){
				if(cod ==  vetor_bilhetes[i].cod_bil_filme){
					//[2]
					printf("\n# Imprimindo o bilhete: \n\n");
					printf("Codigo do filme: %d \n", vetor_bilhetes[i].cod_bil_filme);
					printf("Nome do cliente: %s \n", vetor_bilhetes[i].nome_cliente);
					printf("Telefone do cliente: %d \n", vetor_bilhetes[i].tel_cliente);
					//[3]
					aux = 1;
				}
			}

			if (aux != 1)// [4]
				printf("\nNenhum bilhete reservado para este codigo.\n");
		break;

		case 2:
			printf("\n# Voce optou por procurar o bilhete pelo nome do cliente \n\n");
			printf("# Por favor, digite o nome do cliente: ");
			scanf("%s", nome);
			//[1]
			for(i=0; i < *qtd_bilhetes; i++){
				if((strcmp (vetor_bilhetes[i].nome_cliente, nome)) == 0){// [2] usando strcmp para comparação de strings
					printf("\n# Procurando bilhetes...\n");
					printf("\n# Imprimindo o bilhete: \n\n");
					printf("Codigo do filme: %d \n", vetor_bilhetes[i].cod_bil_filme);
					printf("Nome do cliente: %s \n", vetor_bilhetes[i].nome_cliente);
					printf("Telefone do cliente: %d \n", vetor_bilhetes[i].tel_cliente);
					//[3]
					aux = 1;
				}
			}

			if(aux != 1)//[4]
			printf("\nNenhum bilhete reservado para este nome.\n");
		break;

		default:
			printf("Opcao invalida.\n");
	}

}