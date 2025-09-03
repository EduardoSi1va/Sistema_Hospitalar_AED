#include <stdio.h>
#include <stdlib.h>
#include "TAD_Paciente/paciente.h"
#include "Pilha_Encadeada/pilha.h"
#include "Fila_Encadeada/fila.h"

void carregar_pacientes(void);

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

void registrar_paciente(void);

void alta_paciente(void);

void adicionar_procedimeto(void);

void desfazer_procedimento(void);

void chamar_paciente(void);

void mostrar_fila(void);

void mostrar_historico(void);

void salvar_pacientes(void);

int main() {
    carregar_pacientes();

    printf("Serviço de Atendimento Médico\n");
    printf("-------------------------------------------------\n");
 
    imprimir_escolha_operacao();

    int operacao;
    scanf("%d", &operacao);

    while(operacao != 8) {
        switch(operacao) {
            case 1:
                registrar_paciente();
                break;
            case 2:
                alta_paciente();
                break;
            case 3:
                adicionar_procedimeto();
                break;
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
            default:
                printf("Operação Inexistente.\n");
                break;
        }
        scanf("%d", &operacao);
    } 

    printf("Encerrando serviço de atendimento médico.\n");

    //chamar função que realiza armazenamento dos pacientes em disco
    salvar_pacientes();

    return 0;
}