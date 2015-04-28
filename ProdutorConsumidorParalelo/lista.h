/* 
 * File:   lista.h
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

struct lista{
    int buffer[MAX_TAM_BUFFER_TAREFAS];
    int pos_remocao;
    int pos_insercao;
    int fim_fisico;
};

typedef struct lista lista;

void lista_inicializa(int tamanho, lista* l);
void lista_add(lista* l, int n);
int lista_remove(lista* l);
void lista_imprime(lista* l);
#endif	/* LISTA_H */

