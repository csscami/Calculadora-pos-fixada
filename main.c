#include "expressao.h"
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <math.h>
#include <ctype.h>

void testarExpressao(const char *posfixa, const char *infixa, float valorEsperado) {
    Expressao exp;
    strcpy(exp.posFixa, posfixa);
    
   
    char temp[512];
    strcpy(temp, exp.posFixa);

    float valorCalculado = getValor(temp);
    
    
    strcpy(temp, exp.posFixa);
    char *formaInfixa = getFormaInFixa(temp);
    
    printf("\nTeste:\n");
    printf("Pos-fixa: %s\n", exp.posFixa);
    printf("In-fixa: %s\n", formaInfixa);
    printf("Valor calculado: %.2f\n", valorCalculado);
    printf("Valor esperado: %.2f\n", valorEsperado);
    printf("Resultado: %s\n\n", 
           fabs(valorCalculado - valorEsperado) < 0.01 ? "OK" : "ERRO");
}

int main() {

    testarExpressao("3 4 + 5 *", "(3 + 4) * 5", 35.0f);
    testarExpressao("7 2 * 4 +", "7 * 2 + 4", 18.0f);
    testarExpressao("8 5 2 4 + * +", "8 + (5 * (2 + 4))", 38.0f);
    testarExpressao("6 2 / 3 + 4 *", "(6 / 2 + 3) * 4", 24.0f);
    testarExpressao("9 5 2 8 * 4 + * +", "9 + (5 * (2 + 8 * 4))", 109.0f);
    testarExpressao("2 3 + log 5 /", "log(2 + 3) / 5", 0.14f);               
    testarExpressao("10 log 3 ^ 2 +", "(log 10)^3 + 2", 3.0f);               
    testarExpressao("45 60 + 30 cos *", "(45 + 60) * cos(30)", 90.93f);      
    testarExpressao("0.5 45 sen 2 ^ +", "sen(45)^2 + 0.5", 1.0f);            
    
    return 0;
}