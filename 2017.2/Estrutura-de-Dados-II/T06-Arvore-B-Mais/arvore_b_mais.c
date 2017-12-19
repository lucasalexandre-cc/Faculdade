#ifdef _MSC_VER
#define _CRT_SECURE_NO_WARNINGS
#endif

#include <limits.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "metadados.h"
#include "no_folha.h"
#include "no_interno.h"

#include "arvore_b_mais.h"

void shiftandoCliente(Cliente **p, int pos, int tam);

int busca(int cod_cli, char *nome_arquivo_metadados, char *nome_arquivo_indice, char *nome_arquivo_dados, int *pont_folha, int *encontrou)
{
    FILE *metaArq = fopen(nome_arquivo_metadados, "r+b");
    FILE *folhasArq = fopen(nome_arquivo_dados, "r+b");
    FILE *indiceArq = fopen(nome_arquivo_indice, "r+b");
    if (!(metaArq && folhasArq && indiceArq))exit(1);

    Metadados *meta = le_metadados(metaArq);
    NoFolha *folha;
    int i, pos;
    if (meta->raiz_folha) {
        fseek(folhasArq, meta->pont_raiz, SEEK_SET);
        folha = le_no_folha(folhasArq);
        *pont_folha = meta->pont_raiz;
        for (i = 0; i < folha->m; i++) {
            if (folha->clientes[i]->cod_cliente == cod_cli) {
                *encontrou = 1;
                fclose(metaArq);
                fclose(folhasArq);
                fclose(indiceArq);
                pos = i;
                return pos;
            } else if (folha->clientes[i]->cod_cliente > cod_cli) {
                *encontrou = 0;
                fclose(metaArq);
                fclose(folhasArq);
                fclose(indiceArq);
                pos = i;
                return pos;
            }
        }


    } else {
        fseek(indiceArq, meta->pont_raiz, SEEK_SET);
        NoInterno *atual = le_no_interno(indiceArq);
        *pont_folha = meta->pont_raiz;
        int primeiroInterno = 1;
        while (primeiroInterno || !(atual->aponta_folha)) {

            if (primeiroInterno) primeiroInterno = 0;
            else {
                fseek(indiceArq, *pont_folha, SEEK_SET);
                atual = le_no_interno(indiceArq);
            }
            for (i = 0; i < atual->m; i++) {
                if (atual->chaves[i] > cod_cli) {
                    *pont_folha = atual->p[i];
                    i = atual->m;
                } else if (atual->chaves[i] == cod_cli) {
                    *pont_folha = atual->p[i + 1];
                    i = atual->m;
                } else {
                    *pont_folha = atual->p[i + 1];
                }
            }

        }

        libera_no_interno(atual);

        fseek(folhasArq, *pont_folha, SEEK_SET);
        folha = le_no_folha(folhasArq);
        for (i = 0; i < folha->m; i++) {
            if (folha->clientes[i]->cod_cliente == cod_cli) {
                *encontrou = 1;
                fclose(metaArq);
                fclose(folhasArq);
                fclose(indiceArq);
                pos = i;
                return pos;
            } else if (folha->clientes[i]->cod_cliente > cod_cli) {
                *encontrou = 0;
                fclose(metaArq);
                fclose(folhasArq);
                fclose(indiceArq);
                return i;
            }
        }

    }

    pos = folha->m;
    libera_no_folha(folha);
    free(meta);
    *encontrou = 0;
    fclose(metaArq);
    fclose(folhasArq);
    fclose(indiceArq);
    return pos;
}

