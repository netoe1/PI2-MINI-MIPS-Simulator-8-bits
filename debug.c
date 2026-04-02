#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
#include "debug.h"
#include "utils.h"

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


#pragma endregion FN_PUBLICAS

void debug(
    const InstrucaoDecodificada instrucao_decodificada, 
    const SinaisDeControle sinais_de_controle, 
    const ResultadoUla resultadoUla, 
    const CPU *cpu)
{	
    if (!debugAtivado) {
        return; // Se o debug não estiver ativado, não faz nada.
    }

	printf("PC: %u\n", cpu->pc - 1);
	printf("Instrução executada: ");
	int16_para_binario(cpu->memoria_de_instrucao[cpu->pc - 1]);
	printf("\n======= Instrução Decodificada ======= \n");
	printf("Tipo: ");
	int8_para_binario(instrucao_decodificada.tipo);
	printf(" Opcode: ");
	int8_para_binario(instrucao_decodificada.opcode);
	printf("\nRS: ");
	int8_para_binario(instrucao_decodificada.rs);

	printf(" RT: ");
	int8_para_binario(instrucao_decodificada.rt);
	printf("\nRD: ");
	int8_para_binario(instrucao_decodificada.rd);
	printf(" Funct: ");
	int8_para_binario(instrucao_decodificada.funct);
	printf("\nImediato: %d\n", instrucao_decodificada.imediato);
	printf("Endereco: %u\n", instrucao_decodificada.endereco);

	printf("======= Sinais de Controle Gerados ======= \n");
	printf("Controle ULA: %d\n", sinais_de_controle.controle_ula);
	printf("Escrever Memoria: %d\n", sinais_de_controle.escrever_memoria);
	printf("Escrever Reg: %d\n", sinais_de_controle.escrever_reg);
	printf("Memoria para Reg: %d\n", sinais_de_controle.memoria_para_reg);
	printf("ULA Fonte: %d\n", sinais_de_controle.ula_fonte);
	printf("Reg Destino: %d\n", sinais_de_controle.reg_destino);
	printf("Incremento PC: %d\n", sinais_de_controle.incremento_pc);
	printf("Jump: %d\n", sinais_de_controle.jump);
	printf("Branch: %d\n", sinais_de_controle.branch);

	printf("\n======= Resultado da Operação na Ula =======\n");
	printf("Resultado: %d\n", resultadoUla.resultado);
	printf("Zero: %u\n", resultadoUla.zero);
	
	printf("======= Banco de Registradores =======\n");
	// implementar

	//printf("======= Memória de Instruções =======\n");
	//imprimir_memoria_instrucao(cpu);
	//printf("======= Memória de Dados =======\n");
	//imprimir_memoria_dados(cpu);

	printf("PC novo: %u | ", cpu->pc);
	printf("Instrução atual: %u\n", cpu->memoria_de_instrucao[cpu->pc]);
}

void estado_atual_cpu(const CPU *cpu) {
    printf("\n------------------------------------------------------------------------\n");
    printf("\n| PC: %08u | Instrucao: %16u\n", cpu->pc, cpu->memoria_de_instrucao[cpu->pc]);
    printf("Regs:\n");
    for (int i = 0; i < 8; i++) {
        printf("[R%d] %4d", i, cpu->banco_de_regs[i]);
        if (i < 7) {
            printf(" | ");
        } else {
            printf(";"); 
        }
    }
    printf("\n------------------------------------------------------------------------\n");
}

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
