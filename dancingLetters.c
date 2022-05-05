#include <stdio.h>
#include <string.h>

int main()
{
    char text[255];
    int i;
    int let = 0;
    fgets(text, 255, stdin);
    
    for (i=0;i<=255;i++){
        if ((text[i] != ' ') && (let % 2 == 0)){
            text[i] = toupper(text[i]);
            let+=1;
        }else if(text[i] != ' '){
            text[i] = tolower(text[i]);
            let+=1;
        }
        
    }
    fputs(text, stdout);

    printf("\n");
    return 0;
}
