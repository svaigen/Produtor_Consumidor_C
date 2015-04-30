/* 
 * File:   main.c
 * Author: svaigen
 *
 * Created on April 24, 2015, 10:08 AM
 */

#include "main.h"

par_inteiros sorteia() {
    par_inteiros p;
    int i;
    srand(time(NULL));
    for (i = 0; i < 500000000; i++);
    p.a = populacao[(int) rand() % 19];
    p.b = populacao[(int) rand() % 19];
    return p;
}

void *produz(void* id) {
    par_inteiros p;
    int *pid = (int*) id;
    while (1) {
        printf("Produtor %d acessa buffer tarefas\n", *pid);
        par_inteiros s = sorteia();
        p.a = (s.a * s.b) / (s.a + s.b);
        p.b = (s.a * s.a) / (s.a + s.b);
        sem_wait(&sem_is_vazio_tarefas);
        sem_wait(&sem_mutex_tarefas);
        buffer_tarefas_add(&buffer_t, p.a);
        //lista_imprime(&buffer_t);
        sem_post(&sem_mutex_tarefas);
        sem_post(&sem_is_cheio_tarefas);

        sem_wait(&sem_is_vazio_tarefas);
        sem_wait(&sem_mutex_tarefas);
        buffer_tarefas_add(&buffer_t, p.b);
        //lista_imprime(&buffer_t);
        sem_post(&sem_mutex_tarefas);
        sem_post(&sem_is_cheio_tarefas);
    }
}

void *consome(void* id) {
    int *pid = (int*) id;
    while (1) {
        printf("Consumidor %d acessa buffer de tarefas \n", *pid);
        sem_wait(&sem_is_cheio_tarefas);
        sem_wait(&sem_mutex_tarefas);
        int n = buffer_tarefas_remove(&buffer_t);
        sem_post(&sem_mutex_tarefas);
        sem_post(&sem_is_vazio_tarefas);
        int i;
        for (i = 0; i < 2147483647; i++);
        for (i = 0; i < 2147483647; i++);
        sem_wait(&sem_prenche_individuos);
        sem_wait(&sem_mutex_individuos);
        buffer_individuos_add(&buffer_novos_individuos, n);
        if (buffer_individuos_is_cheio(&buffer_novos_individuos)) {
            sem_post(&sem_atualiza_populacao);
        }
        sem_post(&sem_mutex_individuos);
        //lista_imprime(&buffer_t);
    }
}

void preenche_populacao_inicial() {
    int i = 0;
    srand(time(NULL));
    for (i; i < MAX_TAM_POPULACAO; i++) {
        populacao[i] = rand() % 100;
    }
}

void imprime_populacao() {
    int i = 0;
    printf("---Imprimindo Populacao: [ ");
    for (i; i < MAX_TAM_POPULACAO; i++) {
        printf("%d ",populacao[i]);
    }
    printf("] ---\n");

}

void *atualiza_populacao(void* id) {
    while (1) {
        sem_wait(&sem_atualiza_populacao);
        int melhor = buffer_individuos_seleciona_melhor(&buffer_novos_individuos);
        sem_wait(&sem_mutex_individuos);
        buffer_individuos_esvazia(&buffer_novos_individuos);
        sem_post(&sem_mutex_individuos);
        int i;
        for (i = 0; i < buffer_novos_individuos.fim_logico; i++) {
            sem_post(&sem_prenche_individuos);
            int *n = malloc(sizeof (int));
            sem_getvalue(&sem_prenche_individuos, n);
        }

        /*Codigo de atualizacao*/
        int substituir = 0;
        sem_wait(&sem_mutex_populacao);
        for (i = 1; i < MAX_TAM_POPULACAO; i++) {
            if (populacao[substituir] < populacao[i]) {
                substituir = i;
            }
        }
        populacao[substituir] = melhor;
        sem_post(&sem_mutex_populacao);
        imprime_populacao();
    }


}

int main(int argc, char** argv) {
    /*Captura dos parametros*/
    n_threads = atoi(argv[1]);
    tam_buffer_tarefas = n_threads * 2;
    tam_buffer_novos_individuos = n_threads;

    /*Inicializacao de buffers, populacao e semaforos*/
    buffer_tarefas_inicializa(tam_buffer_tarefas, &buffer_t);
    buffer_individuos_inicializa(tam_buffer_novos_individuos, &buffer_novos_individuos);
    preenche_populacao_inicial();
    sem_init(&sem_mutex_tarefas, 0, 1); //semaforo binario
    sem_init(&sem_is_cheio_tarefas, 0, 0); //semaforo de 0 a tam_buffer_tarefas
    sem_init(&sem_is_vazio_tarefas, 0, tam_buffer_tarefas); //semaforo de 0 a tam_buffer_tarefas
    sem_init(&sem_prenche_individuos, 0, tam_buffer_novos_individuos); //semaforo de 0 a tam_buffer_novos_individuos
    sem_init(&sem_atualiza_populacao, 0, 0); //semaforo binario
    sem_init(&sem_mutex_individuos, 0, 1); //semaforo binario
    sem_init(&sem_mutex_populacao, 0, 1); //semaforo binario

    imprime_populacao();
    
    /*Ativacao das threads*/
    pthread_t threads[n_threads + 2];
    int t;
    int z = 1;
    pthread_create(&threads[0], NULL, produz, &z);
    for (t = 1; t <= n_threads; t++) {
        int *n = malloc(sizeof (int));
        *n = t;
        pthread_create(&threads[t], NULL, consome, n);
    }
    pthread_create(&threads[n_threads + 1], NULL, atualiza_populacao, &z);
    for (t = 0; t < (n_threads + 2); t++) {
        pthread_join(threads[t], NULL);
    }
}