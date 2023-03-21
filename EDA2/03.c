#include <stdio.h>
/*Dado um vetor de números inteiros v, encontre o primeiro inteiro positivo ausente no
vetor. Em outras palavras, deve ser retornado o menor inteiro positivo que não existe no
vetor. A matriz pode conter duplicados e números negativos também. O algoritmo deve
apresentar complexidade de tempo linear e de espaço constante (pode desconsiderar
o esforço para ordenação do vetor).*/

int main()
{
    int v[] = {-2, 0, 1, 3};
    int tamV = sizeof(v) / sizeof(int);
    int extra;
    for (int i=1;i < tamV;i++){
        for (int j=0;j < tamV-1;j++){
            if (v[j] > v[j+1]){
                extra = v[j];
                v[j] = v[j+1];
                v[j+1] = extra;
            }
        }
    }
    
    for (int i=1;i<tamV;i++){
        if (v[i-1] + 1 != v[i] && v[i] - 1 > 0){
            printf("%d", v[i]-1);
        }
    }

    return 0;
}
