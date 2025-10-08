

#include <stdio.h>
#include <stdlib.h>
#include "Lista_Simples_Encadeada/lista.h"
#include "Fila_Encadeada/fila.h"
#include "TAD_functions/functions.h"
#include "TAD_IO/IO.h"

int main()
{
    LISTA *lista = lista_criar(false); // Lista não ordenada
    FILA *fila = fila_criar();
    int operacao;

    // Carregar dados do disco (persistência)
    if (!LOAD(&lista, &fila))
    {
        printf("[Aviso] Não foi possível carregar dados anteriores. Iniciando sistema limpo.\n");
    }

    printf("Serviço de Atendimento Médico\n");
    printf("-------------------------------------------------\n");

    do
    {
        imprimir_escolha_operacao();
        printf("Escolha: ");
        if (scanf("%d", &operacao) != 1)
        {
            printf("Entrada inválida.\n");
            while (getchar() != '\n')
                ; // Limpa buffer
            continue;
        }
        switch (operacao)
        {
        case 1:
            registrar_paciente(lista, fila);
            break;
        case 2:
            registrar_obito(lista, fila);
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
            printf("Digite uma operação válida.\n");
            break;
        }
    } while (operacao != 8);

    // Salvar dados antes de sair
    salvar_pacientes(lista, fila);
    lista_apagar(&lista);
    fila_apagar(&fila);
    return 0;
}