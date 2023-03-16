#include <stdio.h>
/*Dado um vetor de números inteiros v de tamanho n e um número k, retorne verdadeiro
se a soma de qualquer par de números em v for igual a k.*/

int main()
{
    int v[] = {1,2,3,4,5};
    int k = 9;
    for (int i = 0;i<(sizeof(v) / sizeof(int));i++){
        for (int j = i+1;j < (sizeof(v) / sizeof(int));j++){
            if (v[i]+v[j] == k){
                return 0;
            }
        }
    }
    return 1;
}
