/* 
 * File:   buffer_individuos.h
 * Author: svaigen
 *
 * Created on April 28, 2015, 10:25 AM
 */

#ifndef BUFFER_INDIVIDUOS_H
#define	BUFFER_INDIVIDUOS_H

#define MAX_TAM_BUFFER_INDIVIDUOS 1024

struct buffer_individuos {
    int buffer[MAX_TAM_BUFFER_INDIVIDUOS];
    int fim_logico;
    int pos_insercao;
};

typedef struct buffer_individuos buffer_individuos;

void buffer_individuos_inicializa(int tamanho, buffer_individuos* b);
void buffer_individuos_add(buffer_individuos* b, int n);
int buffer_individuos_esvazia(buffer_individuos* b);
void buffer_individuos_imprime(buffer_individuos* b);
int buffer_individuos_is_cheio(buffer_individuos* b);
/*
 * TODO
 * <tipo> buffer_individuos_seleciona_melhor(buffer_individuos* b);
 */

#endif	/* BUFFER_INDIVIDUOS_H */

