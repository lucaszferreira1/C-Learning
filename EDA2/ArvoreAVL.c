#include <stdlib.h>
#include <stdio.h>
#include <time.h>

#define MAX 1

int n_operacoes = 0;

typedef struct no {
    struct no* pai;
    struct no* esquerda;
    struct no* direita;
    int valor;
} No;

typedef struct arvore {
    struct no* raiz;
} Arvore;

void balanceamento(Arvore*, No*);
int altura(No*);
int fb(No*);
No* rsd(Arvore*, No*);
No* rse(Arvore*, No*);
No* rdd(Arvore*, No*);
No* rde(Arvore*, No*);

Arvore* criar() {
    Arvore *arvore = malloc(sizeof(Arvore));
    arvore->raiz = NULL;
  
    return arvore;
}

int vazia(Arvore* arvore) {
    return arvore->raiz == NULL;
}

No* adicionarNo(No* no, int valor) {
    if (valor > no->valor) {
        if (no->direita == NULL) {
            No* novo = malloc(sizeof(No));
            novo->valor = valor;
            novo->pai = no;
            novo->esquerda = NULL;
            novo->direita = NULL;

            no->direita = novo;
				
            return novo;
        } else {
            return adicionarNo(no->direita, valor);
        }
    } else {
        if (no->esquerda == NULL) {
            No* novo = malloc(sizeof(No));
			novo->valor = valor;
            novo->pai = no;
            novo->esquerda = NULL;
            novo->direita = NULL;
			
            no->esquerda = novo;
			
            return novo;
        } else {
            return adicionarNo(no->esquerda, valor);
        }
    }
}

No* adicionar(Arvore* arvore, int valor) {
    if (vazia(arvore)) {
        No* novo = malloc(sizeof(No));
        novo->valor = valor;
        novo->pai = NULL;
        novo->esquerda = NULL;
        novo->direita = NULL;
        
        arvore->raiz = novo;
			
        return novo;
    } else {
        No* no = adicionarNo(arvore->raiz, valor);
        balanceamento(arvore, no);
        return no;
    }
}

No* localizar(No* no, int valor) {
    n_operacoes++;
    if (no->valor == valor) {
        return no;
    } else {
        if (valor < no->valor) {
            if (no->esquerda != NULL) {
                return localizar(no->esquerda, valor);
            }
        } else {
            if (no->direita != NULL) {
                return localizar(no->direita, valor);
            }
        }
    }

    return NULL;
}

void percorrer(No* no, void (*callback)(int)) {
    if (no != NULL) {
        percorrer(no->esquerda,callback);
        callback(no->valor);
        percorrer(no->direita,callback);
    }
}

void visitar(int valor){
    printf("%d ", valor);
}

void balanceamento(Arvore* arvore, No* no) {
    while (no != NULL) {
	n_operacoes++;
        int fator = fb(no);

        if (fator > 1) { //árvore mais pesada para esquerda
            //rotação para a direita
            if (fb(no->esquerda) > 0) {
                rsd(arvore, no); //rotação simples a direita, pois o FB do filho tem sinal igual
            } else {
                rdd(arvore, no); //rotação dupla a direita, pois o FB do filho tem sinal diferente
            }
        } else if (fator < -1) { //árvore mais pesada para a direita
            //rotação para a esquerda
            if (fb(no->direita) < 0) {
                rse(arvore, no); //rotação simples a esquerda, pois o FB do filho tem sinal igual
            } else {
                rde(arvore, no); //rotação dupla a esquerda, pois o FB do filho tem sinal diferente
            }
        }

        no = no->pai; 
    }
}

int altura(No* no){
    int esquerda = 0,direita = 0;

    if (no->esquerda != NULL) {
        esquerda = altura(no->esquerda) + 1;
    }

    if (no->direita != NULL) {
        direita = altura(no->direita) + 1;
    }
  
    return esquerda > direita ? esquerda : direita; //max(esquerda,direita)
}

int fb(No* no) {
    int esquerda = 0,direita = 0;
  
    if (no->esquerda != NULL) {
        esquerda = altura(no->esquerda) + 1;
    }

    if (no->direita != NULL) {
        direita = altura(no->direita) + 1;
    }
  
    return esquerda - direita;
}

