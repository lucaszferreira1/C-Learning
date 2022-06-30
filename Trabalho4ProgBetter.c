#include <stdio.h>
#include <stdlib.h>

void createRandomList(){
  int ntestes, i, j;
  FILE *exit = fopen("random.txt", "w+");
  scanf("%d", &ntestes);
  for (i=0;i<ntestes;i++){
    int size = (rand()%10) + 1;
    fprintf(exit, "%d ", size);
    for (j=0;j<size;j++){
      int number = rand() % 101;
      if ((rand()%2) == 1){
        number = number * (-1);
      }
      fprintf(exit,"%d ", number);
    }
    if (i != (ntestes))
      fprintf(exit, "\n");
  }
  fclose(exit);
  return;
}

int main(){
	int j;
  int mazer, mezer;
	FILE *entrada = fopen("random.txt", "r");
	FILE *saida = fopen("results.txt", "w+");
  createRandomList();
  
  while( !feof(entrada)) {
    int tama;
    mazer = 0;
    mezer = 0;
    fscanf(entrada, "%d", &tama);
    for (j=0;j<tama;j++){
      int numb;
      fscanf(entrada, "%d", &numb);
      if (numb>=0){
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
