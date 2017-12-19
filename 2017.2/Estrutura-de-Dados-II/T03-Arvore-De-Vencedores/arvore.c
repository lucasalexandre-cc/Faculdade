#include <stdio.h>
#include <stdlib.h>
#include "arvore.h"

Arv* cria_No(int index, int valor, Arv *esq, Arv *dir, Cliente *c){
    Arv *resp = (Arv *) malloc(sizeof(Arv));

    resp->index = index;
    resp->esq = esq;
    resp->dir = dir;
    resp->c = c;
    resp->valor = valor;

    return resp;
}

