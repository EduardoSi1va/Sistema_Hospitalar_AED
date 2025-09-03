#include <stdio.h>
#include <stdlib.h>
#include "fila.h"

typedef struct no_
{
    NO *proximo;
    ITEM *conteudo;
} NO;

struct fila_
{
    int tamanho;
    NO *inicio;
    NO *fim;
};

FILA *fila_criar(void)
{
    FILA *f = (FILA *)malloc(sizeof(FILA));
    if (f != NULL)
    {
        f->tamanho = 0;
        f->inicio = NULL;
        f->fim = NULL;
    }
    return (f);
}

void fila_apagar(FILA **f)
{
    if (((*f) != NULL) && (!fila_vazia(*f)))
    {
        NO *p_auxiliar;
        while ((*f)->inicio != NULL)
        {
            p_auxiliar = (*f)->inicio;
            (*f)->inicio = (*f)->inicio->proximo;
            item_apagar(&p_auxiliar->conteudo);
        }
    }
}

bool fila_inserir(FILA *f, ITEM *conteudo)
{
    if ((f != NULL) && (!fila_cheia(f)))
    {
        NO *aux = (NO *)malloc(sizeof(NO));
        aux->conteudo = conteudo;
        aux->proximo = NULL;

        if (f->inicio == NULL)
        {
            f->inicio = aux;
        }
        else
            f->fim->proximo = aux;
        f->fim = aux;
        f->tamanho++;
        return (true);
    }
    return (false);
}

bool fila_cheia(FILA *f) { return 0; }

ITEM *fila_remover(FILA *f)
{
    if (f != NULL && !fila_vazia(f))
    {
        NO *p_aux = f->inicio;
        ITEM *item = p_aux->conteudo;
        f->inicio = p_aux->proximo;
        f->tamanho--;

        if (f->tamanho == 0)
        {
            f->fim = NULL;
        }
        free(p_aux);
        p_aux = NULL;
        return (item);
    }
    return (NULL);
}
