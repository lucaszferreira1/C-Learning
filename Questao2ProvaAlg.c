/*
Escreva um algoritmo que calcule a distância de dois pontos ou de um
ponto e uma reta. 
O usuário tem a opção de entrar com:
•as coordenadas de 2 pontos OU 
•as coordenadas de um ponto e uma reta.
O algoritmo deve escrever , como saída, o valor da distância.
*/

#include <stdio.h>
#include <math.h>

int main()
{
    int escolha;
    float x1, x2, y1, y2, a, b, c;
    
    printf("1 - Para calcular a distância até uma reta: \n2 - Para calcular a distância entre dois pontos: ");
    scanf("%d", &escolha);
    
    printf("Digite o primeiro valor de x: ");
    scanf("%f", &x1);
    
    printf("Digite o primeiro valor de y: ");
    scanf("%f", &y1);
    
    if (escolha == 1){
        printf("Digite o valor de a: ");
        scanf("%f", &a);
    
        printf("Digite o valor de b: ");
        scanf("%f", &b);
        
        printf("Digite o valor de c: ");
        scanf("%f", &c);
        float resultado = (a * x1 + b * y1 + c);
        if (resultado < 0){
            resultado = resultado * -1;
        }
        resultado = resultado / sqrt(pow(a,2) + pow(b, 2));
        printf("%f",resultado);
    }else{
        printf("Digite o primeiro valor de x: ");
        scanf("%f", &x2);
        
        printf("Digite o primeiro valor de y: ");
        scanf("%f", &y2);
        
        float d = sqrt(pow((x2-x1), 2) + pow((y2 - y1), 2));
        printf("%f", d);
    }
    

    return 0;
}
