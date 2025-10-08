## Sistema Hospitalar AED

Este projeto simula um sistema de atendimento médico de pacientes em um Pronto Socorro (PS), utilizando Tipos Abstratos de Dados (TADs) em C.

## Estrutura
- `main.c` - ponto de entrada e loop do menu.
- `build.ps1` - script PowerShell para compilar no Windows usando `gcc` (MinGW/WSL/etc.).
- `sistema_hospitalar.exe` - binário gerado após compilação (não comitado obrigatoriamente).
- `lista_pacientes.bin`, `fila_pacientes.bin` - arquivos de persistência gerados pelo programa.

Diretórios principais:
- `TAD_Paciente/` - (`paciente.c`, `paciente.h`) criação e gerenciamento de `PACIENTE` (id, nome, histórico).
- `Lista_Simples_Encadeada/` - (`lista.c`, `lista.h`) TAD lista para registrar pacientes (a lista é a dona das estruturas `PACIENTE`).
- `Fila_Encadeada/` - (`fila.c`, `fila.h`) TAD fila para triagem (FIFO). A fila armazena ponteiros para `PACIENTE` existentes na lista.
- `Pilha_Encadeada/` - (`pilha.c`, `pilha.h`) TAD pilha para histórico (LIFO) de procedimentos (máx. 10, 100 caracteres cada).
- `TAD_functions/` - (`functions.c`, `functions.h`) implementa as operações do menu (registrar paciente, óbito, procedimentos, chamada, etc.).
- `TAD_IO/` - (`IO.c`, `IO.h`) funções de persistência: `SAVE` e `LOAD` para os arquivos binários.

## Principais funcionalidades e onde estão implementadas
- Registrar paciente: `TAD_functions/registrar_paciente` — cria `PACIENTE`, insere na `Lista_Simples_Encadeada` e em `Fila_Encadeada`.
- Registrar óbito: `TAD_functions/registrar_obito` — só permite apagar paciente se ele NÃO estiver na fila (apenas após ter sido chamado); remove da lista e apaga o `PACIENTE`.
- Adicionar procedimento: `TAD_functions/adicionar_procedimento` — empilha procedimento no `PILHA` do paciente.
- Desfazer procedimento: `TAD_functions/desfazer_procedimento` — desempilha o último procedimento e informa qual foi removido.
- Chamar paciente: `TAD_functions/chamar_paciente` — remove o paciente da fila (`fila_remover_paciente`) e o entrega para atendimento.
- Mostrar fila: `TAD_functions/mostrar_fila` — imprime a fila de espera.
- Mostrar histórico: `TAD_functions/mostrar_historico` — imprime o histórico (pilha) do paciente.
- Salvar/Carregar: `TAD_IO/SAVE` e `TAD_IO/LOAD` são chamados em `salvar_pacientes` e ao iniciar o programa (`main.c`).

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
8. Sair