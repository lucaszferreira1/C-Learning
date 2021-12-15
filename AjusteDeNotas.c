#include <stdio.h>

int main()
{
    // float notas[] = {6.9, 8, 7.5, 3, 8.8, 6, 5.5, 4.5, 2, 1};
    float notas[10];
    for (int i=0; i<10; i++){
        scanf("%f", &notas[i]);
    }
    float maior = notas[0];
    int posicao = 0;
    for (int i=0; i<10;i++){
        if (notas[i] >= maior){
            posicao = i;
            maior = notas[i];
        }
    }
    float ajuste = 10 / maior;
    float notasAjustadas[10];
    for (int i=0;i<10;i++){
        notasAjustadas[i] = notas[i] * ajuste; 
    }
    printf("%.1f\n", maior);
    printf("%d\n", posicao);
    printf("%.3f\n", ajuste);
    printf("Notas Originais | Notas Ajustadas\n");
    for (int i=0; i<10; i++){
        printf("%.1f | ", notas[i]);
        printf("%.1f\n", notasAjustadas[i]);
    }

    return 0;
}
