#ifdef _MSC_VER
#define _CRT_SECURE_NO_WARNINGS
#endif

#include <limits.h>
#include <stdlib.h>
#include <string.h>

#include "arvore_b.h"
#include "metadados.h"
#include "no.h"

void shiftandoCliente(Cliente **p, int pos, int tam);

int busca(int cod_cli, char *nome_arquivo_metadados, char *nome_arquivo_dados, int *pont, int *encontrou) {
    FILE *metaArq = fopen(nome_arquivo_metadados, "r+b");
    FILE *dadosArq = fopen(nome_arquivo_dados, "r+b");

    Metadados *meta = le_metadados(metaArq);
    fseek(dadosArq, meta->pont_raiz * tamanho_no(), SEEK_SET);

    int index, i, pt = meta->pont_raiz, pos, cd;
    No *atual;

    while (1) {
        i = 0;
        fseek(dadosArq, pt * tamanho_no(), SEEK_SET);
        atual = le_no(dadosArq);

        index = pt;
        while ((i < (atual->m)) && (pt == index)) {
            cd = atual->clientes[i]->cod_cliente;
            if (cd == cod_cli) {
                fclose(metaArq);
                fclose(dadosArq);
                *encontrou = 1;
                *pont = pt * tamanho_no();
                pos = i;
                return pos;
            } else if (cd > cod_cli) {
                if (atual->p[i] != -1) pt = atual->p[i]/tamanho_no();
                else {
                    fclose(metaArq);
                    fclose(dadosArq);
                    *encontrou = 0;
                    *pont = pt * tamanho_no();
                    pos = i;
                    return pos;
                }
            }
            i++;
        }

        if (pt == index) {
            if(atual->p[i]==-1){
                fclose(metaArq);
                fclose(dadosArq);
                *encontrou=0;
                *pont = pt * tamanho_no();
                pos = i;
                return pos;
            }
            pt = atual->p[i]/tamanho_no();
        }
    }
}

int insere(int cod_cli, char *nome_cli, char *nome_arquivo_metadados, char *nome_arquivo_dados) {
    FILE *metaArq = fopen(nome_arquivo_metadados, "r+b");
    FILE *dadosArq = fopen(nome_arquivo_dados, "r+b");

    //Indo pra raiz
    Metadados *meta = le_metadados(metaArq);
    fseek(dadosArq, meta->pont_raiz * tamanho_no(), SEEK_SET);

    //Criando cliente
    Cliente *c = (Cliente *) malloc(sizeof(Cliente));
    c->cod_cliente = cod_cli;
    strcpy(c->nome, nome_cli);

    int index = meta->pont_raiz;
    while(1){
        fseek(dadosArq, index * tamanho_no(), SEEK_SET);
        No *atual = le_no(dadosArq);
        int i = 0;
        while(i < atual->m){
            if(atual->clientes[i]->cod_cliente == cod_cli){
                fclose(dadosArq);
                fclose(metaArq);
                return -1;
            }
            else if(atual->clientes[i]->cod_cliente > cod_cli) {
                //Caso 1
                if (atual->m < 4 && atual->p[i] == -1) {
                    shiftandoCliente(atual->clientes, i, atual->m);
                    atual->m++;
                    atual->clientes[i] = c;

                    fseek(dadosArq, index * tamanho_no(), SEEK_SET);
                    salva_no(atual, dadosArq);
                    fclose(dadosArq);
                    fclose(metaArq);
                    return index * tamanho_no();
                }else if(atual->m < 4 && atual->p[i] != -1){
                    index = atual->p[i] / tamanho_no();
                    break;
                }else{
                    //Nao consegui implementar, erros na logica que tentei
                    return -1;
                }
            }else{
                i++;
            }
        }
    }

}