int insere(int cod_cli, char *nome_cli, char *nome_arquivo_metadados, char *nome_arquivo_indice, char *nome_arquivo_dados)
{
    //Abrindo os arquivos
    FILE *metaArq = fopen(nome_arquivo_metadados, "r+b");
    FILE *folhasArq = fopen(nome_arquivo_dados, "r+b");
    FILE *indiceArq = fopen(nome_arquivo_indice, "r+b");
    if (!(metaArq && folhasArq && indiceArq))exit(1);

    Metadados *meta = le_metadados(metaArq);

    fseek(indiceArq, meta->pont_raiz, SEEK_SET);
    NoInterno *interno;
    NoFolha *folha;
    Cliente *c = (Cliente *) malloc(sizeof(Cliente));
    c->cod_cliente = cod_cli;
    strcpy(c->nome, nome_cli);

    int pos_raiz = meta->pont_raiz;
    if(meta->raiz_folha){
        //No folha é o no raiz
        fseek(folhasArq, pos_raiz, SEEK_SET);
        folha = le_no_folha(folhasArq);
        int i = 0;
        while(folha->m > i){
            if(folha->clientes[i]->cod_cliente > cod_cli){
                shiftandoCliente(folha->clientes, i, folha->m);
                folha->clientes[i] = c;
                folha->m++;
                fseek(folhasArq, pos_raiz, SEEK_SET);
                salva_no_folha(folha, folhasArq);
                free(c);
                fclose(folhasArq);
                return pos_raiz;
            }
            else if(folha->clientes[i]->cod_cliente > cod_cli){
                fclose(folhasArq);
                fclose(metaArq);
                fclose(indiceArq);
                return -1;
            }
            else{
                i++;
            }
        }
    }else{
        //No folha não é a raiz
        fseek(indiceArq, pos_raiz, SEEK_SET);
        interno = le_no_interno(indiceArq);
        //Achando o indice para a folha
        int i;
        while(!interno->aponta_folha){
            i = 0;
            while(interno->m > i){
                if(interno->chaves[i] > cod_cli){
                    pos_raiz = interno->p[i];
                    fseek(indiceArq, pos_raiz, SEEK_SET);
                    interno = le_no_interno(indiceArq);
                    break;
                }
                else if(interno->chaves[i] == cod_cli){
                    fclose(folhasArq);
                    fclose(metaArq);
                    fclose(indiceArq);
                    return -1;
                }
                else{
                    i++;
                    if(i == interno->m){
                        pos_raiz = interno->p[i];
                        fseek(indiceArq, pos_raiz, SEEK_SET);
                        interno = le_no_interno(indiceArq);
                        break;
                    }
                }
            }
        }
        //Agora, pos_raiz é um nó interno que aponta para a folha
        //Vamos achar para qual folha ele aponta
        int aponta_folha = 0; i = 0;
        while(interno->m > i){
            if(interno->chaves[i] > cod_cli){
                aponta_folha = interno->p[i];
                break;
            }else{
                i++;
                if(interno->m == i){
                    aponta_folha = interno->p[i];
                    break;
                }
            }
        }

        //Agora, a variavel aponta_folha esta apontando para o indice da folha onde devo inserir
        fseek(folhasArq, aponta_folha, SEEK_SET);
        folha = le_no_folha(folhasArq);
        if(folha->m < 4){
            i = 0;
            while(folha->m > i){
                if(folha->clientes[i]->cod_cliente > cod_cli){
                    shiftandoCliente(folha->clientes, i, folha->m);
                    folha->clientes[i] = c;
                    folha->m++;
                    fseek(folhasArq, pos_raiz, SEEK_SET);
                    salva_no_folha(folha, folhasArq);
                    free(c);
                    fclose(folhasArq);
                    return aponta_folha;
                }
                else if(folha->clientes[i]->cod_cliente == cod_cli){
                    fclose(folhasArq);
                    fclose(metaArq);
                    fclose(indiceArq);
                    return -1;
                }
                else{
                    i++;
                }
            }
        }
        else{
            //folha cheia
        }

    }


    return INT_MAX;
}

