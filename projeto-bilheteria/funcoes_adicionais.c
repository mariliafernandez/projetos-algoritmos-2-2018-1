#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include "estruturas_dados.h"

/* DETECTAR SISTEMA OPERACIONAL */

#if defined (_WIN32) || defined(_WIN64)
    int isWindows = 1;
	#else
		#ifdef __linux
			int isWindows = 0;
		#endif
#endif

/* IMPLEMENTACAO DAS FUNCOES ADICIONAIS */

void limpaTela(){
	if (isWindows == 1){
		//limpa tela no Windows
		system("cls"); 	
	}else if (isWindows == 0){
		//limpa tela em sistemas baseados em Unix
		system("clear"); 
	}
}

FILMES *criarVetorFilmes(int tam_vetor){	//somente cria vetores to tipo FILMES
	FILMES *vetor_dinamico_generico;
	vetor_dinamico_generico = malloc(tam_vetor * sizeof(FILMES));

	return vetor_dinamico_generico;
}

BILHETES *criarVetorBilhetes(int tam_vetor){	//somente cria vetores to tipo BILHETES
	BILHETES *vetor_dinamico_generico;
	vetor_dinamico_generico = malloc(tam_vetor * sizeof(FILMES));

	return vetor_dinamico_generico;
}

void desalocarVetorFilmes(FILMES *vetor_dinamico_generico){ 
	//somente desaloca vetores dinamicos do tipo FILMES
	free(vetor_dinamico_generico);
	vetor_dinamico_generico = NULL;
}

void desalocarVetorBilhetes(BILHETES *vetor_dinamico_generico){ 
	//somente desaloca vetores dinamicos do tipo FILMES
	free(vetor_dinamico_generico);
	vetor_dinamico_generico = NULL;
}