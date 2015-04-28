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

struct lista_ligada{
    int buffer[MAX_TAM_BUFFER_TAREFAS];
    int pos_remocao;
    int pos_insercao;
    int fim_fisico;
};

typedef struct lista_ligada lista_ligada;

void lista_inicializa(int tamanho, lista_ligada* l);
void lista_add(lista_ligada* l, int n);
int lista_remove(lista_ligada* l);
void lista_imprime(lista_ligada* l);
#endif	/* LISTA_H */

