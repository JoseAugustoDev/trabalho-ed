#include "functions.h"
#include <stdio.h>

struct paciente {
    int id;
    char cpf[15];
    char nome[100];
    int idade;
    char data_cadastro[11];
};

struct bdpaciente {
    Paciente pacientes[MAX_PACIENTES];
    int total;
};

void carregar_banco(BDPaciente *bd, const char *arquivo_csv) {

    FILE *arquivo = fopen(arquivo_csv, "r");
    if (!arquivo) {
        printf("Erro ao abrir o arquivo %s.\n", arquivo_csv);
        exit(1);
    }

    bd->total = 0;

    char linha[256];

    // Ignorar a primeira linha (cabeçalho)
    fgets(linha, sizeof(linha), arquivo);

    while (fgets(linha, sizeof(linha), arquivo)) {
        if (bd->total >= MAX_PACIENTES) {
            printf("Limite máximo de pacientes atingido (%d).\n", MAX_PACIENTES);
            break;
        }

        Paciente *p = &bd->pacientes[bd->total];

        remover_quebra_linha(linha);

        // Pegando os valores separando por virgula
        int campos = sscanf(
            linha, "%d,%14[^,],%99[^,],%d,%10s",
            &p->id,
            p->cpf,
            p->nome,
            &p->idade,
            p->data_cadastro
        );

        if (campos == 5) {
            bd->total++;
        } else {
            printf("Erro ao ler linha %d: formato inválido.\n", bd->total + 2); // +2 por conta do cabeçalho
        }
    }

    fclose(arquivo);

}

void remover_quebra_linha(char *str) {
    size_t len = strlen(str);
    if (len > 0 && str[len - 1] == '\n') {
        str[len - 1] = '\0';
    }
}

void consultar_por_nome(const BDPaciente *bd, const char *prefixo) {

    int encontrados = 0;
    int tamanho_prefixo = strlen(prefixo);

    for (int i = 0; i < bd->total; i++) {
        const char *nome = bd->pacientes[i].nome;
        int corresponde = 1;

        for (int j = 0; j < tamanho_prefixo; j++) {
            if (nome[j] != prefixo[j]) {
                corresponde = 0;
                break;
            }
        }

        if (corresponde) {
            Paciente p = bd->pacientes[i];
            printf("%d %s %s %d %s\n", p.id, p.cpf, p.nome, p.idade, p.data_cadastro);
            encontrados++;
        }
    }

    if (encontrados == 0) {
        printf("Nenhum paciente encontrado com o nome iniciado por \"%s\".\n", prefixo);
    }
}

void consultar_por_cpf(const BDPaciente *bd, const char *prefixo) {

    int encontrados = 0;
    int tamanho_prefixo = strlen(prefixo);

    for (int i = 0; i < bd->total; i++) {
        const char *cpf = bd->pacientes[i].cpf;
        int corresponde = 1;

        for (int j = 0; j < tamanho_prefixo; j++) {
            if (cpf[j] != prefixo[j]) {
                corresponde = 0;
                break;
            }
        }

        if (corresponde) {
            Paciente p = bd->pacientes[i];
            printf("%d %s %s %d %s\n", p.id, p.cpf, p.nome, p.idade, p.data_cadastro);
            encontrados++;
        }
    }

    if (encontrados == 0) {
        printf("Nenhum paciente encontrado com o CPF iniciado por \"%s\".\n", prefixo);
    }
}