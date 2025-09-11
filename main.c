#include <stdio.h>
#include <stdlib.h>
#include "TAD_Paciente/paciente.h"
#include "Pilha_Encadeada/pilha.h"
#include "Fila_Encadeada/fila.h"

// Variáveis globais utilizadas para gerenciar as principais estruturas do sistema hospitalar.
// A fila representa os pacientes aguardando atendimento, enquanto a pilha armazena o histórico de atendimentos.
FILA *fila_global = NULL;
PILHA *historico_global = NULL;
// LISTA *lista_global = NULL; // Estrutura para cadastro geral de pacientes, se implementada.


// Função responsável por carregar os dados dos pacientes do disco, caso haja persistência implementada.
// Atualmente, apenas exibe uma mensagem de depuração.
void carregar_pacientes(void) {
    // Exemplo: inicializar lista de pacientes
    // lista_global = lista_criar();
    // Carregar pacientes de arquivo se necessário
    printf("[DEBUG] Carregar pacientes do disco (não implementado)\n");
}

// Função que exibe o menu principal de operações disponíveis ao usuário.
void imprimir_escolha_operacao(void) {
    printf("Operação desejada:\n");
    printf("1 - Registrar paciente.\n");
    printf("2 - Dar alta ao paciente.\n");
    printf("3 - Adicionar procedimento ao histórico médico.\n");
    printf("4 - Desfazer procedimento do histórico médico.\n");
    printf("5 - Chamar paciente para atendimento.\n");
    printf("6 - Mostrar fila de espera.\n");
    printf("7 - Mostrar histórico do paciente.\n");
    printf("8 - Sair.\n");
    return;
}

// Função responsável pelo cadastro de um novo paciente.
// Solicita ao usuário o ID e o nome, cria a estrutura e registra os dados.
void registrar_paciente(void) {
    int id;
    char nome[100];
    printf("Digite o ID do paciente: ");
    scanf("%d", &id);
    printf("Digite o nome do paciente: ");
    scanf("%s", nome);
    PACIENTE *paciente = paciente_criar(id);
    if (paciente != NULL) {
        paciente_set_id(paciente, id);
        paciente_set_nome(paciente, nome);
        printf("Paciente registrado com sucesso!\n");
        // Adicionar paciente à lista_global se existir
    } else {
        printf("Erro ao registrar paciente.\n");
    }
}

// Função que realiza a alta do paciente, removendo-o da fila de espera e registrando no histórico.
void alta_paciente(void) {
    PACIENTE *paciente = fila_remover_paciente(fila_global);
    if (paciente != NULL) {
        pilha_empilhar(historico_global, paciente);
        printf("Paciente %d recebeu alta e foi movido para o histórico.\n", paciente_get_id(paciente));
    } else {
        printf("Nenhum paciente na fila para dar alta.\n");
    }
}

// Função que desfaz o último procedimento realizado, removendo o paciente do topo da pilha de histórico.
void desfazer_procedimento(void) {
    PACIENTE *paciente = pilha_desempilhar(historico_global);
    if (paciente != NULL) {
        printf("Procedimento desfeito para paciente %d.\n", paciente_get_id(paciente));
    } else {
        printf("Histórico vazio, nada a desfazer.\n");
    }
}

// Função para adicionar um procedimento ao histórico médico de um paciente específico.
// A busca e manipulação do histórico depende da implementação da lista de pacientes.
void adicionar_procedimeto(int id_paciente, char procedimento[]) {
    // PACIENTE *paciente = lista_buscarID(lista_global, id_paciente);
    // pilha_empilhar(paciente->historico, procedimento);
    printf("[DEBUG] Adicionar procedimento '%s' ao paciente %d (não implementado)\n", procedimento, id_paciente);
}

// Função que exibe o paciente na frente da fila, simulando a chamada para atendimento.
void chamar_paciente(void) {
    PACIENTE *paciente = fila_frente(fila_global);
    if (paciente != NULL) {
        printf("Chamando paciente %d para atendimento.\n", paciente_get_id(paciente));
    } else {
        printf("Nenhum paciente na fila de espera.\n");
    }
}

// Função que imprime todos os pacientes atualmente na fila de espera.
void mostrar_fila(void) {
    printf("Fila de espera:\n");
    fila_imprimir(fila_global);
}

// Função que imprime o histórico de atendimentos, exibindo todos os pacientes registrados na pilha.
void mostrar_historico(void) {
    printf("Histórico de atendimentos:\n");
    pilha_imprimir(historico_global);
}

// Função responsável por salvar os dados dos pacientes em disco, caso haja persistência implementada.
void salvar_pacientes(void) {
    printf("[DEBUG] Salvar pacientes no disco (não implementado)\n");
}

/*
 * Função principal do sistema hospitalar.
 * Inicializa as estruturas, exibe o menu e executa as operações conforme escolha do usuário.
 * Ao final, libera toda a memória alocada.
 */
int main() {
    fila_global = fila_criar();
    historico_global = pilha_criar();
    int operacao;

    carregar_pacientes();

    printf("Serviço de Atendimento Médico\n");
    printf("-------------------------------------------------\n");

    do {
        imprimir_escolha_operacao();
        scanf("%d", &operacao);
        switch(operacao) {
            case 1:
                registrar_paciente();
                break;
            case 2:
                alta_paciente();
                break;
            case 3: {
                int id;
                char procedimento[100];
                printf("Digite o ID do paciente: ");
                scanf("%d", &id);
                printf("Digite o procedimento: ");
                scanf("%s", procedimento);
                adicionar_procedimeto(id, procedimento);
                break;
            }
            case 4:
                desfazer_procedimento();
                break;
            case 5:
                chamar_paciente();
                break;
            case 6:
                mostrar_fila();
                break;
            case 7:
                mostrar_historico();
                break;
            case 8:
                printf("Encerrando serviço de atendimento médico.\n");
                break;
            default:
                printf("Digite uma operação válida:\n");
                break;
        }
    } while(operacao != 8);

    salvar_pacientes();
    fila_apagar(&fila_global);
    pilha_apagar(&historico_global);
    return 0;
}