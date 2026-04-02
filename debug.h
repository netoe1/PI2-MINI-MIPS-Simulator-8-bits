#ifndef DEBUG_H
#define DEBUG_H
#include "cpu.h"

#define PREFIX "mini-mips"
#define PREFIX_ERRO "mini-mips-err"
#define PREFIX_INFO "mini-mips-info"
#define PREFIX_WARNING "mini-mips-warn"

#define print_info(str)  _log_internal(PREFIX_INFO, str)        // Usar para dar print em uma informação
#define print_err(str)   _log_internal(PREFIX_ERRO, str)        // usar para dar print em algum erro.
#define print_warn(str)  _log_internal(PREFIX_WARNING, str)     // Usar para dar print em warning.

// Função que verifica se o debug irá funcionar ou não.
void set_debug(bool ativar);

// Debug antigo para mostrar para teste
void debug_legacy(
    const InstrucaoDecodificada instrucao_decodificada,
    const SinaisDeControle sinais_de_controle,
    const ResultadoUla resultadoUla, const CPU *cpu);

// Funcões de print de inteiros <stdint.h> para binário.
void print_int16_binario(int16_t valor);
void print_int8_binario(int8_t valor);

#endif