#include "lista_ligada.h"

void lista_inicializa(int tamanho, lista_ligada* l) {
    l->pos_remocao = 0;
    l->pos_insercao = 0;
    l->fim_fisico = tamanho;
}

void lista_add(lista_ligada* l, int n) {
    //printf("pos ins antes -> %d\n",l->pos_insercao);
    l->buffer[l->pos_insercao] = n;
    l->pos_insercao = (l->pos_insercao + 1) % l->fim_fisico;
    //printf("pos ins depois -> %d\n",l->pos_insercao);
}

int lista_remove(lista_ligada* l) {
    int ret = l->buffer[l->pos_remocao];
    l->pos_remocao = (l->pos_remocao + 1) % l->fim_fisico;
    return ret;
}

void lista_imprime(lista_ligada* l) {
    printf("\n----Imprimindo lista----\n");
    int i;
    printf("[ ");
    if (l->pos_remocao <= l->pos_insercao) {
        for (i = l->pos_remocao; i < l->pos_insercao; i++) {
            printf("%d ", l->buffer[i]);
            i++;
        }
    } else {
        for (i = l->pos_remocao; i < l->fim_fisico; i++) {
            printf("%d ", l->buffer[i]);
            i++;
        }
        for (i = 0; i < l->pos_insercao; i++) {
            printf("%d ", l->buffer[i]);
            i++;
        }
    }
    printf("]");
    printf("\n\n");
}