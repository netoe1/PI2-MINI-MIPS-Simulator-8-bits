#include "ula.h"
#include <stdio.h>

#pragma region PROTOTIPO_FN_PRIVADAS

static int8_t operacao_add(int8_t a, int8_t b);
static int8_t operacao_cmp(int8_t a, int8_t b);
static int8_t operacao_and(int8_t a, int8_t b);
static int8_t operacao_or(int8_t a, int8_t b);
static void executar_operacoes(int8_t operador, int8_t operador2, uint8_t controleUla, ResultadoUla *resultadoUla);

#pragma endregion PROTOTIPO_FN_PRIVADAS

#pragma region FUNCOES_PUB



ResultadoUla executar(int8_t operador, int8_t operador2, uint8_t controleUla)
{
    ResultadoUla resultadoUla;
    executar_operacoes(operador, operador2, controleUla, &resultadoUla);
    return resultadoUla;
}

#pragma endregion FUNCOES_PUB

#pragma region IMPL_FN_PRIVADAS
static void executar_operacoes(int8_t operador, int8_t operador2, uint8_t controleUla, ResultadoUla *resultadoUla)
{
    switch (controleUla)
    {
    case OP_ADD:
    case OP_ADDI:
    case OP_LW:
    case OP_SW: resultadoUla->resultado = operacao_add(operador, operador2); resultadoUla->zero = 0; break;
    case OP_OR: resultadoUla->resultado = operacao_or(operador,operador2);   resultadoUla->zero = 0; break;
    case OP_AND:
        break;
    case OP_BEQ:
        resultadoUla->resultado = operacao_cmp(operador, operador2);
        resultadoUla->zero = (resultadoUla->resultado == 1) ? 1 : 0;
        break;
    default:
        // Operação desconhecida ou ainda não implementada, definir resultado como zero ou algum valor padrão
        printf("Operação da ULA ainda não implementada. \n");
        resultadoUla->resultado = 0;
        break;
    }
}

static int8_t operacao_add(int8_t a, int8_t b)
{
    return (a + b);
}

static int8_t operacao_cmp(int8_t a, int8_t b) {
    return (a == b) ? 1 : 0;
}

static int8_t operacao_and(int8_t a, int8_t b) {
    return (int8_t)((uint8_t)a & (uint8_t)b);
}

static int8_t operacao_or(int8_t a, int8_t b) {
    return (int8_t)((uint8_t)a | (uint8_t)b);
}

#pragma endregion IMPL_FN_PRIVADAS