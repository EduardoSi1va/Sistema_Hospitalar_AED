## Sistema Hospitalar AED

Este projeto simula um sistema de atendimento médico de pacientes em um Pronto Socorro (PS), utilizando Tipos Abstratos de Dados (TADs) em C.

## Estrutura
- **TAD_Paciente/**: Cadastro, busca, remoção e persistência de pacientes.
- **Fila_Encadeada/**: Gerencia a fila de espera dos pacientes (FIFO).
- **Pilha_Encadeada/**: Gerencia o histórico médico dos pacientes (LIFO).
- **Persistencia_Dados/**: Arquivos de persistência dos dados.
- **main.c**: Menu principal e integração dos módulos.

## Funcionalidades
1. Registrar paciente
2. Dar alta ao paciente
3. Adicionar procedimento ao histórico médico
4. Desfazer procedimento do histórico médico
5. Chamar paciente para atendimento
6. Mostrar fila de espera
7. Mostrar histórico do paciente
8. Sair

## Persistência
Os dados são salvos e carregados automaticamente ao iniciar e sair do sistema.

## Compilação
Para compilar:
```sh
gcc main.c Fila_Encadeada/fila.c Pilha_Encadeada/pilha.c TAD_Paciente/paciente.c -o sistema_hospitalar
```
