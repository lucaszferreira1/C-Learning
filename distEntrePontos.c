#include <stdio.h>
#include <math.h>
#include <stdio.h>

double distEntrePontos(int x1, int y1, int x2, int y2){
    return (sqrt(pow((x2 - x1), 2) + pow((y2 - y1), 2)));
}


double distEntrePontoReta(int a, int b, int c, int x, int y){
    int result;
    result = a * x + b * y + c;
    result = sqrt(pow(result, 2));
    return (result / sqrt(pow(a, 2) + pow(b, 2)));
}


int main()
{
    int x1, y1, x2, y2, z;
    char escolha;
    scanf("%c", &escolha);
    scanf("%d", &x1);
    scanf("%d", &y1);
    scanf("%c", &escolha);
    scanf("%d", &x2);
    scanf("%d", &y2);
    if (escolha == 'R'){
        scanf("%d", &z);
        printf("%.2f", distEntrePontoReta(x2, y2, z, x1, y1));
    }
    else{
        printf("%.1f", distEntrePontos(x1, y1, x2, y2));
    }
    
    return 0;
}
