#include <stdio.h>
#include <math.h>

int main()
{
    float price  = 237.37;
    float types[] = {100, 50, 20, 10, 5, 2, 1, 0.50, 0.25, 0.10, 0.05, 0.01};
    int bills[12];
    
    for (int i=0; i<12; i++){
        bills[i] = (price - fmod(price, types[i])) / types[i];
        price = fmod(price, types[i]);
    }
    if (price>0) {
        bills[11] += 1;
    }
    for (int i=0;i<12;i++){
        printf("%d notas/moedas de R$%.2f\n", bills[i], types[i]);
    }
    return 0;
}
