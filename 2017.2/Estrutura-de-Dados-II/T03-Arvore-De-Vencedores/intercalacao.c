#ifdef _MSC_VER
#define _CRT_SECURE_NO_WARNINGS
#endif

#include "intercalacao.h"
#include <stdio.h>
#include "arvore.h"
#include "cliente.h"
#include <stdlib.h>
#include <math.h>
#include <limits.h>

int alturaArvore(int qtd);
Arv* arvoreDefault(int alt);
void preecheArvore(FILE **vetor, Arv *tree, int qtd);
void preencheArvoreFinal(Arv *tree);
void atualizaArvore(Arv *tree, int valor, FILE **vetor, int qtd);
void fecharArquivos(FILE **vetor, int qtd);
void limparArvore(Arv *tree);

int indice = 0;
void intercalacao(char **nome_particoes, int qtd, char *nome_arquivo_saida)
{
	//Arquivo de saida
    FILE *out = fopen(nome_arquivo_saida, "wb");

    //Carregando arquivos para um array
    FILE *entrada[qtd];
    int i;
    for(i = 0; i<qtd; i++){
        entrada[i] = fopen(nome_particoes[i], "rb");
    }

    int altura = alturaArvore(qtd);
    Arv *arvore = arvoreDefault(altura);
    indice = 0;
    preecheArvore(entrada, arvore, qtd);
    //preencheArvoreFinal(arvore);
    while(arvore->valor != INT_MAX){
        fwrite(&arvore->valor, sizeof(int), 1, out);
        fwrite(arvore->c->nome, sizeof(char), sizeof(arvore->c->nome), out);
        fwrite(arvore->c->data_nascimento, sizeof(char), sizeof(arvore->c->data_nascimento), out);
        atualizaArvore(arvore, arvore->valor, entrada, qtd);
    }
    int maxi = INT_MAX;
    fwrite(&maxi, sizeof(int), 1, out);
    fwrite("", sizeof(char), sizeof(arvore->c->nome), out);
    fwrite("", sizeof(char), sizeof(arvore->c->data_nascimento), out);
    fclose(out);

    fecharArquivos(entrada, qtd);
    limparArvore(arvore);
}

//Altura que a arvore deve ter
int alturaArvore(int qtd){
    int altura = 0;

    while(pow(2, altura) < qtd) altura++;

    return altura;
}

//Criando uma arvore default
Arv* arvoreDefault(int alt){
    if(alt < 0) return NULL;
    return cria_No(-1, INT_MAX, arvoreDefault(alt-1), arvoreDefault(alt-1), NULL);
}

//Preenchendo a a arvore
void preecheArvore(FILE *vetor[], Arv *tree, int qtd){
    if(tree->esq != NULL) preecheArvore(vetor, tree->esq, qtd);
    if(tree->dir != NULL) preecheArvore(vetor, tree->dir, qtd);
    if(tree->esq == NULL && tree->dir == NULL){	//No folha
        if(indice < qtd){
            Cliente *aux = le_cliente(vetor[indice]);
            tree->c = aux;
            tree->valor = aux->cod_cliente;
            tree->index = indice;

        }else{
            tree->c = NULL;
            tree->index = -1;
            tree->valor = INT_MAX;
        }
        indice++;
    }else{
        if(tree->esq != NULL && tree->dir != NULL){
            if(tree->esq->valor < tree->dir->valor){
                tree->valor = tree->esq->valor;
                tree->c = tree->esq->c;
                tree->index = tree->esq->index;
            }
            else{
                tree->valor = tree->dir->valor;
                tree->c = tree->dir->c;
                tree->index = tree->dir->index;
            }
        }
    }
}

//Atualizando valor da arvore
void atualizaArvore(Arv *tree, int valor, FILE **vetor, int qtd){
    if(tree->esq != NULL && tree->esq->valor == valor) atualizaArvore(tree->esq, valor, vetor,qtd);
    if(tree->dir != NULL && tree->dir->valor == valor) atualizaArvore(tree->dir, valor, vetor, qtd);

    if(tree->esq == NULL && tree->dir == NULL && tree->index < qtd){
        Cliente *aux = le_cliente(vetor[tree->index]);
        tree->valor = aux->cod_cliente;
        Cliente *lixo = tree->c;
        tree->c = aux;
        free(lixo);
    }else{
        if(tree->esq->valor < tree->dir->valor){
            tree->valor = tree->esq->valor;
            tree->c = tree->esq->c;
            tree->index = tree->esq->index;
        }
        else{
            tree->valor = tree->dir->valor;
            tree->c = tree->dir->c;
            tree->index = tree->dir->index;
        }
    }
}

//Fechar arquivos
void fecharArquivos(FILE **vetor, int qtd){
    int i;
    for(i = 0; i<qtd; i++) fclose(vetor[i]);
}

//Limpar arvore
void limparArvore(Arv *tree){
    if(tree->esq != NULL) limparArvore(tree->esq);
    if(tree->dir != NULL) limparArvore(tree->dir);
    free(tree);
}
