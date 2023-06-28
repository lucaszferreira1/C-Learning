#include <stdlib.h>
#include <stdio.h>
#include <stdbool.h>

#define MAX 1

int n_operacoes = 0;

enum coloracao { Vermelho, Preto };
typedef enum coloracao Cor;

typedef struct no {
    struct no* pai;
    struct no* esquerda;
    struct no* direita;
    Cor cor;
    int valor;
} No;

typedef struct arvore {
    struct no* raiz;
    struct no* nulo; 
} Arvore;

No* criarNo(Arvore*, No*, int);
void balancear(Arvore*, No*);
void rotacionarEsquerda(Arvore*, No*);
void rotacionarDireita(Arvore*, No*);

Arvore* criar();
int vazia(Arvore*);
No* adicionar(Arvore*, int);
No* localizar(Arvore* arvore, int valor);

Arvore* criar() {
    Arvore *arvore = malloc(sizeof(Arvore));
    arvore->nulo = NULL;
    arvore->raiz = NULL;

    arvore->nulo = criarNo(arvore, NULL, 0);
    arvore->nulo->cor = Preto;

    return arvore;
}

int vazia(Arvore* arvore) {
    return arvore->raiz == NULL;
}

No* criarNo(Arvore* arvore, No* pai, int valor) {
    No* no = malloc(sizeof(No));

    no->pai = pai;    
    no->valor = valor;
    no->direita = arvore->nulo;
    no->esquerda = arvore->nulo;

    return no;
}

No* adicionarNo(Arvore* arvore, No* no, int valor) {
    if (valor > no->valor) {
        if (no->direita == arvore->nulo) {
            no->direita = criarNo(arvore, no, valor);     
            no->direita->cor = Vermelho;       
        		
            return no->direita;
        } else {
            return adicionarNo(arvore, no->direita, valor);
        }
    } else {
        if (no->esquerda == arvore->nulo) {
            no->esquerda = criarNo(arvore, no, valor);
            no->esquerda->cor = Vermelho;
            
            return no->esquerda;
        } else {
            return adicionarNo(arvore, no->esquerda, valor);
        }
    }
}

No* adicionar(Arvore* arvore, int valor) {
    if (vazia(arvore)) {
        arvore->raiz = criarNo(arvore, arvore->nulo, valor);
        arvore->raiz->cor = Preto;
        	
        return arvore->raiz;
    } else {
        No* no = adicionarNo(arvore, arvore->raiz, valor);
        balancear(arvore, no);
        
        return no;
    }
}

No* localizar(Arvore* arvore, int valor) {
    if (!vazia(arvore)) {
        No* no = arvore->raiz;

        while (no != arvore->nulo) {
            n_operacoes++;
            if (no->valor == valor) {
                return no;
            } else {
                no = valor < no->valor ? no->esquerda : no->direita;
            }
        }
    }

    return NULL;
}

void visitar(int valor){
    printf("%d ", valor);
}

void balancear(Arvore* arvore, No* no) {
    while (no->pai->cor == Vermelho) {
        n_operacoes++;
        if (no->pai == no->pai->pai->esquerda) {
            No *tio = no->pai->pai->direita;
            
            if (tio->cor == Vermelho) {
                tio->cor = Preto; //Caso 1
                no->pai->cor = Preto; 

                no->pai->pai->cor = Vermelho; //Caso 1
                no = no->pai->pai; //Caso 1
            } else {
                if (no == no->pai->direita) {
                    no = no->pai; //Caso 2
                    rotacionarEsquerda(arvore, no); //Caso 2
                } else {
                    no->pai->cor = Preto; 
                    no->pai->pai->cor = Vermelho; //Caso 3
                    rotacionarDireita(arvore, no->pai->pai); //Caso 3
                }
            }
        } else {
            No *tio = no->pai->pai->esquerda;
            
            if (tio->cor == Vermelho) {
                tio->cor = Preto; //Caso 1
                no->pai->cor = Preto; 

                no->pai->pai->cor = Vermelho; //Caso 1
                no = no->pai->pai; //Caso 1
            } else {
                if (no == no->pai->esquerda) {
                    no = no->pai; //Caso 2
                    rotacionarDireita(arvore, no); //Caso 2
                } else {
                    no->pai->cor = Preto; 
                    no->pai->pai->cor = Vermelho; //Caso 3
                    rotacionarEsquerda(arvore, no->pai->pai); //Caso 3
                }
            }
        }
    }
    arvore->raiz->cor = Preto; //Conserta possível quebra regra 2
}

void rotacionarEsquerda(Arvore* arvore, No* no) {
    n_operacoes++;
    No* direita = no->direita;
    no->direita = direita->esquerda; 

    if (direita->esquerda != arvore->nulo) {
        direita->esquerda->pai = no;
    }

    direita->pai = no->pai;
    
    if (no->pai == arvore->nulo) {
        arvore->raiz = direita;
    } else if (no == no->pai->esquerda) {
        no->pai->esquerda = direita;
    } else {
        no->pai->direita = direita;
    }

    direita->esquerda = no;
    no->pai = direita;
}

void rotacionarDireita(Arvore* arvore, No* no) {
    n_operacoes++;
    No* esquerda = no->esquerda;
    no->esquerda = esquerda->direita;
    
    if (esquerda->direita != arvore->nulo) {
        esquerda->direita->pai = no;
    }
    
    esquerda->pai = no->pai;
    
    if (no->pai == arvore->nulo) {
        arvore->raiz = esquerda;
    } else if (no == no->pai->esquerda) {
        no->pai->esquerda = esquerda;
    } else {
        no->pai->direita = esquerda;
    }
    
    esquerda->direita = no;
    no->pai = esquerda;
}

