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

int dissamble_8087(const uint8_t* start, const uint8_t* end, size_t* position, Instruction_info* instruction){
    /*
     * El 8087 es un coprocesador matematico que se conecta al 8086, asi que se ignoran los prefijos.
     * el 8087(x87) no usaba registros de la misma manera que el 8086 lo hace, el x87 tiene 8 registros
     * que van del st(0) al st(7), cada registro tiene 80 bits(16bits * 5) de largo.
     * Los registros st(n) funciona en forma de pila, siendo ST(0) el tope de la pila, y ST(7) el fondo.
     * Esto se le conoce como pila de 8 niveles.
     * Por tanto se entiende que las instrucciones del x87 funcionan apilando(push), calculando, y desapilando(pop).
     * Los registros tope (ST(0) y ST(1)) se pueden usar como operandos explicitos en memoria o registros,
     * por lo que el registro ST(0) puede ser usado como acumulador. Tambien se puede intercambiar el contenido
     * de los registros cib FXCH st(X), lo que hace que se pueda usar 7 registros libremente direccionales mas
     * un acumulador
     *
     * Las instrucciones del x87 empiezan por 1101 1 MF x, donde MF son dos bits que indican el valor con el que trabajan
     */
    if (0 == (size_t)(end - start)) return 0;
    uint8_t *code = start;
    instruction->opcode1.opcode_byte.byte = *code;
    *position += 1; code++;

    // solo queremos obtener los ultimos 3 bytes del opcode de escape para poder saber
    // que flags tiene el opcode 2 para el coprocesador, la tabla my_instruccion_8087_table contiene
    // un puntero a una tabla de flags para la instruccion del 8087
    volatile uint8_t index = instruction->opcode1.opcode_byte.byte & 0b00000111;
    uint8_t *table    = my_instruccion_8087_table[index];
    size_t size_table = my_instruccion_8087_table_sizes[index];
    printf("table[%d]: %p size_table %zu\n", index, table, size_table);

    // obtener las flags de coprocesador de la tabla con indice "index":
    instruction->flags_x87 = table[*code];
    instruction->Mod_rm.byte = *code; // obtener el Mod_rm
    // se puede reciclar el campo Mod_rm para almacenar el opcode 2
    *position += 1; code++;

    if (instruction->flags_x87 & MOD_RM_REG_MASK){
        //instruction->Mod_rm.byte = *code;
        //*position += 1; code++;
        if (instruction->Mod_rm.fields.mod == 0b00) {
            // si 0b110 acceso directo 
            if (instruction->Mod_rm.fields.R_M == 0b110) 
            exit(0);
        } else  if (instruction->Mod_rm.fields.mod == 0b01) {
            instruction->displacement.ui8 =  *code;
            *position += 1; code++;
        } else if (instruction->Mod_rm.fields.mod == 0b10) {
            instruction->displacement.ui16 =  *(uint16_t*)(code);
            *position += 2; code+=2;
        }
    }

    return 1;
}

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

    // si el opcode actual, tiene el X87_MASK activo, entonces no se usa un procesamiento
    // convencional, se debe usar el procesamiento de desensamblador para el 8087
    if (my_instruccion_8086[*code] & X87_MASK) {
        instruction->flags = my_instruccion_8086[*code];
        return dissamble_8087(start, end, position, instruction);
    } else {

        switch (*code)
        {
            //case Prefix_addr_size: 
            //    instruction->flags_prefix |= FLAG_PREFIX_Prefix_addr_size; // se encontro prefijo 0x67
            //    *position += 1; code++;
            //    break;
            case Prefix_SS:
                instruction->flags_prefix |= FLAG_PREFIX_Prefix_SS; // se encontro prefijo 0x36
                *position += 1; code++;
                break;
            case Prefix_CS:
                instruction->flags_prefix |= FLAG_PREFIX_Prefix_CS; // se encontro prefijo 0x2E
                *position += 1; code++;
                break;
            case Prefix_ES:
                instruction->flags_prefix |= FLAG_PREFIX_Prefix_ES; // se encontro prefijo 0x26
                *position += 1; code++;
                break;
            case Prefix_DS:
                instruction->flags_prefix |= FLAG_PREFIX_Prefix_DS; // se encontro prefijo 0x3E
                *position += 1; code++;
                break;
            /*
            // en el 8086 no habia registro  FS y GS
            case Prefix_FS:
                instruction->flags_prefix |= FLAG_PREFIX_Prefix_FS; // se encontro prefijo 0x64
                *position += 1; code++;
                break;
            case Prefix_GS:
                instruction->flags_prefix |= FLAG_PREFIX_Prefix_GS; // se encontro prefijo 0x65
                *position += 1; code++;
                break;
            */
            case 0xf1: // prefijo LOCK no documentado, solo para el 8086
            case 0xF0: // prefijo LOCK
                instruction->flags_prefix |= FLAG_PREFIX_Prefix_LOCK; // se encontro prefijo 0x3E
                *position += 1; code++;
                break;
            case 0xf3: // prefijo REP
            case 0xf2: // prefijo REPNE
                instruction->flags_prefix |= FLAG_PREFIX_Prefix_REP; // se encontro prefijo 0x3E
                *position += 1; code++;
                break;
            default:
                instruction->flags_prefix = 0;
                break;
        }
        instruction->flags = my_instruccion_8086[*code];
        instruction->opcode1.opcode_byte.byte = *code;
        *position += 1; code++;

        // si la unica flag activa es que tiene registro de segmento, salir
        // posiblemente se trate de una instruccion como push/pop <reg_seg>:
        if (REG_SEG_MASK == instruction->flags) return 1;

        if (instruction->flags & TTTN_MASK) {
            instruction->displacement.ui8 = *code;
            *position += 1; code++;
        }

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
        if ( instruction->flags & DIS_HIGH_MASK) {
            instruction->displacement.ui16 = *(uint16_t*)(code);
            *position += 2; code+=2;
        }

        return 1; // mientras no se llegue al final queda por desensamblar
    }
}

