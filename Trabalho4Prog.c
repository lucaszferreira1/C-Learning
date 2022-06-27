#include <stdio.h>
#include <stdlib.h>

int main(){
	int i, j;
  int lista[10];
  int listSizes[9];
	FILE *entrada = fopen("samples.txt", "r");
	FILE *saida = fopen("results.txt", "w+");

  fscanf(entrada, "%d", listSizes);
  printf("%d ", listSizes[0]);
  // for (i=1;i<9;i++){
    
  // }
  
  for (i=0;i<10;i++){
    fscanf(entrada, "%d", lista+i);
  }
  
	for (i=0;i<1;i++){
		int mazer = 0;
    int mezer = 0;
		for (j=1;j<lista[0]+1;j++){
      if (lista[j] < 0){
        mezer++;
      }else{
        mazer++;
      }
    }
    printf("%d Negativos, %d Positivos", mezer, mazer);
	}
    
	
	fclose(entrada);
  fclose(saida);
	return 0;
}
