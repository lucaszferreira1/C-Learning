#include <stdio.h>
#include <stdlib.h>

typedef struct no {
    struct no* pai;
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

No* cria(int valor, No* pai) {
    No *no;
    no = malloc(sizeof(No));
    no->esquerda = NULL;
    no->direita = NULL;
    no->valor = valor;
    if (pai != NULL){
        no->pai = pai;
    }else{
        no->pai = NULL;
    }
    
    return no;
}

int vazio(No* no) {
    return (no == NULL);
}

int altura(No* no){
    int hesquerda = 0;
    int hdireita = 0;
    if (no->esquerda != NULL) 
        hesquerda = altura(no->esquerda) + 1;
    if (no->direita != NULL) 
        hdireita = altura(no->direita) + 1;
    
    return hesquerda > hdireita ? hesquerda : hdireita;
}

void printNo(No* no){
    printf("\nPai: ");
    if (no->pai != NULL)
        printf("%d", no->pai->valor);
    else
        printf("NULL");
    printf("\nEsquerda: ");
    if (no->esquerda != NULL)
        printf("%d", no->esquerda->valor);
    else
        printf("NULL");
    printf("\nDireita: ");
    if (no->direita != NULL)
        printf("%d", no->direita->valor);
    else
        printf("NULL");
    printf("\nValor: %d", no->valor);
}

No* adiciona(No* no, int valor, No* pai) {
    if (vazio(no)) 
        return cria(valor, pai);
    else if(no->valor > valor)
        no->esquerda = adiciona(no->esquerda, valor, no);
    else if (no->valor < valor)
        no->direita = adiciona(no->direita, valor, no);
    
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
    int alt = 0;
    while(fila->inicial){
        no = removerFila(fila);
        printf("%d ", no->valor);
        if (no->esquerda)
            adicionarFila(fila, no->esquerda);
        if (no->direita)
            adicionarFila(fila, no->direita);
        alt = altura(no);
    }
}

int fb(No* no) {
    int esquerda = 0;
    int direita = 0;
    if (no->esquerda != NULL) 
        esquerda = altura(no->esquerda) + 1;
    if (no->direita != NULL) 
        direita = altura(no->direita) + 1;
    
    return esquerda - direita;
}

No* rse(No* no) {
    No* pai = no->pai;
    No* direita = no->direita;
    
    no->direita = direita->esquerda;
    no->pai = direita;
    direita->esquerda = no;
    direita->pai = pai;
    printf("RSE");
    return direita;
}


No* rsd(No* no) {
    No* pai = no->pai;
    No* esquerda = no->esquerda;
    
    no->esquerda = esquerda->direita;
    no->pai = esquerda;
    esquerda->direita = no;
    esquerda->pai = pai;
    printf("RSD");
    return esquerda;
}


No* rde(No* no) {
    no->direita = rsd(no->direita);
    printf("RDE");
    return rse(no);
}

No* rdd(No* no) {
    no->esquerda = rse(no->esquerda);
    printf("RDD");
    return rsd(no);
}

No* adicionaAVL(No* no, int valor) {
    adiciona(no, valor, NULL);
    if (no != NULL){
        int balance = fb(no);
        if (balance > 1 && valor < no->esquerda->valor)
            return rsd(no);
        else if (balance < -1 && valor > no->direita->valor)
            return rse(no);
        else if (balance > 1 && valor > no->esquerda->valor) 
            return rdd(no);
        else if (balance < -1 && valor < no->direita->valor) 
            return rde(no);
    }
    return no;
}

int main()
{
    No *raiz = adiciona(raiz, 4, NULL);
    raiz = adicionaAVL(raiz, 2);
    raiz = adicionaAVL(raiz, 8);
    raiz = adicionaAVL(raiz, 1);
    raiz = adicionaAVL(raiz, 3);
    raiz = adicionaAVL(raiz, 6);
    raiz = adicionaAVL(raiz, 9);
    raiz = adicionaAVL(raiz, 5);
    raiz = adicionaAVL(raiz, 7);
    
    printf("\n");
    percorrerLargura(raiz);

    return 0;
}

