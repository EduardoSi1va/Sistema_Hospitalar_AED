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
        if (l->tamanho == 0)
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
            if (paciente_get_id(p->conteudo) == chave)
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
    if (l == NULL || lista_vazia(l)) 
        return NULL;
    
    NO *p = l->inicio;
    NO *anterior = NULL;
    
    while (p != NULL && paciente_get_id(p->conteudo) != chave) 
    {
        anterior = p;
        p = p->proximo;
    }
    
    if (p == NULL) 
        return NULL;
    
    PACIENTE *paciente = p->conteudo;
    
    if (anterior == NULL) 
    {
        l->inicio = p->proximo;
        if (l->inicio == NULL) 
            l->fim = NULL;
    }
    else 
    {
        anterior->proximo = p->proximo;
        if (p == l->fim) 
            l->fim = anterior;
    }
    
    free(p);
    l->tamanho--;
    return paciente;
}

PACIENTE *lista_primeiro(LISTA *l)
{
    if (l != NULL && l->inicio != NULL) 
    {
        return l->inicio->conteudo;
    }
    return NULL;
}

bool lista_cheia(LISTA *l)
{
    if (l != NULL && l->tamanho == TAM)
        return true;
    return false;
}

bool lista_vazia(LISTA *l)
{
    if (l != NULL && l->tamanho == 0)
        return true;
    return false;
}

bool lista_apagar(LISTA **l)
{
    if (l != NULL && *l != NULL)
    {
        NO *aux;
        while ((*l)->inicio != NULL)
        {
            aux = (*l)->inicio;
            (*l)->inicio = (*l)->inicio->proximo;
            paciente_apagar(&(aux->conteudo));
            free(aux);
        }
        free(*l);
        *l = NULL;
        return true;
    }
    return false;
}