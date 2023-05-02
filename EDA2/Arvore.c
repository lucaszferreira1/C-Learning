#include <stdio.h>
#include <stdlib.h>

typedef struct no {
    struct no* esquerda; //ponteiro para o nó filho a esquerda
    struct no* direita; //ponteiro para o nó filho a direita
    int valor; //conteúdo genérico do nó
} No;

typedef struct elemento{
    struct elemento* proximo;
    No* no;
}Elemento;

typedef struct fila{
    Elemento* inicial;
    Elemento* final;
} Fila;

Fila* criaFila(){
    Fila* fila;
    fila = malloc(sizeof(Fila));
    fila->inicial = NULL;
    fila->final = NULL;
    return fila;
}

void adicionarFila(Fila* fila, No* no){
    Elemento* ele = malloc(sizeof(Elemento));
    ele->no = no;
    ele->proximo = NULL;
    if (fila->final){
        fila->final->proximo = ele;
    }else{
        fila->inicial = ele;
    }
    fila->final = ele;
}

No* removerFila(Fila* fila){
    if (fila->inicial){
        Elemento* ele = fila->inicial;
        No* no = ele->no;
        if (fila->inicial == fila->final){
            fila->inicial = NULL;
            fila->final = NULL;
        }else{
            fila->inicial = ele->proximo;
        }
        free(ele);
        
        return no;
    }
    return NULL;
}

No* cria(int valor) {
    No *no;
    no = malloc(sizeof(No));
    no->esquerda = NULL;
    no->direita = NULL;
    no->valor = valor;
    
    return no;
}

int vazio(No* no) {
    return (no == NULL);
}

No* adiciona(No* no, int valor) {
    if (no == NULL) {
        return cria(valor);
    }else if(no->valor > valor){
        no->esquerda = adiciona(no->esquerda, valor);
    }else if (no->valor < valor){
        no->direita = adiciona(no->direita, valor);
    }
    return no;
}

void remover(No* no){
    if (no->esquerda)
        remover(no->esquerda);
    if (no->direita)
        remover(no->direita);
    free(no);
}

void percorrerPre(No* no) {
    if (no != NULL) {
        printf("%d ", no->valor);
        percorrerPre(no->esquerda);
        percorrerPre(no->direita);
    }
}

void percorrerPos(No* no){
    if (no->esquerda != NULL){
        percorrerPos(no->esquerda);
    }
    if(no->direita != NULL){
        percorrerPos(no->direita);
    }
    printf("%d ", no->valor);
}

void percorrerLargura(No* no){
    Fila* fila = criaFila();
    adicionarFila(fila, no);
    while(fila->inicial){
        no = removerFila(fila);
        printf("%d ", no->valor);
        if (no->esquerda)
            adicionarFila(fila, no->esquerda);
        if (no->direita)
            adicionarFila(fila, no->direita);
    }
}

int main()
{
    No *raiz = cria(4);
    adiciona(raiz, 2);
    adiciona(raiz, 8);
    adiciona(raiz, 1);
    adiciona(raiz, 3);
    adiciona(raiz, 6);
    adiciona(raiz, 9);
    adiciona(raiz, 5);
    adiciona(raiz, 7);
    percorrerPre(raiz);
    printf("\n");
    percorrerPos(raiz);
    printf("\n");
    percorrerLargura(raiz);

    return 0;
}
