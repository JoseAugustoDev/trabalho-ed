#ifndef FUNCTIONS_H
#define FUNCTIONS_H

#define MAX_PACIENTES 100

typedef struct paciente Paciente;

typedef struct bdpaciente BDPaciente;

void carregar_banco(BDPaciente *bd, const char *arquivo_csv);

void consultar_por_nome(const BDPaciente *bd, const char *prefixo);

void consultar_por_cpf(const BDPaciente *bd, const char *prefixo);

void imprimir_pacientes(const BDPaciente *bd);

void remover_quebra_linha(char *str);

void exibir_menu();

void executar_consulta(BDPaciente *bd);

void executar_listagem(BDPaciente *bd);

#endif
