#ifndef MEMORIA_H
#define MEMORIA_H
#include "types.h"
#include <stdint.h>
#include <stdio.h>

#pragma region CONSTANTES
// Região para declaração de constantes

typedef enum{
    DADOS,
    INSTRUCAO,
    REGISTRADOR
}TipoMemoria;

#pragma endregion CONSTANTES

// Modelagem:
// Entidades necessárias: Memória de dados e memória de programa

// ENTIDADE: MEMÓRIA DE DADOS : int8_t
// A memória deve ser capaz de:
// 1) Escrever em um endereço
// 2) Ler um endereço
// 3) Procurar valor e retornar **INTEIRO COM SINAL**


#pragma region MEMORIA_DADOS

int8_t ler_end_mem_dados(CPU *p,uint16_t addr);                     // Retonar o valor daquele endereço
void escrever_end_mem_dados(CPU *p,uint16_t addr,int8_t valor);     // Escreve o valor no endereço                                                                       
                      
#pragma endregion MEMORIA_DADOS


#pragma region MEMORIA_INSTRUCAO

uint16_t ler_end_mem_instrucao(CPU *p,uint16_t addr); 
void escrever_end_mem_instrucao(CPU *p,uint16_t addr,uint16_t valor); 

#pragma endregion MEMORIA_INSTRUCAO

#pragma region REGISTRADORES

void escrever_registrador(CPU *p, uint8_t id,int8_t valor);     // Escrever em registrador
int8_t ler_registrador(CPU *p, uint8_t id);                 // Ler registrador

#pragma end region REGISTRADORES

#pragma region FUNCOES_GENERICAS

void imprimirMemoria(CPU *p, TipoMemoria tipo);     // Mostra todos os dados da memória
void resetarMemoria(CPU *p, TipoMemoria tipo);      // Reseta a memória de acordo com o seu tipo, irá zerar todos os dados.

#pragma endregion FUNCOES_GENERICAS


#endif