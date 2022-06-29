#include <stdio.h>
#include <stdlib.h>

int main(){
	int i, j;
  int mazer, mezer;
  int *lista[9];
  int listSizes[9];
	FILE *entrada = fopen("samples.txt", "r");
	FILE *saida = fopen("results.txt", "w+");

  
  for (i=0;i<9;i++){
    fscanf(entrada, "%d", &listSizes[i]);
    lista[i] = malloc(sizeof(int) * listSizes[i]);
    for (j=0;j<listSizes[i];j++){
      fscanf(entrada, "%d", &lista[i][j]);
    }
  }
  
	for (i=0;i<9;i++){
		mazer = 0;
    mezer = 0;
		for (j=0;j<listSizes[i];j++){
      if (lista[i][j]>0){
        mazer++;
      }else{
        mezer++;
      }
    }
    fprintf(saida, "%d Negativos, %d Positivos\n", mezer, mazer);
	}
	
	fclose(entrada);
  fclose(saida);
	return 0;
}
