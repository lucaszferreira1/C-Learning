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
    int errorMsg = 0;
    
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
      if(errorMsg == 1){
        printf("Erro: Colisão de horários: Horário está colidindo com um horário já cadastrado!\n");
        errorMsg = 0;
      }
    do{
        if ((novo_cadastro.horaIni.hora > novo_cadastro.horaFim.hora) || ((novo_cadastro.horaIni.hora == novo_cadastro.horaFim.hora) && (novo_cadastro.horaIni.minuto >= novo_cadastro.horaFim.minuto)))
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
    
    //Verificar se o Local Foi preenchido
    do{
        printf("Local: ");
        scanf("%s", novo_cadastro.local);
    }while(!novo_cadastro.local);
    
    //Input da descrição
    printf("Descrição: ");
    scanf("%s", novo_cadastro.desc);
    
    //Verificação de Colisão de dois horários
    struct Agenda r;
    fseek(arq, 0, SEEK_SET);
    fread(&r, sizeof(r), 1, arq);
    do{
        //Verifica a data primeiro
        if ((r.data.dia == novo_cadastro.data.dia) && (r.data.mes == novo_cadastro.data.mes) && (r.data.ano == novo_cadastro.data.ano)){
            //Verifica o horário
            int cad_mins_ini = ((novo_cadastro.horaIni.hora * 60) + novo_cadastro.horaIni.minuto);
            int arq_mins_ini = ((r.horaIni.hora * 60) + r.horaIni.minuto);
            int cad_mins_fim = ((novo_cadastro.horaFim.hora * 60) + novo_cadastro.horaFim.minuto);
            int arq_mins_fim = ((r.horaFim.hora * 60) + r.horaFim.minuto);
            if ((cad_mins_ini < arq_mins_fim) && (arq_mins_ini < cad_mins_fim)){
                errorMsg = 1;
            }
          }
        fread(&r, sizeof(r), 1, arq);
    }while(!feof(arq));
  }while(errorMsg);
  
    fseek(arq, 0, SEEK_END);
    fwrite(&novo_cadastro, sizeof(novo_cadastro), 1, arq);
    printf("Novo registro na agenda cadastrado com sucesso!\n");
}


void MostrarTudo(FILE *arq){
    //Função para exibir todos os elementos da lista
    struct Agenda r;
    fseek(arq, 0, SEEK_SET);
    fread(&r, sizeof(r), 1, arq);
    do{
        printf("%s, Local: %s\n", r.desc, r.local);
        printf("Data: %.2d/%.2d/%.2d\n", r.data.dia, r.data.mes, r.data.ano);
        printf("Horário: %.2d:%.2d - %.2d:%.2d\n\n", r.horaIni.hora, r.horaIni.minuto, r.horaFim.hora, r.horaFim.minuto);
        fread(&r, sizeof(r), 1, arq);
    }while(!feof(arq));
}

void MostrarData(FILE *arq){
    //Função para exibir todos os elementos em tal data lida
    struct Dia data_escolhida;
    struct Agenda r;
    printf("\nDia: ");
    scanf("%d", &data_escolhida.dia);
    printf("Mes: ");
    scanf("%d", &data_escolhida.mes);
    printf("Ano: ");
    scanf("%d", &data_escolhida.ano);
    printf("Mostrando Registros do dia: %.2d/%.2d/%.2d\n", data_escolhida.dia, data_escolhida.mes, data_escolhida.ano);
    
    fseek(arq, 0, SEEK_SET);
    fread(&r, sizeof(r), 1, arq);
    do{
        if ((data_escolhida.dia == r.data.dia) && (data_escolhida.mes == r.data.mes) && (data_escolhida.ano == r.data.ano)){
            printf("%s, Local: %s\n", r.desc, r.local);
            printf("Horário: %.2d:%.2d - %.2d:%.2d\n\n", r.horaIni.hora, r.horaIni.minuto, r.horaFim.hora, r.horaFim.minuto);
        }
        fread(&r, sizeof(r), 1, arq);
    }while(!feof(arq));
}

void MostrarProximos(FILE *arq){
    //Função para mostrar os 5 próximos eventos da lista
    struct Agenda r;
    int i;
    fseek(arq, 0, SEEK_SET);
    fread(&r, sizeof(r), 1, arq);
    for (i=0;i<5;i++){
        if (!r.data.ano)
          break;
        printf("%s, Local: %s\n", r.desc, r.local);
        printf("Data: %.2d/%.2d/%.2d\n", r.data.dia, r.data.mes, r.data.ano);
        printf("Horário: %.2d:%.2d - %.2d:%.2d\n\n", r.horaIni.hora, r.horaIni.minuto, r.horaFim.hora, r.horaFim.minuto);
        fread(&r, sizeof(r), 1, arq);
        if(feof(arq))
            break;
    }
}

