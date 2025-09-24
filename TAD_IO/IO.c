#include "IO.h"
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

bool SAVE(LISTA *lista, FILA *fila)
{
    if (!lista || !fila)
        return false;

    // --- Salvar lista de pacientes ---
    FILE *fp_lista = fopen("lista_pacientes.bin", "wb");
    if (!fp_lista)
        return false;

    // Percorre a lista sem remover
    int tam_lista = lista_tamanho(lista);
    fwrite(&tam_lista, sizeof(int), 1, fp_lista);
    // Percorrer manualmente a lista encadeada
    extern struct lista_
    {
        struct no_ *inicio;
        struct no_ *fim;
        int tamanho;
        bool ordenada;
    };
    extern struct no_
    {
        PACIENTE *conteudo;
        struct no_ *proximo;
    };
    struct lista_ *lptr = (struct lista_ *)lista;
    struct no_ *p = lptr->inicio;
    while (p != NULL)
    {
        PACIENTE *paciente = p->conteudo;
        int id = paciente_get_id(paciente);
        char *nome = paciente_get_nome(paciente);
        int nome_len = (int)strlen(nome) + 1;
        fwrite(&id, sizeof(int), 1, fp_lista);
        fwrite(&nome_len, sizeof(int), 1, fp_lista);
        fwrite(nome, sizeof(char), nome_len, fp_lista);
        // Salva histórico
        PILHA *hist = paciente_get_historico(paciente);
        int hist_tam = pilha_tamanho(hist);
        fwrite(&hist_tam, sizeof(int), 1, fp_lista);
        // Salva procedimentos do histórico (do topo para base)
        PILHA *tmp = pilha_criar();
        char proc[100];
        for (int h = 0; h < hist_tam; ++h)
        {
            pilha_desempilhar(hist, proc);
            fwrite(proc, sizeof(char), 100, fp_lista);
            pilha_empilhar(tmp, proc);
        }
        for (int h = 0; h < hist_tam; ++h)
        {
            pilha_desempilhar(tmp, proc);
            pilha_empilhar(hist, proc);
        }
        pilha_apagar(&tmp);
        p = p->proximo;
    }
    fclose(fp_lista);

    // --- Salvar fila de pacientes ---
    FILE *fp_fila = fopen("fila_pacientes.bin", "wb");
    if (!fp_fila)
        return false;

    extern int fila_tamanho(FILA * fila);
    int tam_fila = fila_tamanho(fila);
    fwrite(&tam_fila, sizeof(int), 1, fp_fila);
    // Percorre a fila sem remover
    extern struct fila_
    {
        struct no_ *inicio;
        struct no_ *final;
        int tamanho;
    };
    extern struct no_
    {
        struct no_ *proximo;
        PACIENTE *conteudo;
    };
    struct fila_ *fptr = (struct fila_ *)fila;
    struct no_ *q = fptr->inicio;
    while (q != NULL)
    {
        PACIENTE *paciente = q->conteudo;
        int id = paciente_get_id(paciente);
        char *nome = paciente_get_nome(paciente);
        int nome_len = (int)strlen(nome) + 1;
        fwrite(&id, sizeof(int), 1, fp_fila);
        fwrite(&nome_len, sizeof(int), 1, fp_fila);
        fwrite(nome, sizeof(char), nome_len, fp_fila);
        // Salva histórico
        PILHA *hist = paciente_get_historico(paciente);
        int hist_tam = pilha_tamanho(hist);
        fwrite(&hist_tam, sizeof(int), 1, fp_fila);
        PILHA *tmp = pilha_criar();
        char proc[100];
        for (int h = 0; h < hist_tam; ++h)
        {
            pilha_desempilhar(hist, proc);
            fwrite(proc, sizeof(char), 100, fp_fila);
            pilha_empilhar(tmp, proc);
        }
        for (int h = 0; h < hist_tam; ++h)
        {
            pilha_desempilhar(tmp, proc);
            pilha_empilhar(hist, proc);
        }
        pilha_apagar(&tmp);
        q = q->proximo;
    }
    fclose(fp_fila);
    return true;
}

bool LOAD(LISTA **lista, FILA **fila)
{
    if (!*lista || !*fila)
        return false;

    // --- Carregar lista de pacientes ---
    FILE *fp_lista = fopen("lista_pacientes.bin", "rb");
    if (!fp_lista)
        return false;
    int tam_lista = 0;
    fread(&tam_lista, sizeof(int), 1, fp_lista);
    for (int i = 0; i < tam_lista; ++i)
    {
        int id = 0, nome_len = 0, hist_tam = 0;
        fread(&id, sizeof(int), 1, fp_lista);
        fread(&nome_len, sizeof(int), 1, fp_lista);
        char nome[100];
        fread(nome, sizeof(char), nome_len, fp_lista);
        PACIENTE *paciente = paciente_criar(id, nome);
        fread(&hist_tam, sizeof(int), 1, fp_lista);
        for (int h = 0; h < hist_tam; ++h)
        {
            char proc[100];
            fread(proc, sizeof(char), 100, fp_lista);
            pilha_empilhar(paciente_get_historico(paciente), proc);
        }
        lista_inserir(*lista, paciente);
    }
    fclose(fp_lista);

    // --- Carregar fila de pacientes ---
    FILE *fp_fila = fopen("fila_pacientes.bin", "rb");
    if (!fp_fila)
        return false;
    int tam_fila = 0;
    fread(&tam_fila, sizeof(int), 1, fp_fila);
    for (int i = 0; i < tam_fila; ++i)
    {
        int id = 0, nome_len = 0, hist_tam = 0;
        fread(&id, sizeof(int), 1, fp_fila);
        fread(&nome_len, sizeof(int), 1, fp_fila);
        char nome[100];
        fread(nome, sizeof(char), nome_len, fp_fila);
        PACIENTE *paciente = paciente_criar(id, nome);
        fread(&hist_tam, sizeof(int), 1, fp_fila);
        for (int h = 0; h < hist_tam; ++h)
        {
            char proc[100];
            fread(proc, sizeof(char), 100, fp_fila);
            pilha_empilhar(paciente_get_historico(paciente), proc);
        }
        fila_inserir_paciente(*fila, paciente);
    }
    fclose(fp_fila);
    return true;
}