#include <stdio.h>
#include <stdlib.h>
#include <time.h>

#define MAX 1

int n_operacoes = 0;

typedef struct no {
    int total;
    int* chaves;
    struct no** filhos;
    struct no* pai;
} No;

typedef struct arvoreB {
        No* raiz;
    int ordem;
} ArvoreB;

void visitar(int valor){
    printf("%d ", valor);
}

No* criaNo(ArvoreB*);
ArvoreB* criar(int);
int transbordo(ArvoreB*, No*);
int localizaChave(ArvoreB*, int);
void adicionaChave(ArvoreB*, int);
int pesquisaBinaria(No*, int);
No* localizaNo(ArvoreB*, int);
void adicionaChaveNo(No*, No*, int);
No* divideNo(ArvoreB*, No*);
void adicionaChaveRecursivo(ArvoreB*, No*, No*, int);

No* criaNo(ArvoreB* arvore) {
    int max = arvore->ordem * 2;
    No* no = malloc(sizeof(No));
    no->pai = NULL;
    
    no->chaves = malloc(sizeof(int) * (max + 1));
    no->filhos = malloc(sizeof(No) * (max + 2));
    no->total = 0;
    for (int i = 0; i < max + 2; i++)
        no->filhos[i] = NULL;
    return no;
}

ArvoreB* criar(int ordem) {
    ArvoreB* a = malloc(sizeof(ArvoreB));
    a->ordem = ordem;
    a->raiz = criaNo(a);
    return a;
}

int transbordo(ArvoreB *arvore, No *no) {
    return no->total > arvore->ordem * 2;
}

int localizaChave(ArvoreB* arvore, int chave) {
    No *no = arvore->raiz;
    while (no != NULL) {
        int i = pesquisaBinaria(no, chave);
        if (i < no->total && no->chaves[i] == chave) {
            return 1; //encontrou
        } else {
            no = no->filhos[i];
        }
    }
    return 0; //não encontrou
}

void adicionaChave(ArvoreB* arvore, int chave) {
    No* no = localizaNo(arvore, chave);
    adicionaChaveRecursivo(arvore, no, NULL, chave);
}

void percorreArvore(No* no, void (visita)(int chave)) {
    if (no != NULL) {
        for (int i = 0; i < no->total; i++){
            percorreArvore(no->filhos[i], visita);
            
            visita(no->chaves[i]);
        }
        percorreArvore(no->filhos[no->total], visita);
    }
}

int pesquisaBinaria(No* no, int chave) {
    int inicio = 0, fim = no->total - 1, meio;
    while (inicio <= fim) {
        meio = (inicio + fim) / 2;
        if (no->chaves[meio] == chave) {
            return meio; //encontrou
        } else if (no->chaves[meio] > chave) {
            fim = meio - 1;
        } else {
            inicio = meio + 1;
        }
    }
    return inicio; //não encontrou
}

No* localizaNo(ArvoreB* arvore, int chave) {
    No *no = arvore->raiz;

    while (no != NULL) {
        n_operacoes++;
        int i = pesquisaBinaria(no, chave);
        if (no->filhos[i] == NULL)
            return no; //encontrou nó
        else
            no = no->filhos[i];
    }
    return NULL; //não encontrou nenhum nó
}

void adicionaChaveNo(No* no, No* direita, int chave) {
    int i = pesquisaBinaria(no, chave);
    for (int j = no->total - 1; j >= i; j--) {
        no->chaves[j + 1] = no->chaves[j];
        no->filhos[j + 2] = no->filhos[j + 1];
    }
    
    no->chaves[i] = chave;
    no->filhos[i + 1] = direita;
    no->total++;
}

No* divideNo(ArvoreB* arvore, No* no) {
    n_operacoes++;
    int meio = no->total / 2;
    No* novo = criaNo(arvore);
    novo->pai = no->pai;
    
    for (int i = meio + 1; i < no->total; i++) {
        novo->filhos[novo->total] = no->filhos[i];
        novo->chaves[novo->total] = no->chaves[i];
        if (novo->filhos[novo->total] != NULL) novo->filhos[novo->total]->pai = novo;
        novo->total++;
    }
    novo->filhos[novo->total] = no->filhos[no->total];
    if (novo->filhos[novo->total] != NULL) novo->filhos[novo->total]->pai = novo;
        no->total = meio;
    return novo;
}

void adicionaChaveRecursivo(ArvoreB* arvore, No* no, No* novo, int chave) {
    n_operacoes++;
    adicionaChaveNo(no, novo, chave);
    if (transbordo(arvore, no)) {
        int promovido = no->chaves[arvore->ordem];
        No* novo = divideNo(arvore, no);
        if (no->pai == NULL) {
            No* raiz = criaNo(arvore);
            raiz->filhos[0] = no;
            adicionaChaveNo(no, novo, promovido);
            
            no->pai = raiz;
            novo->pai = raiz;
            arvore->raiz = raiz;
        } else
            adicionaChaveRecursivo(arvore, no->pai, novo, promovido);
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
    int vezes = 1000;
    int n = 10000;
    int sum[n];
    for (int i=0;i<10000;i++){
        sum[i] = 0;
    }
    for (int j=0;j<vezes;j++){
        int* v = geraVetor(n + 1);
    
        ArvoreB* a = criar(10);
        for (int i=0;i<n;i++){
            adicionaChave(a, v[i]);
            sum[i] += n_operacoes;
            n_operacoes = 0;
        }
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
