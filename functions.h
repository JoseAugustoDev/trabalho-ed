#ifndef MAIN_H
#define MAIN_H

#define MAX_PACIENTES 100

typedef struct {
    int id;
    char cpf[15];
    char nome[100];
    int idade;
    char data_cadastro[11];
} Paciente;

typedef struct {
    Paciente pacientes[MAX_PACIENTES];
    int total;
} BDPaciente;

int carregar_banco(BDPaciente *bd, const char *arquivo_csv);

void consultar_por_nome(const BDPaciente *bd, const char *prefixo);

void consultar_por_cpf(const BDPaciente *bd, const char *prefixo);

void imprimir_pacientes(const BDPaciente *bd);

void remover_quebra_linha(char *str);

void exibir_menu();

void executar_consulta(BDPaciente *bd);

void executar_listagem(BDPaciente *bd);

#endif
