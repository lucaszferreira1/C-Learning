#include <stdio.h>
#include <stdlib.h>

int tamanhos[] = {1, 1, 1, 1, 1};

void mostra(int **vp){
    int i, j;
    for (i=0;i<5;i++){
        for (j=0;j<3;j++){
            if (tamanhos[i] != 0)
                printf("[%d]", vp[i][j]);
        }
        printf("\n");
    }
}

void moveto(int **vp, int a, int b){
    tamanhos[b] += 1;
    vp[b] = realloc(vp[b], sizeof(int) * tamanhos[b]);
    tamanhos[a] -= 1;
    vp[b][(tamanhos[b]-1)] = vp[a][(tamanhos[a])];
    vp[a][tamanhos[a]] = NULL;
    vp[a] = realloc(vp[a], sizeof(int) * tamanhos[a]);
}

int main()
{
    int *vp[5];
	int i;
	for (i=0;i<5;i++){
		vp[i] = malloc(sizeof(int));
	}
	for (i=0;i<5;i++){
		vp[i][0] = i;
	}
	moveto(vp, 0, 3);
	moveto(vp, 1, 4);
	moveto(vp, 2, 3);
	moveto(vp, 3, 4);
// 	moveto(vp, 4, 3);
	mostra(vp);
    return 0;
}
