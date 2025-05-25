# Sistema de Gerenciamento de Dados de Pacientes – Parte I

## 📋 Descrição

Este projeto consiste em um sistema simples de gerenciamento de pacientes de uma clínica, desenvolvido em linguagem C. Os dados são armazenados em um arquivo `.csv` e carregados em memória usando um vetor estático. Esta primeira parte do trabalho implementa as funcionalidades de **consulta** e **listagem** de pacientes.

---

## 🚀 Como executar

### 1. Pré-requisitos

- Sistema Linux (recomendado Ubuntu 22.04)
- Compilador GCC 11
- `make` instalado

### 2. Clonar o repositório

    git clone
    cd

### 3. Compilar

    make

### 4. Executar

    ./healthsys

🧠 Funcionalidades
    🔍 Consulta de paciente
    Permite buscar pacientes por nome ou CPF, usando busca por prefixo. Exibe os dados completos de cada paciente correspondente.

📄 Listagem de pacientes

    Exibe todos os pacientes armazenados, com os seguintes campos:

    ID

    CPF

    Nome

    Idade

    Data de Cadastro

🧩 TADs Utilizados

    BDPaciente

    Um TAD que representa o banco de dados em memória. Utiliza um vetor estático de registros, com funções para:

    Carregar dados do arquivo CSV

    Consultar paciente por nome ou CPF

    Listar todos os pacientes

    Cada paciente é representado por uma struct com os seguintes campos:

    typedef struct {
        int id;
        char cpf[15];
        char nome[100];
        int idade;
        char data_cadastro[11];
    } Paciente;

⚙️ Decisões de Implementação

    Vetor estático foi escolhido conforme especificado no enunciado.

    A busca por prefixo foi implementada com strncmp para strings.

    A separação por módulos ajuda a manter o código organizado e facilita a manutenção.

    A leitura do CSV foi feita utilizando fgets() e sscanf() para extração dos campos.