#include "conta_corrente.h"
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

//Cria o ponteiro para uma conta corrente
Conta_Corrente *criaContaCorrente(int cod_conta, int cod_agencia, double saldo){
    //Cria o ponteiro para 'Conta_Corrente'
    Conta_Corrente *cc = (Conta_Corrente *) malloc(sizeof(Conta_Corrente));
    //Zera os valores
    if (cc) memset(cc, 0, sizeof(Conta_Corrente));
    //Atribui os valores corretos aos atributos
    cc->cod_conta = cod_conta;
    cc->cod_agencia = cod_agencia;
    cc->saldo = saldo;
    //Retorna o ponteiro
    return cc;
}

//Salva a conta corrente no final do arquivo
void salva_conta_corrente(Conta_Corrente *cc, FILE *out){
    //Indo para o final do arquivo
    long size_of_file = ftell(out);
    fseek(out, size_of_file, SEEK_SET);
    //Escrevendo no final do arquivo
    fwrite(&cc->cod_conta, sizeof(int), 1, out);
    fwrite(&cc->cod_agencia, sizeof(int), 1, out);
    fwrite(&cc->saldo, sizeof(double), 1, out);
}

//Acha a agencia a partir do codigo da agencia.
Conta_Corrente *acha_conta_corrente(FILE *in, int cod_agencia, int cod_conta){
    //Indo para o comeco do arquivo
    rewind(in);
    //Criando o ponteiro para conta corrente
    Conta_Corrente *cc = (Conta_Corrente *) malloc(sizeof(Conta_Corrente));
    //Buscando no arquivo enquanto ele nao chegar no final
    while(fread(&cc->cod_conta, sizeof(int), 1, in) > 0){
        fread(&cc->cod_agencia, sizeof(int), 1, in);
        fread(&cc->saldo, sizeof(double), 1, in);
        if(cc->cod_agencia == cod_agencia && cc->cod_conta == cod_conta) return cc;
    }
    //Caso ele tenha chegado no final e nao achado a conta corrente a partir do cod_agencia
    //e cod_conta, retorna NULL
    return NULL;
}

void imprimindoTodasContasCorrentes(FILE *in){
    //Indo para o comeco do arquivo
    rewind(in);
    //Criando o ponteiro para conta corrente
    Conta_Corrente *cc = (Conta_Corrente *) malloc(sizeof(Conta_Corrente));
    printf("Printando todas as contas correntes cadastradas!! \n\n");
    int cont = 1;
    while(fread(&cc->cod_conta, sizeof(int), 1, in) > 0){
        fread(&cc->cod_agencia, sizeof(int), 1, in);
        fread(&cc->saldo, sizeof(double), 1, in);

        printf("Conta Corrente %i \n",cont);
        printf("Codigo da Conta Corrente: %i\n",cc->cod_conta);
        printf("Codigo da Agencia: %i\n", cc->cod_agencia);
        printf("Saldo: %.2f\n\n",cc->saldo);
        cont++;
    }
}

void imprimindoUmaContaCorrente(FILE *in, int cod_agencia, int cod_conta){
    Conta_Corrente *aux = acha_conta_corrente(in, cod_agencia, cod_conta);
    if(!aux) printf("\nNenhuma conta corrente existente com esses codigos.\n\n");
    else{
        printf("\nCodigo da conta corrente: %i\n", aux->cod_conta);
        printf("Codigo da agencia: %i\n",aux->cod_agencia);
        printf("Saldo da conta corrente: %.2f\n\n", aux->saldo);
        free(aux);
    }
}