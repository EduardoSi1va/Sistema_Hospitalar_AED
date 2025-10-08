

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
        printf("\n");
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
            lista_imprimir(lista);
            break;
        case 9:
            printf("Encerrando serviço de atendimento médico.\n");
            break;
        case 471728:
            //Limpeza dos arquivos .bin para resetar o sistema.            
            lista_esvaziar(lista);
            fila_esvaziar(fila);
            
            salvar_pacientes(lista, fila);
            
            printf("Base de Dados Apagada - Sistema Resetado\n");
            printf("Estado vazio salvo com sucesso.\n\n");
            break;
        default:
            printf("Digite uma operação válida.\n");
            break;
        }
    } while (operacao != 9);

    // Salvar dados antes de sair
    salvar_pacientes(lista, fila);
    
    // Limpeza segura com verificação de erros
    if (lista != NULL) {
        lista_apagar(&lista);
    }
    if (fila != NULL) {
        fila_apagar(&fila);
    }
    
    return 0;
}