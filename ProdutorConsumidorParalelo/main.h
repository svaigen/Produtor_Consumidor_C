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

struct par_inteiros {
    int a;
    int b;
};

typedef struct par_inteiros par_inteiros;

int n_threads;
int tam_buffer_tarefas;
int tam_buffer_novos_individuos;
int populacao[MAX_TAM_POPULACAO];
int * buffer_novos_individuos;
sem_t sem_exc_mutua;
sem_t sem_is_cheio;
sem_t sem_is_vazio;
buffer_tarefas buffer_t;

#endif	/* MAIN_H */

