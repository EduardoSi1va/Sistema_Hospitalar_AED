## Sistema Hospitalar AED

Este projeto simula um sistema de atendimento médico de pacientes em um Pronto Socorro (PS), utilizando Tipos Abstratos de Dados (TADs) em C.
Desenvolvido por:
- André Campanholo Paschoalini - 14558061
- Eduardo Poltroniere da Silva - 16862892
- Pedro Hamamoto da Palma - 16818280

- ## Estrutura
- `main.c` - ponto de entrada e loop do menu.

Diretórios principais / TADs:
- `TAD_Paciente/` - (`paciente.c`, `paciente.h`) cadastro, busca, remoção e gerenciamento de pacientes (id, nome, histórico).
- `Lista_Simples_Encadeada/` - (`lista.c`, `lista.h`) lista dinâmica para armazenar pacientes (a lista é dona das estruturas `PACIENTE`).
- `Fila_Encadeada/` - (`fila.c`, `fila.h`) fila encadeada para triagem (FIFO) com capacidade finita (implementada como 10 no código atual).
- `Pilha_Encadeada/` - (`pilha.c`, `pilha.h`) pilha encadeada para histórico de procedimentos (LIFO) — máximo 10 procedimentos, cada um até 100 caracteres.
- `TAD_functions/` - (`functions.c`, `functions.h`) implementa as operações do menu e a lógica de negócio (registrar, óbito, procedimentos, chamada, etc.).
- `TAD_IO/` - (`IO.c`, `IO.h`) persistência: `SAVE` e `LOAD` para ler/gravar `lista_pacientes.bin` e `fila_pacientes.bin`.

## Principais funcionalidades e onde estão implementadas
- Registrar paciente: `TAD_functions/registrar_paciente` — cria `PACIENTE`, insere na `Lista_Simples_Encadeada` e em `Fila_Encadeada`.
- Registrar óbito: `TAD_functions/registrar_obito` — só permite apagar paciente se ele NÃO estiver na fila (apenas após ter sido chamado); remove da lista e apaga o `PACIENTE`.
- Adicionar procedimento: `TAD_functions/adicionar_procedimento` — empilha procedimento no `PILHA` do paciente.
- Desfazer procedimento: `TAD_functions/desfazer_procedimento` — desempilha o último procedimento e informa qual foi removido.
- Chamar paciente: `TAD_functions/chamar_paciente` — remove o paciente da fila (`fila_remover_paciente`) e o entrega para atendimento.
- Mostrar fila: `TAD_functions/mostrar_fila` — imprime a fila de espera.
- Mostrar histórico: `TAD_functions/mostrar_historico` — imprime o histórico (pilha) do paciente.
- Mostrar lista: `TAD_Lista_Simples_Encadeada/lista_imprimir` - imprime a lista de todos os pacientes.
- Salvar/Carregar: `TAD_IO/SAVE` e `TAD_IO/LOAD` carregam e salvam a lista e a fila de pacientes ao iniciar e ao fechar o programa (`main.c`) respectivamente.

## Persistência
- Ao sair (opção de menu), o programa chama `SAVE(lista, fila)` e grava `lista_pacientes.bin` e `fila_pacientes.bin`.
- Ao iniciar, `LOAD(&lista, &fila)` tenta recarregar os dados.

## Funções da interface
1. Registrar paciente
2. Registrar óbito de paciente
3. Adicionar procedimento ao histórico médico
4. Desfazer procedimento do histórico médico
5. Chamar paciente para atendimento
6. Mostrar fila de espera
7. Mostrar histórico do paciente
8. Mostrar lista de pacientes
9. Sair

## Compilação
gcc -o sistema_hospitalar main.c Fila_Encadeada/fila.c Lista_Simples_Encadeada/lista.c Pilha_Encadeada/pilha.c TAD_functions/functions.c TAD_IO/IO.c TAD_Paciente/paciente.c

## Execução
./sistema_hospitalar

