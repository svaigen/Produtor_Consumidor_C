/* 
 * File:   lista_ligada.h
 * Author: svaigen
 *
 * Created on April 24, 2015, 4:40 PM
 */

#ifndef LISTA_H
#define	LISTA_H

#include <stdio.h>
#include <stdlib.h>
#include <malloc.h>

#define MAX_TAM_BUFFER_TAREFAS 1024

struct buffer_tarefas{
    int buffer[MAX_TAM_BUFFER_TAREFAS];
    int pos_remocao;
    int pos_insercao;
    int fim_fisico;
};

typedef struct buffer_tarefas buffer_tarefas;

void buffer_tarefas_inicializa(int tamanho, buffer_tarefas* l);
void buffer_tarefas_add(buffer_tarefas* l, int n);
int buffer_tarefas_remove(buffer_tarefas* l);
void buffer_tarefas_imprime(buffer_tarefas* l);

#endif	/* LISTA_H */

