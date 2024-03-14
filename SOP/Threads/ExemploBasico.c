#include <pthread.h>
#include <stdio.h>
#include <stdlib.h>

#define NUM_THREADS 5

void *PrintHello(void *arg) {
    long tid = (long)arg;
    printf("Alo da thread %ld\n", tid);
    pthread_exit(NULL);
}

void *PrintSquared(void *arg){
    long x = (long)arg;
    x *= x;
    printf("x^2 = %ld\n", x);
    pthread_exit((void *)x);
}

int main (int argc, char *argv[]) {
    pthread_t threads[(NUM_THREADS*2)+3];
    int rc;
    long t, result;
    long i = atol(argv[1]);
    long sum = 0;
    for (t=0; t<NUM_THREADS; t++){
        printf("main: criando thread %ld\n", t);
        
        rc = pthread_create(&threads[t], NULL, PrintHello, (void *)t);
        if (rc) {
            printf("ERRO - rc=%d\n", rc);
            exit(-1);
        }
    }
    for (t=t; t<NUM_THREADS*2+3; t++){
        void *status;
        printf("main: criando thread %ld\n", t);
        
        rc = pthread_create(&threads[t], NULL, PrintSquared, (void *)i);
        pthread_join(threads[t], &status);
        result = (long) status;
        sum += result;
        if (rc) {
            printf("ERRO - rc=%d\n", rc);
            exit(-1);
        }
    }
    printf("\n Sum : %ld\n", sum);
    /* Ultima coisa que main() deve fazer */
    pthread_exit(NULL);
    return 0;
}