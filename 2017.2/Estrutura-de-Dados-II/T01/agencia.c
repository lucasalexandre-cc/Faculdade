#include "agencia.h"
#include <string.h>

//Cria o ponteiro para uma agencia
Agencia *criaAgencia(int cod, char nome[50], char nome_gerente[50]){
    //Cria o ponteiro para 'Agencia'
    Agencia *ag = (Agencia *) malloc(sizeof(Agencia));
    //Zera os valores
    if (ag) memset(ag, 0, sizeof(Agencia));
    //Atribui os valores corretos aos atributos
    ag->cod_agencia = cod;
    strcpy(ag->nome, nome);
    strcpy(ag->nome_gerente, nome_gerente);
    //Retorna o ponteiro
    return ag;
}

//Salva a agencia no final do arquivo
void salva_agencia(Agencia *ag, FILE *out){
    //Indo para o final do arquivo
    long size_of_file = ftell(out);
    fseek(out, size_of_file, SEEK_SET);
    //Escrevendo no final do arquivo
    fwrite(&ag->cod_agencia, sizeof(int), 1, out);
    fwrite(ag->nome, sizeof(char), sizeof(ag->nome), out);
    fwrite(ag->nome_gerente, sizeof(char), sizeof(ag->nome_gerente), out);
}

//Acha a agencia a partir do codigo da agencia.
Agencia *acha_Agencia(FILE *in, int cod_agencia){
    //Indo para o comeco do arquivo
    rewind(in);
    //Criando o ponteiro para agencia
    Agencia *ag = (Agencia *) malloc(sizeof(Agencia));
    //Buscando no arquivo enquanto ele nao chegar no final
    while(fread(&ag->cod_agencia, sizeof(int), 1, in) > 0){
        fread(ag->nome, sizeof(char), sizeof(ag->nome), in);
        fread(ag->nome_gerente, sizeof(char), sizeof(ag->nome_gerente), in);
        if(ag->cod_agencia == cod_agencia) return ag;
    }
    //Caso ele tenha chegado no final e nao achado a agencia a partir do cod_agencia, retorna NULL
    return NULL;
}

void imprimindoTodasAgencias(FILE *in){
    //Indo para o comeco do arquivo
    rewind(in);
    //Criando o ponteiro para agencia
    Agencia *ag = (Agencia *) malloc(sizeof(Agencia));

    printf("Printando todas as agencias cadastradas!! \n\n");
    int cont = 1;
    while(fread(&ag->cod_agencia, sizeof(int), 1, in) > 0){
        fread(ag->nome, sizeof(char), sizeof(ag->nome), in);
        fread(ag->nome_gerente, sizeof(char), sizeof(ag->nome_gerente), in);

        printf("Agencia %i \n",cont);
        printf("Codigo da Agencia: %i\n", ag->cod_agencia);
        printf("Nome da Agencia: %s\n",ag->nome);
        printf("Nome do Gerente: %s\n\n",ag->nome_gerente);
        cont++;
    }
}

void imprimindoUmaAgencia(FILE *in, int cod){
    Agencia *aux = acha_Agencia(in, cod);
    if(!aux) printf("Nenhuma agencia existente com esse codigo.");
    else{
        printf("\nCodigo da agencia: %i\n",aux->cod_agencia);
        printf("Nome da agencia: %s\n", aux->nome);
        printf("Nome do gerente: %s\n\n", aux->nome_gerente);
        free(aux);
    }
}