#include <stdio.h>
#include <stdlib.h>

#include "memoria.h"
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

void print_int8_hexa(int8_t valor) {
    printf("0x%02X", (uint8_t)valor);
}

void print_int16_hexa(int16_t valor) {
    printf("0x%04X", (uint16_t)valor);
}

static void debug_legacy(const InstrucaoDecodificada instrucao_decodificada, const SinaisDeControle sinais_de_controle, const ResultadoUla resultadoUla, const CPU *cpu)
{	
	printf("PC: %u\n", cpu->pc - 1);
	printf("Instrução executada: ");
	print_int16_para_binario(cpu->memoria_de_instrucao[cpu->pc - 1]);
	printf("\n======= Instrução Decodificada ======= \n");
	printf("Tipo: ");
	print_int8_para_binario(instrucao_decodificada.tipo);
	printf(" Opcode: ");
	print_int8_para_binario(instrucao_decodificada.opcode);
	printf("\n RS: ");
	print_int8_para_binario(instrucao_decodificada.rs);

	printf(" RT: ");
	print_int8_para_binario(instrucao_decodificada.rt);
	printf("\n RD: ");
	print_int8_para_binario(instrucao_decodificada.rd);
	printf(" Funct: ");
	print_int8_para_binario(instrucao_decodificada.funct);
	printf("\nImediato: %d\n", instrucao_decodificada.imediato);
	printf("Endereco: %u\n", instrucao_decodificada.endereco);

	printf("======= Sinais de Controle Gerados ======= \n");
	printf("Controle ULA: ");
	print_int8_para_binario(sinais_de_controle.controle_ula);
	printf("\nEscrever Memoria: ");
	print_int8_para_binario(sinais_de_controle.escrever_memoria);
	printf("\nEscrever Reg: ");
	print_int8_para_binario(sinais_de_controle.escrever_reg);
	printf("\nMemoria para Reg: ");
	print_int8_para_binario(sinais_de_controle.memoria_para_reg);
	printf("\nULA Fonte: ");
	print_int8_para_binario(sinais_de_controle.ula_fonte);
	printf("\nReg Destino: ");
	print_int8_para_binario(sinais_de_controle.reg_destino);
	printf("\nIncremento PC: ");
	print_int8_para_binario(sinais_de_controle.incremento_pc);
	printf("\nJump:");
	print_int8_para_binario(sinais_de_controle.jump);
	printf("\nBranch:");
	print_int8_para_binario(sinais_de_controle.branch);

	printf("\n======= Resultado da Operação na Ula =======\n");
	printf("Resultado: %d\n", resultadoUla.resultado);
	printf("Zero: %u\n", resultadoUla.zero);
	
	printf("======= Banco de Registradores =======\n");
    imprimirMemoria(cpu,REGISTRADOR,DECIMAL);
	printf("======= Memória de Instruções =======\n");
	imprimirMemoria(cpu,INSTRUCAO,HEXADECIMAL);
	printf("======= Memória de Dados =======\n");
	imprimirMemoria(cpu,DADOS,HEXADECIMAL);

	printf("PC novo: %u | ", cpu->pc);
	printf("Instrução atual: %u\n", cpu->memoria_de_instrucao[cpu->pc]);

}