void Remover(FILE *arq){
    //Função para remover tal elemento, recebe-se a data e hora inicial do mesmo
    struct Dia data_escolhida;
    struct Hora hora_escolhida;
    
    printf("Dia: ");
    scanf("%d", &data_escolhida.dia);
    printf("Mes: ");
    scanf("%d", &data_escolhida.mes);
    printf("Ano: ");
    scanf("%d", &data_escolhida.ano);
    printf("Hora de Início: ");
    scanf("%d", &hora_escolhida.hora);
    printf("Minuto de Início: ");
    scanf("%d", &hora_escolhida.minuto);
    
    struct Agenda r;
    FILE *arq_temp = fopen("arq_temp.dat", "w+b");
    if(!arq_temp){
        printf("Erro ao abrir arquivo temporário!\n");
        return;
    }
    fseek(arq, 0, SEEK_SET);
    fread(&r, sizeof(r), 1, arq);
    do{
        if ((data_escolhida.dia == r.data.dia) && (data_escolhida.mes == r.data.mes) && (data_escolhida.ano == r.data.ano) && (hora_escolhida.hora == r.horaIni.hora) && (hora_escolhida.minuto == r.horaIni.minuto)){
            printf("Registro Deletado!\n");
        }else{
            fwrite(&r, sizeof(struct Agenda), 1, arq_temp);
        }
        fread(&r, sizeof(r), 1, arq);
    }while(!feof(arq));
    
    fclose(arq_temp);
    fclose(arq);

    remove("arquivo.dat");
    rename("arq_temp.dat", "arquivo.dat");
}
//Tentei fazer a função para ordenar a lista porém alguma coisa esta fazendo datas como 01/01/2001 ficarem no meio da lista
/*void OrdenarAgenda(FILE *arq){
	struct Agenda r;
	struct Agenda aux;
	struct Agenda *orderedList = malloc(sizeof(struct Agenda));
	int i = 0;
	int j, h;
	
	fseek(arq, 0, SEEK_SET);
    fread(&r, sizeof(r), 1, arq);
	do{
		orderedList = realloc(orderedList, sizeof(struct Agenda) * (i+1));
		orderedList[i] = r;
		i++;
		fread(&r, sizeof(r), 1, arq);
    }while(!feof(arq));
	int temp1, temp2;
	for (j=0;j<i;j++){
		for (h=0;h<(i-1);h++){
			temp1 = (orderedList[j].horaIni.hora * 60) + (orderedList[j].horaIni.minuto);
			temp2 = (orderedList[j+1].horaIni.hora * 60) + (orderedList[j+1].horaIni.minuto);
			if ((orderedList[j].data.ano > orderedList[j+1].data.ano) || ((orderedList[j].data.ano == orderedList[j+1].data.ano) && (orderedList[j].data.mes > orderedList[j+1].data.mes)) || ((orderedList[j].data.ano == orderedList[j+1].data.ano) && (orderedList[j].data.mes == orderedList[j+1].data.mes) && (orderedList[j].data.dia > orderedList[j+1].data.dia)) || ((orderedList[j].data.ano == orderedList[j+1].data.ano) && (orderedList[j].data.mes == orderedList[j+1].data.mes) && (orderedList[j].data.dia == orderedList[j+1].data.dia) && (temp1 > temp2))){
				aux = orderedList[j];
	            orderedList[j] = orderedList[j+1];
	            orderedList[j+1] = aux;
			    fwrite(&orderedList[j], sizeof(struct Agenda), 1, arq_temp);
			}
		}
	}
}*/

int main()
{
    int escolha;
    int i;
    struct Agenda testes[] = {{25, 2, 2003, 12, 30, 13, 0, "Joinville", "Isto é um Teste"}, {24, 2, 2003, 13, 00, 14, 30, "Área 51", "Datas iguais"}, {29, 5, 2007, 14, 0, 23, 59, "São Paulo", "Segundo Teste"}, {19, 9, 2012, 9, 40, 22, 0, "Recife", "Terceiro Teste"}, {1, 1, 2001, 2, 10, 19, 0, "Fortaleza", "Quarto Teste"}, {12, 12, 2012, 0, 12, 12, 12, "Acre", "Quinto Teste"}, {19, 9, 2009, 9, 9, 21, 9, "Manáus", "Sexto Teste"}};
    FILE *arq = fopen("arquivo.dat", "w+b");
    if (!arq){
        printf("Erro ao abrir o arquivo!\n");
        return 1;
    }
    for (i=0;i<7;i++){
        fwrite(&testes[i], sizeof(struct Agenda), 1, arq);
    }
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
                Cadastrar(arq);
                break;
            case 2:
                MostrarTudo(arq);
                break;
            case 3:
                MostrarData(arq);
                break;
            case 4:
                MostrarProximos(arq);
                break;
            case 5:
                Remover(arq);
                FILE *arq = fopen("arquivo.dat", "r+b");
                break;
            case 6:
                fclose(arq);
                return 0;
                break;
        }
    }
}
