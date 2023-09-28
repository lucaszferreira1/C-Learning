#include <stdio.h>
#include <stdlib.h>

#define MAX_MOVE 3


int findBestMove(int nMoedas){

    int nPegas;
    int limit = (nMoedas < MAX_MOVE) ? nMoedas : MAX_MOVE;
    for (nPegas = 1; nPegas <= limit; nPegas++){
        if (nMoedas - nPegas == 1)
            return nPegas;
        if (findBestMove(nMoedas - nPegas) == -1)
            return nPegas;
    }
    return -1;
}

int main() {
    int nMoedas = 11;
    int temp;
    int escolha;

    while (nMoedas > 1){
        printf("Tem %d moedas. Quantas você quer? :", nMoedas);
        scanf("%d", &escolha);
        temp = nMoedas - escolha;
        while (temp < 1 || (escolha < 1 || escolha > 3)){
            printf("Escolha um valor possível :");
            scanf("%d", &escolha);
            temp = nMoedas - escolha;
        }
        nMoedas = nMoedas - escolha;
        if (nMoedas == 1){
            temp = 0;
            break;
        }

        temp = findBestMove(nMoedas);
        if (temp == -1)
            temp = 3;

        printf("Vou pegar %d\n", temp);
        nMoedas = nMoedas - temp;

        temp = 1;
    }

    printf("Tem %d moedas\n", nMoedas);
    if (temp == 0)
        printf("Jogador Venceu");
    else
        printf("Computador Venceu");
    return 0;
}
