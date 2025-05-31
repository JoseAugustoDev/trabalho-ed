#include <stdio.h>
#include "functions.h"

#define CSV_ARQUIVO "bd_paciente.csv"

int main() {
    BDPaciente *bd;
    carregar_banco(&bd, CSV_ARQUIVO);

    char opcao;

    do {
        exibir_menu();
        printf("Escolha uma opção: ");
        scanf(" %c", &opcao);
        getchar(); // Limpa o buffer do teclado

        switch (opcao) {
            case '1':
                executar_consulta(&bd);
                break;
            case '5':
                executar_listagem(&bd);
                break;
            case 'Q':
            case 'q':
                printf("Saindo.\n");
                break;
            default:
                printf("Opção inválida. Tente novamente.\n");
        }
    } while (opcao != 'Q' && opcao != 'q');

    return 0;
}
