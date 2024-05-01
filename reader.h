#ifndef ATTRIBUTE_PROCESSING_H
#define ATTRIBUTE_PROCESSING_H

#define SIZE_CHARBUF 1025 /* Tamanho da linha auxiliar, usada para conseguir informações do arquivo ARFF. */

#include <stdio.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

typedef struct Atributos {
        char *rotulo;
        char *tipo;
        char *categorias;
} atributo;

void exibe_atributos(atributo *infos, int tamanho);

int conta_atributos(FILE *arff);

atributo *processa_atributos(FILE *arff);

void libera_atributos(atributo *vetor, int n_atr);

#endif // ATTRIBUTE_PROCESSING_H