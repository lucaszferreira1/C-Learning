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

bool inArr(int m[LEN], int key){
    for (int i = 0;i < LEN;i++) {
        if (m[i] == key)
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

int lengthArr(bool m[LEN]){
    int cont = 0;
    for (int i = 0;i < LEN;i++) 
        if (m[i])
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

Queue* bfs(int matriz[LEN][LEN], int no) {
    bool visited[LEN] = { false };

    Queue* q = cria();
    Queue* v = cria();
    
    append(q, no);
    append(v, no);

    while (!isEmpty(q)) {
        int currNo = pop(q);
        
        for (int i = 0; i < LEN; i++) {
            if (matriz[currNo][i] != 0 && !in(v, i)) {
                append(q, i);
                append(v, i);
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

    if (flores){
        Flor pri, sec;
        int matriz[LEN][LEN];
        for (int i = 0;i < LEN;i++){
            for (int j = 0;j < LEN;j++){
                matriz[i][j] = 0;
            }
        }
        
        
        for (int i = 0;i < LEN;i++){
            for (int j = i + 1;j < LEN;j++){
                pri = flores[i];
                sec = flores[j];
                if (i != j){
                    float eucDist = pow(pow((pri.sepLen - sec.sepLen), 2) + pow((pri.sepWid - sec.sepWid), 2) + pow((pri.petLen - sec.petLen), 2) + pow((pri.petWid - sec.petWid), 2), 0.5);
                    if (eucDist <= .4){
                        matriz[i][j] = 1;
                        matriz[j][i] = 1;
                    }
                }
            }
        }
        
        
        bool has_cluster[LEN];
        bool arrays[LEN][LEN];
        for(int i=0;i<LEN;i++){
            for (int j=0;j<LEN;j++){
                arrays[i][j] = false;
            }
        }
        Queue *vis = cria();
        bool already_in;
        int index_in;
        for (int i = 0;i < LEN;i++){
            already_in = false;
            for (int j = 0;j < LEN;j++){
                if (arrays[j][i]){
                    already_in = true;
                    has_cluster[i] = false;
                    break;
                }
            }
            if (!already_in){
                has_cluster[i] = true;
                vis = bfs(matriz, i);
                for (int j=0;j<LEN;j++){
                    if (in(vis, j))
                        arrays[i][j] = true;
                }
            }
        }
        
        for (int i=0;i<LEN;i++){
            if (has_cluster[i]){
                sum += lengthArr(arrays[i]);
                printf("%d:\n", i);
                for (int j=0;j<LEN;j++){
                    printf("%d ", arrays[i][j]);
                }
            }
        }
    }
    
    
    return 0;
}