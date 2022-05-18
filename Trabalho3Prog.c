#include <stdio.h>

struct Agenda{
    char nome[100], email[100], endereco[100], rua[100], complemento[100], bairro[100], cidade[100], estado[100], pais[100];
    int numero, cep, ddd, telefone, dia, mes, ano;
};


int main()
{
    struct Agenda teste[2]= {{"Teste", "Teste@gmail.com", "Rua Teste", "Teste", "Apto. Teste", "Teste", "Testecity", "Teste State", "United States of Teste", 69, 123456, 12, 40028922, 12, 12, 2012},
                      {"Teste 2", "Teste2@gmail.com", "Rua Teste 2", "Teste 2", "Apto. Teste 2", "Teste 2", "Testecity 2", "Teste State 2", "United States of Teste 2", 420, 654321, 21, 22982004, 25, 12, 0}
    };
    buscarPessoa("Teste", teste);
    aniversariantesDoMes(12, teste);
    aniversariantesDoDia(12,12, teste);
    return 0;
}

void buscarPessoa(char name[100], struct Agenda teste[2]){
    for (int i=0;i<2;i++){
        if (strcmp(teste[i].nome, name) == 0){
            printf("Nome da Pessoa: %s\n", teste[i].nome);
            printf("E-mail da Pessoa: %s\n", teste[i].email);
            printf("Telefone da Pessoa: (%d)%d\n", teste[i].ddd, teste[i].telefone);
        }
    }
}

void aniversariantesDoMes(int mensal, struct Agenda teste[2]){
    for (int i=0;i<2;i++){
        if (mensal == teste[i].mes){
            printf("%s faz aniversário no mês %d\n", teste[i].nome, teste[i].mes);
        }
    }
}

void aniversariantesDoDia(int diario, int mensal, struct Agenda teste[2]){
    for (int i=0;i<2;i++){
        if (mensal == teste[i].mes){
            if (diario == teste[i].dia){
                printf("%s faz aniversário no dia %d/%d\n", teste[i].nome, teste[i].dia, teste[i].mes);
            }
        }
    }
}
