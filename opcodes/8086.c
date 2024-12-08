#include "8086.h"

#include <stdio.h>

int main() {
    // Número de elementos en el enum
    int num_opcodes = sizeof(opcodes_8086_names) / sizeof(opcodes_8086_names[0]);

    printf("Lista de valores del enum opcodes_8086:\n");

    for (int i = 0; i < num_opcodes; i++) {
        printf("Identificador: %060s, Valor: 0x%X\n", 
        opcodes_8086_names[i].string, opcodes_8086_names[i].val);
    }

    return 0;
}