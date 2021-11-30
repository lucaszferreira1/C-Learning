#include <stdio.h>

int main()
{
    int n, x, y;
    y = 0;
    printf("Digite um número: ");
    scanf("%d", &n);

    for (x = n - 1;x != 0;--x){
        if (n % x == 0){
            y = y + x;
        }
    }
    
    if (y == n){
        printf("PERFEITO");
    }else{
        printf("NAO PERFEITO");
    }
    
    return 0;
}
