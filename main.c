#include <stdio.h>
#include <stdlib.h>
#include "paciente.h"

#define CSV_ARQUIVO "bd_paciente.csv"

int main() {
    ListaPaciente *bd = malloc(sizeof(ListaPaciente));

    if (carregar_banco(bd, "bd_paciente.csv") != 0) {
        return 1;
    }

    menu(bd); 

    return 0;
}

