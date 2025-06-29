#include "paciente.h"
#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <ctype.h>


// TODO
// Pedir confirmação para remover, atualizar e inserir antes de realizar a ação.


void exibir_menu() {
    printf("\n=== MENU PRINCIPAL ===\n");
    printf("1 - Consultar Paciente\n");
    printf("2 - Atualizar Paciente\n");
    printf("3 - Remover Paciente\n");
    printf("4 - Inserir Paciente\n");
    printf("5 - Imprimir Lista de Pacientes\n");
    printf("Q - Sair\n");
    printf("======================\n");
}

void menu(ListaPaciente *lista) {
    char opcao;

    do {
        exibir_menu();
        printf("Escolha uma opção: ");
        scanf(" %c", &opcao);
        getchar();

        switch (opcao) {
            case '1':
                executar_consulta(lista);
                break;
            case '2':
                atualizar_paciente(lista);
                break;
            case '3':
                remover_paciente(lista);
                break;
            case '4':
                inserir_paciente(lista);
                break;
            case '5':
                imprimir_pacientes(lista); 
                break;
            case 'Q':
            case 'q':
                printf("Saindo do sistema...\n");
                break;
            default:
                printf("Opção inválida. Tente novamente.\n");
        }

    } while (opcao != 'Q' && opcao != 'q');
}

