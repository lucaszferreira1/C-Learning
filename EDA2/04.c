/*Dada um vetor inteiros v, retorne a maior soma dos números não adjacentes. Os
números podem incluir 0 ou negativos no vetor.*/
#include <stdio.h>
Não está pronto

int maior(int n1, int n2){
    if (n1 > n2){
        return n1;
    }
    return n2;
}

int somatorio(int v[], int indice){
    if (indice > (sizeof(v) / sizeof(int))){
        return 0;
    }
    return maior(v[indice] + somatorio(v, indice + 2), somatorio(v, indice + 1));
}

int determinar(int v[]){
    return somatorio(v, 0);
}

int main()
{
    int v[] = {2, 4, 6, 2, 5};
    printf("%d", determinar(v));
    
    return 0;
}
