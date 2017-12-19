#ifndef T01_AGENCIA_H
#define T01_AGENCIA_H

#include <stdlib.h>
#include <stdio.h>

typedef struct Agencia {
    int cod_agencia;
    char nome[50];
    char nome_gerente[50];
} Agencia;

Agencia *criaAgencia(int cod, char nome[50], char nome_gerente[50]);
void salva_agencia(Agencia *ag, FILE *out);
Agencia *acha_Agencia(FILE *in, int cod_agencia);
void imprimindoTodasAgencias(FILE *in);
void imprimindoUmaAgencia(FILE *in, int cod);

#endif //T01_AGENCIA_H
