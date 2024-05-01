#include "reader.h"

void exibe_atributos(atributo *infos, int tamanho) {
    	if (!infos) {
		printf("O arquivo ARFF fornecido é inválido!\n");
    		exit(0);
    	}

    	printf("==== ATRIBUTOS DO ARQUIVO ====\n");
    
    	for (int i = 0; i < tamanho; i++) {
		printf("-> Atributo #%d\n", i + 1);
        	printf("Rótulo: %s\n", infos[i].rotulo);
        	printf("Tipo: %s\n", infos[i].tipo);

        if (infos[i].categorias) 
		printf("Categorias: %s\n", infos[i].categorias);

        if (i < tamanho - 1) 
		printf("------------------------------\n");
    	}

    	printf("===============================\n");
}

int conta_atributos(FILE *arff) {
	if (!arff) {
		perror("[-] conta_atributos: Arquivo ARFF recebido não existe");

		return -1;
	}

	rewind(arff);
	int n_atr = 0;
	char *linha_aux = (char *)malloc(SIZE_CHARBUF * sizeof(char));

	if (!linha_aux) {
		perror("[-] conta_atributos(): Impossível alocar substring auxiliar de linha_aux");

		return -1;
	}

	while (fgets(linha_aux, SIZE_CHARBUF, arff) != NULL) {
		if (strncmp(linha_aux, "@attribute", strlen("@attribute")) == 0) {
			n_atr++;
		} else if (strncmp(linha_aux, "@data", strlen("@data")) == 0) {
			free(linha_aux);
			linha_aux = NULL;
			rewind(arff);

			return n_atr;
		}
	}

	perror("[-] conta_atributos(): Formato de atributo inválido");
	free(linha_aux);
	linha_aux = NULL;

	return -1;
}

atributo *processa_atributos(FILE *arff) {
	if (!arff) {
		perror("[-] processa_atributos: Arquivo ARFF recebido não existe");

		return NULL;
	}

	char *linha_aux = (char *)malloc(SIZE_CHARBUF * sizeof(char));

	if (!linha_aux) {
		perror("[-] processa_atributos(): Impossível alocar substring auxiliar de linha_aux");

		return NULL;
	}

	int n_atr = conta_atributos(arff);

	if (n_atr < 0) {
		perror("[-] processa_atributos(): Impossível criar um vetor de atributos com tamanho negativo");
		free(linha_aux);
		linha_aux = NULL;

		return NULL;
	}

	atributo *atr = (atributo *)malloc(n_atr * sizeof(atributo));

	if (!atr) {
		perror("[-] processa_atributos(): Impossível alocar atributos de retorno");
		free(linha_aux);
		linha_aux = NULL;

		return NULL;
	}

	int i = 0;
	
	while (fgets(linha_aux, SIZE_CHARBUF, arff) != NULL) {
		if (strncmp(linha_aux, "@attribute", strlen("@attribute")) == 0) {
			char *token = strtok(linha_aux, " ");
			token = strtok(NULL, " ");
			atr[i].rotulo = strdup(token);
			token = strtok(NULL, " ");

			if (strchr(token, '{')) {
				atr[i].tipo = strdup("categoric");
				atr[i].categorias = strdup(token);
			} else {
				atr[i].tipo = strdup(token);
				atr[i].categorias = NULL;
			}

			i++;
		} else if (strncmp(linha_aux, "@data", strlen("@data")) == 0) {
			free(linha_aux);
			linha_aux = NULL;

			return atr;
		}
	}

	perror("[-] processa_atributos(): O formato de arquivo ARFF é inválido");
	free(linha_aux);
	linha_aux = NULL;
	free(atr);
	atr = NULL;

	return NULL;
}

void libera_atributos(atributo *vetor, int n_atr) {
	if (vetor) {
		for (int i = 0; i < n_atr; i++) {
			free(vetor[i].rotulo);
			free(vetor[i].tipo);
			free(vetor[i].categorias);
		}

		free(vetor);
		vetor = NULL;
	}
}