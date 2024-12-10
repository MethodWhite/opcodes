
#include <stdio.h>
#include <stdlib.h>
#include <stdint.h>
#include <string.h>

#include "opcodes_prefix.h"

// Función que desensambla un archivo completo
void dissamble_file(const char *file_path) {
    // Abrir el archivo en modo binario
    FILE *f = fopen(file_path, "rb");
    if (!f) {
        perror("Error al abrir el archivo");
        return;
    }

    // Determinar el tamaño del archivo
    fseek(f, 0, SEEK_END);  // Ir al final del archivo
    long file_size = ftell(f);  // Obtener la posición actual (el tamaño del archivo)
    rewind(f);  // Volver al inicio del archivo

    // Reservar memoria para leer el archivo completo
    unsigned char *bios = (unsigned char *)malloc(file_size);
    if (!bios) {
        perror("Error al asignar memoria");
        fclose(f);
        return;
    }

    // Leer el archivo completo en memoria
    size_t read_size = fread(bios, 1, file_size, f);
    if (read_size != file_size) {
        perror("Error al leer el archivo");
        free(bios);
        fclose(f);
        return;
    }

    printf("Archivo leído con éxito, tamaño: %ld bytes\n", file_size);
    fclose(f);


// Disassemble the file
    size_t position = 0;
    while (position < file_size) {
        Instruction_info instruction = {0};
        size_t instructionSize = 0;

        int result = dissamble(bios + position, bios + file_size, &instructionSize, &instruction, ENCODER_IN_16bits);
        
        if (result == 0) {
            fprintf(stderr, "Error: Disassembly failed at position %zu\n", position);
            break;
        }

        print_Instruction_info(&instruction, ENCODER_IN_16bits);

        char* string = calloc(64, sizeof(char));
        get_string_Instruction_info_8086(&instruction, string, 64);

        // Print the offset and the instruction string
        printf("%04zX: %s\n", position, string);
        if (instruction.opcode1.opcode_byte.byte == opcodes_8086_JMP_SHORT) {
            // sumar el desplazamiento a saltar:
            position += instruction.immediate.ui16;
        }

        free(string);
        position += instructionSize;

    }

    free(bios);

}
int main() {
    dissamble_file("bios.bin");
    puts("exit...");
    return 0;
}