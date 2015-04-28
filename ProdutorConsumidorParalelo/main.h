/* 
 * File:   main.h
 * Author: svaigen
 *
 * Created on April 24, 2015, 4:36 PM
 */

#ifndef MAIN_H
#define	MAIN_H

#define MAX_TAM_POPULACAO 20

#include <stdio.h>
#include <stdlib.h>
#include <pthread.h>
#include <semaphore.h>
#include <string.h>
#include <time.h>
#include "buffer_tarefas.h"
#include "buffer_individuos.h"

struct par_inteiros {
    int a;
    int b;
};

typedef struct par_inteiros par_inteiros;

int n_threads;
int tam_buffer_tarefas;
int tam_buffer_novos_individuos;
int populacao[MAX_TAM_POPULACAO];
buffer_individuos buffer_novos_individuos;
sem_t sem_mutex_tarefas;
sem_t sem_is_cheio_tarefas;
sem_t sem_is_vazio_tarefas;
sem_t sem_mutex_individuos;
sem_t sem_prenche_individuos;
sem_t sem_mutex_att_populacao;
sem_t sem_atualiza_pop;
buffer_tarefas buffer_t;

par_inteiros sorteia();
void *produz(void* id);
void *consome(void* id);
void preenche_populacao_inicial();
void imprime_populacao();
void *atualiza_populacao(void* id);
#endif	/* MAIN_H */