#define level_tab "\t"

void print_flags(uint16_t flags) {
    if (flags == 0) {
        printf(level_tab"NONE_FLAGS");}
    if (DISP_LOW_MASK    & flags){
        printf("DISP_LOW_MASK | ");}
    if (DISP_HIGH_MASK   & flags){
        printf("DISP_HIGH_MASK | ");}
    if (DATA_MASK_8086   & flags){
        printf("DATA_MASK_8086 | ");}
    if (MASK_PREFIX & flags){
        printf("MASK_PREFIX | ");}
    if (REG_MEM_16_MASK & flags){
        printf("REG_MEM_16_MASK | ");}
    if (INMED8_MASK & flags){
        printf("INMED8_MASK | ");}
    if (DATA_SX_MASK & flags){
        printf("DATA_SX_MASK | ");}
    if (REG_MEM_8_MASK & flags){
        printf("REG_MEM_8_MASK | ");}
    if (INMED16_MASK & flags){
        printf("INMED16_MASK | ");}
    if (REG_SEG_MASK & flags){
        printf("REG_SEG_MASK | ");}
    if (UNDOCUMENTED_OPCODE_MASK & flags){
        printf("UNDOCUMENTED_OPCODE_MASK | ");}
    if (TTTN_MASK & flags){
        printf("TTTN_MASK ");}
    if (DIS_HIGH_MASK & flags){
        printf("DIS_HIGH_MASK ");}
    if (MOD_RM_REG_MASK & flags){
        printf("MOD_RM_REG_MASK ");}
    if (X87_MASK & flags){
        printf("X87_MASK ");}

    printf("\n");
}

void print_flags_x87(uint16_t flags) {
    if (flags == 0) {
        printf(level_tab"NONE_FLAGS_x87");}
    if (ST_REGISTER    & flags){
        printf("ST_REGISTER");}
    if (REG_MEM_8_MASK    & flags){
        printf("\t REG_MEM_8_MASK | ");}
    if (REG_MEM_16_MASK    & flags){
        printf("\t REG_MEM_16_MASK | ");}
    if (MOD_RM_REG_MASK    & flags){
        printf("MOD_RM_REG_MASK");}

    printf("\n");
}

void print_Instruction_info(Instruction_info* instruction, encoder_x86 encode){
    printf("Instruction_info->flags %04hx\n", instruction->flags);
    print_flags(instruction->flags);
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
    if (MOD_RM_REG_MASK  & instruction->flags || X87_MASK & instruction->flags){
        printf("MOD_RM_REG_MASK = 0x%x\n", instruction->Mod_rm.byte);
        printf("\tmod %02x\n", instruction->Mod_rm.fields.mod);
        printf("\treg %02x\n", instruction->Mod_rm.fields.reg);
        printf("\tR_M %02x\n", instruction->Mod_rm.fields.R_M);
    }

    // solo imprimir si es una instruccion para coprocesadores
    if (X87_MASK & instruction->flags ){
        printf("instruction->flags_x87 =  0x%x\n", instruction->flags_x87);
        print_flags_x87(instruction->flags_x87);
    }

    printf("instruction->flags_prefix %02x\n", instruction->flags_prefix);    
    if (FLAG_PREFIX_Prefix_addr_size  & instruction->flags_prefix){
        printf("FLAG_PREFIX_Prefix_addr_size\n");
    }
}

