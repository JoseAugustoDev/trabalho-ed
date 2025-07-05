# Sistema de Gerenciamento de Dados de Pacientes – Parte I

## 📋 Descrição

Este projeto consiste em um sistema simples de gerenciamento de pacientes de uma clínica, desenvolvido em linguagem C. Os dados são armazenados em um arquivo `.csv` e carregados em memória usando uma lista encadeada. Esta primeira parte do trabalho implementa as funcionalidades de consulta, por nome e cpf, e listagem de pacientes.

---

## 🚀 Como executar

### 1. Pré-requisitos

- Compilador GCC 11
- `make` instalado
    - Se não tiver instalado: sudo apt install make

### 2. Clonar o repositório

    git clone https://github.com/JoseAugustoDev/trabalho-ed
    cd trabalho-ed

### 3. Compilar e Executar

    make -> Compila o projeto
    make clean -> remove os arquivos compilados
    make run -> compila e executa
    make clean run -> Compila e executa o projeto, removendo arquivos de execução anteriores


🧠 Funcionalidades
    🔍 Consulta de paciente
    1 - Permite buscar pacientes por nome ou CPF, usando busca por prefixo. 
    2 - Exibe os dados completos de cada paciente correspondente.

📄 Listagem de Pacientes

    O sistema permite a listagem completa dos pacientes cadastrados, exibindo na tela, em formato de tabela, os seguintes campos para cada registro:

    ID

    CPF

    Nome

    Idade

    Data de Cadastro

    Os dados são exibidos na ordem de inserção, ou seja, do paciente mais antigo para o mais recente, refletindo o comportamento de uma fila (FIFO).

🧩 TADs Utilizados

    Paciente

    ```c
    typedef struct paciente {
        int id;
        char cpf[15];
        char nome[100];
        int idade;
        char data_cadastro[11];
        struct paciente *prox;
    } Paciente;
    ```

    ListaPaciente

    ```c
    typedef struct {
        Paciente *inicio;
        int total;
    } ListaPaciente;
    ```
            int total;
        } ListaPaciente;

    A ListaPaciente é o TAD principal do sistema. Ela armazena:

        * Um ponteiro para o primeiro paciente da lista (inicio);

        * O número total de pacientes cadastrados (total).

    O uso dessas estruturas seguem o comportamento de uma fila, ou seja:

        * A inserção de um novo paciente é feita no final da lista
        * A remoção de um paciente é feita no ínicio

⚙️ Decisões de Implementação

    Utilizar uma lista encadeada simples como estrutura principal. Isso permite:
        * Alocação dinâmica
        * Ausência de limite fixo de pacientes
        * Mais flexibilidade

    Apesar de estar implementada como uma lista encadeade, seu comportamento é de uma fila. Foi feito dessa maneira, pois é a melhor forma de representar um ambiente tradicional de atendimentos real.

    Modularização

        * Todas as funções foram organizadas em módulos independentes a fim de ter uma melhor organização 