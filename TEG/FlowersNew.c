#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <stdbool.h>
#include <math.h>

#define MAXCHAR 128
#define LEN 150

// Estrutura da flor, sendo, "sepal.length","sepal.width","petal.length","petal.width","variety"

typedef struct{
    float sepLen, sepWid, petLen, petWid;
    char nome[16];
}Flor;


typedef struct {
    int items[LEN];
    int frente;
    int cauda;
} Queue;


Queue* cria(){
    Queue *q = malloc(sizeof(Queue));
    q->frente = -1;
    q->cauda = -1;
    return q;
}


bool isEmpty(Queue* q) {
    if (q->cauda == -1) {
        return true;
    }
    return false;
}


void append(Queue* q, int valor) {
    if (q->cauda == LEN - 1) {
        return;
    }

    if (q->frente == -1) {
        q->frente = 0;
    }

    q->cauda++;
    q->items[q->cauda] = valor;
}

int pop(Queue* q) {
    if (isEmpty(q)) {
        return -1;
    }

    int valor = q->items[q->frente];
    q->frente++;

    if (q->frente > q->cauda) {
        q->frente = -1;
        q->cauda = -1;
    }

    return valor;
}

bool in(Queue* q, int key){
    if (isEmpty(q)) 
        return false;

    for (int i = q->frente;i <= q->cauda;i++) {
        if (q->items[i] == key)
            return true;
    }
    return false;
}

int length(Queue* q){
    int cont = 0;
    for (int i = q->frente;i <= q->cauda;i++) 
        cont++;
    return cont;
}

void display(Queue* q) {
    if (isEmpty(q)) 
        return;

    for (int i = q->frente;i <= q->cauda;i++) {
        printf("%d ", q->items[i]);
    }
}

Queue* bfs(float matriz[LEN][LEN], int no) {
    bool visited[LEN] = { false };

    Queue* q = cria();
    Queue* v = cria();
    append(q, no);
    visited[no] = true;

    while (!isEmpty(q)) {
        int currNo = pop(q);
        append(v, currNo);

        for (int i = 0; i < LEN; i++) {
            if (matriz[currNo][i] != 0 && !visited[i]) {
                append(q, i);
                visited[i] = true;
            }
        }
    }
    return v;
}


int main()
{
    FILE *fp;
    Flor flores[LEN];
    fp = fopen("IrisDataset.txt", "r");
    // O arquivo é aberto e se lê o conteúdo, o qual vai para a lista flores
    if (!fp)
        printf("Can't open file\n");
    else{
        Flor flor;
        int cont = 0;
        char line[MAXCHAR];
        char *token;
        while(fgets(line, MAXCHAR, fp )!= NULL){
            token = strtok(line, ",");
            flor.sepLen = atof(token);
            token = strtok(NULL, ",");
            flor.sepWid = atof(token);
            token = strtok(NULL, ",");
            flor.petLen = atof(token);
            token = strtok(NULL, ",");
            flor.petWid = atof(token);
            token = strtok(NULL, ",");
            strcpy(flor.nome, token);
            
            flores[cont] = flor;
            cont++;
        }
    }
    
    fclose(fp);
    
    // Cálculo de distância euclideana
    if (flores){
        Flor pri, sec;
        float matriz[LEN][LEN];
        // Todos os valores são inicializados e setados para 0
        for (int i = 0;i < LEN;i++){
            for (int j = 0;j < LEN;j++){
                matriz[i][j] = 0;
            }
        }
        // É calculado a distância euclideana de todos para todos
        for (int i = 0;i < LEN;i++){
            for (int j = i + 1;j < LEN;j++){
                pri = flores[i];
                sec = flores[j];
                if (i != j){
                    float eucDist = pow(pow((pri.sepLen - sec.sepLen), 2) + pow((pri.sepWid - sec.sepWid), 2) + pow((pri.petLen - sec.petLen), 2) + pow((pri.petWid - sec.petWid), 2), 0.5);
                    if (eucDist <= .4){
                        matriz[i][j] = eucDist;
                    }
                }
            }
        }
        
        Queue *vis = cria();
        for (int i=0;i<LEN;i++){
            
            vis = bfs(matriz, i);
            display(vis);
            printf("\n Len = %d\n", length(vis));
        }
    }
    
    
    return 0;
}
