#include <stdio.h>
/*Dado um vetor de números inteiros v, retorne um novo vetor de forma que cada
elemento no índice i seja o produto de todos os números na matriz original, com
exceção de i.*/
int main()
{
    int v[] = {1,2,3,4,5};
    int tamv = (sizeof(v) / sizeof(int));
    int multi, resp[tamv];
    for (int i = 0;i<tamv;i++){
        multi = 1;
        for (int j = 0;j < tamv;j++){
            if (j != i){
                multi = multi * v[j];
            }
        }
        resp[i] = multi;
        printf("%d ", resp[i]);
    }
    return 0;
}
