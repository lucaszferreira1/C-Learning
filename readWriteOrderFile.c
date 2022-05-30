#include <stdio.h>

int main(){
  int orderedList[10];
  FILE *arq = fopen( "exemplo1.txt", "r+t" );
  
  if( arq == NULL) {
    printf("Erro no arquivo!\n");
    return -1;
  }
  
  for (int i=0;i<10;i++){
    fscanf(arq, "%d", orderedList+i);
  }
  
  for (int i=0;i<10;i++){
    for (int j=0;j<9;j++){
      if (orderedList[j] > orderedList[j+1]){
        int aux = orderedList[j];
        orderedList[j] = orderedList[j+1];
        orderedList[j+1] = aux;
      }
    }
  }
  fprintf(arq, "\nOrdenada: ");
  for (int i=0;i<10;i++){
    fprintf(arq, "%d ", orderedList[i]);
  }
  fclose(arq);
  
  return 0;
}
