#include <stdio.h>
#include <stdlib.h>

int pesquisaSequencial(int chave, int v[], int n) {
    int i;
    for (i = 0; i < n; i++) {
        if (v[i] == chave) {
            return i+1;
        }
    }
    return -1; //índice inválido
}

int pesquisaSequencialSentinela(int chave, int v[], int n) {
    int i = 0;
    v[n] = chave; //A última posição do vetor possui o sentinela
    int cont = 1;
    while (v[i] != chave) {
        i++;
        cont++;
    }
    if (i < n) return cont;
    return -1; //Índice inválido
}

int pesquisaBinaria(int chave, int v[], int n) {
    int inicio = 0;
    int meio;
    int fim = n - 1;
    int cont = 1;
    while (inicio <= fim) {
        meio = (inicio + fim) / 2;
        if (chave == v[meio]) {
            return cont;
        } else if (chave < v[meio]) {
            fim = meio - 1;
        } else {
            inicio = meio + 1;
        }
        cont++;
    }
    return -1;
}

int pesquisaBinariaRecursiva(int chave, int v[], int ini, int fim, int cont) {
    int meio = (ini + fim) / 2;
    cont++;
    if (ini > fim){
        return -1;
    }
    if (chave == v[meio]){
        return cont;
    }
    else if (chave < v[meio])
        return pesquisaBinariaRecursiva(chave, v, ini, meio--, cont);
    else
        return pesquisaBinariaRecursiva(chave, v, meio++, fim, cont);
}

int pesquisaInterpolacao(int chave, int v[], int n) {
    int ini = 0;
    int meio;
    int fim = n - 1;
    int cont = 1;
    while (ini <= fim) {
        meio = ini + ((fim - ini) * (chave - v[ini])) / (v[fim] - v[ini]);
        if (chave < v[meio]) {
            fim = meio - 1;
        } else if (chave > v[meio]) {
            ini = meio + 1;
        } else {
            return cont;
        }
        cont++;
    }
    return -1;
}


int* create_ordered_list(int n) {
    int* list = (int*) malloc(n * sizeof(int));
    for (int i = 0; i < n; i++) {
        list[i] = i;
    }
    return list;
}


int main()
{
    int sums[] = {0, 0, 0, 0, 0};
    int highest[5];
    int lowest[5];
    int n = 513;
    int* v = create_ordered_list(n);
    int h = 0;
    int chave;
    
    highest[0] += pesquisaSequencial(chave, v, n);
    highest[1] += pesquisaSequencialSentinela(chave, v, n);
    highest[2] += pesquisaBinaria(chave, v, n);
    highest[3] += pesquisaBinariaRecursiva(chave, v, 0, n, 0);
    highest[4] += pesquisaInterpolacao(chave, v, n);
    
    lowest[0] = highest[0];
    lowest[1] = highest[1];
    lowest[2] = highest[2];
    lowest[3] = highest[3];
    lowest[4] = highest[4];
    
    for (int i=0;i<n;i++){
        chave = i;
        
        h = pesquisaSequencial(chave, v, n);
        sums[0] += h;
        if (h > highest[0]) 
            highest[0] = h;
        if (h < lowest[0])
            lowest[0] = h;
        
        h = pesquisaSequencialSentinela(chave, v, n);
        sums[1] += h;
        if (h > highest[1]) 
            highest[1] = h;
        if (h < lowest[1])
            lowest[1] = h;
        
        h = pesquisaBinaria(chave, v, n);
        sums[2] += h;
        if (h > highest[2]) 
            highest[2] = h;
        if (h < lowest[2])
            lowest[2] = h;
        
        h = pesquisaBinariaRecursiva(chave, v, 0, n, 0);
        sums[3] += h;
        if (h > highest[3]) 
            highest[3] = h;
        if (h < lowest[3])
            lowest[3] = h;
        
        h = pesquisaInterpolacao(chave, v, n);
        sums[4] += h;
        if (h > highest[4]) 
            highest[4] = h;
        if (h < lowest[4])
            lowest[4] = h;
    }
    printf("Maiores: \n");
    printf("%d\n", highest[0]);
    printf("%d\n", highest[1]);
    printf("%d\n", highest[2]);
    printf("%d\n", highest[3]);
    printf("%d\n", highest[4]);
    
    printf("Menores: \n");
    printf("%d\n", lowest[0]);
    printf("%d\n", lowest[1]);
    printf("%d\n", lowest[2]);
    printf("%d\n", lowest[3]);
    printf("%d\n", lowest[4]);
    
    printf("Média: \n");
    printf("%f\n", (float)sums[0] / n);
    printf("%f\n", (float)sums[1] / n);
    printf("%f\n", (float)sums[2] / n);
    printf("%f\n", (float)sums[3] / n);
    printf("%f\n", (float)sums[4] / n);
    
    return 0;
}
