# ifndef UTILS_H
# define UTILS_H

#include <stdio.h>
#include <stdlib.h>
#include <stdint.h>
# include "types.h"

int8_t extender_sinal(uint16_t instrucao);
void int8_para_binario(int8_t valor);
void int16_para_binario(int16_t valor);
int8_t binario_para_int8(const char *binario);
uint8_t binario_para_int8_sem_sinal(const char *binario);
int16_t binario_para_int16(const char *binario);
uint16_t binario_para_int16_sem_sinal(const char *binario);

# endif
