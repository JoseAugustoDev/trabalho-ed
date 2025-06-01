#include <stdio.h>
#include <stdlib.h>
#include "functions.h"

#define CSV_ARQUIVO "bd_paciente.csv"

int main() {
    BDPaciente *bd = malloc(sizeof(BDPaciente));

    if (carregar_banco(bd, "bd_paciente.csv") != 0) {
        return 1;
    }

    menu(bd); 

    return 0;
}

