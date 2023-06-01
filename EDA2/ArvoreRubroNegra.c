#include <stdio.h>
#include <stdlib.h>
#include <time.h>

#define MAX 1

enum coloracao { Preto, Vermelho };

typedef enum coloracao Cor;

typedef struct no {
    struct no* pai;
    struct no* esquerda;
    struct no* direita;
    Cor cor; //cor do nó (Vermelho ou Preto)
    int valor;
} No;

typedef struct arvore{
    struct no* raiz;
} Arvore;

void rotacionarEsquerda(Arvore*, No*);
void rotacionarDireita(Arvore*, No*);
void balancear(Arvore*, No*);
No* adicionar(Arvore*, int);
No* adicionarNo(No*, int);

int vazia(Arvore* arvore) {
    return arvore->raiz == NULL;
}

void visitar(int valor){
    printf("%d ", valor);
}

Arvore* criar() {
    Arvore *arvore = malloc(sizeof(Arvore));
    arvore->raiz = NULL;
  
    return arvore;
}

No* adicionar(Arvore* arvore, int valor) {
    if (vazia(arvore)) {
        printf("Adicionando %d\n",valor);
        No* novo = malloc(sizeof(No));
        novo->valor = valor;
        novo->pai = NULL;
        novo->esquerda = NULL;
        novo->direita = NULL;
        novo->cor = Preto;
        
        arvore->raiz = novo;
			
        return novo;
    } else {
        No* no = adicionarNo(arvore->raiz, valor);
        balancear(arvore, no);
        printf("Adicionando %d\n",valor);
        return no;
    }
}

No* adicionarNo(No* no, int valor) {
    if (valor > no->valor) {
        if (no->direita == NULL) {
            No* novo = malloc(sizeof(No));
            novo->valor = valor;
            novo->pai = no;
            novo->esquerda = NULL;
            novo->direita = NULL;
            novo->cor = Vermelho;

            no->direita = novo;
				
            return novo;
        } else 
            return adicionarNo(no->direita, valor);
    } else if (no->esquerda == NULL) {
            No* novo = malloc(sizeof(No));
			novo->valor = valor;
            novo->pai = no;
            novo->esquerda = NULL;
            novo->direita = NULL;
            novo->cor = Vermelho;
			
            no->esquerda = novo;
			
            return novo;
        } else 
            return adicionarNo(no->esquerda, valor);
}

void balancear(Arvore* arvore, No* no) {
    while (arvore->raiz != no && no->pai->cor == Vermelho) { //Garante que todos os níveis foram balanceados
        if (no->pai == no->pai->pai->esquerda) {
            No *tio = no->pai->pai->direita;
            
            if (tio != NULL && tio->cor == Vermelho) {
                tio->cor = Preto; //Resolve caso 2
                no->pai->cor = Preto;
                no->pai->pai->cor = Vermelho;
                no = no->pai->pai; //Vai para o nível anterior
            } else {
                if (no == no->pai->direita) {
                    no = no->pai; //Vai para o nível anterior
                    rotacionarEsquerda(arvore, no); //Resolve caso 3
                } else {
                    no->pai->cor = Preto; //Resolve caso 4
                    no->pai->pai->cor = Vermelho;
                    rotacionarDireita(arvore, no->pai->pai);
                }
            }
        } else if (no->pai == no->pai->pai->direita){
        //Repete o mesmo código do bloco if, invertendo o lado dos direita e esquerda
            No *tio = no->pai->pai->esquerda;
            
            if (tio != NULL && tio->cor == Vermelho) {
                tio->cor = Preto; //Resolve caso 2
                no->pai->cor = Preto;
                no->pai->pai->cor = Vermelho;
                no = no->pai->pai; //Vai para o nível anterior
            } else {
                if (no == no->pai->esquerda) {
                    no = no->pai; //Vai para o nível anterior
                    rotacionarDireita(arvore, no); //Resolve caso 3
                } else {
                    no->pai->cor = Preto; //Resolve caso 4
                    no->pai->pai->cor = Vermelho;
                    rotacionarEsquerda(arvore, no->pai->pai);
                }
            }
        }
    }
    arvore->raiz->cor = Preto; //Resolve caso 1
}

void rotacionarEsquerda(Arvore* arvore, No* no) {
    No* direita = no->direita;
    no->direita = direita->esquerda;
    if (direita->esquerda != NULL)
        direita->esquerda->pai = no; //Se houver filho à esquerda em direita, ele será pai do nó
    direita->pai = no->pai; //Ajusta no pai do nó à direita
    
    if (no->pai == NULL)
        arvore->raiz = direita; //Se nó for raiz, o nó direita será a nova raiz da árvore
    else if (no == no->pai->esquerda)
        no->pai->esquerda = direita; //Corrige relação pai-filho do novo pai (esquerda)
    else
        no->pai->direita = direita; //Corrige relação pai-filho do novo pai (direita)
    direita->esquerda = no; //Corrige relação pai-filho entre o nó pivô e o nó à direita
    no->pai = direita;
}

void rotacionarDireita(Arvore* arvore, No* no) {
    No* esquerda = no->esquerda;
    no->esquerda = esquerda->direita;
    if (esquerda->direita != NULL)
        esquerda->direita->pai = no; //Se houver filho à direita em esquerda, ele será pai do nó
    esquerda->pai = no->pai; //Ajusta no pai do nó à esquerda
    
    if (no->pai == NULL)
        arvore->raiz = esquerda; //Se nó for raiz, o nó esquerda será a nova raiz da árvore
    else if (no == no->pai->esquerda)
        no->pai->esquerda = esquerda; //Corrige relação pai-filho do novo pai (esquerda)
    else
        no->pai->direita = esquerda; //Corrige relação pai-filho do novo pai (direita)
    esquerda->direita = no; //Corrige relação pai-filho entre o nó pivô e o nó à esquerda
    no->pai = esquerda;
}

void percorrer(No* no, void (*callback)(int)) {
    if (no != NULL) {
        percorrer(no->esquerda,callback);
        callback(no->valor);
        percorrer(no->direita,callback);
    }
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
    int n = 10000;
    int* v = geraVetor(n + 1);

    int medio = v[rand() % n];
    int pior = (n * MAX) + 1;
    int melhor = v[0];
    
    clock_t begin = clock();
    Arvore* a = criar();
    for (int i=0;i<n;i++){
        adicionar(a, v[i]);
    }
    clock_t end = clock();
    double time_spent = (double)(end - begin) / CLOCKS_PER_SEC;
    
    percorrer(a->raiz, visitar);
    printf("\n%f", time_spent);
    
    return 0;
}
