# Sistema de Gerenciamento de Dados de Pacientes – Parte I

## 📋 Descrição

Este projeto consiste em um sistema simples de gerenciamento de pacientes de uma clínica, desenvolvido em linguagem C. Os dados são armazenados em um arquivo `.csv` e carregados em memória usando um vetor estático. Esta primeira parte do trabalho implementa as funcionalidades de consulta, por nome e cpf, e listagem de pacientes.

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

    make clean run all


🧠 Funcionalidades
    🔍 Consulta de paciente
    1 - Permite buscar pacientes por nome ou CPF, usando busca por prefixo. 
    2 - Exibe os dados completos de cada paciente correspondente.

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

    A busca por prefixo foi implementada parecido com uma questão da prova.

    Decidi limitar o numero de pacientes para 50.