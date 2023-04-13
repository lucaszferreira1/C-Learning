#include <stdio.h>

int pesquisaBinaria(int chave, int v[], int n) {
    int inicio = 0;
    int meio;
    int fim = n - 1;
    int cont = 1;
    while (inicio <= fim) {
        meio = (inicio + fim) / 2;
        if (chave == v[meio]) {
            printf("\n%d", cont);
            return meio;
        } else if (chave < v[meio]) {
            fim = meio - 1;
        } else {
            inicio = meio + 1;
        }
        cont++;
    }
    printf("\n%d", cont);
    return -1;
}

int pesquisaBinariaRecursiva(int chave, int v[], int ini, int fim, int cont) {
    int meio = (ini + fim) / 2;
    cont++;
    if (ini > fim){
        return -1;
    }
    if (chave == v[meio]){
        printf("\n%d", cont);
        return meio;
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
            printf("\n%d", cont);
            return meio;
        }
        cont++;
    }
    return -1;
}


int main()
{
    int v[] = {0, 1, 2, 3, 4, 5, 6, 7, 8, 9, 10, 11, 12, 13, 14, 15, 16, 17, 18, 19, 20};
    int chave = 12;
    int n = sizeof(v)/sizeof(v[0]);
    
    printf("\n%d", pesquisaBinaria(chave, v, n));
    printf("\n%d", pesquisaBinariaRecursiva(chave, v, 0, n, 0));
    printf("\n%d", pesquisaInterpolacao(chave, v, n));
    return 0;
}
