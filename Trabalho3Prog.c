#include <stdio.h>
#include <string.h>

struct Agenda{
    char nome[100], email[100], endereco[100], rua[100], complemento[100], bairro[100], cidade[100], estado[100], pais[100];
    int numero, cep, ddd, telefone, dia, mes, ano;
};

struct Agenda lista[50]= {{"Teste"   , "Teste@gmail.com" , "Rua Teste"           , "Teste"       , "Apto. Teste"     , "Teste"       , "Testecity"       , "Teste State"     , "United States of Teste"  , 72    , 123456, 12, 40028922  , 12, 12, 2012  },
                      {"Teste 2"    , "Teste2@gmail.com", "Rua Teste 2"         , "Teste 2"     , "Apto. Teste 2"   , "Teste 2"     , "Testecity 2"     , "Teste State 2"   , "United States of Teste 2", 360   , 654321, 21, 22982004  , 25, 12, 0     },
                      {"Lucas"      , "lucas@gmail.com" , "Rua das Palmeiras"   , "Palmeiras"   , "Apto 1"          , "Centro"      , "Joinville"       , "Santa Catarina"  , "Brasil"                  ,  1    , 123   , 47, 999000099 , 24, 02, 2003  }
};
int lastPos = 3;
int arrayLength = sizeof(lista) / sizeof(lista[0]);

void buscarPessoa(char name[100], struct Agenda lista[arrayLength]){
    for (int i=0;i<lastPos;i++){
        if (strcmp(lista[i].nome, name) == 0){
            printf("Nome da Pessoa: %s\n", lista[i].nome);
            printf("E-mail da Pessoa: %s\n", lista[i].email);
            printf("Telefone da Pessoa: (%d)%d\n", lista[i].ddd, lista[i].telefone);
            return;
        }
    }
    printf("Pessoa não encontrada.\n");
}

void aniversariantesDoMes(int mensal, struct Agenda lista[arrayLength]){
    for (int i=0;i<lastPos;i++){
        if (mensal == lista[i].mes){
            printf("%s faz aniversário no mês %d\n", lista[i].nome, lista[i].mes);
        }
    }
}

void aniversariantesDoDia(int diario, int mensal, struct Agenda lista[arrayLength]){
    for (int i=0;i<lastPos;i++){
        if (mensal == lista[i].mes){
            if (diario == lista[i].dia){
                printf("%s faz aniversário no dia %d/%d\n", lista[i].nome, lista[i].dia, lista[i].mes);
            }
        }
    }
}

void inserePessoa(struct Agenda *a){
    printf("Nome: ");
    scanf("%s", a->nome);
    printf("Email: ");
    scanf("%s", a->email);
    printf("Endereço: ");
    scanf("%s", a->endereco);
    printf("Rua: ");
    scanf("%s", a->rua);
    printf("Complemento: ");
    scanf("%s", a->complemento);
    printf("Bairro: ");
    scanf("%s", a->bairro);
    printf("Cidade: ");
    scanf("%s", a->cidade);
    printf("Estado: ");
    scanf("%s", a->estado);
    printf("País: ");
    scanf("%s", a->pais);
    printf("Número da Casa: ");
    scanf("%d", &a->numero);
    printf("CEP: ");
    scanf("%d", &a->cep);
    printf("DDD: ");
    scanf("%d", &a->ddd);
    printf("Telefone: ");
    scanf("%d", &a->telefone);
    printf("Dia de Nascimento: ");
    scanf("%d", &a->dia);
    printf("Mês de Nascimento: ");
    scanf("%d", &a->mes);
    printf("Ano de Nascimento: ");
    scanf("%d", &a->ano);
    lastPos++;
}

void removerUser(struct Agenda a[arrayLength], int pos){
    for (int i=0;i<lastPos;i++){
        if (i >= pos){
            a[i] = a[i+1];
        }
    }
    lastPos--;
}

int main()
{
    buscarPessoa("Teste 2", lista);
    aniversariantesDoMes(12, lista);
    aniversariantesDoDia(12,12, lista);
    inserePessoa(&lista[3]);
    buscarPessoa("Lucas", lista);
    removerUser(lista, 2);
    removerUser(lista, 1);
    for (int i=0;i<lastPos;i++){
        if (strcmp(lista[i].nome, "") != 0)
            printf("%s -> %d\n", lista[i].nome, i);
    }
    return 0;
}
