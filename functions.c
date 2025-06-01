#include "functions.h"
#include <stdio.h>
#include <string.h>
#include <ctype.h>

void exibir_menu() {
    printf("1 - Consultar Paciente \n");
    printf("5 - Imprimir lista de Pacientes \n");
    printf("Q - Sair \n");
}

void menu(BDPaciente *bd) {

    char opcao;
    
    do {
        exibir_menu();
        printf("Escolha uma opção: ");
        scanf(" %c", &opcao);
        getchar();

        switch (opcao) {
            case '1':
                executar_consulta(bd);
                break;
            case '5':
                executar_listagem(bd);
                break;
            case 'Q':
            case 'q':
                printf("Saindo do sistema.\n");
                break;
            default:
                printf("Opção inválida. Tente novamente.\n");
        }

    } while (opcao != 'Q' && opcao != 'q');
}

int carregar_banco(BDPaciente *bd, const char *arquivo_csv) {

    FILE *arquivo = fopen(arquivo_csv, "r");
    if (!arquivo) {
        printf("Erro ao abrir o arquivo %s.\n", arquivo_csv);
        return 1;
    }

    bd->total = 0;

    char linha[256];

    // Ignorar a primeira linha
    fgets(linha, sizeof(linha), arquivo);

    while (fgets(linha, sizeof(linha), arquivo)) {
        if (bd->total >= MAX_PACIENTES) {
            printf("Limite máximo de pacientes atingido (%d).\n", MAX_PACIENTES);
            break;
        }

        Paciente *p = &bd->pacientes[bd->total];

        remover_quebra_linha(linha);

        // Pegando os valores separados por virgula
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

    return 0;
}

void remover_quebra_linha(char *str) {
    size_t len = strlen(str);
    if (len > 0 && str[len - 1] == '\n') {
        str[len - 1] = '\0';
    }
}

void consultar_por_nome(const BDPaciente *bd, const char *prefixo) {

    int encontrados = 0;
    int tam_prefixo = strlen(prefixo);

    for (int i = 0; i < bd->total; i++) {
        int j;
        int match = 1;

        for (j = 0; j < tam_prefixo; j++) {
            char c1 = tolower((unsigned char)prefixo[j]);
            char c2 = tolower((unsigned char)bd->pacientes[i].nome[j]);

            if (c2 == '\0' || c1 != c2) {
                match = 0;
                break;
            }
        }

        if (match) {
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

void executar_consulta(BDPaciente *bd) {

    char opcao;
    char entrada[100];

    printf("1 - Consulta por nome\n");
    printf("2 - Consulta por CPF\n");
    printf("3 - Retornar ao menu principal\n");
    printf("Opção: ");
    scanf(" %c", &opcao);
    getchar(); 

    if (opcao == '1') {
        printf("Digite o nome: ");
        fgets(entrada, sizeof(entrada), stdin);
        remover_quebra_linha(entrada);
        consultar_por_nome(bd, entrada);

    } else if (opcao == '2') {
        printf("Digite o CPF: ");
        fgets(entrada, sizeof(entrada), stdin);
        remover_quebra_linha(entrada);
        consultar_por_cpf(bd, entrada);

    } else if (opcao == '3') {
        printf("Retornando ao menu principal...\n");
        return;

    } else {
        printf("Opção inválida.\n");
    }

}

void executar_listagem(BDPaciente *bd) {
    if (bd->total == 0) {
        printf("Nenhum paciente cadastrado.\n");
        return;
    }

    printf("\nImprimindo lista de pacientes...\n\n");
    printf("ID | CPF              | Nome                         | Idade | Data de Cadastro\n");
    printf("------------------------------------------------------------------------------\n");

    for (int i = 0; i < bd->total; i++) {
        Paciente p = bd->pacientes[i];
        printf("%-2d | %-16s | %-28s | %-5d | %s\n", p.id, p.cpf, p.nome, p.idade, p.data_cadastro);
    }

    printf("------------------------------------------------------------------------------\n");
    printf("Total de pacientes: %d\n\n", bd->total);
}