#include <stdio.h>

int main()
{
    int valor, testes;
    printf("DIGITE UM VALOR: ");
    scanf("%d", &valor);
    if (valor > 0){
        if (valor % 2 == 0){
            printf("%d é Par\n", valor);
            printf("2 é Divisor de %d\n", valor);
        }else{
            printf("%d é Ímpar\n", valor);
        }
        for (testes = 3; testes < 8; testes = testes + 2){
            if (valor % testes == 0){
                printf("%d é Divisor de %d\n", testes, valor);
            }
        }
    }
    return 0;
}