static inline char *get_string_instruction_by_id_8086(string_instrution_id_8086 id) {
    /*
     * 
     * Retorna el string de la instruccion correspondiente a la id string.
     * Se uso en este caso un array para ingresar los valores, en lugar de un switch case
     * que retornara un string por cuestiones de optimizacion. El switch case generara
     * un caso por instruccion agregada. Cada case genera este codigo ensamblador:
     * 
     * loc_140003061:          ; jumptable 0000000140002FAE case 7
     * lea     rax, aEdi_0     ; "aaa"
     * jmp     loc_140002FB7
     * 
     * Lo que quiere decir que con lea se carga el string a devolver y con jmp se salta a la parte de la funcion
     * donde se retorna, por lo tanto 2 instrucciones por caso por 150 instrucciones corresponde a 300 instrucciones
     * assembly para devolver el string correspondiente. el metodo del array es mas eficiente en codigo generado
     * pues solo se necesita verificar los limites antes de acceder a retornar el valor del string
     * 
     */

    if (id >= STRING_INSTRUCTION8086(ADD) && id <= STRING_INSTRUCTION8086(DEC)) return instruction_8086[id];
    else return "error - not exits this instruttion.";
}

static inline const char* get_reg_8086(uint8_t reg, uint8_t w) {
    // esta funcion se usa para obtener un registro atraves del capo RM y REG de mod/rm:
    return reg_8086[w][reg];
}    // en caso de que W = 0 entonces reg8, en caso de W = 1 entonces reg16

static const char* get_mod_rm_8086(Instruction_info *Instruction) {
    Mod_rm mod = Instruction->Mod_rm;
    // en el caso de ser mod 0b11 el campo rm se usa como otro registro:
    // Instruction->opcode1.opcode_bits.b1 es el bit W 0000 000W
    if (mod.fields.mod == 3) return get_reg_8086(mod.fields.R_M, Instruction->opcode1.opcode_bits.b1);
    else return Mod_rm_disp_8086[mod.fields.mod][mod.fields.R_M];
}

const char* get_prefix_by_flags_prefix(uint8_t flags_prefix){
    switch (flags_prefix)
    {
        case FLAG_PREFIX_Prefix_ES: return reg_seg[0];
        case FLAG_PREFIX_Prefix_CS: return reg_seg[1];
        case FLAG_PREFIX_Prefix_SS: return reg_seg[2];
        case FLAG_PREFIX_Prefix_DS: return reg_seg[3];
        case FLAG_PREFIX_Prefix_FS: return reg_seg[4];
        case FLAG_PREFIX_Prefix_GS: return reg_seg[5];
        default: return NULL;
    }
}

