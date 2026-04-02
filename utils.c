
#include "utils.h"

int8_t extender_sinal(uint16_t instrucao) {
    uint8_t imm6 = (uint8_t)(instrucao & 0x3F); // extrai 6 bits

    // verifica se o 6º (5) bit (bit de sinal, máscara 0x20 que é 0010 0000) é 1
    if (imm6 & 0x20) {
        // Se for 1, precisamos preencher os bits 6 e 7 com '1'
        // 0xC0 em binário é 1100 0000. 
        // Usamos o operador OR para "forçar" esses bits para 1.
        return (int8_t)(imm6 | 0xC0); 
    }
    return (int8_t)imm6;
}

void int16_para_binario(int16_t valor) {
    char binario[17];
    for (int posicao_bit = 15; posicao_bit >= 0; posicao_bit--) {
        binario[15 - posicao_bit] = (valor & (1 << posicao_bit)) ? '1' : '0';
    }
    binario[16] = '\0';
    printf("%s", binario);
}

void int8_para_binario(int8_t valor) {
	char binario[9];
	for (int posicao_bit = 7; posicao_bit >= 0; posicao_bit--) {
		binario[7 - posicao_bit] = (valor & (1 << posicao_bit)) ? '1' : '0';
	}
	
	binario[8] = '\0';
	printf("%s", binario);
}

int8_t binario_para_int8(const char *binario) {
    return (int8_t)strtoul(binario, NULL, 2);
}

uint8_t binario_para_int8_sem_sinal(const char *binario) {
    return (uint8_t)strtoul(binario, NULL, 2);
}

int16_t binario_para_int16(const char *binario) {
    return (int16_t)strtoul(binario, NULL, 2);
}

uint16_t binario_para_int16_sem_sinal(const char *binario) {
    return (uint16_t)strtoul(binario, NULL, 2);
}