No* rse(Arvore* arvore, No* no) {
    n_operacoes++;
    No* pai = no->pai;
    No* direita = no->direita;

    if (direita->esquerda != NULL) {
        direita->esquerda->pai = no;
    } 
  
    no->direita = direita->esquerda;
    no->pai = direita;

    direita->esquerda = no;
    direita->pai = pai;

    if (pai == NULL) {
        arvore->raiz = direita;
    } else {
        if (pai->esquerda == no) {
            pai->esquerda = direita;
        } else {
            pai->direita = direita;
        }
    }

    return direita;
}



No* rsd(Arvore* arvore, No* no) {
    n_operacoes++;
    No* pai = no->pai;
    No* esquerda = no->esquerda;

    if (esquerda->direita != NULL) {
        esquerda->direita->pai = no;
    } 
  
    no->esquerda = esquerda->direita;
    no->pai = esquerda;
  
    esquerda->direita = no;
    esquerda->pai = pai;

    if (pai == NULL) {
        arvore->raiz = esquerda;
    } else {
        if (pai->esquerda == no) {
            pai->esquerda = esquerda;
        } else {
            pai->direita = esquerda;
        }
    }

    return esquerda;
}

No* rde(Arvore* arvore, No* no) {
    n_operacoes++;
    no->direita = rsd(arvore, no->direita);
    return rse(arvore, no);
}

No* rdd(Arvore* arvore, No* no) {
    n_operacoes++;
    no->esquerda = rse(arvore, no->esquerda);
    return rsd(arvore, no);
}

No* minValueNo(No* no)
{
    No* curr = no;
 
    while (curr->esquerda != NULL)
        curr = curr->esquerda;
 
    return curr;
}

No* deleteNo(No* raiz, int valor, Arvore *a)
{
    if (raiz == NULL)
        return raiz;
 
    if (valor < raiz->valor )
        raiz->esquerda = deleteNo(raiz->esquerda, valor, a);
 
    else if(valor > raiz->valor )
        raiz->direita = deleteNo(raiz->direita, valor, a);
 
    else{
        if( (raiz->esquerda == NULL) || (raiz->direita == NULL) )
        {
            No *temp = raiz->esquerda ? raiz->esquerda : raiz->direita;
 
            if (temp == NULL)
            {
                temp = raiz;
                raiz = NULL;
            }
            else
                *raiz = *temp;
             
            free(temp);
        }
        else{
            No* temp = minValueNo(raiz->direita);
 
            raiz->valor = temp->valor;
 
            raiz->direita = deleteNo(raiz->direita, temp->valor, a);
        }
    }
 
    if (raiz == NULL)
      return raiz;
 
    int balance = fb(raiz);
 
    if (balance > 1 && fb(raiz->esquerda) >= 0)
        return rsd(a, raiz);
 
    if (balance > 1 && fb(raiz->esquerda) < 0)
        return rdd(a, raiz);
 
    if (balance < -1 && fb(raiz->direita) <= 0)
        return rse(a, raiz);
 
    if (balance < -1 && fb(raiz->direita) > 0)
        return rde(a, raiz);
 
    return raiz;
}

int compara(const void* a, const void* b) {
    return (*(int*) a - *(int*) b);
}

int* geraVetor(int n) {
    int* v = malloc(sizeof(int) * n);
    
    for (int i = 0; i < n; i++) {
        v[i] = (rand() % n) * MAX;
    }

    qsort(v, n, sizeof(int), compara);

    return v;
}

int main()
{
    int vezes = 50;
    int n = 10000;
    int sum[n];
    for (int i=0;i<n;i++){
        sum[i] = 0;
    }
    for (int j=0;j<vezes;j++){
        
        int* v = geraVetor(n + 1);
    
        Arvore* a = criar();
        for (int i=0;i<n;i++){
            adicionar(a, v[i]);
            sum[i] += n_operacoes;
	        n_operacoes = 0;
        }
        // n_operacoes = 0;
        // for (int i=0;i<n;i++){
        //     deleteNo(a->raiz, v[i], a);
        //     printf("%d %d\n", i, n_operacoes);
        //     fprintf(fp, "%d %d\n", i, n_operacoes);
        // }
    }
    FILE *fp;
    fp = fopen("results.txt", "w");
    if (!fp){
        printf("Can't open file\n");
    }else{
        float avrg;
        for (int i=0;i<n;i++){
            avrg = sum[i] / vezes;
            fprintf(fp, "%d %f\n", i, avrg);
        }
    }
    return 0;
}
