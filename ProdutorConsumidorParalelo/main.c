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
    for (i; i < MAX_TAM_POPULACAO; i++) {
        printf("Individuo %d -> %d\n", i, populacao[i]);
    }

}

int main(int argc, char** argv) {
    /*Captura dos parametros*/
    n_threads = atoi(argv[1]);
    tam_buffer_tarefas = atoi(argv[2]);
    tam_buffer_novos_individuos = atoi(argv[3]);

    /*Inicializacao de buffers, populacao e semaforos*/
    buffer_tarefas_inicializa(tam_buffer_tarefas, &buffer_t);
    buffer_individuos_inicializa(tam_buffer_novos_individuos, &buffer_novos_individuos);
    preenche_populacao_inicial();
    sem_init(&sem_mutex_tarefas, 0, 1); //semaforo binario
    sem_init(&sem_is_cheio_tarefas, 0, 0); //semaforo de 0 a tam_buffer_tarefas
    sem_init(&sem_is_vazio_tarefas, 0, tam_buffer_tarefas); //semaforo de 0 a tam_buffer_tarefas

    /*Ativacao das threads*/
    pthread_t threads[n_threads + 1];
    int t;
    int z = 0;
    pthread_create(&threads[0], NULL, produz, &z);
    for (t = 1; t <= n_threads; t++) {
        int *n = malloc(sizeof (int));
        *n = t * 10;
        pthread_create(&threads[t], NULL, consome, n);
    }
    for (t = 0; t < n_threads; t++) {
        pthread_join(threads[t], NULL);
    }
}