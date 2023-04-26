#include <stdio.h>
#include <string.h>
#include <stdlib.h>

#define MAXCHAR 128

typedef struct{
    float sepLen, sepWid, petLen, petWid;
    char nome[16];
}Flor;

int main()
{
    FILE *fp;
    char line[MAXCHAR];
    fp = fopen("flores.txt", "r");
    
    if (!fp)
        printf("Can't open file\n");
    else{
        float valFl;
        char name[16];
        while(fgets(line, MAXCHAR, fp )!= NULL){
            strcpy(name, strtok(line, ","));
            printf("%.2f\n", atof(name));
        }
    }
    
    fclose(fp);
    
    return 0;
}
