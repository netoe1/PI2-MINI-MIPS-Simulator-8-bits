# include "ula.h"
#include <stdio.h>

static int8_t operacao_add(int8_t a, int8_t b);

static void executar_operacoes(int8_t operador, int8_t operador2, uint8_t controleUla, ResultadoUla *resultadoUla);

ResultadoUla executar(int8_t operador, int8_t operador2, uint8_t controleUla) {
    ResultadoUla resultadoUla;
    executar_operacoes(operador, operador2, controleUla, &resultadoUla);
    return resultadoUla;
}

static void executar_operacoes(int8_t operador, int8_t operador2, uint8_t controleUla, ResultadoUla *resultadoUla) {
    switch (controleUla) {
        case OP_ADD:
        case OP_ADDI:
        case OP_LW:
        case OP_SW:
            resultadoUla->resultado = operacao_add(operador, operador2);
            break;;
        default:
            // Operação desconhecida ou ainda não implementada, definir resultado como zero ou algum valor padrão
            printf("Operação da ULA ainda não implementada. \n");
            resultadoUla->resultado = 0; 
            break;
    }
    resultadoUla->zero = (resultadoUla->resultado == 1) ? 1 : 0; // Sinaliza se o resultado é zero
}

static int8_t operacao_add(int8_t a, int8_t b) {
    return (a + b);
}
