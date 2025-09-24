#ifndef _PILHA_H
#define _PILHA_H


#include <stdbool.h>
#define TAM 1005

typedef struct pilha PILHA;

PILHA* pilha_criar(void);
void pilha_apagar(PILHA** pilha);
bool pilha_vazia(PILHA* pilha);
bool pilha_cheia(PILHA* pilha);
int pilha_tamanho(PILHA* pilha);
char* pilha_topo(PILHA* pilha);
bool pilha_empilhar(PILHA* pilha, const char* procedimento);
bool pilha_desempilhar(PILHA* pilha, char* procedimento);
void pilha_imprimir(PILHA* pilha);

#endif 