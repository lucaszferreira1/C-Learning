#include <stdio.h>
#include <stdlib.h>

int tamanhos[] = {1, 1, 1, 1, 1};

void mostra(int **vp){
    int i, j;
    for (i=0;i<5;i++){
        for (j=0;j<5;j++){
            if (tamanhos[i] > 0)
                printf("[%d]", ((vp[i][j] > 0) ? vp[i][j]-1 : 0));
        }
        printf("\n");
    }
}

void find(int **vp, int n, int* vallis, int* valin){ 
    int i, j;
    for (i=0;i<5;i++){
        for (j=0;j<5;j++){
            if (tamanhos[i] != 0){
                if (n == vp[i][j]){
                    *vallis = i;
                    *valin = j;
                    return;
                }
            }
        }
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

void moveon(int **vp, int a, int b){
    int posa[2], posb[2];
    int temp = a;
    find(vp, a, &posa[0], &posa[1]);
    find(vp, b, &posb[0], &posb[1]);
    int i;
    for (i=posa[1];i<5;i++){
        if (vp[posa[0]][i+1])
            vp[posa[0]][i] = vp[posa[0]][i+1];
        else
            vp[posa[0]][i] = NULL;
    }
    for (i=posb[1];i<5;i++){
        vp[posb[0]][i+1] = temp;
        temp = vp[posb[0]][i+2];
    }
}

int main()
{
    int *vp[5];
	int i;
	for (i=0;i<5;i++){
		vp[i] = malloc(sizeof(int));
	}
	for (i=0;i<5;i++){
		vp[i][0] = i+1;
	}
// 	moveto(vp, 1, 2);
// 	moveto(vp, 0, 4);
	moveto(vp, 3, 4);
// 	moveon(vp, 4, 3);
	mostra(vp);
    return 0;
}
