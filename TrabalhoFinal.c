#include <stdio.h>

struct Dia{
    int dia, mes, ano;
};

struct Hora{
    int hora, minuto;
};

struct Agenda{
    struct Dia data;
    struct Hora horaIni, horaFim;
    char local[100], desc[255];
};

void Cadastrar(FILE *arq){
    //Função para cadastrar elementos na lista
    struct Agenda novo_cadastro;
    
    printf("Dia: ");
    scanf("%d", &novo_cadastro.data.dia);
    while((novo_cadastro.data.dia < 1) || (novo_cadastro.data.dia > 31)){
        printf("Erro: Dia Invalido\n");
        printf("Dia: ");
        scanf("%d", &novo_cadastro.data.dia);
    }
    printf("Mes: ");
    scanf("%d", &novo_cadastro.data.mes);
    while((novo_cadastro.data.mes < 1) || (novo_cadastro.data.mes > 12)){
        printf("Erro: Mes Invalido\n");
        printf("Mes: ");
        scanf("%d", &novo_cadastro.data.mes);
    }
    printf("Ano: ");
    scanf("%d", &novo_cadastro.data.ano);
    while(novo_cadastro.data.ano < 0){
        printf("Erro: Ano invalido\n");
        printf("Ano: ");
        scanf("%d", &novo_cadastro.data.ano);
    }
    
    do{
        if ((novo_cadastro.horaFim.minuto >= 0) && (novo_cadastro.horaFim.minuto <= 59))
            printf("Erro: Colisao de Horarios\n");

        printf("Hora Inicio: ");
        scanf("%d", &novo_cadastro.horaIni.hora);
        while((novo_cadastro.horaIni.hora < 0) || (novo_cadastro.horaIni.hora > 24)){
            printf("Erro: Hora Invalida\n");
            printf("Hora Inicio: ");
            scanf("%d", &novo_cadastro.horaIni.hora);
        }
        printf("Minuto Inicio: ");
        scanf("%d", &novo_cadastro.horaIni.minuto);
        while((novo_cadastro.horaIni.minuto < 0) || (novo_cadastro.horaIni.minuto > 59)){
            printf("Erro: Minuto Invalido\n");
            printf("Minuto Inicio: ");
            scanf("%d", &novo_cadastro.horaIni.minuto);
        }
        printf("Hora Fim: ");
        scanf("%d", &novo_cadastro.horaFim.hora);
        while((novo_cadastro.horaFim.hora < 0) || (novo_cadastro.horaFim.hora > 24)){
            printf("Erro: Hora invalida\n");
            printf("Hora Fim: ");
            scanf("%d", &novo_cadastro.horaFim.hora);
        }
        printf("Minuto Fim: ");
        scanf("%d", &novo_cadastro.horaFim.minuto);
        while((novo_cadastro.horaFim.minuto < 0) || (novo_cadastro.horaFim.minuto > 59)){
            printf("Erro: Minuto Invalido\n");
            printf("Minuto Fim: ");
            scanf("%d", &novo_cadastro.horaFim.minuto);
        }
    }while((novo_cadastro.horaIni.hora > novo_cadastro.horaFim.hora) || ((novo_cadastro.horaIni.hora == novo_cadastro.horaFim.hora) && (novo_cadastro.horaIni.minuto >= novo_cadastro.horaFim.minuto)));

    do{
        printf("Local: ");
        scanf("%s", novo_cadastro.local);
    }while(!novo_cadastro.local);
    printf("Descrição: ");
    scanf("%s", novo_cadastro.desc);
    
    // fseek(arq, 0, SEEK_END);
    // fwrite(&novo_cadastro, sizeof(novo_cadastro), 1, arq);
}

void MostrarTudo(){
    //Função para exibir todos os elementos da lista
}

void MostrarData(){
    //Função para exibir todos os elementos em tal data lida
    struct Dia data_escolhida;
    printf("Dia: ");
    scanf("%d", &data_escolhida.dia);
    printf("Mes: ");
    scanf("%d", &data_escolhida.mes);
    printf("Ano: ");
    scanf("%d", &data_escolhida.ano);
    printf("%d/%d/%d\n", data_escolhida.dia, data_escolhida.mes, data_escolhida.ano);
}

void MostrarProximos(){
    //Função para mostrar os 5 próximos eventos da lista
}

void Remover(){
    //Função para remover tal elemento, recebe-se a data e hora inicial do mesmo
}

int main()
{
    int escolha;
    while (1==1){
        printf("-=-=-=-=-= MENU =-=-=-=-=-\n");
        printf("(1) Cadastrar\n");
        printf("(2) Mostrar Todos Eventos\n");
        printf("(3) Mostrar Eventos Data\n");
        printf("(4) Mostrar Próximos Eventos\n");
        printf("(5) Remover Evento\n");
        printf("(6) Sair\n");
        scanf("%d", &escolha);
        
        switch(escolha){
            case 1:
                Cadastrar();
                break;
            case 2:
                // Mostrar();
                break;
            case 3:
                MostrarData();
                break;
            case 4:
                // MostrarProximos
                break;
            case 5:
                // Remover();
                break;
            case 6:
                // fclose(saida);
                return 0;
                break;
        }
    }
}
