#include <stdio.h>
#include <stdlib.h>

typedef struct ab{
    int info;
    int cor;
    struct ab *esq, *dir;
}TAB;

TAB* criaArvore(int info, TAB *esq, TAB *dir){
    TAB *p = (TAB *)malloc(sizeof(TAB));
    p->info = info;
    p->esq = esq;
    p->dir = dir;

    return p;
}

void printaArvore(TAB *a){
    if(!a) return;
    printaArvore(a->esq);
    printf("%i ", a->info);
    printaArvore(a->dir);
}

void printarCor(TAB *a){
    if(!a) return;
    printarCor(a->esq);
    printf("%i:%i ",a->info, a->cor);
    printarCor(a->dir);
}

TAB* copia (TAB *a);
TAB* espelho (TAB *a);
TAB* maior(TAB *a);
TAB* menor(TAB *a);
int igual (TAB* a1, TAB* a2);
TAB* retira_impares (TAB* arv);
void colore (TAB* arv);
int ni(TAB *a);
int nf(TAB *a);

int main(void){
    TAB *raiz = criaArvore(3, NULL, NULL);
    raiz->esq = criaArvore(1, NULL, NULL);
    raiz->esq->esq = criaArvore(0, NULL, NULL);
    raiz->esq->dir = criaArvore(2, NULL, NULL);
    raiz->esq->dir->dir = criaArvore(1, NULL, NULL);
    raiz->dir = criaArvore(20, NULL, NULL);
    raiz->dir->dir = criaArvore(30, NULL, NULL);
    raiz->dir->dir->dir = criaArvore(35, NULL, NULL);

    int i = nf(raiz);
    printf("%i \n",i);

    return 0;
}


//Q02
TAB* copia (TAB *a){
    if(!a) return a;
    TAB *p = criaArvore(a->info, copia(a->esq), copia(a->dir));
    return p;
}

//Q03
TAB* espelho (TAB *a){
    if(!a) return a;
    TAB *p = criaArvore(a->info, a->dir, a->esq);
    return p;
}

//Q04
int max(int a, int b){
    if(a>b) return a;
    return b;
}
TAB* maior(TAB *a){
    if(!(a->dir)) return a;
    while(a->dir) a = a->dir;
    return a;
}

//Q05
int min(int a, int b){
    if(a > b) return a;
    return b;
}
TAB* menor(TAB *a){
    if((!a->esq)) return a;
    while(a->esq) a = a->esq;
    return a;
}

//Q06
int igual (TAB* a1, TAB* a2){
    if(a1 && a2){
        if(a1->info != a2->info) return 0;
        return igual(a1->esq, a2->esq) && igual(a1->dir, a2->dir);
    }
    else if(!a1 && a2) return 0;
    else if(a1 && !a2) return 0;
    return 1;
}

//Q07
void exclueNo(TAB *no){//Exceção de folhas
    TAB *flag = no;
    if(no->esq){
        while(no->esq->esq) no = no->esq;
        flag->info = no->esq->info;
        TAB *lixo = no->esq;
        no->esq = no->esq->dir;
        free(lixo);
    }
    else{
        while(no->dir->dir) no = no->dir;
        flag->info = no->dir->info;
        TAB *lixo = no->dir;
        no->dir = no->dir->esq;
        free(lixo);
    }
}
TAB* retira_impares (TAB* arv){
    if(!arv) return arv; //Se arv é nulo, retorna NULL (ele mesmo)

    if(arv->info%2){
        if(arv->esq || arv->dir){
            exclueNo(arv);
            retira_impares(arv);
        }
        else{
            free(arv);
            return NULL;
        }
    }

    if(arv->esq){
        if(arv->esq->info%2){
            if(arv->esq->esq || arv->esq->dir){
                exclueNo(arv->esq);
                retira_impares(arv);
            }
            else{
                TAB *lixo = arv->esq;
                arv->esq = NULL;
                free(lixo);
            }
        }
    }

    if(arv->dir){
        if(arv->dir->info%2){
            if(arv->dir->esq || arv->dir->dir){
                exclueNo(arv->dir);
                retira_impares(arv);
            }else{
                TAB *lixo = arv->dir;
                arv->dir = NULL;
                free(lixo);
            }
        }
    }

    retira_impares(arv->dir);
    retira_impares(arv->esq);

    return arv;
}

//Q08 -> 1: vermelho, 0:preto
void aux_colore(TAB *a, int indice){
    if(!a) return;
    if(indice%2 == 0) a->cor = 1;
    else a->cor = 0;
    aux_colore(a->dir, indice+1);
    aux_colore(a->esq, indice+1);
}

void colore (TAB* arv){
    aux_colore(arv, 0);
}

//Q09
int ni(TAB *a){
    if(!a) return 0;
    return 1+ni(a->esq) + ni(a->dir);
}

//Q10
int nf(TAB *a){
    if(!a) return 0;
    if(!a->esq && !a->dir) return 1;
    return nf(a->esq) + nf(a->dir);
}
