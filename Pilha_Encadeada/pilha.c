#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
#include "pilha.h"
#include "../TAD_Paciente/paciente.h"

typedef struct no NO;
struct no
{
    char procedimento[100];
    NO *anterior;
};

struct pilha
{
    NO *topo;
    int tamanho;
};

PILHA *pilha_criar()
{
    PILHA *pilha = (PILHA *)malloc(sizeof(PILHA));
    if (pilha != NULL)
    {
        pilha->topo = NULL;
        pilha->tamanho = 0;
    }
    return pilha;
}

void pilha_apagar(PILHA **pilha)
{
    if (pilha && *pilha)
    {
        NO *paux;
        while ((*pilha)->topo != NULL)
        {
            paux = (*pilha)->topo;
            (*pilha)->topo = (*pilha)->topo->anterior;
            free(paux);
        }
        free(*pilha);
        *pilha = NULL;
    }
}

bool pilha_vazia(PILHA *pilha)
{
    if (pilha != NULL)
        return (pilha->tamanho == 0);
    return false;
}

bool pilha_cheia(PILHA *pilha)
{
    if (pilha != NULL)
    {
        NO *novo = (NO *)malloc(sizeof(NO));
        if (novo != NULL)
        {
            free(novo);
            return false;
        }
        return true;
    }
    return false;
}

int pilha_tamanho(PILHA *pilha)
{
    return (pilha != NULL) ? pilha->tamanho : -1;
}

char *pilha_topo(PILHA *pilha)
{
    if (pilha != NULL && !pilha_vazia(pilha))
    {
        return pilha->topo->procedimento;
    }
    return NULL;
}

bool pilha_empilhar(PILHA *pilha, const char *procedimento)
{
    if (!pilha_cheia(pilha))
    {
        NO *pnovo = (NO *)malloc(sizeof(NO));
        if (pnovo != NULL)
        {
            snprintf(pnovo->procedimento, sizeof(pnovo->procedimento), "%s", procedimento);
            pnovo->anterior = pilha->topo;
            pilha->topo = pnovo;
            pilha->tamanho++;
            return true;
        }
    }
    return false;
}

bool pilha_desempilhar(PILHA *pilha, char *procedimento)
{
    if (pilha != NULL && !pilha_vazia(pilha))
    {
        NO *pno = pilha->topo;
        if (procedimento != NULL)
        {
            snprintf(procedimento, 100, "%s", pno->procedimento);
        }
        pilha->topo = pilha->topo->anterior;
        free(pno);
        pilha->tamanho--;
        return true;
    }
    return false;
}

void pilha_imprimir(PILHA *pilha)
{
    if (pilha != NULL && !pilha_vazia(pilha))
    {
        NO *aux = pilha->topo;
        printf("Histórico de procedimentos:\n");
        while (aux != NULL)
        {
            printf("- %s\n", aux->procedimento);
            aux = aux->anterior;
        }
    }
    else
    {
        printf("Histórico vazio!\n");
    }
}