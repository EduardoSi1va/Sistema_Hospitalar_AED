#include <stdio.h>
#include <stdlib.h>
#include "functions.h"
#include "../TAD_Paciente/paciente.h"
#include "../Pilha_Encadeada/pilha.h"
#include "../Fila_Encadeada/fila.h"
#include "../TAD_IO/IO.h"

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
    return;
}

// Função responsável pelo cadastro de um novo paciente.
// Solicita ao usuário o ID e o nome, cria a estrutura e registra os dados na lista e na fila recebidas por parâmetro.
void registrar_paciente(LISTA *lista, FILA *fila)
{
    if(fila_cheia(fila)) {
        printf("Não é possível registrar paciente pois a fila de espera está cheia.\n");
        return;
    }
    int id;
    char nome[100];
    printf("Digite o ID do paciente: ");
    scanf("%d", &id);
    printf("Digite o nome do paciente: ");
    scanf("%s", nome);
    if (lista_busca(lista, id) != NULL)
    {
        printf("Já existe paciente com esse ID!\n");
        return;
    }
    PACIENTE *paciente = paciente_criar(id, nome);
    if (paciente != NULL)
    {
        lista_inserir(lista, paciente);
        fila_inserir_paciente(fila, paciente);
        printf("Paciente registrado com sucesso!\n");
    }
    else
    {
        printf("Erro ao registrar paciente.\n");
    }
}

// Função que realiza a alta do paciente, removendo-o da fila de espera.
void alta_paciente(FILA *fila)
{
    PACIENTE *paciente = fila_remover_paciente(fila);
    if (paciente != NULL)
    {
        printf("Paciente %d recebeu alta.\n", paciente_get_id(paciente));
    }
    else
    {
        printf("Nenhum paciente na fila para dar alta.\n");
    }
}

// Função que desfaz o último procedimento realizado do histórico do paciente informado.
void desfazer_procedimento(LISTA *lista)
{
    int id;
    char procedimento[100];
    printf("Digite o ID do paciente: ");
    scanf("%d", &id);
    PACIENTE *paciente = lista_busca(lista, id);
    if (paciente == NULL)
    {
        printf("Paciente não encontrado!\n");
        return;
    }
    if (pilha_desempilhar(paciente_get_historico(paciente), procedimento))
    {
        printf("Procedimento '%s' desfeito para paciente %d.\n", procedimento, id);
    }
    else
    {
        printf("Histórico vazio, nada a desfazer.\n");
    }
}

// Função para adicionar um procedimento ao histórico médico de um paciente específico, identificado na lista.
void adicionar_procedimento(LISTA *lista)
{
    int id;
    char procedimento[100];
    printf("Digite o ID do paciente: ");
    scanf("%d", &id);
    printf("Digite o procedimento: ");
    scanf("%s", procedimento);
    PACIENTE *paciente = lista_busca(lista, id);
    if(pilha_cheia(paciente_get_historico(paciente))) {
        printf("Não é possível adicionar procedimento ao histórico do paciente %d pois este já atingiu a quantidade máxima de procedimentos.\n", id);
        return;
    }
    if (paciente == NULL)
    {
        printf("Paciente não encontrado!\n");
        return;
    }
    pilha_empilhar(paciente_get_historico(paciente), procedimento);
    printf("Procedimento '%s' adicionado ao histórico do paciente %d.\n", procedimento, id);
}

// Função que exibe o paciente na frente da fila recebida, simulando a chamada para atendimento.
void chamar_paciente(FILA *fila)
{
    PACIENTE *paciente = fila_frente(fila);
    if (paciente != NULL)
    {
        printf("Chamando paciente %d para atendimento.\n", paciente_get_id(paciente));
    }
    else
    {
        printf("Nenhum paciente na fila de espera.\n");
    }
}

// Função que imprime todos os pacientes atualmente na fila recebida.
void mostrar_fila(FILA *fila)
{
    printf("Fila de espera:\n");
    fila_imprimir(fila);
}

// Função que imprime o histórico de procedimentos do paciente informado (busca na lista).
void mostrar_historico(LISTA *lista)
{
    int id;
    printf("Digite o ID do paciente: ");
    scanf("%d", &id);
    PACIENTE *paciente = lista_busca(lista, id);
    if (paciente == NULL)
    {
        printf("Paciente não encontrado!\n");
        return;
    }
    printf("Histórico do paciente %d:\n", id);
    pilha_imprimir(paciente_get_historico(paciente));
}

// Função responsável por salvar os dados dos pacientes em disco, caso haja persistência implementada, usando lista e fila recebidas por parâmetro.
void salvar_pacientes(LISTA *lista, FILA *fila)
{
    // Chama função de persistência se implementada
    if (SAVE(lista, fila))
        printf("Dados salvos com sucesso!\n");
    else
        printf("Erro ao salvar dados!\n");
}

