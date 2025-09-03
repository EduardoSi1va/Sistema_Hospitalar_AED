#include <stdlib.h>
#include <stdio.h>
#include <stdbool.h>
#include "paciente.h"

struct paciente{ 
        int id;
        char nome[100];
};

PACIENTE *paciente_criar (int id){
          PACIENTE *paciente;
          
          paciente = (PACIENTE *) malloc(sizeof(PACIENTE));
          
          if (paciente != NULL){
             paciente->id = id;
             return(paciente);
          }
          return(NULL);
}

bool paciente_apagar(PACIENTE **paciente){
   if (*paciente != NULL){
      free (*paciente); // Free apenas marca o espaço de memória como disponível
      *paciente = NULL; // Limpa o valor do espaço, pois o ponteiro recebe NULL
      return(true);
   }
   return(false);
}

int paciente_get_id(PACIENTE *paciente){
    if (paciente != NULL)
      return(paciente->id);
    exit(1);
}


bool paciente_set_id(PACIENTE *paciente, int id){
  if (paciente != NULL){
    paciente->id = id;
    return (true);
  }
  return (false);
}

void paciente_imprimir(PACIENTE *paciente){
     if (paciente != NULL){
        printf("\n-->ID do Paciente: %d\n", paciente->id);
     }
}