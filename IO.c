#include "IO.h"
#include <stdio.h>
#include <stdlib.h>

bool SAVE(LISTA *lista, FILA *fila)
{
    if (!lista || !fila)
        return false;

    PACIENTE *paciente; // Variável auxiliar

    // Salvando os itens da lista

    FILE *fp_lista = fopen("lista_itens.bin", "wb");
    if (!fp_lista)
        return false;

    PACIENTE paciente = LISTA_remover_inicio(lista);
    int chave;
    char *nome = malloc(50 * sizeof(char));
    while (paciente != NULL)
    { // Se mantém no while enquanto a lista não estiver vazia
        // Escreve a chave no arquivo
        chave = paciente_get_id(paciente);
        fwrite(&chave, sizeof(int), 1, fp_lista);

        nome = paciente_get_nome(paciente);
        fwrite(&nome, sizeof(nome), 1, fp_lista);

        // Apaga o item removido
        paciente_apagar(&paciente);
        // Atualiza a variável auxiliar
        paciente = LISTA_remover_inicio(lista);
    }
    // Libera memória
    LISTA_apagar(&lista);
    fclose(fp_lista);
    fp_lista = NULL;

    // Salvando os itens da fila

    FILE *fp_fila = fopen("fila_itens.bin", "wb");
    if (!fp_fila)
        return false;

    paciente = FILA_remover(fila);
    while (it != NULL)
    { // Se mantém no while enquanto a fila não estiver vazia
        // Escreve a chave no arquivo
        chave = ITEM_get_chave(it);
        fwrite(&chave, sizeof(int), 1, fp_fila);

        nome = paciente_get_nome(paciente);
        fwrite(&nome, sizeof(nome), 1, fp_fila);
        // Apaga o item removido
        paciente_apagar(&paciente);
        // Atualiza a variável auxiliar
        paciente = FILA_remover(fila);
    }
    // Libera memória
    FILA_apagar(&fila);
    fclose(fp_fila);
    fp_fila = NULL;
    free(nome);

    return true;
}

bool LOAD(LISTA **lista, FILA **fila)
{
    if (!*lista || !*fila)
        return false;

    int chave; // Variável auxiliar
    char *nome = malloc(50*sizeof(char));

    // Carregando os itens do arquivo na lista

    FILE *fp_lista = fopen("lista_itens.bin", "rb");
    if (!fp_lista)
        return false;

    // Lê as chaves até o fim do arquivo
    while (fread(&chave, sizeof(int), 1, fp_lista) == 1)
    {
        ITEM *it = ITEM_criar(chave);
        LISTA_inserir(*lista, it);
    }
    fclose(fp_lista); // Libera memória

    // Carregando os itens do arquivo na fila

    FILE *fp_fila = fopen("fila_itens.bin", "rb");
    if (!fp_fila)
        return false;

    // Lê as chaves até o fim do arquivo
    while (fread(&chave, sizeof(int), 1, fp_fila) == 1)
    {
        ITEM *it = ITEM_criar(chave);
        FILA_inserir(*fila, it);
    }
    fclose(fp_fila); // Libera memória

    return true;
}