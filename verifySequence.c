//Foi pedido para não se utilizar vetores então está bem feio o código
#include <stdio.h>

int main()
{
    char naipeum, naipedois, naipetres;
    int valorum, valordois, valortres;
    int meio;
    scanf("%c", &naipeum);
    scanf("%d", &valorum);
    int menor = valorum;
    int maior = valorum;
    
    scanf("%c", &naipedois);
    scanf("%d", &valordois);
    if (valordois < menor){
        menor = valordois;
    }
    if (valordois > maior){
        maior = valordois;
    }
    
    scanf("%c", &naipetres);
    scanf("%d", &valortres);
    if (valortres < menor){
        menor = valortres;
    }
    if (valortres > maior){
        maior = valortres;
    }
    
    if (valorum > menor && valorum < maior){
        meio = valorum;
    }else if (valordois > menor && valordois < maior){
        meio = valordois; 
    }else if (valortres > menor && valortres < maior){
        meio = valortres; 
    }
    
    if (meio == (menor + 1) && maior == (meio + 1)){
        printf("SEQUENCIA");
    }else{
        printf("NADA");
    }


    return 0;
}
