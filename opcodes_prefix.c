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

int dissamble(const uint8_t* start, const uint8_t* end, size_t* position, Instruction_info* instruction, encoder_x86 encoder){
    /*
     * i8086 - datos:
     *
     * Los prefijos no son parte del 8086, asi que se ignoran a no ser que sea un 80386 en modo real u otro
     *  ________________________________________________________________________________________________
     * | opcode  | d | w || mod | reg | r/m || low disp/data || high disp/data || low data || high data |
     * |-----------------||-----------------||---------------||----------------||----------||-----------|
     * |      byte 1     ||      byte 2     ||     byte 3    ||     byte 4     ||  byte 5  ||  byte 6   |
     * |-----------------||-----------------||---------------||----------------||----------||-----------|
     * S = 0 (No extension de signo) ; S = 1 (extender signo de 8bits a 16bits si W = 1)
     * W = 0 (operando de un byte)   ; W = 1 (operando de 2bytes o de palabra)
     * D = 0 (campo REG es el origen); D = 1 (campo REG es el destino)
     * 
     * El 8086 dispone de un byte de opcode maximo, donde se encuentra el Bit D y el bit W normalmente
     * El segundo byte suele codificar Mod/RM
     *      - mod(00, memoria, no desplazamiento)
     *      - mod(01, memoria, desplazamiento de 8bits)
     *      - mod(10, memoria, desplazamiento de 16bits)
     *      - mod(11, modo registro, no desplazamiento)
     *           *excepto R/M = 110, que codifica un desplazamiento de 16 bits
     * 
     * el tercer byte codifica un desplazamiento bajo o datos
     * el cuarto byte codifica direcciones altas o datos
     * el quito byte codifica un dato bajo
     * el sexto byte codifica un dato alto
     * maximo 6 bytes por instruccion.
     * 
     *      | R/M |	                       MOD
     *      |     |   00            01 	              10	         11
     *      | 000 |	[BX+SI] 	[BX+SI+disp8]	[BX+SI+disp16]	   AL / AX
     *      | 001 |	[BX+DI] 	[BX+DI+disp8]	[BX+DI+disp16]	   CL / CX
     *      | 010 |	[BP+SI] 	[BP+SI+disp8]	[BP+SI+disp16]	   DL / DX
     *      | 011 |	[BP+DI] 	[BP+DI+disp8]	[BP+DI+disp16]	   BL / BX
     *      | 100 |	[SI]	    [SI+disp8]	    [SI+disp16]	       AH / SP
     *      | 101 |	[DI]	    [DI+disp8]	    [DI+disp16]	       CH / BP
     *      | 110 |	[disp16]	[BP+disp8]	    [BP+disp16]	       DH / SI
     *      | 111 |	[BX]	    [BX+disp8]	    [BX+disp16]	       BH / DI
     * 
     * Los modos de direccionamiento permitidos:
     * [BX + SI]
     * [BX + DI]
     * [BP + SI]
     * [BP + DI]
     * 
     */
    if (0 == (size_t)(end - start)) return 0;
    uint8_t *code = start;

    switch (*code)
    {
        case Prefix_addr_size: 
            instruction->flags_prefix |= FLAG_PREFIX_Prefix_addr_size; // se encontro prefijo 0x67
            *position += 1; code++;
            break;
    
        default: break;
    }
    instruction->flags = my_instruccion_8086[*code];
    instruction->opcode1.opcode_byte.byte = *code;
    *position += 1; code++;

    // si la unica flag activa es que tiene registro de segmento, salir
    // posiblemente se trate de una instruccion como push/pop <reg_seg>:
    if (REG_SEG_MASK == instruction->flags) return 1;


    if (instruction->flags & MOD_RM_REG_MASK){
        instruction->Mod_rm.byte = *code;
        *position += 1; code++;
        if (instruction->Mod_rm.fields.mod == 0b00) {
            // si 0b110 acceso directo 
            if (instruction->Mod_rm.fields.R_M == 0b110) 
                exit(0);
        } else {
            if ((instruction->flags & DISP_LOW_MASK) || (instruction->flags & DISP_HIGH_MASK)){
                if (instruction->Mod_rm.fields.mod == 0b01) {
                instruction->displacement.ui8 =  *code;
                *position += 1; code++;
                } else if (instruction->Mod_rm.fields.mod == 0b10) {
                    instruction->displacement.ui16 =  *(uint16_t*)(code);
                    *position += 2; code+=2;
                }
            }
        }
    }
    if (instruction->flags & INMED8_MASK){
        instruction->immediate.ui8 =  *code;
        *position += 1; code++;
    } else if (instruction->flags & INMED16_MASK) {
        instruction->immediate.ui16 =  *(uint16_t*)(code);
        *position += 2; code+=2;
    } else if (instruction->flags & DATA_SX_MASK){ // inmediato de 8bits a extender a 16
        instruction->immediate.ui8 =  *code;
        *position += 1; code++;
    }

    return 1; // mientras no se llegue al final queda por desensamblar
}
#include "./print_structs_format.h"

void print_Instruction_info(Instruction_info* instruction, encoder_x86 encode){
    printf("Instruction_info->flags %04hx\n", instruction->flags);
    printf("instruction->opcode1.opcode_byte.byte %02x\n", instruction->opcode1.opcode_byte.byte);
    if (instruction->flags == 0) {
        printf("NONE_FLAGS\n");
        return;
    }
    char* string = get_addr_to_encoder_x86(instruction->displacement.ui64, encode);
    printf("instruction->displacement %s\n", string);
    free(string); string = get_addr_to_encoder_x86(instruction->immediate.ui64, encode);
    printf("instruction->immediate %s\n", string);
    free(string); string = NULL;
    if (MOD_RM_REG_MASK  & instruction->flags){
        printf("MOD_RM_REG_MASK = 0x%x\n", instruction->Mod_rm.byte);
        printf("\tmod %02x\n", instruction->Mod_rm.fields.mod);
        printf("\treg %02x\n", instruction->Mod_rm.fields.reg);
        printf("\tR_M %02x\n", instruction->Mod_rm.fields.R_M);
    }
    if (DISP_LOW_MASK    & instruction->flags){
        printf("DISP_LOW_MASK\n");}
    if (DISP_HIGH_MASK   & instruction->flags){
        printf("DISP_HIGH_MASK\n");}
    if (DATA_MASK_8086   & instruction->flags){
        printf("DATA_MASK_8086\n");}
    if (DATA_MASK_8086_w & instruction->flags){
        printf("DATA_MASK_8086_w\n");}
    if (REG_MEM_16_MASK & instruction->flags){
        printf("REG_MEM_16_MASK\n");}
    if (INMED8_MASK & instruction->flags){
        printf("INMED8_MASK\n");}
    if (DATA_SX_MASK & instruction->flags){
        printf("DATA_SX_MASK\n");}
    if (REG_MEM_8_MASK & instruction->flags){
        printf("REG_MEM_8_MASK\n");}
    if (INMED16_MASK & instruction->flags){
        printf("INMED16_MASK\n");}
    if (REG_SEG_MASK & instruction->flags){
        printf("REG_SEG_MASK\n");}
    

    printf("instruction->flags_prefix %02x\n", instruction->flags_prefix);    
    if (FLAG_PREFIX_Prefix_addr_size  & instruction->flags_prefix){
        printf("FLAG_PREFIX_Prefix_addr_size\n");
    }
}


#endif