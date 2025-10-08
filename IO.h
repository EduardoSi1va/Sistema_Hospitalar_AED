#ifndef IO_H
#define IO_H
#include "TAD_Paciente/paciente.h"
#include "Pilha_Encadeada/pilha.h"
#include "Fila_Encadeada/fila.h"

#include <stdbool.h>

bool SAVE(LISTA *lista, FILA *fila);   // Salva os itens da lista e da fila em arquivos
bool LOAD(LISTA **lista, FILA **fila); // Carrega os itens dos arquivos na lista e na fila

#endif
