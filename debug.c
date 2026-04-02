#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
#include "debug.h"

// Variável de controle do debug, por padrão, é false.
static unsigned int debugAtivado = false;

#pragma region FN_PUBLICAS

// Função para iniciar o log. Caso seja falsa, nenhum debug é escrito.

void set_debug(bool estado){
    if(estado){
        debugAtivado = estado;
        return;
    }

    debugAtivado = false;   
}

void print_int16_binario(int16_t valor) {
    char binario[17];
    for (int posicao_bit = 15; posicao_bit >= 0; posicao_bit--) {
        binario[15 - posicao_bit] = (valor & (1 << posicao_bit)) ? '1' : '0';
    }
    binario[16] = '\0';
    printf("%s", binario);
}

void print_int8_binario(int8_t valor) {
	char binario[9];
	for (int posicao_bit = 7; posicao_bit >= 0; posicao_bit--) {
		binario[7 - posicao_bit] = (valor & (1 << posicao_bit)) ? '1' : '0';
	}
	
	binario[8] = '\0';
	printf("%s", binario);
}

#pragma endregion FN_PUBLICAS


#pragma region FN_PRIVADAS

// Função de log interna para o macro, ela é privada. Você pode ignorar
static void _log_internal(const char *prefix, const char *str) {
    if(debugAtivado){
        if (prefix && str) {
            printf("%s:%s\n", prefix, str);
        }   
    }
}

#pragma endregion FN_PRIVADAS
