#include <stdio.h>

int main()
{
    int listaUm[6], listaDois[6];
    int contIgual[] = {0, 0, 0, 0, 0, 0};
    int contMaior[] = {0, 0, 0, 0, 0, 0};
    for (int i=0;i<6;i++){
        scanf("%d", &listaUm[i]);
    }
    for (int i=0;i<6;i++){
        scanf("%d", &listaDois[i]);
    }
    
    for (int i=0;i<6;i++){
        for (int h=0;h<6;h++){
            if (listaUm[i] == listaDois[h]){
                contIgual[i]++;
            }
            if (listaUm[i] < listaDois[h]){
                contMaior[i]++;
            }
        }
        printf("A[%d]=%d Total iguais em B=%d ; Total de maiores em B=%d\n", i, listaUm[i], contIgual[i], contMaior[i]);
    }
    return 0;
}


