#include "buffer_tarefas.h"

void buffer_tarefas_inicializa(int tamanho, buffer_tarefas* l) {
    l->pos_remocao = 0;
    l->pos_insercao = 0;
    l->fim_fisico = tamanho;
}

void buffer_tarefas_add(buffer_tarefas* l, int n) {
    //printf("pos ins antes -> %d\n",l->pos_insercao);
    l->buffer[l->pos_insercao] = n;
    l->pos_insercao = (l->pos_insercao + 1) % l->fim_fisico;
    //printf("pos ins depois -> %d\n",l->pos_insercao);
}

int buffer_tarefas_remove(buffer_tarefas* l) {
    int ret = l->buffer[l->pos_remocao];
    l->pos_remocao = (l->pos_remocao + 1) % l->fim_fisico;
    return ret;
}

void buffer_tarefas_imprime(buffer_tarefas* l) {
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