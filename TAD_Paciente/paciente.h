#ifndef ITEM_H
	#define ITEM_H
	
	#include <stdbool.h>

	typedef struct paciente PACIENTE;

	PACIENTE *paciente_criar(int id);
	bool paciente_apagar(PACIENTE **paciente);
	void paciente_imprimir(PACIENTE *paciente);
	int paciente_get_id(PACIENTE *paciente);
	bool paciente_set_id(PACIENTE *paciente, int id);
	bool paciente_set_nome(PACIENTE *paciente, const char *nome);

#endif
