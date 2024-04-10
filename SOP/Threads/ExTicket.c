#include <stdio.h>
#include <stdlib.h>
#include <pthread.h>
#include <semaphore.h>

#define N_THREADS 4
#define N_LUGARES 10000
#define N_CLIENTES 10000
#define PRECO_ING 300

int lugares[N_LUGARES];
sem_t sema_lugares[N_LUGARES];
pthread_barrier_t barr;

int compra_lugar(int lugar, int din){
	if (din >= PRECO_ING){
		lugares[lugar] += 1;
		return 1;
	}
	return 0;
}

void *escolhe_lugar(void *arg){
	int dinheiro, lugar;
	time_t t;
	srand((unsigned) time(&t));
	for (int i=0;i < N_CLIENTES;i++){
		dinheiro = rand() % 1000;
		lugar = rand() % N_LUGARES;
		sem_wait(&sema_lugares[lugar]);
		if (lugares[lugar] == 0)
			compra_lugar(lugar, dinheiro);
		sem_post(&sema_lugares[lugar]);
	}
	pthread_exit(NULL);
}

int main(int argc, char *argv[]){
	for (int i=0;i<N_LUGARES;i++){
		sem_init(&sema_lugares[i], 0, 1);
		lugares[i] = 0;
	}

    pthread_t threads[N_THREADS];
    int rc;
    for (long t=0; t<N_THREADS; t++){
        printf("main: criando thread %ld\n", t);
        
        rc = pthread_create(&threads[t], NULL, escolhe_lugar, NULL);
        if (rc) {
            printf("ERRO - rc=%d\n", rc);
            exit(-1);
        }
    }
	
	for (long t=0; t < N_THREADS; t++) {
        pthread_join(threads[t], NULL);
    }

	int err = 0;
	int empty = 0;
	for (int i=0;i<N_LUGARES;i++){
		sem_destroy(&sema_lugares[i]);
		if (lugares[i] == 0)
			empty++;
		else if (lugares[i] > 1)
			err = 1;
	}
	printf("Lugares vazios = %d", empty);
    return err;
}
