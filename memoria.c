#include "memoria.h"
#include <stdbool.h>


#pragma region MEMORIA_DE_DADOS


int8_t ler_end_mem_dados(CPU *p,uint16_t addr){
    return p->memoria_de_dados[addr];
}                
void escrever_end_mem_dados(CPU *p,uint8_t addr,int8_t valor, SinaisDeControle sinais_de_controle){
    if (sinais_de_controle.escrever_memoria == 0) return;
    p->memoria_de_dados[addr] = (uint8_t) valor;
} 

#pragma endregion MEMORIA_DE_DADOS

#pragma region MEMORIA_DE_INSTRUCAO

uint16_t ler_end_mem_instrucao(CPU *p,uint16_t addr){
    return p->memoria_de_instrucao[addr];
}
void escrever_end_mem_instrucao(CPU *p,uint16_t addr,uint16_t valor){ // Não sei se terá uso.
    p->memoria_de_instrucao[addr] = valor;
}

#pragma endregion MEMORIA_DE_INSTRUCAO

#pragma region REGISTRADOR

// Permite a escrita no banco de registradores.
// Recebe o ID[0,7] e o valor [-128,127]
// Bloqueia a escrita

void escrever_registrador(CPU *p, uint8_t id,int8_t valor, SinaisDeControle sinais_de_controle){
    if (sinais_de_controle.escrever_reg == 0) return;
    // Verifica se o usuário digitou r0 
    if(id == 0){puts("mini-mips: r0 não pode ser sobrescrito!");return;}

    // if(!verifica_id_registrador(id) || !verifica_valor_signed_reg(valor)){
    //     puts("mini-mips: O id ou o valor a ser armazenado no reg é inválido.");
    //     return;
    // }

    // Caso passe pelas verificações, guarda o valor.
    p->banco_de_regs[id] = (int8_t) valor;
        printf("mini-mips: O registrador [%u] tem um novo valor: %d\n",id,valor);

}

int8_t ler_registrador(const CPU *p, uint8_t id){
    // Se for r0, retorna 0
    if(id == 0) return 0;
    return (p->banco_de_regs[id]);
}              

#pragma endregion REGISTRADOR

#pragma region FUNCOES_GENERICAS

// Nas funçoes genéricas, você deve especificar o ponteiro da CPU e o tipo de memória.
// A memória pode ser DADOS,INSTRUCAO ou REGISTRADOR

void imprimirMemoria(CPU *p, TipoMemoria tipo){
    if(tipo == DADOS){
        puts("++++++++++MEMÓRIA DE DADOS++++++++++");
        puts("++++++++++END----VALOR++++++++++");

        for(int i = 0; i < 256;i++){
            printf("%3d [%3d]",i, p->memoria_de_dados[i]);
        }
        puts("++++++++++++++++++++++++++++++++");
        return;
    }
    else if(tipo == INSTRUCAO){
        puts("++++++++++MEMÓRIA DE PROGRAMA++++++++++");
        puts("++++++++++END----VALOR++++++++++");

        for(int i = 0; i < 256;i++){
            printf("%3d [%3d]",i, p->memoria_de_instrucao[i]);
        }
        puts("++++++++++++++++++++++++++++++++");
        return;
    }
    else if(tipo == REGISTRADOR){
        puts("++++++++++BANCO DE REGS++++++++++");
        puts("++++++++++REG----VALOR++++++++++");

        for(int i = 0; i < 8;i++){
            printf("%3d [%3d]",i,p->banco_de_regs[i]);
        }
        puts("++++++++++++++++++++++++++++++++");
        return;
    }
    
    puts("mini-mips: Enum inválido para TipoMemória.");
   
}
void resetarMemoria(CPU *p, TipoMemoria tipo){
     if(tipo == DADOS){
        for(int i = 0; i < 256;i++){
            p->memoria_de_dados[i] = 0;
        }
        return;
    }
    else if(tipo == INSTRUCAO){
        for(int i = 0; i < 256;i++){
            p->memoria_de_instrucao[i] = 0;
        }
        return;
    }
    else if(tipo == REGISTRADOR){
        for(int i = 0; i < 8;i++){
            p->banco_de_regs[i] = 0;
        }
        return;
    }
}

#pragma endregion FUNCOES_GENERICAS

#pragma region FUNCOES_PRIVADAS

// Funções de validação.
// Verifica se o endereço é válido

// static bool verificar_end_valido_memoria(uint8_t end_acesso){
//    return (end_acesso < 256);
// }

// Verifica se o valor a ser guardado é maior que o registrador consegue armazenar
// Caso válido, retorna true
// Caso inválido, retorna false

// static bool verifica_valor_signed_reg(uint8_t valor){
//     return (valor >= -128 && valor <= 127);
// }
// static bool verifica_id_registrador(uint8_t id){
//     return (id <= 7);
// }
    

#pragma endregion FUNCOES_PRIVADAS