#include "IO.h"
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

bool SAVE(LISTA *lista, FILA *fila) {
    if(!lista || !fila) 
        return false;
    
    PACIENTE *paciente; // Variável auxiliar 

    // Salvando os pacientes da lista

    FILE *fp_lista = fopen("lista_pacientes.bin", "wb");
    if(!fp_lista)
        return false;

    while(!lista_vazia(lista)) { // Enquanto a lista não estiver vazia
        // Pega o primeiro paciente da lista
        paciente = lista_primeiro(lista);
        if(paciente == NULL) break;
        
        // Escreve o ID no arquivo
        int id = paciente_get_id(paciente);
        fwrite(&id, sizeof(int), 1, fp_lista);
        
        // Escreve o nome no arquivo
        char *nome = paciente_get_nome(paciente);
        int nome_len = strlen(nome);
        fwrite(&nome_len, sizeof(int), 1, fp_lista); // Escreve o tamanho do nome primeiro
        fwrite(nome, sizeof(char), nome_len, fp_lista); // Escreve o nome
        
        // Remove o paciente da lista
        paciente = lista_remover(lista, id);
        // Apaga o item removido
        paciente_apagar(&paciente);
    }
    // Libera memória
    lista_apagar(&lista);
    fclose(fp_lista); 
    fp_lista = NULL;

    // Salvando os pacientes da fila

    FILE *fp_fila = fopen("fila_pacientes.bin", "wb");
    if(!fp_fila)
        return false;

    paciente = fila_remover_paciente(fila);
    while(paciente != NULL) { // Se mantém no while enquanto a fila não estiver vazia
        // Escreve o ID no arquivo
        int id = paciente_get_id(paciente);
        fwrite(&id, sizeof(int), 1, fp_fila);
        
        // Escreve o nome no arquivo
        char *nome = paciente_get_nome(paciente);
        int nome_len = strlen(nome);
        fwrite(&nome_len, sizeof(int), 1, fp_fila); // Escreve o tamanho do nome primeiro
        fwrite(nome, sizeof(char), nome_len, fp_fila); // Escreve o nome
        
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

    int id, nome_len; // Variáveis auxiliares
    char nome[100]; // Buffer para o nome

    // Carregando os itens do arquivo na lista

    FILE *fp_lista = fopen("lista_pacientes.bin", "rb");
    if(!fp_lista)
        return false;

    // Lê os dados até o fim do arquivo
    while(fread(&id, sizeof(int), 1, fp_lista) == 1) {
        // Lê o tamanho do nome
        if(fread(&nome_len, sizeof(int), 1, fp_lista) != 1) break;
        
        // Lê o nome
        if(fread(nome, sizeof(char), nome_len, fp_lista) != nome_len) break;
        nome[nome_len] = '\0'; // Adiciona terminador de string
        
        // Cria paciente com dados completos
        PACIENTE *paciente = paciente_criar(id);
        if(paciente != NULL) {
            paciente_set_nome(paciente, nome);
            lista_inserir(*lista, paciente);
        }
    }
    fclose(fp_lista); // Libera memória

    // Carregando os itens do arquivo na fila

    FILE *fp_fila = fopen("fila_pacientes.bin", "rb");
    if(!fp_fila)
        return false;

    // Lê os dados até o fim do arquivo
    while(fread(&id, sizeof(int), 1, fp_fila) == 1) {
        // Lê o tamanho do nome
        if(fread(&nome_len, sizeof(int), 1, fp_fila) != 1) break;
        
        // Lê o nome
        if(fread(nome, sizeof(char), nome_len, fp_fila) != nome_len) break;
        nome[nome_len] = '\0'; // Adiciona terminador de string
        
        // Cria paciente com dados completos
        PACIENTE *paciente = paciente_criar(id);
        if(paciente != NULL) {
            paciente_set_nome(paciente, nome);
            fila_inserir_paciente(*fila, paciente);
        }
    }
    fclose(fp_fila); // Libera memória

    return true;
}