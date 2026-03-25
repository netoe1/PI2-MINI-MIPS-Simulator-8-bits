#include <stdio.h>
#include <stdlib.h>
#include <locale.h>

#pragma region MACROS

// netoe1: Definição de macro para limpar tela.
#if _WIN32
#define limparTela() system("cls")
#elif __linux__
#define limparTela() system("clear")
#endif

#define esperar()                                         \
    printf("mini-mips: Aperte ENTER para continuar..\n"); \
    setbuf(stdin, NULL);                                  \
    getchar();

#pragma endregion MACROS

#pragma region CONSTANTES

#define LIM_MIN_OPC 0  // Limite mínimo das opções
#define LIM_MAX_OPC 10 // Limite máximo das opções.

// netoe1: Mensagem para dar print no menu, colocada em uma constante

char *MENU_BUF =
    "====================MENU-PRINCIPAL: MINI-MIPS-8BITS====================\n"
    "1.  Carregar memória de instruções (.mem) \n"
    "2.  Carregar memória de Dados (.dat) \n"
    "3.  Imprimir memórias (instruções e dados) \n"
    "4.  Imprimir banco de registradores \n"
    "5.  Imprimir todo o simulador (registradores e memórias) \n"
    "6.  Salvar .asm \n"
    "7.  Salvar .dat \n"
    "8.  Executa Programa (run) \n"
    "9.  Executa uma instrução (Step) \n"
    "10. Volta uma instrução (Back) \n"
    "0.  Encerrar \n"
    "========================================================================";

// netoe1: Enum para organizar as opções do menu.
// Usando typedef para não precisar digitar enum toda a hora.
typedef enum
{
    FECHAR = 0,
    CARREGAR_MEMORIA_INSTRUCOES,
    CARREGAR_MEMORIA_DADOS,
    IMPRIMIR_MEMORIAS,
    IMPRIMIR_BANCO_REG,
    IMPRIMIR_TODO_SIMULADOR,
    SALVAR_ASM,
    SALVAR_DAT,
    EXECUTAR_PROGRAMA,
    EXECUTA_INSTRUCAO,
    VOLTAR_INSTRUCAO

} EOpcoes;

#pragma endregion CONSTANTES

#pragma region VARIAVEIS_GLOBAIS

int opc = -1; // netoe1: variável de opção do menu principal

#pragma endregion VARIAVEIS_GLOBAIS

#pragma region PROTOTIPO_FUNCOES

void carregar_menu_principal();                 // Função que executa o menu principal, com os loops e selecionando as opções.
void receber_opcao_sanitizada(const char *msg); // Recebe a opção do usuário e sanitiza para que não haja erros. Armazena na variavel opc

#pragma endregion PROTOTIPO_FUNCOES

int main(void)
{
    setlocale(LC_ALL, ""); // netoe1: Suporte a acentos
    carregar_menu_principal();
    return EXIT_SUCCESS; // EXIT_SUCCESS é um label definido para 0.
}

#pragma region IMPLEMENTACAO_FUNCOES

void carregar_menu_principal()
{
    //==========Receber o valor digitado pelo usuário:==========
    // Cria o loop e verifica se a opção é válida
    // Opc é uma variável global declarada nos blocos de constantes.
    // Executa um loop e usa um switch para verificar as opções.
    // OBS: opc tem o valor = -1 para entrar no loop

    while (opc != FECHAR)
    {
        limparTela();
        // netoe1: Dá o print da constate criada na REGION
        puts(MENU_BUF);
        receber_opcao_sanitizada("Selecione uma das opções:");
        switch (opc)
        {

        case CARREGAR_MEMORIA_INSTRUCOES:
            puts("opc = CARREGAR_MEMORIA_INSTRUCOES");

            break;
        case CARREGAR_MEMORIA_DADOS:
            puts("opc = CARREGAR_MEMORIA_DADOS");

            break;
        case IMPRIMIR_MEMORIAS:
            puts("opc = IMPRIMIR_MEMORIAS");

            break;
        case IMPRIMIR_BANCO_REG:
            puts("opc = IMPRIMIR_BANCO_REG");

            break;
        case IMPRIMIR_TODO_SIMULADOR:
            puts("opc = IMPRIMIR_TODO_SIMULADOR");

            break;
        case SALVAR_ASM:
            puts("opc = SALVAR_ASM");

            break;
        case SALVAR_DAT:
            puts("opc = SALVAR_DAT");

            break;
        case EXECUTAR_PROGRAMA:
            puts("opc = EXECUTAR_PROGRAMA");

            break;
        case EXECUTA_INSTRUCAO:
            puts("opc = EXECUTA_INSTRUCAO");

            break;
        case VOLTAR_INSTRUCAO:
            puts("opc = VOLTAR_INSTRUCAO");

            break;
        case FECHAR:
            puts("mini-mips-info: Encerrando programa!");
            break;
        default:
            puts("mini-mips-err: opção inválida não reconhecida.");
           
            break;
            
        }
        esperar(); // Usa o macro de esperar
    }
}

void receber_opcao_sanitizada(const char *msg)
{
    // Função feita com o GEMINI.
    int resultado;

    while (1)
    { // Loop infinito que só quebra (break) quando o dado for válido
        printf("%s", msg);

        resultado = scanf("%d", &opc); // Lendo direto na global 'opc'

        if (resultado == 1)
        {
            // Sucesso! Leu um número.
            // Agora limpamos o '\n' (Enter) que sobrou no buffer.
            while (getchar() != '\n')
                ;
            break;
        }
        else
        {
            // Erro! O usuário digitou uma letra ou símbolo.
            puts("mini-mips-err: O menu aceita apenas números.");

            // LIMPEZA DO BUFFER: remove as letras que travaram o scanf
            while (getchar() != '\n')
                ;
        }
    }
}

#pragma endregion IMPLEMENTACAO_FUNCOES