void debug_geral(const InstrucaoDecodificada inst,
    const SinaisDeControle sinais,
    const ResultadoUla ula,
    const CPU *cpu,
    int opcao)// opcao: 0 = Decimal, 1 = Hexa, 2 = Binario
     {

    if(!debugAtivado){
        return;
    }
    
    printf("\n=== ESTADO COMPLETO DA CPU ===\n");
    
    // 1. PC e Instrução (16 bits)
    printf("PC: "); 
    if(opcao == 1) print_int16_hexa(cpu->pc - 1); 
    else if(opcao == 2) print_int16_binario(cpu->pc - 1);
    else printf("%d", cpu->pc - 1);

    printf(" | Instrucao: ");
    if(opcao == 1) print_int16_hexa(cpu->memoria_de_instrucao[cpu->pc - 1]);
    else if(opcao == 2) print_int16_binario(cpu->memoria_de_instrucao[cpu->pc - 1]);
    else printf("%d", cpu->memoria_de_instrucao[cpu->pc - 1]);

    // 2. Campos Decodificados (8 bits)
    printf("\nOpcode: "); opcao == 1 ? print_int8_hexa(inst.opcode) : (opcao == 2 ? print_int8_binario(inst.opcode) : printf("%d", inst.opcode));
    printf(" | RS: ");     opcao == 1 ? print_int8_hexa(inst.rs)     : (opcao == 2 ? print_int8_binario(inst.rs)     : printf("%d", inst.rs));
    printf(" | RT: ");     opcao == 1 ? print_int8_hexa(inst.rt)     : (opcao == 2 ? print_int8_binario(inst.rt)     : printf("%d", inst.rt));
    printf(" | RD: ");     opcao == 1 ? print_int8_hexa(inst.rd)     : (opcao == 2 ? print_int8_binario(inst.rd)     : printf("%d", inst.rd));
    printf("\nImediato: %d | Endereco: %u", inst.imediato, inst.endereco);

    // 3. Sinais de Controle (Sempre Binário como no Logisim)
    printf("\n\n--- Sinais de Controle ---");
    printf("\nULA Ctrl: "); print_int8_binario(sinais.controle_ula);
    printf(" | EscMem: %d | EscReg: %d | Jump: %d | Branch: %d", 
            sinais.escrever_memoria, sinais.escrever_reg, sinais.jump, sinais.branch);

    // 4. ULA
    printf("\n\n--- ULA ---");
    printf("\nResultado: ");
    if(opcao == 1) print_int16_hexa(ula.resultado);
    else if(opcao == 2) print_int16_binario(ula.resultado);
    else printf("%d", ula.resultado);
    printf(" | Zero: %u", ula.zero);

    // 5. Memórias e Registradores (Reutilizando sua função)
    imprimirMemoria((CPU*)cpu, REGISTRADOR, opcao);
    imprimirMemoria((CPU*)cpu, DADOS, opcao);
    
    printf("\n==============================\n");
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

static void debug_decimal(const InstrucaoDecodificada inst,
    const SinaisDeControle sinais,
    const ResultadoUla ula,
    const CPU *cpu) {

    printf("\n--- DEBUG COMPLETO (DECIMAL) ---\n");
    printf("PC: %d | Instrução: %d\n", cpu->pc - 1, cpu->memoria_de_instrucao[cpu->pc - 1]);
    
    printf("--- Campos da Instrução ---\n");
    printf("Tipo: %d | Opcode: %d | RS: %d | RT: %d | RD: %d | Funct: %d\n", 
            inst.tipo, inst.opcode, inst.rs, inst.rt, inst.rd, inst.funct);
    printf("Imediato: %d | Endereço: %u\n", inst.imediato, inst.endereco);

    printf("--- Sinais de Controle ---\n");
    printf("ULA_Ctrl: %d | MemWrite: %d | RegWrite: %d | MemToReg: %d | ALUSrc: %d\n",
            sinais.controle_ula, sinais.escrever_memoria, sinais.escrever_reg, sinais.memoria_para_reg, sinais.ula_fonte);
    printf("RegDest: %d | Jump: %d | Branch: %d\n", sinais.reg_destino, sinais.jump, sinais.branch);

    printf("--- ULA & Memória ---\n");
    printf("Resultado ULA: %d | Flag Zero: %u\n", ula.resultado, ula.zero);
    printf("PC Novo: %d\n", cpu->pc);
}

static void debug_binario(const InstrucaoDecodificada inst,
    const SinaisDeControle sinais,
    const ResultadoUla ula,
    const CPU *cpu) {

    printf("\n--- DEBUG COMPLETO (BINÁRIO) ---\n");
    printf("PC: "); print_int16_binario(cpu->pc - 1); 
    printf(" | Instrução: "); print_int16_binario(cpu->memoria_de_instrucao[cpu->pc - 1]);
    
    printf("\n--- Campos da Instrução ---\n");
    printf("Opcode: "); print_int8_binario(inst.opcode);
    printf(" | RS: ");  print_int8_binario(inst.rs);
    printf(" | RT: ");  print_int8_binario(inst.rt);
    printf(" | RD: ");  print_int8_binario(inst.rd);
    printf("\nFunct:  "); print_int8_binario(inst.funct);
    printf(" | Immed: "); print_int16_binario(inst.imediato);

    printf("\n--- Sinais de Controle ---\n");
    printf("ULA_Ctrl: "); print_int8_binario(sinais.controle_ula);
    printf(" | MemW: %d | RegW: %d | M2R: %d | Src: %d | J: %d | B: %d\n",
            sinais.escrever_memoria, sinais.escrever_reg, sinais.memoria_para_reg, 
            sinais.ula_fonte, sinais.jump, sinais.branch);

    printf("--- ULA & Memória ---\n");
    printf("Resultado: "); print_int16_binario(ula.resultado);
    printf(" | Zero: %u\n", ula.zero);
}

static void debug_hexa(const InstrucaoDecodificada inst,
    const SinaisDeControle sinais,
    const ResultadoUla ula,
    const CPU *cpu) {
    printf("\n--- DEBUG COMPLETO (HEXADECIMAL) ---\n");
    printf("PC: "); print_int16_hexa(cpu->pc - 1);
    printf(" | Instrução: "); print_int16_hexa(cpu->memoria_de_instrucao[cpu->pc - 1]);

    printf("\n--- Campos da Instrução ---\n");
    printf("Opcode: "); print_int8_hexa(inst.opcode);
    printf(" | RS: ");  print_int8_hexa(inst.rs);
    printf(" | RT: ");  print_int8_hexa(inst.rt);
    printf(" | RD: ");  print_int8_hexa(inst.rd);
    printf("\nImediato: "); print_int16_hexa(inst.imediato);
    printf(" | Endereço: "); print_int16_hexa(inst.endereco);

    printf("\n--- Sinais de Controle ---\n");
    printf("ULA_Ctrl: "); print_int8_hexa(sinais.controle_ula);
    printf(" | Sinais (W/R/J/B): %X%X%X%X", 
            sinais.escrever_memoria, sinais.escrever_reg, sinais.jump, sinais.branch);

    printf("\n--- ULA & Memória ---\n");
    printf("Resultado ULA: "); print_int16_hexa(ula.resultado);
    printf(" | Zero: %u\n", ula.zero);
    
    printf("--- Memórias ---\n");
    imprimirMemoria(cpu, DADOS,HEXADECIMAL); 
    imprimirMemoria(cpu,INSTRUCAO,HEXADECIMAL);

}

#pragma endregion FN_PRIVADAS
