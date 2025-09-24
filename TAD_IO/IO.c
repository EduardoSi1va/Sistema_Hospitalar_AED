#include "IO.h"
#include <stdio.h>
#include <stdlib.h>

bool SAVE(LISTA *lista, FILA *fila) {
    if(!lista || !fila) 
        return false;
    
    PACIENTE *paciente; // Variável auxiliar 

    // Salvando os pacientes da lista

    FILE *fp_lista = fopen("lista_pacientes.bin", "wb");
    if(!fp_lista)
        return false;

    paciente = lista_remover(lista, paciente_get_id(paciente));
    int chave;
    while(paciente != NULL) { // Se mantém no while enquanto a lista não estiver vazia
        // Escreve a chave no arquivo
        chave = paciente_get_chave(paciente);
        fwrite(&chave, sizeof(int), 1, fp_lista);
        // Apaga o item removido
        paciente_apagar(&paciente);
        // Atualiza a variável auxiliar
        paciente = paciente_remover(lista, paciente_get_id(paciente));
    }
    // Libera memória
    LISTA_apagar(&lista);
    fclose(fp_lista); 
    fp_lista = NULL;

    // Salvando os pacientes da fila

    FILE *fp_fila = fopen("fila_pacientes.bin", "wb");
    if(!fp_fila)
        return false;

    paciente = fila_remover_paciente(fila);
    while(paciente != NULL) { // Se mantém no while enquanto a fila não estiver vazia
        // Escreve a chave no arquivo
        chave = paciente_get_id(paciente);
        fwrite(&chave, sizeof(int), 1, fp_fila);
        // Apaga o item removido
        paciente_apagar(&paciente);
        // Atualiza a variável auxiliar
        paciente = fila_remover_paciente(fila);
    }
    // Libera memória
    fila_apagar(&fila);
    fclose(fp_fila);
    fp_fila = NULL;

    return true;
}

bool LOAD(LISTA **lista, FILA **fila) {
    if(!*lista || !*fila) 
        return false;

    int chave; // Variável auxiliar

    // Carregando os itens do arquivo na lista

    FILE *fp_lista = fopen("lista_pacientes.bin", "rb");
    if(!fp_lista)
        return false;

    // Lê as chaves até o fim do arquivo
    while(fread(&chave, sizeof(int), 1, fp_lista) == 1) {
        PACIENTE *paciente = paciente_criar(chave);
        lista_inserir(*lista, paciente);
    }
    fclose(fp_lista); // Libera memória

    // Carregando os itens do arquivo na fila

    FILE *fp_fila = fopen("fila_pacientes.bin", "rb");
    if(!fp_fila)
        return false;

    // Lê as chaves até o fim do arquivo
    while(fread(&chave, sizeof(int), 1, fp_fila) == 1) {
        PACIENTE *paciente = paciente_criar(chave);
        fila_inserir_paciente(*fila, paciente);
    }
    fclose(fp_fila); // Libera memória

    return true;
}