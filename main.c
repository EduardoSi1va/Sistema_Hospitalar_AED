
#include <stdio.h>
#include <stdlib.h>
#include "Lista_Simples_Encadeada/lista.h"
#include "Fila_Encadeada/fila.h"
#include "TAD_functions/functions.h"

// Função que exibe o menu principal de operações disponíveis ao usuário.
void imprimir_escolha_operacao(void)
{
    printf("Operação desejada:\n");
    printf("1 - Registrar paciente.\n");
    printf("2 - Dar alta ao paciente.\n");
    printf("3 - Adicionar procedimento ao histórico médico.\n");
    printf("4 - Desfazer procedimento do histórico médico.\n");
    printf("5 - Chamar paciente para atendimento.\n");
    printf("6 - Mostrar fila de espera.\n");
    printf("7 - Mostrar histórico do paciente.\n");
    printf("8 - Sair.\n");
}

int main()
{
    LISTA *lista = lista_criar(false);
    FILA *fila = fila_criar();
    int operacao;

    // Carregar dados do disco
    LOAD(&lista, &fila);

    printf("Serviço de Atendimento Médico\n");
    printf("-------------------------------------------------\n");

    do
    {
        imprimir_escolha_operacao();
        scanf("%d", &operacao);
        switch (operacao)
        {
        case 1:
            registrar_paciente(lista, fila);
            break;
        case 2:
            alta_paciente(fila);
            break;
        case 3:
            adicionar_procedimento(lista);
            break;
        case 4:
            desfazer_procedimento(lista);
            break;
        case 5:
            chamar_paciente(fila);
            break;
        case 6:
            mostrar_fila(fila);
            break;
        case 7:
            mostrar_historico(lista);
            break;
        case 8:
            printf("Encerrando serviço de atendimento médico.\n");
            break;
        default:
            printf("Digite uma operação válida:\n");
            break;
        }
    } while (operacao != 8);

    salvar_pacientes(lista, fila);
    lista_apagar(&lista);
    fila_apagar(&fila);
    return 0;
}