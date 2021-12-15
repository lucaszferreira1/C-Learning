#include <stdio.h>

int main()
{
    int i = 0;
    char vogais[250];
    scanf("%[^\n]", vogais);
    int contVog = 0;
    while (vogais[i] != '\0'){
        if (vogais[i] == 'a' || vogais[i] == 'e' || vogais[i] == 'i' || vogais[i] == 'o' || vogais[i] == 'u' || vogais[i] == 'A' || vogais[i] == 'E' || vogais[i] == 'I' || vogais[i] == 'O' || vogais[i] == 'U'){
            contVog = contVog + 1;
        }
        i++;
    }
    printf("%d", contVog);

    return 0;
}
//Eu odeio Barras de espaço. Nunca utilizar scanf("%s", string) caso for pegar espaços
