/* Leitor de atributos em arquivos ARFF */
/* @author: Caio E. F. de Miranda */
/* @date: 24/03/2024 */

#include <unistd.h>
#include <bits/getopt_core.h>
#include "reader.h"

int main(int argc, char **argv) {
	int opt;
  	char exibicao = 0;
  	char *entrada = 0;

	while ((opt = getopt(argc, argv, "pi:")) != -1) {
		switch (opt) {
			case 'i':
				entrada = strdup(optarg);
			
				break;
			case 'p':
				exibicao = 1;

				break;
			default:
				fprintf(stderr, "Forma de uso: ./arff -i <arq_in> [-p]\n");
				exit(1);
		}
	}

	if (!entrada) {
		fprintf(stderr, "Forma de uso: ./arff -i <arq_in> [-p]\n");
		exit(2);
	}

	FILE *arff = fopen(entrada, "r");

	if (!arff) {
		perror("[-] main(): Ponteiro para arquivo ARFF não existe");

		return EXIT_FAILURE;
	}

	int n_atr = conta_atributos(arff);

	if (n_atr < 0) {
		perror("[-] main(): Não foi possível contar os atributos do arquivo ARFF");
		free(entrada);
		entrada = NULL;
		fclose(arff);

		return EXIT_FAILURE;
	}

	atributo *atr = processa_atributos(arff);

	if (exibicao)
		exibe_atributos(atr, n_atr);

	libera_atributos(atr, n_atr);
	free(entrada);
	entrada = NULL;
	fclose(arff);

	return EXIT_SUCCESS;
}
