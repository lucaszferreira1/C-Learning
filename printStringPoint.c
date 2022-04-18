
#include <stdio.h>
#include <string.h>

int main()
{
    char frase[100];
    int i;
    char *ptr;
    
    printf("Entre com uma frase: ");
    fgets(frase, 100, stdin);
    
    ptr = &(frase[0]);
    while(*ptr)
        printf("%c", *ptr++);
    // for (i=0;i<=strlen(frase);i++){
    //     printf("%c", frase[i]);
    // }

    return 0;
}
