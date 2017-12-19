#ifdef _MSC_VER
#define _CRT_SECURE_NO_WARNINGS
#endif

#include <limits.h>
#include <stdio.h>
#include <stdlib.h>

#include "chave_secundaria.h"
#include "cliente.h"

typedef struct struct_aux01 {
    int ed;
    int cod;
    int idade;
} struct_aux01;

struct_aux01 *le_struct01(FILE *in){
    struct_aux01 *resp = (struct_aux01 *)malloc(sizeof(struct_aux01));
    fread(&resp->ed, sizeof(int), 1, in);
    fread(&resp->cod, sizeof(int), 1, in);
    fread(&resp->idade, sizeof(int), 1, in);
    return resp;
}

void escrever_struct(FILE *out, struct_aux01 *p){
    fwrite(&p->ed,sizeof(int), 1, out);
    fwrite(&p->cod, sizeof(int), 1, out);
    fwrite(&p->idade, sizeof(int), 1, out);
}

void indexa(char *nome_arquivo, int tam)
{
    //Arquivo de entrada
    FILE *in = fopen(nome_arquivo, "r+b");
    //Arquivo de saida
    FILE *out = fopen("indice_idade.dat", "w+b");
    fclose(out);
    out = fopen("indice_idade.dat", "r+b");

    //Passo 1/2: (ED, COD, IDADE)
    FILE *aux01 = fopen("aux01.dat", "w+b");
    fclose(aux01);
    aux01 = fopen("aux01.dat", "r+b");
    int i;
    for(i = 0; i<tam; i++){
        Cliente *c = le_cliente(in);
        int ED = i;
        fwrite(&ED, sizeof(int), 1, aux01);
        fwrite(&c->cod_cliente, sizeof(int), 1, aux01);
        fwrite(&c->idade, sizeof(int), 1, aux01);
    }

    //Passo 3: ordenar pela chave secundaria (idade)
    int j;
    for(i = 0; i<tam; i++){
        fseek(aux01, i*sizeof(int)*3, SEEK_SET);
        int idade_min = INT_MAX; int indice = i;
        for(j = i; j<tam; j++){
            struct_aux01 *aux = le_struct01(aux01);
            if(aux->idade < idade_min){
                idade_min = aux->idade;
                indice = j;
            }
        }
        if(i != indice){
            fseek(aux01, i*sizeof(int)*3, SEEK_SET);
            struct_aux01 *troca01 = le_struct01(aux01);
            fseek(aux01, indice*sizeof(int)*3, SEEK_SET);
            struct_aux01 *troca02 = le_struct01(aux01);
            fseek(aux01, indice*sizeof(int)*3, SEEK_SET);
            escrever_struct(aux01, troca01);
            fseek(aux01, i*sizeof(int)*3, SEEK_SET);
            escrever_struct(aux01, troca02);
        }
    }

    //Passo 4:
    rewind(aux01);
    i = 0;
    while(i < tam){
        struct_aux01 *p = le_struct01(aux01);
        int cont = 1;int ed= p->ed; int idade = p->idade;
        fwrite(&p->idade, sizeof(int), 1, out);
        i++;
        while(i < tam){
            p = le_struct01(aux01);
            if(p->idade != idade){
                fseek(aux01, i*sizeof(int)*3, SEEK_SET);
                break;
            }
            else{
                i++;
                cont++;
            }
        }
        fwrite(&ed, sizeof(int),1, out);
        fwrite(&cont, sizeof(int), 1, out);
    }

    fclose(aux01);
    fclose(in);
    fclose(out);
}

