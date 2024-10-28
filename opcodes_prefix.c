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
#ifndef __OPCODES_PREFIX_C_
#define __OPCODES_PREFIX_C_

#include "opcodes_prefix.h"

int dissamble(uint8_t* code, uint8_t* code_final, size_t* position, Instruction_info* instruction, encoder_x86 encode){
    uint8_t *ptr_code = code + *position;
    uint8_t byte = *ptr_code;
    switch (byte)
    {
        case Prefix_addr_size: 
            instruction->flags_prefix |= FLAG_PREFIX_Prefix_addr_size; // se encontro prefijo 0x67
            *position += 1;
            break;
    
        default: break;
    }
    instruction->flags = my_instruccion_8086[*(code + *position)];
    instruction->opcode1.opcode_byte.byte = *(code + *position);
    *position += 1;

    if (instruction->flags & MOD_RM_REG_MASK){
        *((uint8_t*)&(instruction->Mod_rm)) = *(code + *position);
        *position += 1;
    }
    if ((instruction->flags & DISP_LOW_MASK) & (instruction->flags & DISP_HIGH_MASK)){
        instruction->displacement.ui16 = *(uint16_t*)(code + *position); // desplazamiento bajo y alto
        *position += 2;
    }

    return ((code+*position)  < code_final) ? 1 : 0; // mientras no se llegue al final queda por desensamblar
}
#include "./print_structs_format.h"

void print_Instruction_info(Instruction_info* instruction, encoder_x86 encode){
    printf("Instruction_info->flags %04hx\n", instruction->flags);
    printf("instruction->opcode1.opcode_byte.byte %02x\n", instruction->opcode1.opcode_byte.byte);
    char* string = get_addr_to_encoder_x86(instruction->displacement.ui64, encode);
    printf("instruction->displacement %s\n", string);
    free(string); string = get_addr_to_encoder_x86(instruction->immediate.ui64, encode);
    printf("instruction->immediate %s\n", string);
    free(string); string = NULL;
    if (MOD_RM_REG_MASK  & instruction->flags){
        printf("MOD_RM_REG_MASK\n");
        printf("\tmod %02x\n", instruction->Mod_rm.mod);
        printf("\tR_M %02x\n", instruction->Mod_rm.R_M);
        printf("\treg %02x\n", instruction->Mod_rm.reg);
    }
    if (DISP_LOW_MASK    & instruction->flags){
        printf("DISP_LOW_MASK\n");}
    if (DISP_HIGH_MASK   & instruction->flags){
        printf("DISP_HIGH_MASK\n");}
    if (DATA_MASK_8086   & instruction->flags){
        printf("DATA_MASK_8086\n");}
    if (DATA_MASK_8086_w & instruction->flags){
        printf("DATA_MASK_8086_w\n");}

    printf("instruction->flags_prefix %02x\n", instruction->flags_prefix);    
    if (FLAG_PREFIX_Prefix_addr_size  & instruction->flags_prefix){
        printf("FLAG_PREFIX_Prefix_addr_size\n");
    }
}


#endif