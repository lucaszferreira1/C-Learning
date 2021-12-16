#include <stdio.h>

int main()
{
    int i, maior, cont, impares, pares;
    scanf("%d", &i);
    maior = i;
    cont = 0;
    impares = 1;
    pares = 0;
    while (i != 1){
        cont++;
        printf("%d, ", i);
        if (i % 2 == 0){
            i = i / 2;
            pares++;
        }else{
            i = 3 * i + 1;
            impares++;
        }
        if (i > maior){
            maior = i;
        }
    }
    printf("1\n");
    printf("Há %d passos e o maior valor é %d\n", cont, maior);
    printf("Há %d pares e %d ímpares", pares, impares);
    return 0;
}
