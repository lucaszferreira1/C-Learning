#include <stdio.h>
#include <math.h>

float juros(int mes, float vMontante, float vPrestacao){
  float diferenca = 1.0f, suposto_juros = 0.0f;
  while (diferenca > 0.000000001){
    suposto_juros += 0.000000001;
    float suposta_parcela = (vMontante * suposto_juros) / (1.0 - pow(1.0/(1.0+suposto_juros), mes));
    diferenca = fabs(vPrestacao - suposta_parcela);
    printf("%f", suposto_juros);
    }
  return (suposto_juros * 100);
}                                                      

int main()
{
    int mes;
    float vlFinan, vlPres;
    scanf("%d", &mes);
    scanf("%f", &vlFinan);
    scanf("%f", &vlPres);
    printf("%f", juros(mes, vlFinan, vlPres));
    return 0;
}
