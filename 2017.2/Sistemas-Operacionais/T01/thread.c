#include <stdio.h>
#include <pthread.h>

void thr_func(int *id); /* codigo threads 1 e 3 */
void thr_yield(int *id); /* codigo thread 2 */

int main(){
    pthread_t thr1,thr2,thr3; /* declara as threads */
    int nThrID1,nThrID2,nThrID3;

    nThrID1 = 1;
    nThrID2 = 2;
    nThrID3 = 3;

    /* cria threads: id, inic, funcao, param funcao */
    pthread_create(&thr1,NULL,(void* )thr_func,&nThrID1);
    pthread_create(&thr2,NULL,(void* )thr_yield,&nThrID2);
    pthread_create(&thr3,NULL,(void* )thr_func,&nThrID3);

    /* espera fim das threads: id, status de saida */
    pthread_join(thr3,NULL);
    pthread_join(thr2,NULL);
    pthread_join(thr1,NULL);
}

/* codigo das threads 1 e 3 */
void thr_func(int *id){
    printf("Eu sou a thread %d\n",*id);
}

/* codigo da thread 2 */
void thr_yield(int *id){
    sched_yield();
    printf("Eu sou a thread %d\n",*id);
}
/* compilacao: gcc -o threads -lthread -lposix4 threads.c */