int carregar_banco(ListaPaciente *lista, const char *arquivo_csv) {
    FILE *arquivo = fopen(arquivo_csv, "r");
    if (!arquivo) {
        printf("Erro ao abrir o arquivo %s.\n", arquivo_csv);
        return 1;
    }

    lista->inicio = NULL;
    lista->total = 0;

    char linha[256];
    fgets(linha, sizeof(linha), arquivo); // ignora cabeçalho

    while (fgets(linha, sizeof(linha), arquivo)) {
        remover_quebra_linha(linha);
        Paciente *novo = malloc(sizeof(Paciente));
        if (!novo) {
            printf("Erro de alocação.\n");
            continue;
        }

        int campos = sscanf(linha, "%d,%14[^,],%99[^,],%d,%10s",
                            &novo->id, novo->cpf, novo->nome, &novo->idade, novo->data_cadastro);
        if (campos != 5) {
            printf("Erro ao ler linha %d.\n", lista->total + 2);
            free(novo);
            continue;
        }

        novo->prox = NULL;

        if (lista->inicio == NULL) {
            lista->inicio = novo;
        } else {
            Paciente *fim = lista->inicio;
            while (fim->prox) fim = fim->prox;
            fim->prox = novo;
        }

        lista->total++;
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

void consultar_por_nome(const ListaPaciente *lista, const char *prefixo) {
    Paciente *atual = lista->inicio;
    int encontrados = 0;
    int tam_prefixo = strlen(prefixo);

    while (atual != NULL) {
        int match = 1;

        for (int i = 0; i < tam_prefixo; i++) {
            char c1 = tolower((unsigned char)prefixo[i]);
            char c2 = tolower((unsigned char)atual->nome[i]);

            if (c2 == '\0' || c1 != c2) {
                match = 0;
                break;
            }
        }

        if (match) {
            printf("%d %s %s %d %s\n",
                   atual->id,
                   atual->cpf,
                   atual->nome,
                   atual->idade,
                   atual->data_cadastro);
            encontrados++;
        }

        atual = atual->prox;
    }

    if (encontrados == 0) {
        printf("Nenhum paciente encontrado com o nome iniciado por \"%s\".\n", prefixo);
    }
}


void consultar_por_cpf(const ListaPaciente *lista, const char *prefixo) {
    Paciente *atual = lista->inicio;
    int encontrados = 0;
    int tam_prefixo = strlen(prefixo);

    while (atual != NULL) {
        int match = 1;

        for (int i = 0; i < tam_prefixo; i++) {
            if (prefixo[i] != atual->cpf[i]) {
                match = 0;
                break;
            }
        }

        if (match) {
            printf("%d %s %s %d %s\n",
                   atual->id,
                   atual->cpf,
                   atual->nome,
                   atual->idade,
                   atual->data_cadastro);
            encontrados++;
        }

        atual = atual->prox;
    }

    if (encontrados == 0) {
        printf("Nenhum paciente encontrado com o CPF iniciado por \"%s\".\n", prefixo);
    }
}

void executar_consulta(ListaPaciente *lista) {
    char opcao;
    char entrada[100];

    printf("\n=== CONSULTA DE PACIENTES ===\n");
    printf("1 - Consulta por nome\n");
    printf("2 - Consulta por CPF\n");
    printf("3 - Retornar ao menu principal\n");
    printf("Opção: ");
    scanf(" %c", &opcao);
    getchar(); 

    switch (opcao) {
        case '1':
            printf("Digite o nome ou o início do nome: ");
            fgets(entrada, sizeof(entrada), stdin);
            remover_quebra_linha(entrada);
            consultar_por_nome(lista, entrada);
            break;

        case '2':
            printf("Digite o CPF ou o início do CPF: ");
            fgets(entrada, sizeof(entrada), stdin);
            remover_quebra_linha(entrada);
            consultar_por_cpf(lista, entrada);
            break;

        case '3':
            printf("Retornando ao menu principal...\n");
            break;

        default:
            printf("Opção inválida.\n");
    }
}

void imprimir_pacientes(const ListaPaciente *lista) {
    if (lista->inicio == NULL) {
        printf("Nenhum paciente cadastrado.\n");
        return;
    }

    printf("\nID | CPF              | Nome                      | Idade | Data_Cadastro\n");
    printf("-------------------------------------------------------------------------\n");

    Paciente *atual = lista->inicio;

    while (atual != NULL) {
        printf("%-2d | %-16s | %-24s | %-5d | %s\n",
               atual->id,
               atual->cpf,
               atual->nome,
               atual->idade,
               atual->data_cadastro);
        atual = atual->prox;
    }
}


void inserir_paciente(ListaPaciente *lista) {
    Paciente *novo = malloc(sizeof(Paciente));
    if (!novo) {
        printf("Erro de alocação.\n");
        return;
    }

    // Gera ID com base no maior existente
    int maior_id = 0;
    Paciente *atual = lista->inicio;
    while (atual) {
        if (atual->id > maior_id) maior_id = atual->id;
        atual = atual->prox;
    }
    novo->id = maior_id + 1;

    // Leitura dos dados
    printf("Digite o CPF: ");
    scanf("%s", novo->cpf);
    getchar();
    
    printf("Digite o nome: ");
    // Aqui utilizei o fgets para ler o nome, pois pode acontecer de ter nomes compostos. O scanf só iria reconhecer o primeiro nome.
    fgets(novo->nome, sizeof(novo->nome), stdin);
    remover_quebra_linha(novo->nome);
    
    char buffer[16];
    printf("Digite a idade: ");
    scanf("%s", buffer);
    novo->idade = atoi(buffer);
    getchar();

    printf("Digite a data de cadastro (AAAA-MM-DD): ");
    scanf("%s", novo->data_cadastro);
    getchar();
    
    if (strlen(novo->cpf) == 0 || strlen(novo->nome) == 0 || novo->idade <= 0 || strlen(novo->data_cadastro) != 10) {
        printf("Erro: dados inválidos.\n");
        free(novo);
        return;
    }

    novo->prox = NULL;

    // Inserir no final da lista
    if (lista->inicio == NULL) {
        lista->inicio = novo;
    } else {
        Paciente *fim = lista->inicio;
        while (fim->prox) {
            fim = fim->prox;
        }
        fim->prox = novo;
    }

    lista->total++;
    printf("Paciente inserido com sucesso!\n");
}


void remover_paciente(ListaPaciente *lista) {
    if (lista->inicio == NULL) {
        printf("Nenhum paciente cadastrado.\n");
        return;
    }

    char termo[100];
    printf("Digite parte do nome ou CPF para localizar o paciente: ");
    fgets(termo, sizeof(termo), stdin);
    remover_quebra_linha(termo);

    Paciente *anterior = NULL;
    Paciente *atual = lista->inicio;
    Paciente *encontrado = NULL;
    Paciente *anterior_encontrado = NULL;
    int contador = 0;
    int tam_termo = strlen(termo);

    while (atual != NULL) {
        int match_nome = 1;
        int match_cpf = 1;

        for (int i = 0; i < tam_termo; i++) {
            if (tolower(termo[i]) != tolower(atual->nome[i])) {
                match_nome = 0;
                break;
            }
        }

        for (int i = 0; i < tam_termo; i++) {
            if (termo[i] != atual->cpf[i]) {
                match_cpf = 0;
                break;
            }
        }

        if (match_nome || match_cpf) {
            contador++;
            if (contador > 1) {
                printf("Mais de um paciente corresponde ao termo. Refine sua busca.\n");
                return;
            }
            encontrado = atual;
            anterior_encontrado = anterior;
        }

        anterior = atual;
        atual = atual->prox;
    }

    if (contador == 0) {
        printf("Paciente não encontrado.\n");
        return;
    }

    // Confirma remoção
    printf("Paciente encontrado:\n");
    printf("%d %s %s %d %s\n",
           encontrado->id, encontrado->cpf, encontrado->nome,
           encontrado->idade, encontrado->data_cadastro);

    printf("Deseja realmente remover este paciente? (S/N): ");
    char confirmacao;
    scanf(" %c", &confirmacao);
    getchar();

    if (confirmacao != 'S' && confirmacao != 's') {
        printf("Remoção cancelada.\n");
        return;
    }

    if (anterior_encontrado == NULL) {
        // é o primeiro
        lista->inicio = encontrado->prox;
    } else {
        anterior_encontrado->prox = encontrado->prox;
    }

    free(encontrado);
    lista->total--;

    printf("Paciente removido com sucesso.\n");
}


void atualizar_paciente(ListaPaciente *lista) {
    if (lista->inicio == NULL) {
        printf("Nenhum paciente cadastrado.\n");
        return;
    }

    char termo[100];
    printf("Digite parte do nome ou CPF para localizar o paciente: ");
    fgets(termo, sizeof(termo), stdin);
    remover_quebra_linha(termo);

    Paciente *atual = lista->inicio;
    Paciente *encontrado = NULL;
    int tam_termo = strlen(termo);
    int contador = 0;

    while (atual != NULL) {
        int match_nome = 1;
        int match_cpf = 1;

        for (int i = 0; i < tam_termo; i++) {
            if (tolower(termo[i]) != tolower(atual->nome[i])) {
                match_nome = 0;
                break;
            }
        }

        for (int i = 0; i < tam_termo; i++) {
            if (termo[i] != atual->cpf[i]) {
                match_cpf = 0;
                break;
            }
        }

        if (match_nome || match_cpf) {
            contador++;
            if (contador > 1) {
                printf("Mais de um paciente corresponde ao termo informado. Refine sua busca.\n");
                return;
            }
            encontrado = atual;
        }

        atual = atual->prox;
    }

    if (contador == 0 || encontrado == NULL) {
        printf("Paciente não encontrado.\n");
        return;
    }

    // Atualizar os campos
    char buffer[100];
    int nova_idade;

    printf("\nPaciente encontrado:\n");
    printf("%d %s %s %d %s\n", encontrado->id, encontrado->cpf, encontrado->nome, encontrado->idade, encontrado->data_cadastro);

    printf("\nNovo CPF (ENTER para manter): ");
    fgets(buffer, sizeof(buffer), stdin);
    remover_quebra_linha(buffer);
    if (strlen(buffer) > 0) {
        int i = 0;
        while (buffer[i] != '\0') {
            encontrado->cpf[i] = buffer[i];
            i++;
        }
        encontrado->cpf[i] = '\0';
    }

    printf("Novo nome (ENTER para manter): ");
    fgets(buffer, sizeof(buffer), stdin);
    remover_quebra_linha(buffer);
    if (strlen(buffer) > 0) {
        int i = 0;
        while (buffer[i] != '\0') {
            encontrado->nome[i] = buffer[i];
            i++;
        }
        encontrado->nome[i] = '\0';
    }

    printf("Nova idade (0 para manter): ");
    fgets(buffer, sizeof(buffer), stdin);
    remover_quebra_linha(buffer);
    nova_idade = atoi(buffer);
    if (nova_idade > 0) {
        encontrado->idade = nova_idade;
    }

    printf("Nova data de cadastro (AAAA-MM-DD) (ENTER para manter): ");
    fgets(buffer, sizeof(buffer), stdin);
    remover_quebra_linha(buffer);
    if (strlen(buffer) == 10) {
        int i = 0;
        while (buffer[i] != '\0') {
            encontrado->data_cadastro[i] = buffer[i];
            i++;
        }
        encontrado->data_cadastro[i] = '\0';
    }

    printf("\nPaciente atualizado com sucesso:\n");
    printf("%d %s %s %d %s\n", encontrado->id, encontrado->cpf, encontrado->nome, encontrado->idade, encontrado->data_cadastro);
}

