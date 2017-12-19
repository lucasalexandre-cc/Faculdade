#ifndef T01_CONTA_CORRENTE_H
#define T01_CONTA_CORRENTE_H

#include <stdlib.h>
#include <stdio.h>

typedef struct Conta_Corrente {
    int cod_conta;
    int cod_agencia;
    double saldo;
} Conta_Corrente;

Conta_Corrente *criaContaCorrente(int cod_conta, int cod_agencia, double saldo);
void salva_conta_corrente(Conta_Corrente *cc, FILE *out);
Conta_Corrente *acha_conta_corrente(FILE *in, int cod_agencia, int cod_conta);
void imprimindoTodasContasCorrentes(FILE *in);
void imprimindoUmaContaCorrente(FILE *in, int cod_agencia, int cod_conta);

#endif //T01_CONTA_CORRENTE_H