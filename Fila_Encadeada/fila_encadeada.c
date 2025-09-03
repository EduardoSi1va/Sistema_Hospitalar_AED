#include "fila.h"
#include "../TAD_Paciente/paciente.h"
#include <stdlib.h>

#define TAM 1000

struct fila_ {
    NO *inicio;
    NO *final;
    int tamanho;
};

typedef struct no_ {
    NO *proximo;
    PACIENTE *conteudo;
} NO;


FILA *fila_criar(void) {
    FILA *f = (FILA *)malloc(sizeof(FILA));
    if(f != NULL) {
        f->inicio = NULL;
        f->final = NULL;
        f->tamanho = 0;
    };
    return f;
}

void fila_apagar(FILA **f) {
    if(f != NULL && *f != NULL) {
        NO *aux;
        while((*f)->inicio != NULL) {
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

bool fila_inserir(FILA *f, PACIENTE *it) {
    if(f != NULL && !fila_cheia(f)) {
        NO *aux = (NO *)malloc(sizeof(NO));
        if(aux != NULL) {
            aux->conteudo = it;
            aux->proximo = NULL;
            if(fila_vazia(f)) {
                f->inicio = aux;
            } else {
                f->final->proximo = aux;
            }  
            f->final = aux;
            f->tamanho++;
            return true;
        }
    }
    return false;
}

PACIENTE *fila_remover(FILA *f) {
    if(f != NULL && !fila_vazia(f)) {
        NO *aux = f->inicio;
        PACIENTE *it = aux->conteudo;
        f->inicio = f->inicio->proximo; //f->inicio = aux->proximo;
        if(f->inicio == NULL) {
            f->final = NULL;
        }
        free(aux);
        aux = NULL;
        f->tamanho--;
        return it;
    }
    return NULL;
}

PACIENTE *fila_frente(FILA *f) {
    if(f != NULL && !fila_vazia(f))
        return f->inicio->conteudo;
    return NULL;
}

PACIENTE *fila_atras(FILA *f) {
    if(f != NULL && !fila_vazia(f)) 
        return f->final->conteudo;
    return NULL;
}

int fila_tamanho(FILA *f) {
    if(f != NULL)
        return f->tamanho;
    return -1;
}

bool fila_cheia(FILA *f) {
    if(f != NULL && f->tamanho == TAM) 
        return true;
    return false;
}

bool fila_vazia(FILA *f) {
    if(f != NULL && f->tamanho == 0) 
        return true;
    return false;
}