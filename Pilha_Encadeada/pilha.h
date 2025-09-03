#ifndef _PILHA_H
#define _PILHA_H

  #include "../TAD_Paciente/paciente.h"
  #include <stdbool.h>

  #define TAM 1005

  typedef struct pilha PILHA;

  PILHA* pilha_criar(void);
  void pilha_apagar(PILHA** pilha);
  bool pilha_vazia(PILHA* pilha);
  bool pilha_cheia(PILHA* pilha);
  int pilha_tamanho(PILHA* pilha);
  PACIENTE* pilha_topo(PILHA* pilha);
  bool pilha_empilhar(PILHA* pilha, PACIENTE* paciente);
  PACIENTE* pilha_desempilhar(PILHA* pilha);

#endif 