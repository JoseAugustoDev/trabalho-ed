#ifndef PACIENTE_H
#define PACIENTE_H

#include <stdio.h>

typedef struct paciente {
    int id;
    char cpf[15];
    char nome[100];
    int idade;
    char data_cadastro[11];
    struct paciente *prox;
} Paciente;

typedef struct {
    Paciente *inicio;
    int total;
} ListaPaciente;


void menu(ListaPaciente *lista);

int carregar_banco(ListaPaciente *lista, const char *arquivo_csv);

void imprimir_pacientes(const ListaPaciente *lista);

void inserir_paciente(ListaPaciente *lista);

void remover_paciente(ListaPaciente *lista);    

void atualizar_paciente(ListaPaciente *lista);

void executar_consulta(ListaPaciente *lista);

void remover_quebra_linha(char *str);

void consultar_por_nome(const ListaPaciente *lista, const char *prefixo);

void consultar_por_cpf(const ListaPaciente *lista, const char *prefixo);

#endif