int exclui(int cod_cli, char *nome_arquivo_metadados, char *nome_arquivo_indice, char *nome_arquivo_dados)
{
    //Realiza Busca
    int encontrou, pont_folha, pos;
    pos = busca(cod_cli, nome_arquivo_metadados, nome_arquivo_indice, nome_arquivo_dados, &pont_folha, &encontrou);

    //Se a chave não está no arquivo, retorna -1
    if (!encontrou) return -1;


    //Caso contrário, abre os arquivos necessários
    FILE *metaArq = fopen(nome_arquivo_metadados, "r+b");
    FILE *folhasArq = fopen(nome_arquivo_dados, "r+b");
    FILE *indiceArq = fopen(nome_arquivo_indice, "r+b");
    if (!(metaArq && folhasArq && indiceArq))exit(1);



    //lê a folha em que a chave se encontra
    fseek(folhasArq, pont_folha, SEEK_SET);
    NoFolha *folha = le_no_folha(folhasArq);

    int i;
    for (i = pos; i < folha->m - 1; i++) {
        if (folha->clientes[i]) {
            folha->clientes[i] = folha->clientes[i + 1];
        }
    }
    folha->clientes[i] = NULL;



    if ((--folha->m) < D) {
        int redistribui = 0, indiceP;

        fseek(indiceArq, folha->pont_pai, SEEK_SET);
        NoInterno *w = le_no_interno(indiceArq);
        int indice;
        for (i = 0; i < w->m + 1; i++) {
            if (w->p[i] == pont_folha) {
                indice = i;
                i = w->m + 1;
            }
        }



        NoFolha *p;
        //Se não for o primeiro filho, verificamos o anterior
        if (indice != 0) {
            fseek(folhasArq, w->p[indice - 1], SEEK_SET);
            p = le_no_folha(folhasArq);

            if (p->m + folha->m >= 2 * D) {
                redistribui = 1;
                indiceP = indice - 1;
            }
        }

        //Se não for o último, verificamos o próximo
        if (indice < w->m && !redistribui) {
            fseek(folhasArq, w->p[indice + 1], SEEK_SET);
            p = le_no_folha(folhasArq);

            if (p->m + folha->m >= 2 * D) {
                redistribui = 1;
                indiceP = indice + 1;
            }
        }

        if (redistribui) {

            Cliente **c = folha->clientes;
            int x, tamP = p->m, tamQ = folha->m;

            if (indiceP < indice) {
                w->chaves[indiceP] = p->clientes[p->m - 1]->cod_cliente;



                i = 0;
                x = (tamP + folha->m) / 2;
                while (x < (tamP)) {
                    folha->clientes[i] = p->clientes[x];
                    p->clientes[x] = NULL;
                    p->m--;
                    folha->m++;
                    x++;
                    i++;
                }
                int j;
                for (j = 0; j < tamQ; j++) {
                    folha->clientes[i] = c[j];
                    i++;
                }


            } else {


                w->chaves[indice] = p->clientes[(tamP-1)/2]->cod_cliente;
                i = tamQ;
                x = 0;

                while (x < (tamP-1) / 2) {
                    folha->clientes[i] = p->clientes[x];
                    p->clientes[x] = p->clientes[x + 1];
                    p->m--;
                    folha->m++;
                    x++;
                    i++;
                }

                for(x; x<p->m; x++){
                    p->clientes[x] = p->clientes[x+1];
                }


                int j;
                for (j = p->m; j < tamP; j++) {
                    p->clientes[j] = NULL;
                }


            }

            fseek(indiceArq, folha->pont_pai, SEEK_SET);
            salva_no_interno(w, indiceArq);

            fseek(folhasArq, w->p[indice], SEEK_SET);
            salva_no_folha(folha, folhasArq);


            fseek(folhasArq, w->p[indiceP], SEEK_SET);
            salva_no_folha(p, folhasArq);


            fclose(metaArq);
            fclose(folhasArq);
            fclose(indiceArq);


            return pont_folha;

        }

    }

    fseek(folhasArq, pont_folha, SEEK_SET);
    salva_no_folha(folha, folhasArq);

    fclose(metaArq);
    fclose(folhasArq);
    fclose(indiceArq);


    return pont_folha;
}

void shiftandoCliente(Cliente **p, int pos, int tam){
    Cliente *vouEscrever = p[pos];
    while(pos != tam + 1){
        pos++;
        Cliente *aux = p[pos];
        p[pos] = vouEscrever;
        vouEscrever = aux;
    }
}
