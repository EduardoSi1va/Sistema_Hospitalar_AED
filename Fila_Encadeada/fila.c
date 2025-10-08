#include <stdio.h>
#include <stdlib.h>
#include "fila.h"
#include "../TAD_Paciente/paciente.h"

#define TAM 1000 // Quantidade máxima de pacientes do sistema hospitalar

struct fila_
{
    NO *inicio;
    NO *final;
    int tamanho;
};

typedef struct no_
{
    NO *proximo;
    PACIENTE *conteudo;
} NO;

FILA *fila_criar(void)
{
    FILA *f = (FILA *)malloc(sizeof(FILA));
    if (f != NULL)
    {
        f->inicio = NULL;
        f->final = NULL;
        f->tamanho = 0;
    };
    return f;
}

void fila_apagar(FILA **f)
{
    if (f != NULL && *f != NULL)
    {
        NO *aux;
        while ((*f)->inicio != NULL)
        {
            aux = (*f)->inicio;
            (*f)->inicio = (*f)->inicio->proximo;
            paciente_apagar(&(aux->conteudo));
            aux->conteudo = NULL;
            free(aux);
            aux = NULL;
        }
        free(*f);
        (*f) = NULL;
    }
}

bool fila_inserir_paciente(FILA *f, PACIENTE *paciente)
{
    if (f != NULL && !fila_cheia(f))
    {
        NO *aux = (NO *)malloc(sizeof(NO));
        if (aux != NULL)
        {
            aux->conteudo = paciente;
            aux->proximo = NULL;
            if (fila_vazia(f))
            {
                f->inicio = aux;
            }
            else
            {
                f->final->proximo = aux;
            }
            f->final = aux;
            f->tamanho++;
            return true;
        }
    }
    return false;
}

PACIENTE *fila_remover_paciente(FILA *f)
{
    if (f != NULL && !fila_vazia(f))
    {
        NO *aux = f->inicio;
        PACIENTE *paciente = aux->conteudo;
        f->inicio = f->inicio->proximo;
        if (f->inicio == NULL)
        {
            f->final = NULL;
        }
        paciente_apagar(&paciente); // Libera histórico e paciente
        free(aux);
        aux = NULL;
        f->tamanho--;
        return NULL; // Retorna NULL pois o paciente foi apagado
    }
    return NULL;
}

PACIENTE *fila_frente(FILA *f)
{
    if (f != NULL && !fila_vazia(f))
        return f->inicio->conteudo;
    return NULL;
}

PACIENTE *fila_atras(FILA *f)
{
    if (f != NULL && !fila_vazia(f))
        return f->final->conteudo;
    return NULL;
}

int fila_tamanho(FILA *f)
{
    if (f != NULL)
        return f->tamanho;
    return -1;
}

bool fila_cheia(FILA *f)
{
    if (f != NULL && f->tamanho == TAM)
        return true;
    return false;
}

bool fila_vazia(FILA *f)
{
    if (f != NULL && f->tamanho == 0)
        return true;
    return false;
}

void fila_imprimir(FILA *f)
{
    if (f != NULL)
    {
        NO *aux = f->inicio;
        while (aux != NULL)
        {
            paciente_imprimir(aux->conteudo);
            aux = aux->proximo;
        }
    }
}

void *fila_primeiro_no(FILA *fila)
{
    if (!fila)
        return NULL;
    return (void *)fila->inicio;
}
void *fila_proximo_no(void *no)
{
    if (!no)
        return NULL;
    return (void *)(((NO *)no)->proximo);
}
PACIENTE *fila_no_paciente(void *no)
{
    if (!no)
        return NULL;
    return ((NO *)no)->conteudo;
}