bool isOnLeft(No* no){
    return no == no->pai->esquerda; 
}
  
No *irmao(No* no){
    if (no->pai == NULL)
        return NULL;
    
    if (isOnLeft(no))
        return no->pai->direita;
    
    return no->pai->esquerda;
}

No *sucessor(No *no) {
    No *temp = no;
    
    while (temp->esquerda != NULL)
        temp = temp->esquerda;
    
    return temp;
}

bool hasRedChild(No* no) {
    return (((no->esquerda != NULL) && (no->esquerda->cor == Vermelho)) || ((no->direita != NULL) && (no->direita->cor == Vermelho)));
}

void swapValues(No *u, No *v) {
    int temp;
    temp = u->valor;
    u->valor = v->valor;
    v->valor = temp;
}

No *findReplacement(No* no) {
    // no com 2 filhos
    if ((no->esquerda != NULL) && (no->direita != NULL))
        return sucessor(no->direita);
 
    // quando Folha
    if (no->esquerda == NULL && no->direita == NULL)
        return NULL;
 
    // quando Filho Único
    if (no->esquerda != NULL)
        return no->esquerda;
    else
        return no->direita;
}

void fixDoubleBlack(Arvore* a, No *no) {
    if (no == a->raiz || no == a->nulo)
        return;
     
    No *irmaoNo = irmao(no);
    No *pai = no->pai;
    if (irmaoNo == NULL) {
        fixDoubleBlack(a, pai);
    } else {
        if (irmaoNo->cor == Vermelho) {
            // irmao vermelho
            pai->cor = Vermelho;
            irmaoNo->cor = Preto;
            if (isOnLeft(irmaoNo)) {
            // esquerda
            rotacionarDireita(a, pai);
            } else {
            // direita
            rotacionarEsquerda(a, pai);
            }
            fixDoubleBlack(a, no);
        } else {
            // irmao preto
            if (hasRedChild(irmaoNo)) {
                // pelo menos 1 filho vermelho
                if (irmaoNo->esquerda != NULL && irmaoNo->esquerda->cor == Vermelho) {
                    if (isOnLeft(irmaoNo)) {
                        // esquerda esquerda
                        irmaoNo->esquerda->cor = irmaoNo->cor;
                        irmaoNo->cor = pai->cor;
                        rotacionarDireita(a, pai);
                    } else {
                        // direita esquerda
                        irmaoNo->esquerda->cor = pai->cor;
                        rotacionarDireita(a, irmaoNo);
                        rotacionarEsquerda(a, pai);
                    }
                } else {
                    if (isOnLeft(irmaoNo)) {
                        // esquerda direita
                        irmaoNo->direita->cor = pai->cor;
                        rotacionarEsquerda(a, irmaoNo);
                        rotacionarDireita(a, pai);
                    } else {
                        // direita direita
                        irmaoNo->direita->cor = irmaoNo->cor;
                        irmaoNo->cor = pai->cor;
                        rotacionarEsquerda(a, pai);
                    }
                }
                pai->cor = Preto;
            } else {
                // 2 filhos pretos
                irmaoNo->cor = Vermelho;
                if (pai->cor == Preto)
                    fixDoubleBlack(a, pai);
                else
                    pai->cor = Preto;
            }
        }
    }
}

void removerNo(Arvore* a, No* no){
    n_operacoes++;
    No* re = findReplacement(no);
    // true quando no e re são pretos
    bool nrPreto = ((re == NULL || re->cor == Preto) && (no->cor == Preto));
    No *pai = no->pai;
    if (pai == NULL)
        return;
    
    if (re == NULL) {
        // no é folha
        if (no == a->raiz) {
            a->raiz = NULL;
        } else {
            if (nrPreto) {
                // re e no Pretos
                // no é folha, fix double black em no
                fixDoubleBlack(a, no);
            } else {
                // re ou no é vermelho
                if (irmao(no) != NULL)
                    irmao(no)->cor = Vermelho;
            }
            
            // remove no da árvore
            if (isOnLeft(no)) 
                pai->esquerda = NULL;
            else 
                pai->direita = NULL;
        }
        free(no);
        return;
    }
 
    if (no->esquerda == NULL || no->direita == NULL) {
    // no tem 1 filho
        if (no == a->raiz) {
            no->valor = re->valor;
            no->esquerda = NULL;
            no->direita = NULL;
            free(re);
        } else {
            if (isOnLeft(no)) {
                pai->esquerda = re;
            } else {
                pai->direita = re;
            }
            free(no);
            re->pai = pai;
            if (nrPreto) {
                fixDoubleBlack(a, re);
                } else {
                  re->cor = Preto;
            }
        }
        return;
    }
 
    // no tem 2 filhos, troca de valor com sucessor e remove ele
    swapValues(re, no);
    removerNo(a, re);

}

void remover(Arvore *a, int valor){
    if (vazia(a))
        return;
    No* no = localizar(a, valor);
    if (no != NULL){
        if (no->valor == valor)
            removerNo(a, no);
    }
    return;
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
    // Red Black
    FILE *fp;
    fp = fopen("results.txt", "w");
    if (!fp){
        printf("Can't open file\n");
    } else {
        int vezes = 1;
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
            
            n_operacoes = 0;
            for (int i=0;i<n;i++){
                remover(a, v[i]);
                printf("%d %d\n", i, n_operacoes);
                fprintf(fp, "%d %d\n", i, n_operacoes);
                n_operacoes = 0;
            }
        }
        
        // float avrg;
        // for (int i=0;i<n;i++){
        //     avrg = sum[i] / vezes;
        //     fprintf(fp, "%d %f\n", i, avrg);
        // }
    }
    
    return 0;
}
