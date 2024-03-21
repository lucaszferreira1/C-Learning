#include <stdio.h>
#include <stdlib.h>
#include <pthread.h>

#define TRUE 1
#define FALSE 0
#define N_THREADS 2

void faz_algo(long t){
    printf("Thread %ld Fazendo Algo\n", t);
}
void come_memoria(){
    return;
}
void come_cpu(){
    return;
}

int sema_mem = 0;
int sema_cpu = 0;

int up(int *s){
    (*s)++;
}

int down(int *s){
    (*s) -= 1;
}

void *aplicacao(void *arg) {
    long tid = (long)arg;
    while (TRUE) {
        faz_algo(tid);
        while (sema_mem > 0);
        down(&sema_mem);
        come_memoria();
        up(&sema_mem);

        while (sema_cpu > 0);
        down(&sema_cpu);
        come_cpu();
        up(&sema_cpu);
        sleep(1);
    }
    pthread_exit(NULL);
}

int main(int argc, char *argv[]){
    pthread_t threads[N_THREADS];
    int rc;
    for (long t=0; t<N_THREADS; t++){
        printf("main: criando thread %ld\n", t);
        
        rc = pthread_create(&threads[t], NULL, aplicacao, (void *)t);
        if (rc) {
            printf("ERRO - rc=%d\n", rc);
            exit(-1);
        }
    }

    pthread_exit(NULL);

    return 0;
}
