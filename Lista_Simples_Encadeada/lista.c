#include <stdio.h>
#include <stdlib.h>
#include "lista.h"
#include "../TAD_Paciente/paciente.h"

#define TAM 1000

typedef struct no_
{
    PACIENTE *conteudo;
    NO *proximo;
} NO;

typedef struct lista_
{
    NO *inicio;
    NO *fim;
    int tamanho;
    bool ordenada;
} LISTA;

LISTA *lista_criar(bool ordenada)
{
    LISTA *l = (LISTA *)malloc(sizeof(LISTA));
    if (l)
    {
        l->inicio = NULL;
        l->fim = NULL;
        l->tamanho = 0;
        l->ordenada = ordenada;
    }
    return (l);
}

bool lista_inserir_fim(LISTA *l, PACIENTE *conteudo)
{
    NO *p = (NO *)malloc(sizeof(NO));
    if (p)
    {
        p->conteudo = conteudo;
        p->proximo = NULL;
        if (l->tamanho = 0)
        {
            l->inicio = p;
        }
        else
        {
            l->fim->proximo = p;
        }
        l->fim = p;
        l->tamanho++;
        return (true);
    }
    return (false);
}

bool lista_inserir(LISTA *l, PACIENTE *item)
{
    bool x = false;
    if (l != NULL && (!lista_cheia(l)))
    {
        if (l->ordenada)
        {
        }
        else
        {
            x = lista_inserir_fim(l, item);
            return x;
        }
    }
}

PACIENTE *lista_busca(LISTA *l, int chave)
{
    if (l != NULL)
    {
        NO *p = l->inicio;
        while (p != NULL)
        {
            if (item_get_chave(p->conteudo) == chave)
            {
                return (p->conteudo);
            }
            p = p->proximo;
        }
    }
    return (NULL);
}

PACIENTE *lista_remover(LISTA *l, int chave)
{
    if (l != NULL)
    {
        NO *p = l->inicio;
    }
}

bool fila_cheia(LISTA *l)
{
    if (l != NULL && l->tamanho == TAM)
        return true;
    return false;
}

bool fila_vazia(LISTA *l)
{
    if (l != NULL && l->tamanho == 0)
        return true;
    return false;
}