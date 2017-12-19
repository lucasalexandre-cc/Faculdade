#ifndef T03_ARVORE_H
#define T03_ARVORE_H

#include <stdio.h>
#include "cliente.h"

typedef struct Arv{
    int index;
    int valor;
    struct Arv *esq;
    struct Arv *dir;
    Cliente *c;
} Arv;

Arv* cria_No(int index, int valor, Arv *esq, Arv *dir, Cliente *c);

#endif //T03_ARVORE_H
