#ifndef FILA_H
	#define FILA_H
	#include "../TAD_Paciente/paciente.h"

	typedef struct fila_ FILA;

	FILA *fila_criar(void);
	bool fila_inserir(FILA *fila, PACIENTE *paciente);
	PACIENTE *fila_remover(FILA *fila);
	void fila_apagar(FILA **fila);
	PACIENTE *fila_frente(FILA *fila);
	int fila_tamanho(FILA *fila);
	bool fila_vazia(FILA *fila);
	bool fila_cheia(FILA *fila);
	void fila_imprimir(FILA *fila);

#endif
