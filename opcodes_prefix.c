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
#include "./print_structs_format.h"

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

static char *get_string_instruction_by_id_8086(string_instrution_id_8086 id) {
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
    static char *strings[] = {
        [STRING_INSTRUCTION8086(ADD)]   = "ADD",
        [STRING_INSTRUCTION8086(OR)]    = "OR",
        [STRING_INSTRUCTION8086(ADC)]   = "ADC",
        [STRING_INSTRUCTION8086(SBB)]   = "SBB",
        [STRING_INSTRUCTION8086(AND)]   = "AND",
        [STRING_INSTRUCTION8086(DAA)]   = "DAA",
        [STRING_INSTRUCTION8086(SUB)]   = "SUB",
        [STRING_INSTRUCTION8086(DAS)]   = "DAS",
        [STRING_INSTRUCTION8086(XOR)]   = "XOR",
        [STRING_INSTRUCTION8086(AAA)]   = "AAA",
        [STRING_INSTRUCTION8086(CMP)]   = "CMP",
        [STRING_INSTRUCTION8086(AAS)]   = "AAS",
        [STRING_INSTRUCTION8086(JO)]    = "JO",
        [STRING_INSTRUCTION8086(JNO)]   = "JNO",
        [STRING_INSTRUCTION8086(JB)]    = "JB",
        [STRING_INSTRUCTION8086(JNB)]   = "JNB",
        [STRING_INSTRUCTION8086(JZ)]    = "JZ",
        [STRING_INSTRUCTION8086(JNZ)]   = "JNZ",
        [STRING_INSTRUCTION8086(JBE)]   = "JBE",
        [STRING_INSTRUCTION8086(JNBE)]  = "JNBE",
        [STRING_INSTRUCTION8086(JS)]    = "JS",
        [STRING_INSTRUCTION8086(JNS)]   = "JNS",
        [STRING_INSTRUCTION8086(JP)]    = "JP",
        [STRING_INSTRUCTION8086(JNP)]   = "JNP",
        [STRING_INSTRUCTION8086(JL)]    = "JL",
        [STRING_INSTRUCTION8086(JNL)]   = "JNL",
        [STRING_INSTRUCTION8086(JLE)]   = "JLE",
        [STRING_INSTRUCTION8086(JNLE)]  = "JNLE",
        [STRING_INSTRUCTION8086(TEST)]  = "TEST",
        [STRING_INSTRUCTION8086(LEA)]   = "LEA",
        [STRING_INSTRUCTION8086(PUSH)]  = "PUSH",
        [STRING_INSTRUCTION8086(POP)]   = "POP",
        [STRING_INSTRUCTION8086(NOP)]   = "NOP",
        [STRING_INSTRUCTION8086(XCHG)]  = "XCHG",
        [STRING_INSTRUCTION8086(CBW)]   = "CBW",
        [STRING_INSTRUCTION8086(CWD)]   = "CWD",
        [STRING_INSTRUCTION8086(CALL)]  = "CALL",
        [STRING_INSTRUCTION8086(WAIT)]  = "WAIT",
        [STRING_INSTRUCTION8086(PUSHF)] = "PUSHF",
        [STRING_INSTRUCTION8086(POPF)]  = "POPF",
        [STRING_INSTRUCTION8086(SAHF)]  = "SAHF",
        [STRING_INSTRUCTION8086(LAHF)]  = "LAHF",
        [STRING_INSTRUCTION8086(MOV)]   = "MOV",
        [STRING_INSTRUCTION8086(MOVS)]  = "MOVS",
        [STRING_INSTRUCTION8086(CMPS)]  = "CMPS",
        [STRING_INSTRUCTION8086(STOS)]  = "STOS",
        [STRING_INSTRUCTION8086(LODS)]  = "LODS",
        [STRING_INSTRUCTION8086(SCAS)]  = "SCAS",
        [STRING_INSTRUCTION8086(RET)]   = "RET",
        [STRING_INSTRUCTION8086(LES)]   = "LES",
        [STRING_INSTRUCTION8086(LDS)]   = "LDS",
        [STRING_INSTRUCTION8086(INT_3)] = "INT 3",
        [STRING_INSTRUCTION8086(INT)]   = "INT",
        [STRING_INSTRUCTION8086(INTO)]  = "INTO",
        [STRING_INSTRUCTION8086(IRET)]  = "IRET",
        [STRING_INSTRUCTION8086(ROL)]   = "ROL",
        [STRING_INSTRUCTION8086(ROR)]   = "ROR",
        [STRING_INSTRUCTION8086(RCL)]   = "RCL",
        [STRING_INSTRUCTION8086(RCR)]   = "RCR",
        [STRING_INSTRUCTION8086(SHL)]   = "SHL",
        [STRING_INSTRUCTION8086(SHR)]   = "SHR",
        [STRING_INSTRUCTION8086(SAR)]   = "SAR",
        [STRING_INSTRUCTION8086(AAM)]   = "AAM",
        [STRING_INSTRUCTION8086(SALC)]  = "SALC",
        [STRING_INSTRUCTION8086(JMP)] = "JMP",
        [STRING_INSTRUCTION8086(AAD)]   = "AAD",
        [STRING_INSTRUCTION8086(XLAT)]  = "XLAT",
        [STRING_INSTRUCTION8086(CLD)] = "CLD",
        [STRING_INSTRUCTION8086(ESC)]   = "ESC",
        [STRING_INSTRUCTION8086(LOOPNE)]    = "LOOPNE",
        [STRING_INSTRUCTION8086(LOOPE)] = "LOOPE",
        [STRING_INSTRUCTION8086(LOOP)] = "LOOP",
        [STRING_INSTRUCTION8086(JCXZ)]  = "JCXZ",
        [STRING_INSTRUCTION8086(IN)]    = "IN",
        [STRING_INSTRUCTION8086(OUT)]   = "OUT",
        [STRING_INSTRUCTION8086(REPNE)] = "REPNE",
        [STRING_INSTRUCTION8086(REP)]   = "REP",
        [STRING_INSTRUCTION8086(LOCK)]  = "LOCK",
        [STRING_INSTRUCTION8086(CMD)]   = "CMD",
        [STRING_INSTRUCTION8086(HLT)]   = "HLT",
        [STRING_INSTRUCTION8086(CMC)]   = "CMC",
        [STRING_INSTRUCTION8086(NOT)]   = "NOT",
        [STRING_INSTRUCTION8086(NEG)]   = "NEG",
        [STRING_INSTRUCTION8086(MUL)]   = "MUL",
        [STRING_INSTRUCTION8086(IMUL)]  = "IMUL",
        [STRING_INSTRUCTION8086(DIV)]   = "DIV",
        [STRING_INSTRUCTION8086(IDIV)]  = "IDIV",
        [STRING_INSTRUCTION8086(CLC)]   = "CLC",
        [STRING_INSTRUCTION8086(STC)]   = "STC",
        [STRING_INSTRUCTION8086(CLI)]   = "CLI",
        [STRING_INSTRUCTION8086(STI)]   = "STI",
        [STRING_INSTRUCTION8086(CLD)]   = "CLD",
        [STRING_INSTRUCTION8086(STD)]   = "STD",
        [STRING_INSTRUCTION8086(INC)]   = "INC",
        [STRING_INSTRUCTION8086(DEC)]    = "DEC"
        
    };

    if (id >= STRING_INSTRUCTION8086(ADD) && id <= STRING_INSTRUCTION8086(DEC)) return strings[id];
    else return "error - not exits this instruttion.";

}

#endif