int exclui(int cod_cli, char *nome_arquivo_metadados, char *nome_arquivo_dados) {
    int encontrou = INT_MAX, pont = INT_MAX, pos = INT_MAX;
    pos = busca(cod_cli, nome_arquivo_metadados, nome_arquivo_dados, &pont, &encontrou);

    FILE *metaArq = fopen(nome_arquivo_metadados, "r+b");
    FILE *dadosArq = fopen(nome_arquivo_dados, "r+b");


    //CASO 1: Chave não está na tabela
    if (!encontrou) {
        fclose(metaArq);
        fclose(dadosArq);
        return -1;
    }
    //CASO 2: Chave está na tabela
    Metadados *meta = le_metadados(metaArq);
    fseek(dadosArq, pont, SEEK_SET);
    No *atual = le_no(dadosArq);
    //printf("%d",pos);
    int i, temFilhos = 0;
    for (i = 0; i < atual->m + 1; i++) {
        if (atual->p[i] != -1) {
            temFilhos++;
            i = atual->m + 1;
        }
    }

    //2.1: Chave está em uma folha
    if (!temFilhos) {
        //CASO 2.1.1: Chave pode ser removida normalmente
        if (atual->m != D) {

            //CASO 2.1.1.1: Cliente é ultimo do nó
            if (!atual->clientes[pos + 1]) {
                atual->clientes[pos] = NULL;
                fseek(dadosArq, -tamanho_no(), SEEK_CUR);
                salva_no(atual, dadosArq);
            }                //2.1.1.2: Cliente não é último do nó
            else {
                i = pos;
                while (i < atual->m - 1) {
                    atual->clientes[i] = atual->clientes[i + 1];
                    i++;
                }
                atual->clientes[i] = NULL;
                atual->m--;
                fseek(dadosArq, -tamanho_no(), SEEK_CUR);
                salva_no(atual, dadosArq);
                libera_no(atual);
            }
        }            
	//CASO 2.1.2: Necessita Redistribuição ou concatenação
        else {
            No *pai;
            fseek(dadosArq, atual->pont_pai, SEEK_SET);
            pai = le_no(dadosArq);
            int index;
            for (i = 0; i < pai->m + 1; i++) {
                if (pai->p[i] == pont) {
                    index = i;
                    i = pai->m + 1;
                }
            }
            No *prox;
            if (index == 0) {
                fseek(dadosArq, pai->p[1], SEEK_SET);
                prox = le_no(dadosArq);
                if (pai->m + prox->m >= 2 * D) {
                    i = pos;
                    while (i < atual->m - 1) {
                        atual->clientes[i] = atual->clientes[i + 1];
                        i++;
                    }
                    atual->clientes[i] = NULL;
                    atual->m;
                    prox->clientes[prox->m++] = pai->clientes[0];
                    for(i=0;i<atual->m;i++){
                        if(atual->clientes[i]){
                            prox->clientes[prox->m++] = atual->clientes[i];
                            atual->clientes[i] = NULL;
                        }
                    }

                    pai->clientes[0] = prox->clientes[(prox->m-1)/2];
                    prox->clientes[(prox->m-1)/2] = NULL;
                    int j=0;
                    for((i=(prox->m-1)/2)+1; i<prox->m; i++){
                        if(prox->clientes[i]){
                            atual->clientes[j]=prox->clientes[i];
                            prox->clientes[i]=NULL;
                            j++;
                        }
                    }
                    atual->m = prox->m - 1 -(prox->m-1)/2;
                    prox->m = (prox->m-1)/2;

                    fseek(dadosArq, atual->pont_pai, SEEK_SET);
                    salva_no(pai, dadosArq);

                    fseek(dadosArq, pai->p[1], SEEK_SET);
                    salva_no(prox, dadosArq);

                    fseek(dadosArq, pont, SEEK_SET);
                    salva_no(atual, dadosArq);


                }
            }

        }
    }

    //TODO: Inserir aqui o codigo do algoritmo de remocao
    fclose(dadosArq);
    fclose(metaArq);
    return pont;
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