void get_string_Instruction_info_8086(Instruction_info *instruction, char* string, size_t size) {
    uint32_t opcode = instruction->opcode1.opcode_byte.byte;
    //print_Instruction_info(instruction, ENCODER_IN_16bits);
    char* string_opcode = NULL;
    if (opcode >= 0xd8 && opcode <= 0xdf) {

    } else {
        char* string_rg = NULL, *string_modrm = NULL;
        char* temp = NULL;  // se usa para operaciones temporales o intermedias como formateos. recordar liberar siempre al finalizar
        char estado = 0;   // se usa en algunos casos para indicar si es necesario liberar o no un buffer
        if (opcode >= 0x80 && opcode <= 0x83){
            // en estas instrucciones el campo reg especifica la instruccion
            // ademas son del tipo "instruccion mem/reg, inmediato"
            string_rg = malloc(15);
            uint32_t id_string_opcode = 0;
            switch (instruction->Mod_rm.fields.reg) {
                case 0b000: id_string_opcode = STRING_INSTRUCTION8086(ADD); break;
                case 0b001: id_string_opcode = STRING_INSTRUCTION8086(OR);  break;
                case 0b010: id_string_opcode = STRING_INSTRUCTION8086(ADC); break;
                case 0b011: id_string_opcode = STRING_INSTRUCTION8086(SBB); break;
                case 0b100: id_string_opcode = STRING_INSTRUCTION8086(AND); break;
                case 0b101: id_string_opcode = STRING_INSTRUCTION8086(SUB); break;
                case 0b110: id_string_opcode = STRING_INSTRUCTION8086(XOR); break;
                case 0b111: id_string_opcode = STRING_INSTRUCTION8086(CMP); break;
            }

            if       (opcode == 0x80 || opcode == 0x81) {  // reg8/mem8,   inmed16; W = 0
                                                           // reg16/mem16, inmed16; W = 1
                snprintf(string_rg, size, "0x%04x", instruction->immediate.ui16);
            }else if (opcode == 0x82 || opcode == 0x83) {  // reg8/mem8,   inmed8;  W = 0
                                                           // reg16/mem16, inmed8;  W = 1
                snprintf(string_rg, size, "0x%02x", instruction->immediate.ui8); 
            }
            char* temp2 = malloc(10);
            if(instruction->flags_prefix != 0) {
                temp = string_modrm = malloc(10);
                snprintf(string_modrm, size, "%s:%s", get_prefix_by_flags_prefix(instruction->flags_prefix), get_mod_rm_8086(instruction)); 
                snprintf(temp2, size, string_modrm, instruction->displacement.ui16); // añadir el desplazamiento del mod rm
                free(temp);
            } else {
                string_modrm = get_mod_rm_8086(instruction);
                snprintf(temp2, size, string_modrm, instruction->displacement.ui16); // añadir el desplazamiento del mod rm
            }
            temp = string_modrm = temp2;
        
            snprintf(string, size, "%s %s %s, %s", 
                get_string_instruction_by_id_8086(id_string_opcode), // 0
                (instruction->opcode1.opcode_bits_final.d == 0 && instruction->Mod_rm.fields.mod != 0b11) ? 
                (instruction->opcode1.opcode_bits.b1 == 0) ? "byte" : "word" : "", // 1
            string_modrm, string_rg ); 

            if (temp != NULL) free(temp); // liberar la memoria reservada
            return;
        } else if (opcode >= 0xd0 && opcode <= 0xd3){
            // en estas instrucciones el campo reg especifica la instruccion
            // ademas son del tipo "instruccion mem/reg, inmediato"
            string_rg = malloc(15);
            uint32_t id_string_opcode = 0;
            switch (instruction->Mod_rm.fields.reg) {
                case 0b000: id_string_opcode = STRING_INSTRUCTION8086(ROL); break;
                case 0b001: id_string_opcode = STRING_INSTRUCTION8086(ROR);  break;
                case 0b010: id_string_opcode = STRING_INSTRUCTION8086(RCL); break;
                case 0b011: id_string_opcode = STRING_INSTRUCTION8086(RCR); break;
                case 0b100: id_string_opcode = STRING_INSTRUCTION8086(SHL); break;
                case 0b101: id_string_opcode = STRING_INSTRUCTION8086(SHR); break;
                case 0b110: id_string_opcode = STRING_INSTRUCTION8086(NOP); break; // invalida
                case 0b111: id_string_opcode = STRING_INSTRUCTION8086(SAR); break;
            }

            if        (opcode == 0xd0 || opcode == 0xd1) {  
                snprintf(string_rg, size, "%s", "1");
            } else if (opcode == 0xd2 || opcode == 0xd3) {
                snprintf(string_rg, size, "%s", "CL"); 
            }
            char* temp2 = malloc(10);
            if(instruction->flags_prefix != 0) {
                temp = string_modrm = malloc(10);
                snprintf(string_modrm, size, "%s:%s", get_prefix_by_flags_prefix(instruction->flags_prefix), get_mod_rm_8086(instruction)); 
                snprintf(temp2, size, string_modrm, instruction->displacement.ui16); // añadir el desplazamiento del mod rm
                free(temp);
            } else {
                string_modrm = get_mod_rm_8086(instruction);
                snprintf(temp2, size, string_modrm, instruction->displacement.ui16); // añadir el desplazamiento del mod rm
            }
            temp = string_modrm = temp2;
        
            snprintf(string, size, "%s %s %s, %s", 
                get_string_instruction_by_id_8086(id_string_opcode), // 0
                (instruction->opcode1.opcode_bits.b1 & 1) ? "word" : "byte", // 1
            string_modrm, string_rg ); 

            if (temp != NULL) free(temp); // liberar la memoria reservada
            return;
        } else if (opcode >= 0xf6 && opcode <= 0xf7){
            // en estas instrucciones el campo reg especifica la instruccion
            // ademas son del tipo "instruccion mem/reg, inmediato"
            string_rg = malloc(15);
            uint32_t id_string_opcode = 0;
            switch (instruction->Mod_rm.fields.reg) {
                case 0b000: id_string_opcode = STRING_INSTRUCTION8086(TEST); break;
                case 0b001: id_string_opcode = STRING_INSTRUCTION8086(ROR);  break; // no usada
                case 0b010: id_string_opcode = STRING_INSTRUCTION8086(NOT); break;
                case 0b011: id_string_opcode = STRING_INSTRUCTION8086(NEG); break;
                case 0b100: id_string_opcode = STRING_INSTRUCTION8086(MUL); break;
                case 0b101: id_string_opcode = STRING_INSTRUCTION8086(IMUL); break;
                case 0b110: id_string_opcode = STRING_INSTRUCTION8086(DIV); break; 
                case 0b111: id_string_opcode = STRING_INSTRUCTION8086(IDIV); break;
            }
            snprintf(string, size, "%s %s %s", 
                get_string_instruction_by_id_8086(id_string_opcode), (opcode == 0xf7) ? "word" : "byte", // 1
                get_mod_rm_8086(instruction)); 

            return;
        } else if (opcode >= 0xfe && opcode <= 0xff){
            // en estas instrucciones el campo reg especifica la instruccion
            // ademas son del tipo "instruccion mem/reg, inmediato"
            string_rg = malloc(15);
            uint32_t id_string_opcode = 0;
            switch (instruction->Mod_rm.fields.reg) {
                case 0b000: id_string_opcode = STRING_INSTRUCTION8086(INC); break;
                case 0b001: id_string_opcode = STRING_INSTRUCTION8086(DEC);  break;
                case 0b010: id_string_opcode = STRING_INSTRUCTION8086(CALL); break;
                case 0b011: id_string_opcode = STRING_INSTRUCTION8086(CALL); break;
                case 0b100: id_string_opcode = STRING_INSTRUCTION8086(JMP); break;
                case 0b101: id_string_opcode = STRING_INSTRUCTION8086(JMP); break;
                case 0b110: id_string_opcode = STRING_INSTRUCTION8086(PUSH); break; 
                case 0b111: id_string_opcode = STRING_INSTRUCTION8086(ROR); break; // no se vale
            }
            snprintf(string, size, "%s %s %s", 
                get_string_instruction_by_id_8086(id_string_opcode), (opcode == 0xff) ? "word" : "byte", // 1
                get_mod_rm_8086(instruction)); 

            return;
        }


        // obtener el string de la instruccion atrabes de su flags obteniada atraves de la tabla de instrucciones
        string_opcode = get_string_instruction_by_id_8086(
            (my_instruccion_8086[instruction->opcode1.opcode_byte.byte]) >> 24);

        if (instruction->flags & MOD_RM_REG_MASK){
            uint8_t opcode = instruction->opcode1.opcode_byte.byte;
            if(
                opcode == 0xc6 || opcode == 0xc7
            ) goto call_far_create;
            // si se trata de la instruccion LEA  reg, [BX + DI + mem16] solo hay una forma de analizarla:
            if (
                opcode == 0x8D
                ) instruction->opcode1.opcode_bits_final.d = 1;
            else if (opcode == 0xc4 || 0xc5 == opcode) {
                instruction->opcode1.opcode_bits_final.d = 1;
                instruction->opcode1.opcode_bits.b1 = 1; // estas instrucciones solo son en 16bits
            }

            if (instruction->opcode1.opcode_bits_final.d == 0) {
                if (instruction->flags_prefix != 0) {
                    
                    // la instruccion usa un registro de segmento
                    temp = string_modrm = malloc(10);
                    snprintf(string_modrm, size, "%s:%s", get_prefix_by_flags_prefix(instruction->flags_prefix), get_mod_rm_8086(instruction)); 
                } else string_modrm = get_mod_rm_8086(instruction);

                // para el opcode 0x8c el campo reg especifica un registro de segmento:
                string_rg    = (opcode == 0x8c) ?
                    reg_seg[instruction->Mod_rm.fields.reg] :
                    get_reg_8086(instruction->Mod_rm.fields.reg, instruction->opcode1.opcode_bits.b1);

            } else {
                 // para el opcode 0x8c el campo reg especifica un registro de segmento:
                string_modrm = (opcode == 0x8e) ?
                    reg_seg[instruction->Mod_rm.fields.reg] :
                    get_reg_8086(instruction->Mod_rm.fields.reg, instruction->opcode1.opcode_bits.b1);
                if (instruction->flags_prefix != 0) {
                    // la instruccion usa un registro de segmento
                    temp = string_rg = malloc(10);
                    snprintf(string_rg, size, "%s:%s", get_prefix_by_flags_prefix(instruction->flags_prefix), get_mod_rm_8086(instruction)); 
                } else string_rg = get_mod_rm_8086(instruction);
            }
            if (instruction->opcode1.opcode_byte.byte == 0x8F) {
                // solo para "pop word ptr [reg + reg]"
                snprintf(string, size, "%s %s %s", string_opcode, 
                    (instruction->opcode1.opcode_bits.b1 == 0) ? "byte" : "word",
                    string_rg
                );
            }else {
                snprintf(string, size, "%s %s %s, %s", string_opcode,
                    (instruction->opcode1.opcode_bits_final.d == 0 && instruction->Mod_rm.fields.mod != 0b11) 
                    ? (instruction->opcode1.opcode_bits.b1 == 0) ? "byte" : "word" : "",
                    string_modrm, string_rg ); 
            }
            if (temp != NULL) free(temp); // liberar la memoria reservada
            snprintf(string, size, string, instruction->displacement.ui16 ); 
            return;
        }
        uint64_t mem = "0x%x\0";
        if (
            (instruction->opcode1.opcode_byte.byte >= 0xa0 && instruction->opcode1.opcode_byte.byte <= 0xa3) ||
            (instruction->opcode1.opcode_byte.byte >= 0xa8 && instruction->opcode1.opcode_byte.byte <= 0xa9)
        ){
            mem = "[0x%x]\0";
        }
        if (instruction->flags & INMED16_MASK || instruction->flags & INMED8_MASK) {
            uint8_t opcode = instruction->opcode1.opcode_byte.byte;
            if(
                opcode == 0x9a || // call far
                (
                    // mov reg, inmed
                    opcode >= 0xB0 && opcode <= 0xBF) || (

                    // ret near inmed16
                    opcode == 0xc0 ) || (opcode == 0xc2) ||( // ret(0xc2) near inmed16 no documentado
                    // el opcode 0xc2 es ret near solo en el 8086

                    // ret far inmed16
                    opcode == 0xc8 ) || (opcode == 0xca)  // ret(0xca) far inmed16 no documentado
                    // el opcode 0xca es ret far solo en el 8086

            ) goto call_far_create;
            if (instruction->opcode1.opcode_bits_final.d == 1) {
                temp = string_modrm = malloc(10);
                snprintf(string_modrm, size, (char*)mem, instruction->immediate.ui16);
                string_rg    = get_reg_8086(instruction->Mod_rm.fields.reg, instruction->opcode1.opcode_bits.b1);
            } else {
                string_modrm = get_reg_8086(instruction->Mod_rm.fields.reg, instruction->opcode1.opcode_bits.b1);
                temp = string_rg = malloc(10);
                snprintf(string_rg, size, (char*)mem, instruction->immediate.ui16);
            }
            snprintf(string, size, "%s %s, %s", string_opcode,string_modrm, string_rg );
            free(temp); // liberar la memoria reservada
            return;
        }
        if (instruction->flags & REG_SEG_MASK) {
            switch (instruction->opcode1.opcode_byte.byte)
            {
                // 00 -> es, 01 -> cs,
                // 10 -> ss, 11 -> ds,
                // opreaciones push & pop
                case 0b00000110: // push es
                case 0b00000111: // pop  es
                case 0b00001110: // push cs
                case 0b00001111: // pop  cs
                case 0b00010110: // push ss
                case 0b00010111: // pop  ss
                case 0b00011110: // push ds
                case 0b00011111: // pop  ds
                    snprintf(string, size, "%s %s",  
                        // obtener si es push o pop
                        (instruction->opcode1.opcode_byte.byte & 0b00000001) 
                            ? instruction_8086[STRING_INSTRUCTION8086(POP)]
                            : instruction_8086[STRING_INSTRUCTION8086(PUSH)],
                        reg_seg[instruction->opcode1.opcode_byte.byte >> 3]);
                        // obtener el registro de segmento
                    return;
            
            default:
                break;
            }
        }
        if (instruction->flags & TTTN_MASK) {
            // todas las instrucciones de salto se describren aqui, estas usan un desplazamiento relativo
            // si son condicionales, el cual es un desplazamiento con signo.
            uint8_t bit_tttn = (instruction->opcode1.opcode_byte.byte >= 0x60 && instruction->opcode1.opcode_byte.byte <= 0x6f) ?
                instruction->opcode1.opcode_byte.byte & 0x0F : instruction->opcode1.opcode_byte.byte & 0x0F;
            /*
             * En el 8086 las instrucciones que van de 0x60 a 0x6f son instrucciones de salto condicionales
             * Las instrucciones que van desde 0x70 a 0x7f no documentadas, son validas en el 8086 como saltos condicionales
             * por lo que la instruccion 0x70 y la instruccion 0x60 son la misma, a de identificarse entonces los bits
             * tttn los cuales estan en uno de los nibbles -> (60...) 0110 tttn o (70...) 0111 tttn
             *
             * El desplazamiento de la instruccion de salto se calcula apartir de ella, por lo tanto se suma los
             * 2 bytes de la instruccion al desplazamiento
             */
            snprintf(string, size, "%s %hhd",
                        // obtener la instruccion via el ID flags de su tabla
                        instruction_8086[STRING_INSTRUCTION8086(JO) + bit_tttn],
                                (int8_t)instruction->displacement.ui8 +2
                            );
            return;
        }
        call_far_create:
        if (
            instruction->flags == 0 || instruction->flags & INMED8_MASK || 
            instruction->flags & INMED16_MASK || instruction->flags & UNDOCUMENTED_OPCODE_MASK
        ) { // si NONE_FLAGS
            volatile uint8_t disp_sub = 0;
            volatile register uint8_t opcode = instruction->opcode1.opcode_byte.byte;
            switch (opcode) {
                /*
                 * hay dos tipos de instrucciones que tienen NONE_FLAGS normalmente. las que no usan registros
                 * como aaa o aas, y las que si lo hacen como inc ax
                 */
                case 0xec: snprintf(string, size, "IN AL, DX"); return;
                case 0xed: snprintf(string, size, "IN AX, DX"); return;
                case 0xee: snprintf(string, size, "OUT AL, DX"); return;
                case 0xef: snprintf(string, size, "OUT AX, DX"); return;
                case 0xa4: snprintf(string, size, "MOVSB BYTE ES:[DI], BYTE [SI]"); return;
                case 0xa5: snprintf(string, size, "MOVSW WORD ES:[DI], WORD [SI]"); return;
                case 0xA6: snprintf(string, size, "CMPSB BYTE ES:[SI], BYTE [DI]"); return;
                case 0xA7: snprintf(string, size, "CMPSW WORD ES:[SI], WORD [DI]"); return;
                case 0xaa: snprintf(string, size, "STOSB BYTE ES:[DI], AL");        return;
                case 0xab: snprintf(string, size, "STOSW WORD ES:[DI], AX");        return;
                case 0xAC: snprintf(string, size, "LODSB AL, BYTE PTR [SI]");       return;
                case 0xAD: snprintf(string, size, "LODSW AX, WORD PTR [SI]");       return;
                case 0xAE: snprintf(string, size, "SCASB AL, BYTE PTR ES:[DI]");    return;
                case 0xAF: snprintf(string, size, "SCASW AX, WORD PTR ES:[DI]");    return;
                case 0xCB: snprintf(string, size, "RET FAR");                       return; // retf
                case 0xc0: // no documentada
                case 0xc2: snprintf(string, size, "RET NEAR 0x%04x", instruction->immediate.ui16);    return;

                // estos dos casos solo pueden usar mod 00
                case 0xc6: // mov  byte ptr [reg + reg], inmed8
                case 0xc7: // mov  word ptr [reg + reg], inmed16
                    snprintf(string, size, "%s %s %s, 0x%x",
                        // obtener la instruccion via el ID flags de su tabla
                            get_string_instruction_by_id_8086(
                                STRING_INSTRUCTION8086(MOV)),
                                (opcode == 0xc6) ? "byte" : "word",
                                Mod_rm_disp_8086[0][instruction->Mod_rm.fields.R_M],
                                instruction->immediate.ui16

                            );
                    return;
                case 0xc1: // ret (no documentada) solo para el 8086
                case 0xc3: // ret
                case 0xcc: // int 0x3
                case 0xce: // into
                case 0xcf: // iret
                case 0xd4: // aam
                case 0xd5: // aad
                case 0xd6: // salc
                case 0xd7: // xlat
                case 0x2F:
                case 0x27:
                case 0x37:
                case 0x3F:
                //case 0x90: // nop
                case 0x98: // cbw
                case 0x99: // cwd
                case 0x9b: // wait
                case 0x9c: // pushf
                case 0x9d: // popf
                case 0x9e: // sahf
                case 0x9f: // lahf
                case 0xf2: // repne/repnz
                case 0xf3: // rep/repe/repz
                case 0xf4: // hlt
                case 0xf5: // cmc
                case 0xf8: // clc
                case 0xf9: // stc
                case 0xfa: // cli
                case 0xfb: // sti
                case 0xfc: // cld
                case 0xfd: // std
                    // las instrucciones que no tienen flags no necesitan ser procesadas para estos casos:
                    snprintf(string, size, "%s",  
                            // obtener la instruccion via el ID flags de su tabla
                                get_string_instruction_by_id_8086(
                                    // acceder a las flags de la instruccion atraves de su opcode
                                    (my_instruccion_8086[opcode]
                                    // obtener el ID string de la instruccion actual
                                    & 0xff000000) >> 24)
                                );
                    return;
                    
                default: // el resto de caso son instrucciones a procesar de distinta manera

                    if      (opcode >= 0x40 && opcode <= 0x47) disp_sub = 0x40;
                        // inc ax; inc cx; inc dx; inc bx; inc sp; inc bp; inc si; inc di
                    else if (opcode >= 0x48 && opcode <= 0x4f) disp_sub = 0x48;
                        // dec ax; dec cx; dec dx; dec bx; dec sp; dec bp; dec si; dec di
                    else if (opcode >= 0x50 && opcode <= 0x57) disp_sub = 0x50;
                        // push ax; push cx; push dx; push bx; push sp; push bp; push si; push di
                    else if (opcode >= 0x58 && opcode <= 0x5f) disp_sub = 0x58;
                        // pop ax; pop cx; pop dx; pop bx; pop sp; pop bp; pop si; pop di
                    else if (opcode >= 0x90 && opcode <= 0x97) {
                        // xchg ax, ax; xchg ax, cx; xchg ax, dx; xchg ax, bx; xchg ax, sp; xchg ax, bp; xchg ax, si; xchg ax, di
                        snprintf(string, size, "%s AX, %s",
                        // obtener la instruccion via el ID flags de su tabla
                            get_string_instruction_by_id_8086(
                                STRING_INSTRUCTION8086(XCHG)),
                                reg_8086[1][instruction->opcode1.opcode_byte.byte - 0x90]
                            );
                        return;
                    } else if (opcode == 0x9a) {
                        snprintf(string, size, "%s FAR 0x%04x:0x%04x",
                        // obtener la instruccion via el ID flags de su tabla
                            get_string_instruction_by_id_8086(STRING_INSTRUCTION8086(CALL)),
                                instruction->displacement.ui16, instruction->immediate.ui16
                            );
                        return;
                    } else if (opcode == 0XC8 || opcode == 0xCA) {
                        snprintf(string, size, "%s FAR 0x%04x",
                        // obtener la instruccion via el ID flags de su tabla
                            get_string_instruction_by_id_8086(STRING_INSTRUCTION8086(RET)),
                                instruction->immediate.ui16
                            );
                        return;
                    } else if(opcode >= 0xB0 && opcode <= 0xBf ) {
                        snprintf(string, size, "%s %s, 0x%04x",
                        // obtener la instruccion via el ID flags de su tabla
                        get_string_instruction_by_id_8086(STRING_INSTRUCTION8086(MOV)),
                            // las instrucciones "mov   reg, inmed" son las siguientes:
                            // entre 0xB0 y 0xB7 se usa reg8 y desde 0xB8 a 0xB9 reg16
                            // al hacer (opcode & 0b1000) >> 3 indicaremos que el bit W sera activo si se da
                            // que el bit de la cuarta posicion esta activo. mientras (opcode - 0xB0) obtendra
                            // uno de los nibbles, donde se descibre el registro a usar, este va de 0x0 a 0xf
                            // pero la tabla reg_8086 es de 2 * 8
                            // 0xB0,0xB1,0xB2,0xB3,0xB4,0xB5,0xB6,0xB7,0xB8,0xB9,0xBA,0xBB,0xBC,0xBD,0xBE,0xBF,
                            reg_8086[(opcode & 0b1000) >> 3][(opcode - 0xB0) % 0b1000 ],
                            instruction->immediate.ui16
                        );
                        return;
                    }
                    else {
                        snprintf(string, size, "error unkonow opcode"); return;
                    }
                    // formatear la instruccion:
                    snprintf(string, size, "%s %s",
                        // obtener la instruccion via el ID flags de su tabla
                            get_string_instruction_by_id_8086(
                                // acceder a las flags de la instruccion atraves de su opcode
                                (my_instruccion_8086[opcode]
                                // obtener el ID string de la instruccion actual
                                & 0xff000000) >> 24),
                                reg_8086[1][opcode - disp_sub]
                            );
                    return;
            }
        } else snprintf(string, size, "error unkonow opcode"); 
    }
}
    


#endif