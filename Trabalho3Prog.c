// Autor: Lucas Ziemann Ferreira
#include <stdio.h>
#include <string.h>

/* Obs: Preferi utilizar funções que recebem a lista como parâmetro do que simplesmente usar a variável global, pois assim é mais divertido e interessante, 
    além de ser melhor caso tenha de criar mais listas.
*/ 

// Criação da estrutura Agenda
struct Agenda{
    char nome[100], email[100], endereco[100], rua[100], complemento[100], bairro[100], cidade[100], estado[100], pais[100];
    int numero, cep, ddd, telefone, dia, mes, ano;
};

// Criação da variável a qual vai abrigar os dados
struct Agenda list[50]= {{"Teste"   , "Teste@gmail.com" , "Rua Teste"           , "Teste"       , "Apto. Teste"     , "Teste"       , "Testecity"       , "Teste State"     , "United States of Teste"  , 72    , 123456, 12, 40028922  , 12, 12, 2012  },
                      {"Teste 2"    , "Teste2@gmail.com", "Rua Teste 2"         , "Teste 2"     , "Apto. Teste 2"   , "Teste 2"     , "Testecity 2"     , "Teste State 2"   , "United States of Teste 2", 360   , 654321, 21, 22982004  , 25, 12, 0     },
                      {"Lucas"      , "lucas@gmail.com" , "Rua das Palmeiras"   , "Palmeiras"   , "Apto 1"          , "Centro"      , "Joinville"       , "Santa Catarina"  , "Brasil"                  ,  1    , 123   , 47, 999000099 , 24, 02, 2003  }
};
// Variável para guardar o último índice da matriz, utilizada para encurtar loops, otimizando o código
int lastPos = 3;
// Variável para guardar o tamanho da matriz
int arrayLength = sizeof(list) / sizeof(list[0]);

// Função para buscar pelo primeiro nome de uma pessoa (caso haja duas pessoas com nome igual a primeira a aparecer na lista será exibida)
void buscarPessoa(struct Agenda lista[arrayLength]){
    char name[100];
    printf("Digite o nome da Pessoa: \n");
    scanf("%s", name);
    
    for (int i=0;i<lastPos;i++){
        if (strcmp(lista[i].nome, name) == 0){
            printf("Nome da Pessoa: %s\n", lista[i].nome);
            printf("E-mail da Pessoa: %s\n", lista[i].email);
            printf("Telefone da Pessoa: (%d)%d\n", lista[i].ddd, lista[i].telefone);
        }
    }
}

// Função para buscar todas as pessoas que fazem aniversário no mês dado
void aniversariantesDoMes(struct Agenda lista[arrayLength]){
    int mensal;
    printf("Digite o mês: \n");
    scanf("%d", &mensal);
    
    for (int i=0;i<lastPos;i++){
        if (mensal == lista[i].mes){
            printf("%s faz aniversário no mês %d\n", lista[i].nome, lista[i].mes);
        }
    }
}

// Função para buscar todas as pessoas que fazem aniversário no mês e dia inseridos
void aniversariantesDoDia(struct Agenda lista[arrayLength]){
    int diario, mensal;
    printf("Digite o dia: \n");
    scanf("%d", &diario);
    printf("Digite o mês: \n");
    scanf("%d", &mensal);
    
    for (int i=0;i<lastPos;i++){
        if (mensal == lista[i].mes){
            if (diario == lista[i].dia){
                printf("%s faz aniversário no dia %d/%d\n", lista[i].nome, lista[i].dia, lista[i].mes);
            }
        }
    }
}

// Função para adicionar contatos à Agenda
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

// Função para remover usuários da Agenda
void removerUser(struct Agenda a[arrayLength]){
    int pos;
    printf("Digite a posição do registro: (começando do 0)\n");
    scanf("%d", &pos);
    
    for (int i=0;i<lastPos;i++){
        if (i >= pos){
            a[i] = a[i+1];
        }
    }
    lastPos--;
}

// Função para ver todos os nomes dos contatos da Agenda
void verContatos(){
    printf("Agenda: \n");
    for (int i=0;i<lastPos;i++){
        if (strcmp(list[i].nome, "") != 0)
            printf("%s -> %d\n", list[i].nome, i);
    }
}

// Main, Menu de 7 opções
int main()
{
    int escolha;
    while (1){
        printf("--- Menu ---\n");
        printf("Escolha uma das opções: \n");
        printf("1 - Buscar uma Pessoa\n");
        printf("2 - Aniversariantes do Mês\n");
        printf("3 - Aniversarantes do Dia\n");
        printf("4 - Inserir Pessoa\n");
        printf("5 - Remover Pessoa\n");
        printf("6 - Ver Contatos\n");
        printf("7 - Sair\n");
        scanf("%d", &escolha);
        switch(escolha){
            case 1:
                buscarPessoa(list);
                break;
            case 2:
                aniversariantesDoMes(list);
                break;
            case 3:
                aniversariantesDoDia(list);
                break;
            case 4:
                inserePessoa(&list[lastPos]);
                break;
            case 5:
                removerUser(list);
                break;
            case 6:
                verContatos();
                break;
            case 7:
                return 0;
        }
    }
    return 0;
}
