
#include <stdio.h>
#include <stdlib.h>

#include "buffer_individuos.h"

void buffer_individuos_inicializa(int tamanho, buffer_individuos* b) {
    b->pos_insercao = 0;
    b->fim_logico = tamanho;
}

void buffer_individuos_add(buffer_individuos* b, int n) {
    if (buffer_individuos_is_cheio(b)) {
        perror("ERRO! O Buffer de individuos está cheio. O programa sera finalizado.\n");
        exit(-1);
    } else {
        b->buffer[b->pos_insercao] = n;
        b->pos_insercao++;
    }
}

int buffer_individuos_esvazia(buffer_individuos* b) {
    b->pos_insercao = 0;
}

void buffer_individuos_imprime(buffer_individuos* b) {
    int i;
    printf("----Imprimindo buffer de individuos----\n");
    printf("[ ");
    for (i = 0; i < b->pos_insercao; i++) {
        printf("%d ", b->buffer[i]);
    }
    printf("]\n");

}

int buffer_individuos_is_cheio(buffer_individuos* b) {
    if (b->fim_logico == b->pos_insercao) {
        return 1;
    }
    return 0;
}

int buffer_individuos_seleciona_melhor(buffer_individuos* b) {
    int i;
    int melhor = b->buffer[0];
    for (i = 1; i < b->fim_logico; i++) {
        if (b->buffer[i] < melhor){
            melhor = b->buffer[i];
        }
    }
    return melhor;
}