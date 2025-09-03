#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
#include "pilha.h"
#include "../TAD_Paciente/paciente.h"

typedef struct no NO;
struct no
{
    PACIENTE *paciente;
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
    return (pilha);
}

void pilha_apagar(PILHA **pilha)
{
    NO *paux;
    if (((*pilha) != NULL) && (!pilha_vazia(*pilha)))
    {

        while ((*pilha)->topo != NULL)
        {
            paux = (*pilha)->topo;
            (*pilha)->topo = (*pilha)->topo->anterior;
            paciente_apagar(&paux->paciente);
            paux->anterior = NULL;
            free(paux);
            paux = NULL;
        }
    }
    free(*pilha);
    *pilha = NULL;
}

bool pilha_vazia(PILHA *pilha)
{
    if (pilha != NULL)
        return ((pilha->tamanho == 0) ? true : false);
    return (false);
}

bool pilha_cheia(PILHA *pilha)
{
    if (pilha != NULL)
    {
        NO *novo = (NO *)malloc(sizeof(NO));
        if (novo != NULL)
        {
            free(novo);
            return (false);
        }
        return (true);
    }
}

int pilha_tamanho(PILHA *pilha)
{
    return ((pilha != NULL) ? pilha->tamanho : -1);
}

bool pilha_empilhar(PILHA *pilha, PACIENTE *paciente)
{
    if (!pilha_cheia(pilha))
    {
        NO *pnovo = (NO *)malloc(sizeof(NO));
        if (pnovo != NULL)
        {
            pnovo->paciente = paciente;
            pnovo->anterior = pilha->topo;
            pilha->topo = pnovo;
            pilha->tamanho++;
            return true;
        }
    }
    return false;
}

PACIENTE *pilha_desempilhar(PILHA *pilha)
{
    if ((pilha != NULL) && (!pilha_vazia(pilha)))
    {
        NO *pno = pilha->topo;
        PACIENTE *paciente = pilha->topo->paciente;
        pilha->topo = pilha->topo->anterior;
        pno->anterior = NULL;
        free(pno);
        pno = NULL;
        pilha->tamanho--;
        return (paciente);
    }
    return (NULL);
}