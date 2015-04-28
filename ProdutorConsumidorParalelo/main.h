/* 
 * File:   main.h
 * Author: svaigen
 *
 * Created on April 24, 2015, 4:36 PM
 */

#ifndef MAIN_H
#define	MAIN_H

#define TAM_POPULACAO 20

#include <stdio.h>
#include <stdlib.h>
#include <pthread.h>
#include <semaphore.h>
#include <string.h>
#include <time.h>
#include "lista.h"

struct par_inteiros {
    int a;
    int b;
};

typedef struct par_inteiros par_inteiros;

int n_threads;
int tam_buffer_tarefas;
int tam_buffer_novos_individuos;
int populacao[TAM_POPULACAO];
int * buffer_novos_individuos;
sem_t sem_exc_mutua;
sem_t sem_is_cheio;
sem_t sem_is_vazio;
lista buffer_tarefas;

#endif	/* MAIN_H */

