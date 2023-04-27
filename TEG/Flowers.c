#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <math.h>

#define MAXCHAR 128

// Estrutura da flor, sendo, "sepal.length","sepal.width","petal.length","petal.width","variety"

typedef struct{
    float sepLen, sepWid, petLen, petWid;
    char nome[16];
}Flor;


int main()
{
    FILE *fp;
    Flor flores[150];
    fp = fopen("flowers.txt", "r");
    // O arquivo é aberto e se lê o conteúdo, o qual vai para a lista flores
    if (!fp)
        printf("Can't open file\n");
    else{
        Flor flor;
        int cont = 0;
        char line[MAXCHAR];
        char *token;
        while(fgets(line, MAXCHAR, fp )!= NULL){
            token = strtok(line, ",");
            flor.sepLen = atof(token);
            token = strtok(NULL, ",");
            flor.sepWid = atof(token);
            token = strtok(NULL, ",");
            flor.petLen = atof(token);
            token = strtok(NULL, ",");
            flor.petWid = atof(token);
            token = strtok(NULL, ",");
            strcpy(flor.nome, token);
            
            flores[cont] = flor;
            cont++;
        }
        
    }
    
    fclose(fp);
    
    // Cálculo de distância euclideana
    if (flores){
        Flor pri, sec;
        int matriz[150][150];
        // Todos os valores são inicializados e setados para 0
        for (int i = 0;i < 150;i++){
            for (int j = 0;j < 150;j++){
                matriz[i][j] = 0;
            }
        }
        // É calculado a distância euclideana de todos para todos
        for (int i = 0;i < 150;i++){
            for (int j = 0;j < 150;j++){
                pri = flores[i];
                sec = flores[j];
                if (i != j){
                    float eucDist = pow((pri.sepLen - sec.sepLen), 2) + pow((pri.sepWid - sec.sepWid), 2) + pow((pri.petLen - sec.petLen), 2) + pow((pri.petWid - sec.petWid), 2);
                    if (eucDist <= .3){
                        matriz[i][j] = 1;
                        matriz[j][i] = 1;
                    }
                }
            }
        }
        
        // É aberto o arquivo com os resultados
        fp = fopen("results.txt", "w");
        if (!fp){
            printf("Can't open file\n");
        }else{
            // É adicionado os resultados ao arquivo
            char str[150];
            fprintf(fp, "150\n");
            for (int i = 0;i < 150;i++){
                for (int j = 0;j < 150;j++){
                    // char c = matriz[i][j] + '0';
                    // str[j] = c;
                    if (matriz[i][j] == 1){
                        fprintf(fp, "%d %d\n", i, j);
                    }
                }
                // fprintf(fp, "%s\n", str);
            }
        }
    }
    
    
    
    return 0;
}
