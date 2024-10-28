/*
 *	Licencia Apache, Version 2.0 con Modificacion
 *	
 *	Copyright 2023 Desmon (David)
 *	
 *	Se concede permiso, de forma gratuita, a cualquier persona que obtenga una copia de 
 *	este software y archivos de documentacion asociados (el "Software"), para tratar el 
 *	Software sin restricciones, incluidos, entre otros, los derechos de uso, copia, 
 *	modificacion, fusion, publicacion, distribucion, sublicencia y/o venta de copias del 
 *	Software, y para permitir a las personas a quienes se les proporcione el Software 
 *	hacer lo mismo, sujeto a las siguientes condiciones:
 *	
 *	El anterior aviso de copyright y este aviso de permiso se incluiran en todas las 
 *	copias o partes sustanciales del Software.
 *	
 *	EL SOFTWARE SE PROPORCIONA "TAL CUAL", SIN GARANTiA DE NINGÚN TIPO, EXPRESA O 
 *	IMPLiCITA, INCLUYENDO PERO NO LIMITADO A LAS GARANTiAS DE COMERCIABILIDAD, IDONEIDAD 
 *	PARA UN PROPoSITO PARTICULAR Y NO INFRACCIoN. EN NINGÚN CASO LOS TITULARES DEL 
 *	COPYRIGHT O LOS TITULARES DE LOS DERECHOS DE AUTOR SERaN RESPONSABLES DE NINGÚN 
 *	RECLAMO, DAnO U OTRA RESPONSABILIDAD, YA SEA EN UNA ACCIoN DE CONTRATO, AGRAVIO O DE 
 *	OTRA MANERA, QUE SURJA DE, FUERA DE O EN CONEXIoN CON EL SOFTWARE O EL USO U OTRO TIPO
 *	DE ACCIONES EN EL SOFTWARE.
 *	
 *	Ademas, cualquier modificacion realizada por terceros se considerara propiedad del 
 *	titular original de los derechos de autor. Los titulares de derechos de autor 
 *	originales no se responsabilizan de las modificaciones realizadas por terceros.
 *	
 *	Queda explicitamente establecido que no es obligatorio especificar ni notificar los 
 *	cambios realizados entre versiones, ni revelar porciones especificas de codigo 
 *	modificado.
 */
//#define DEBUG_ENABLE // debug activado
#include "opcodes_prefix.h"

#include <stdio.h>

size_t get_size_func(unsigned char* func_ptr) {
    for (size_t n_bytes_func = 0; func_ptr != NULL; func_ptr++)
    {
        if ( 
            (
                *(func_ptr + 0) == (unsigned char)0xc3 &&
                *(func_ptr + 1) == (unsigned char)0xc3 &&
                *(func_ptr + 2) == (unsigned char)0xc3 &&
                *(func_ptr + 3) == (unsigned char)0xc3 &&
                *(func_ptr + 4) == (unsigned char)0xc3 &&
                *(func_ptr + 5) == (unsigned char)0xc3 &&
                *(func_ptr + 6) == (unsigned char)0xc3 
            ) || n_bytes_func > 0x75D410 // poner un tamaño limite
        ) return n_bytes_func;
        else {
            n_bytes_func++;
        }
    }
    return 0;
}   

int main(){
    uint8_t instrucciones[] = {
        0x67, 0x12, 0x04, 0x20, // adc al, [al+ah]
        0x03, 0x00,             // add ax, [bx+si]
        0x13, 0x0E,             // adc cx, [ax+cx]
        0x83, 0xc0, 0x10,       // add ax, 16
        0x83, 0xd1, 0x20,       // adc cx, 32
        0x14, 0x30,             // adc al, 48
        0x80, 0xc1, 0x40,       // add cl, 64
        0x80, 0xd1, 0x50,       // adc cl, 80

    };

    Instruction_info instruccion = {0};
    size_t position = 0;
    while (dissamble(
        instrucciones, 
        instrucciones + sizeof(instrucciones),
        &position, 
        &instruccion, ENCODER_IN_16bits
    )) { // mientras dissamble devuelva 1, quedara instrucciones por desensamblar
        print_Instruction_info(&instruccion, ENCODER_IN_16bits);
        printf("%p - %p -> %zu\n", instrucciones, instrucciones + sizeof(instrucciones), position);
        memset(&instruccion, 0, sizeof(Instruction_info));
    }
    
   

    puts("Exit...");
    return 0;
    
}

