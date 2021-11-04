#include <stdio.h>

int main()
{   
    int escolha;
    char testeArray[8][10] = {"Sul", "Norte", "Leste", "Oeste", "Sudeste", "Sudoeste", "Noroeste","Nordeste"};
    printf("Digite um ponto cardial: \n");
    scanf("%d", &escolha);
    printf(testeArray[escolha-1]);
    return 0;
}
