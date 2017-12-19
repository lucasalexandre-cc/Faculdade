#include <pthread.h>
#include <semaphore.h>
#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>

#define N_CLIENTES 10
#define 	N_CADEIRAS 5

sem_t cadeiras;

sem_t barbeiro_cabelo;
sem_t barbeiro_barba;
sem_t barbeiro_pinta;

sem_t cabelo_cortado;
sem_t cabelo_pintado;
sem_t barbeado;

sem_t cliente_cadeira_cabelo;
sem_t cliente_cadeira_barba;
sem_t cliente_cadeira_pinta;

void* func_barbeiro(void *v) {

  while(1) {
    sem_wait(&cliente_cadeira_barba);
    printf("Barbeiro barbeou um cliente.\n");
    sem_post(&barbeado);
  }
  return NULL;
}

void* func_cabelereiro(void *v) {

  while(1) {
    sem_wait(&cliente_cadeira_cabelo);
    printf("Barbeiro cortou o cabelo de um cliente.\n");
    sem_post(&cabelo_cortado);
  }
  return NULL;
}

void* func_barbeiro_pinta(void *v) {

  while(1) {
    sem_wait(&cliente_cadeira_pinta);
    printf("Barbeiro pintou o cabelo de um cliente.\n");
    sem_post(&cabelo_pintado);
  }
  return NULL;
}

void* func_cliente_cabelo(void* v) {
  int id = *(int*) v;

  sleep(id%3);
  if (sem_trywait(&cadeiras) == 0) {
    printf("Cliente %d entrou na barbearia para cortar o cabelo.\n", id);
    sem_wait(&barbeiro_cabelo);
    printf("Cliente %d sentou na cadeira do cabelereiro.\n", id);
    sem_post(&cliente_cadeira_cabelo);
    sem_post(&cadeiras);
    sem_wait(&cabelo_cortado);
    sem_post(&barbeiro_cabelo);
    printf("Cliente %d deixou a barbearia.\n", id);
  } else
    printf("Cliente %d não entrou na barbearia.\n", id);
  return NULL;
}

void* func_cliente_barba(void* v) {
  int id = *(int*) v;

  sleep(id%3);
  if (sem_trywait(&cadeiras) == 0) {
    printf("Cliente %d entrou na barbearia para fazer a barba.\n", id);
    sem_wait(&barbeiro_barba);
    printf("Cliente %d sentou na cadeira do barbeiro.\n", id);
    sem_post(&cliente_cadeira_barba);
    sem_post(&cadeiras);
    sem_wait(&barbeado);
    sem_post(&barbeiro_barba);
    printf("Cliente %d deixou a barbearia.\n", id);
  } else
    printf("Cliente %d não entrou na barbearia.\n", id);
  return NULL;
}


void* func_cliente_pinta(void* v) {
  int id = *(int*) v;

  sleep(id%3);
  if (sem_trywait(&cadeiras) == 0) {
    printf("Cliente %d entrou na barbearia para pintar o cabelo.\n", id);
    sem_wait(&barbeiro_pinta);
    printf("Cliente %d sentou na cadeira para ter seu cabelo pintado.\n", id);
    sem_post(&cliente_cadeira_pinta);
    sem_post(&cadeiras);
    sem_wait(&cabelo_pintado);
    sem_post(&barbeiro_pinta);
    printf("Cliente %d deixou a barbearia.\n", id);
  } else
    printf("Cliente %d não entrou na barbearia.\n", id);
  return NULL;
}

int main() {
  pthread_t thr_clientes_corte[N_CLIENTES], thr_clientes_barba[N_CLIENTES], thr_clientes_pinta[N_CLIENTES], thr_barbeiro, thr_cabelereiro, thr_barbeiro_pinta;
  int i, id[N_CLIENTES];

  sem_init(&cadeiras, 0, 5);
  sem_init(&barbeiro_cabelo, 0, 1);
  sem_init(&barbeiro_barba, 0, 1);
  sem_init(&barbeiro_pinta, 0, 1);
  sem_init(&cliente_cadeira_cabelo, 0, 0);
  sem_init(&cliente_cadeira_barba, 0, 0);
  sem_init(&cliente_cadeira_pinta, 0, 0);
  sem_init(&cabelo_cortado, 0, 0);
  sem_init(&cabelo_pintado, 0, 0);
  sem_init(&barbeado, 0, 0);
  
  for (i = 0; i < N_CLIENTES; i++) {
    id[i] = i;
    pthread_create(&thr_clientes_corte[i], NULL, func_cliente_cabelo, (void*) &id[i]);
  }

  for (i = 0; i < N_CLIENTES; i++) {
    id[i] = i+N_CLIENTES;
    pthread_create(&thr_clientes_barba[i], NULL, func_cliente_barba, (void*) &id[i]);
  }

  for (i = 0; i < N_CLIENTES; i++) {
    id[i] = i+ 2*(N_CLIENTES);
    pthread_create(&thr_clientes_pinta[i], NULL, func_cliente_pinta, (void*) &id[i]);
  }

  pthread_create(&thr_barbeiro, NULL, func_barbeiro, NULL);
  pthread_create(&thr_cabelereiro, NULL, func_cabelereiro, NULL);
  pthread_create(&thr_barbeiro_pinta, NULL, func_barbeiro_pinta, NULL);
  
  for (i = 0; i < N_CLIENTES; i++) 
    pthread_join(thr_clientes_corte[i], NULL);
  
  for (i = 0; i < N_CLIENTES; i++) 
    pthread_join(thr_clientes_barba[i], NULL);
  
  for (i = 0; i < N_CLIENTES; i++) 
    pthread_join(thr_clientes_pinta[i], NULL);

  /* Barbeiro é assassinado */
  
  return 0;
}