/******************************************************************************

Zero não é considerado um número positivo mas vou deixar como está no exemplo

*******************************************************************************/

#include <stdio.h>

int main()
{
    float numeros[3];
    int nsPos = 0;
    int posMaior = 1;
    int posMenor = 1;
    printf("Digite o primeiro valor: ");
    scanf("%f", &numeros[0]);
    int maior = numeros[0];
    int menor = numeros[0];
    
    printf("Digite o segundo valor: ");
    scanf("%f", &numeros[1]);
    if (numeros[1] > maior){
        maior = numeros[1];
        posMaior = 2;
    }
    if (numeros[1] < menor){
        menor = numeros[1];
        posMenor = 2;
    }
    
    printf("Digite o terceiro valor: ");
    scanf("%f", &numeros[2]);
    if (numeros[2] > maior){
        maior = numeros[2];
        posMaior = 3;
    }
    if (numeros[2] < menor){
        menor = numeros[2];
        posMenor = 3;
    }
    
    for(int x = 0; x < 3; x++){
        if(numeros[x] >= 0){
            nsPos++;
        }
    }
    
    printf("Maior: %d", maior);
    if (posMaior == 1){
        printf("( na posição 1)");
    }
    else if (posMaior == 2){
        printf("( na posição 2)");
    }
    else {
        printf("( na posição 3)");
    }
    
    printf("\nMenor: %d", menor);
    if (posMenor == 1){
        printf("( na posição 1)");
    }
    else if (posMenor == 2){
        printf("( na posição 2)");
    }
    else {
        printf("( na posição 3)");
    }
    printf("\nTotal de positivos: %d\n", nsPos);

    return 0;
}
