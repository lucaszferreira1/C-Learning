#include <stdio.h>

int main()
{
    int lista[10], listaresult[9], posicao, ajuste;
    ajuste = 0;
    for (int i=0;i<10;i++){
        scanf("%d", &lista[i]);
    }
    
    scanf("%d", &posicao);
    
    for (int i=0;i<10;i++){
        if (i != posicao){
            listaresult[i + ajuste] = lista[i];
        }else{
            ajuste = -1;
        }
    }
    for (int i=0;i<9;i++){
        printf("%d\n", listaresult[i]);
    }
    return 0;
}
