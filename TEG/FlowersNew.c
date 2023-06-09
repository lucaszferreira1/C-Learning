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


float get_avrg_flor(Flor f){
    float sum = f.sepLen + f.sepWid + f.petLen + f.petWid;
    return sum / 4;
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
                    if (eucDist <= .412){
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
        
        
        
        float averages_clusters[3];
        bool clusters[3][LEN];
        for (int i = 0;i < 3;i++){
            for (int j = 0;j < LEN;j++){
                clusters[i][j] = false;
            }    
        }
        int count_avrg = 0;
        float sum;
        for (int i=0;i<LEN;i++){
            sum = 0;
            if (has_cluster[i]){
                for (int j=0;j<LEN;j++){
                    if (arrays[i][j])
                        sum += get_avrg_flor(flores[i]);
                }
                if (lengthArr(arrays[i]) > 5){
                    for (int j = 0;j < LEN;j++){
                        clusters[count_avrg][j] = arrays[i][j];
                    }
                    averages_clusters[count_avrg] = sum / lengthArr(arrays[i]);
                    count_avrg++;
                }
            }
        }
        
        
        float f;
        float dist, dist2;
        
        FILE *fp;
        fp = fopen("result.txt", "w");
        int pos;
        if (!fp)
            printf("Can't open file\n");
        else{
            for (int i=0;i<LEN;i++){
                already_in = false;
                for (int j = 0;j<3;j++){
                    if (clusters[j][i])
                        already_in = true;
                }
                pos = 0;
                if (!already_in){
                    f = get_avrg_flor(flores[i]);
                    dist = f - averages_clusters[0];
                    if (dist < 0)
                        dist *= -1;
                    for (int j = 1;j < 3;j++){
                        dist2 = f - averages_clusters[j];
                        if (dist2 < 0)
                            dist2 *= -1;
                        if (dist > dist2){
                            dist = dist2;
                            pos = j;
                        }
                    }
                }else{
                    for (int j = 0;j<3;j++){
                        if (clusters[j][i])
                            pos = j;
                    }
                }
                fprintf(fp, "%d %d\n", i, pos);
            }
            fclose(fp);
        }    
        
        
    }
    
    
    return 0;
}
