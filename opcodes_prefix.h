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
#ifndef __OPCODES_PREFIX_H_
#define __OPCODES_PREFIX_H_
/* 
 * Formato general de instrucciones x86 (http://www.c-jump.com/CIS77/images/x86_instruction_format.png): 
 * 
 *      |-----------------|---------|--------|----------------------------------------------------------|-------|----------------|-------------|
 *      | numero de bytes |  0 a 4  | 1 a 3  |                                0 o 1                     | 0 o 1 |  0, 1,  2 o 4  | 0, 1, 2 o 4 |  
 *      | valores         | prefijo | opcode |                               Mod-RM                     |  SIB  | desplazamiento |  inmediato  |
 *      |-----------------|---------|------v-|-------------------------------v--------------------------|---v---|----------------|-------------|
 *           ______________________________|                                 |                              |
 *          |                                                                |                              |
 *        |-v---|------------------|-----------|-----------------------|  |--v--|-----|-------|-------|  |--v--|-------|-------|-------|
 *        | Bit |  7  6 5  4 3  2  |     1     |            0          |  | Bit | 7 6 | 5 4 3 | 2 1 0 |  | Bit |  7 6  | 5 4 3 | 2 1 0 |
 *        | uso | main bits opcode | direccion | Longitud del operando |  | Uso | MOD |  REG  |  R/M  |  | Uso | SCALE | INDEX |  BASE |
 *        |-----|------------------|-----------|-----------------------|  |-----|-----|-------|-------|  |-----|-------|-------|-------|
 *             
 */
#include <stdint.h>

#include "./opcodes/8086.h"

#include "./DebugLibC/time_code.h"

typedef enum string_instrution_id_64 {

    // AAA – ASCII Adjust after Addition 0011 0111
    STRING_AAA,

    // AAD – ASCII Adjust AX before Division 1101 0101 : 0000 1010
    STRING_AAD,

    // AAM – ASCII Adjust AX after Multiply 1101 0100 : 0000 1010
    STRING_AAM,

    // AAS – ASCII Adjust AL after Subtraction 0011 1111
    STRING_AAS,

    /*
     * ADC – ADD with Carry.
     * register1 to register2 0001 000w : 11 reg1 reg2.
     * register2 to register1 0001 001w : 11 reg1 reg2.
     * memory to register 0001 001w : mod reg r/m.
     * register to memory 0001 000w : mod reg r/m.
     * immediate to register 1000 00sw : 11 010 reg : immediate data.
     * immediate to AL, AX, or EAX 0001 010w : immediate data.
     * immediate to memory 1000 00sw : mod 010 r/m : immediate data.
     */
    STRING_ADC,

    /*
     * ADD – Add.
     * register1 to register2 0000 000w : 11 reg1 reg2.
     * register2 to register1 0000 001w : 11 reg1 reg2.
     * memory to register 0000 001w : mod reg r/m.
     * register to memory 0000 000w : mod reg r/m.
     * immediate to register 1000 00sw : 11 000 reg : immediate data.
     * immediate to AL, AX, or EAX 0000 010w : immediate data.
     * immediate to memory 1000 00sw : mod 000 r/m : immediate data.
     */
    STRING_ADD,

    /*
     * AND – Logical AND.
     * register1 to register2 0010 000w : 11 reg1 reg2.
     * register2 to register1 0010 001w : 11 reg1 reg2.
     * memory to register 0010 001w : mod reg r/m.
     * register to memory 0010 000w : mod reg r/m.
     * immediate to register 1000 00sw : 11 100 reg : immediate data.
     * immediate to AL, AX, or EAX 0010 010w : immediate data.
     * immediate to memory 1000 00sw : mod 100 r/m : immediate data.
     */
    STRING_AND,

    /*
     * ARPL – Adjust RPL Field of Selector.
     * from register 0110 0011 : 11 reg1 reg2.
     * from memory 0110 0011 : mod reg r/m.
     */
    STRING_ARPL,

    // BOUND – Check Array Against Bounds 0110 0010 : modA reg r/m
    STRING_BOUND,

    /*
     * BSF – Bit Scan Forward.
     * register1, register2 0000 1111 : 1011 1100 : 11 reg1 reg2.
     * memory, register 0000 1111 : 1011 1100 : mod reg r/m.
     */
    STRING_BSF,

    /*
     * BSR – Bit Scan Reverse.
     * register1, register2 0000 1111 : 1011 1101 : 11 reg1 reg2.
     * memory, register 0000 1111 : 1011 1101 : mod reg r/m.
     */
    STRING_BSR,

    // BSWAP – Byte Swap 0000 1111 : 1100 1 reg
    STRING_BSWAP,

    /*
     * BT – Bit Test.
     * register, immediate 0000 1111 : 1011 1010 : 11 100 reg: imm8 data.
     * memory, immediate 0000 1111 : 1011 1010 : mod 100 r/m : imm8 data.
     * register1, register2 0000 1111 : 1010 0011 : 11 reg2 reg1.
     * memory, reg 0000 1111 : 1010 0011 : mod reg r/m.
     */
    STRING_BT,

    /*
     * BTC – Bit Test and Complement.
     * register, immediate 0000 1111 : 1011 1010 : 11 111 reg: imm8 data.
     * memory, immediate 0000 1111 : 1011 1010 : mod 111 r/m : imm8 data.
     * register1, register2 0000 1111 : 1011 1011 : 11 reg2 reg1.
     * memory, reg 0000 1111 : 1011 1011 : mod reg r/m.
     */
    STRING_BTC,

    /*
     * BTR – Bit Test and Reset,
     * register, immediate 0000 1111 : 1011 1010 : 11 110 reg: imm8 data,
     * memory, immediate 0000 1111 : 1011 1010 : mod 110 r/m : imm8 data,
     * register1, register2 0000 1111 : 1011 0011 : 11 reg2 reg1,
     * memory, reg 0000 1111 : 1011 0011 : mod reg r/m,
     */
    STRING_BTR,

    /*
     * BTS – Bit Test and Set.
     * register, immediate 0000 1111 : 1011 1010 : 11 101 reg: imm8 data.
     * memory, immediate 0000 1111 : 1011 1010 : mod 101 r/m : imm8 data.
     * register1, register2 0000 1111 : 1010 1011 : 11 reg2 reg1.
     * memory, reg 0000 1111 : 1010 1011 : mod reg r/m.
     */
    STRING_BTS,

    /*
     * CALL – Call Procedure (in same segment).
     * direct 1110 1000 : full displacement.
     * register indirect 1111 1111 : 11 010 reg.
     * memory indirect 1111 1111 : mod 010 r/m.
     */
    STRING_CALL,      

    /*
     * CALL – Call Procedure (in other segment).
     * direct 1001 1010 : unsigned full offset, selector.
     * indirect 1111 1111 : mod 011 r/m.
     */
    STRING_CALL_FAR, 

    // CBW – Convert Byte to Word 1001 1000
    STRING_CBW,

    // CDQ – Convert Doubleword to Qword 1001 1001
    STRING_CDQ,

    // CLC – Clear Carry Flag 1111 1000
    STRING_CLC,

    // CLD – Clear Direction Flag 1111 1100
    STRING_CLD,

    // CLI – Clear Interrupt Flag 1111 1010
    STRING_CLI,

    // CLTS – Clear Task-Switched Flag in CR0 0000 1111 : 0000 0110
    STRING_CLTS,

    // CMC – Complement Carry Flag 1111 0101
    STRING_CMC,

    /*
     * CMP – Compare Two Operands.
     * register1 with register2 0011 100w : 11 reg1 reg2.
     * register2 with register1 0011 101w : 11 reg1 reg2.
     * memory with register 0011 100w : mod reg r/m.
     * register with memory 0011 101w : mod reg r/m.
     * immediate with register 1000 00sw : 11 111 reg : immediate data.
     * immediate with AL, AX, or EAX 0011 110w : immediate data.
     * immediate with memory 1000 00sw : mod 111 r/m : immediate data.
     */
    STRING_CMP,

    // CMPS/CMPSB/CMPSW/CMPSD – Compare String Operands 1010 011w
    STRING_CMPS, 
                STRING_CMPSB = STRING_CMPS,
                STRING_CMPSW = STRING_CMPS,
                STRING_CMPSD = STRING_CMPS,
    
    /*
     * CMPXCHG – Compare and Exchange.
     * register1, register2 0000 1111 : 1011 000w : 11 reg2 reg1.
     * memory, register 0000 1111 : 1011 000w : mod reg r/m.
     */
    STRING_CMPXCHG,

    // CPUID – CPU Identification 0000 1111 : 1010 0010
    STRING_CPUID,

    // CWD – Convert Word to Doubleword 1001 1001
    STRING_CWD,

    // CWDE – Convert Word to Doubleword 1001 1000
    STRING_CWDE,

    // DAA – Decimal Adjust AL after Addition 0010 0111
    STRING_DAA,

    // DAS – Decimal Adjust AL after Subtraction 0010 1111
    STRING_DAS,

    /*
     * DEC – Decrement by 1.
     * register 1111 111w : 11 001 reg.
     * register (alternate encoding) 0100 1 reg.
     * memory 1111 111w : mod 001 r/m.
     */
    STRING_DEC,

    /*
     * DIV – Unsigned Divide.
     * AL, AX, or EAX by register 0100 000B 1111 011w : 11 110 reg.
     * Divide RDX:RAX by qwordregister 0100 100B 1111 0111 : 11 110 qwordreg.
     * AL, AX, or EAX by memory 0100 00XB 1111 011w : mod 110 r/m.
     * Divide RDX:RAX by memory64 0100 10XB 1111 0111 : mod 110 r/m.
     */
    STRING_DIV,

    // HLT – Halt 1111 0100
    STRING_HLT,

    /* 
     * IDIV – Signed Divide.
     * AL, AX, or EAX by register 1111 011w : 11 111 reg.
     * AL, AX, or EAX by memory 1111 011w : mod 111 r/m.
     */
    STRING_IDIV,

    /*
     * IMUL – Signed Multiply.
     * AL, AX, or EAX with register 1111 011w : 11 101 reg.
     * AL, AX, or EAX with memory 1111 011w : mod 101 reg.
     * register1 with register2 0000 1111 : 1010 1111 : 11 : reg1 reg2.
     * register with memory 0000 1111 : 1010 1111 : mod reg r/m.
     * register1 with immediate to register2 0110 10s1 : 11 reg1 reg2 : immediate data.
     * memory with immediate to register 0110 10s1 : mod reg r/m : immediate data.
     */
    STRING_IMUL,

    /*
     * IN – Input From Port.
     * fixed port 1110 010w : port number.
     * variable port 1110 110w.
     */
    STRING_IN,

    /*
     * INC – Increment by 1.
     * reg 1111 111w : 11 000 reg.
     * reg (alternate encoding) 0100 0 reg.
     * memory 1111 111w : mod 000 r/m.
     */
    STRING_INC,

    // INS – Input from DX Port 0110 110w
    STRING_INS,

    // INT n – Interrupt Type n 1100 1101 : type
    STRING_INT_n, 

    // INT   – Single-Step Interrupt 3 1100 1100
    STRING_INT_3, 

    // INTO – Interrupt 4 on Overflow 1100 1110
    STRING_INTO,  

    // INVD – Invalidate Cache 0000 1111 : 0000 1000
    STRING_INVD,

    // INVLPG – Invalidate TLB Entry 0000 1111 : 0000 0001 : mod 111 r/m
    STRING_INVLPG,

    // INVPCID – Invalidate Process-Context Identifier 0110 0110:0000 1111:0011 1000:1000 0010: mod reg r/m
    STRING_INVPCID,

    // IRET/IRETD – Interrupt Return 1100 1111
    STRING_IRET,
        STRING_IRETD = STRING_IRET,

    /*
     * Jcc – Jump if Condition is Met.
     * 8-bit displacement 0111 tttn : 8-bit displacement.
     * full displacement 0000 1111 : 1000 tttn : full displacement.
     */
    STRING_JCC,

    /*
     * JCXZ/JECXZ – Jump on CX/ECX Zero
     *  Address-size prefix differentiates JCXZ
     *  and JECXZ.
     * 1110 0011 : 8-bit displacement.
     */
    STRING_JCXZ,
        STRING_JECXZ = STRING_JCXZ,

    /*
     * JMP – Unconditional Jump (to same segment).
     * short 1110 1011 : 8-bit displacement.
     * direct 1110 1001 : full displacement.
     * register indirect 1111 1111 : 11 100 reg.
     * memory indirect 1111 1111 : mod 100 r/m.
     */
    STRING_JMP,    

    /*
     * JMP – Unconditional Jump (to other segment).
     * direct intersegment 1110 1010 : unsigned full offset, selector.
     * indirect intersegment 1111 1111 : mod 101 r/m.
     */  
    STRING_JMP_FAR,  
    
    // LAHF – Load Flags into AHRegister 1001 1111
    STRING_LAHF,

    /*
     * LAR – Load Access Rights Byte.
     * from register 0000 1111 : 0000 0010 : 11 reg1 reg2.
     * from memory 0000 1111 : 0000 0010 : mod reg r/m.
     */
    STRING_LAR,

    // LDS – Load Pointer to DS 1100 0101 : modA,B reg r/m
    STRING_LDS,

    // LEA – Load Effective Address 1000 1101 : modA reg r/m
    STRING_LEA,

    // LEAVE – High Level Procedure Exit 1100 1001
    STRING_LEAVE,

    // LES – Load Pointer to ES 1100 0100 : modA,B reg r/m
    STRING_LES,

    // LFS – Load Pointer to FS 0000 1111 : 1011 0100 : modA reg r/m
    STRING_LFS,

    // LGDT – Load Global Descriptor Table Register 0000 1111 : 0000 0001 : modA 010 r/
    STRING_LGDT,

    // LGS – Load Pointer to GS 0000 1111 : 1011 0101 : modA reg r/m
    STRING_LGS,

    // LIDT – Load Interrupt Descriptor Table Register 0000 1111 : 0000 0001 : modA 011 r/m
    STRING_LIDT,

    /*
     * LLDT – Load Local Descriptor Table Register.
     * LDTR from register 0000 1111 : 0000 0000 : 11 010 reg.
     * LDTR from memory 0000 1111 : 0000 0000 : mod 010 r/m.
     */
    STRING_LLDT,

    /*
     * LMSW – Load Machine Status Word.
     * from register 0000 1111 : 0000 0001 : 11 110 reg.
     * from memory 0000 1111 : 0000 0001 : mod 110 r/m.
     */
    STRING_LMSW,

    // LOCK – Assert LOCK# Signal Prefix 1111 0000    
    STRING_LOCK,

    // LODS/LODSB/LODSW/LODSD – Load String Operand 1010 110w
    STRING_LODS,
        STRING_LODSB = STRING_LODS,
        STRING_LODSW = STRING_LODS,
        STRING_LODD  = STRING_LODS,

    // LOOP – Loop Count 1110 0010 : 8-bit displacement
    STRING_LOOP,

    // LOOPZ/LOOPE – Loop Count while Zero/Equal 1110 0001 : 8-bit displacement
    STRING_LOOPZ,
        STRING_LOOPE = STRING_LOOPZ,
        
    // LOOPNZ/LOOPNE – Loop Count while not Zero/Equal 1110 0000 : 8-bit displacement
    STRING_LOOPNZ,
        STRING_LOOPNE = STRING_LOOPNZ,

    /*
     * LSL – Load Segment Limit.
     * from register 0000 1111 : 0000 0011 : 11 reg1 reg2.
     * from memory 0000 1111 : 0000 0011 : mod reg r/m.
     */
    STRING_LSL,

    // LSS – Load Pointer to SS 0000 1111 : 1011 0010 : modA reg r/m
    STRING_LSS,

    /*
     * LTR – Load Task Register.
     * from register 0000 1111 : 0000 0000 : 11 011 reg.
     * from memory 0000 1111 : 0000 0000 : mod 011 r/m.
     */
    STRING_LTR,

    /*
     * MOV – Move Data.
     * register1 to register2 1000 100w : 11 reg1 reg2.
     * register2 to register1 1000 101w : 11 reg1 reg2.
     * memory to reg 1000 101w : mod reg r/m.
     * reg to memory 1000 100w : mod reg r/m.
     * immediate to register 1100 011w : 11 000 reg : immediate data.
     * immediate to register (alternate encoding) 1011 w reg : immediate data.
     * immediate to memory 1100 011w : mod 000 r/m : immediate data.
     * memory to AL, AX, or EAX 1010 000w : full displacement.
     * AL, AX, or EAX to memory 1010 001w : full displacement.
     * 
     * MOV – Move to/from Control Registers.
     * CR0 from register 0000 1111 : 0010 0010 : -- 000 reg.
     * CR2 from register 0000 1111 : 0010 0010 : -- 010reg.
     * CR3 from register 0000 1111 : 0010 0010 : -- 011 reg.
     * CR4 from register 0000 1111 : 0010 0010 : -- 100 reg.
     * register from CR0-CR4 0000 1111 : 0010 0000 : -- eee reg.
     * 
     * MOV – Move to/from Debug Registers.
     * DR0-DR3 from register 0000 1111 : 0010 0011 : -- eee reg.
     * DR4-DR5 from register 0000 1111 : 0010 0011 : -- eee reg.
     * DR6-DR7 from register 0000 1111 : 0010 0011 : -- eee reg.
     * register from DR6-DR7 0000 1111 : 0010 0001 : -- eee reg.
     * register from DR4-DR5 0000 1111 : 0010 0001 : -- eee reg.
     * register from DR0-DR3 0000 1111 : 0010 0001 : -- eee reg.
     * 
     * MOV – Move to/from Segment Registers.
     * register to segment register 1000 1110 : 11 sreg3 reg.
     * register to SS 1000 1110 : 11 sreg3 reg.
     * memory to segment reg 1000 1110 : mod sreg3 r/m.
     * memory to SS 1000 1110 : mod sreg3 r/m.
     * segment register to register 1000 1100 : 11 sreg3 reg.
     * segment register to memory 1000 1100 : mod sreg3 r/m.
    */
    STRING_MOV,

    /*
     * MOVBE – Move data after swapping bytes.
     * memory to register 0000 1111 : 0011 1000:1111 0000 : mod reg r/m.
     * register to memory 0000 1111 : 0011 1000:1111 0001 : mod reg r/m.
     */
    STRING_MOVBE,

    // MOVS/MOVSB/MOVSW/MOVSD – Move Data from String to String 1010 010w
    STRING_MOVS,
        STRING_MOVSB = STRING_MOVS,
        STRING_MOVSW = STRING_MOVS,
        STRING_MOVSD = STRING_MOVS,

    /*
     * MOVSX – Move with Sign-Extend.
     * memory to reg 0000 1111 : 1011 111w : mod reg r/m.
     */
    STRING_MOVSX,

    /*
     * MOVZX – Move with Zero-Extend.
     * register2 to register1 0000 1111 : 1011 011w : 11 reg1 reg2.
     * memory to register 0000 1111 : 1011 011w : mod reg r/m.
     */
    STRING_MOVZX,

    /*
     * MUL – Unsigned Multiply.
     * AL, AX, or EAX with register 1111 011w : 11 100 reg.
     * AL, AX, or EAX with memory 1111 011w : mod 100 r/m.
     */
    STRING_MUL,

    /*
     * NEG – Two's Complement Negation.
     * register 1111 011w : 11 011 reg.
     * memory 1111 011w : mod 011 r/m.
     */
    STRING_NEG,

    /*
     * NOP – No Operation 1001 0000.
     * NOP – Multi-byte No Operation1.
     * register 0000 1111 0001 1111 : 11 000 reg.
     * memory 0000 1111 0001 1111 : mod 000 r/m.
     */
    STRING_NOP,

    /* 
     * NOT – One's Complement Negation.
     * register 1111 011w : 11 010 reg.
     * memory 1111 011w : mod 010 r/m.
     */
    STRING_NOT,

    /*
     * OR – Logical Inclusive OR.
     * register1 to register2 0000 100w : 11 reg1 reg2.
     * register2 to register1 0000 101w : 11 reg1 reg2.
     * memory to register 0000 101w : mod reg r/m.
     * register to memory 0000 100w : mod reg r/m.
     * immediate to register 1000 00sw : 11 001 reg : immediate data.
     * immediate to AL, AX, or EAX 0000 110w : immediate data.
     * immediate to memory 1000 00sw : mod 001 r/m : immediate data.
     */
    STRING_OR,

    /*
     * OUT – Output to Port.
     * fixed port 1110 011w : port number.
     * variable port 1110 111w.
     */
    STRING_OUT,

    // OUTS – Output to DX Port 0110 111w
    STRING_OUTS,

    /*
     * POP – Pop a Word from the Stack.
     * register 1000 1111 : 11 000 reg.
     * register (alternate encoding) 0101 1 reg.
     * memory 1000 1111 : mod 000 r/m.
     * 
     * POP – Pop a Segment Register from the Stack (Note: CS cannot be sreg2 in this usage.).
     * segment register DS, ES 000 sreg2 111.
     * segment register SS 000 sreg2 111.
     * segment register FS, GS 0000 1111: 10 sreg3 001.
     */
    STRING_POP,

    // POPA/POPAD – Pop All General Registers 0110 0001
    STRING_POPA,
        STRING_POPAD = STRING_POPA,

    // POPF/POPFD – Pop Stack into FLAGS or EFLAGS Register 1001 1101
    STRING_POPF,
        STRING_POPFD = STRING_POPF,

    /*
     * PUSH – Push Operand onto the Stack.
     * register 1111 1111 : 11 110 reg.
     * register (alternate encoding) 0101 0 reg.
     * memory 1111 1111 : mod 110 r/m.
     * immediate 0110 10s0 : immediate data.
     * 
     * PUSH – Push Segment Register onto the Stack.
     * segment register CS,DS,ES,SS 000 sreg2 110.
     * segment register FS,GS 0000 1111: 10 sreg3 000.
     */
    STRING_PUSH,

    // PUSHA/PUSHAD – Push All General Registers 0110 0000
    STRING_PUSHA,
        STRING_PUSHAD = STRING_PUSHA,

    // PUSHF/PUSHFD – Push Flags Register onto the Stack 1001 1100
    STRING_PUSHF,
        STRING_PUSHFD = STRING_PUSHF,
    
    /*
     * RCL – Rotate thru Carry Left.
     * register by 1 1101 000w : 11 010 reg.
     * memory by 1 1101 000w : mod 010 r/m.
     * register by CL 1101 001w : 11 010 reg.
     * memory by CL 1101 001w : mod 010 r/m.
     * register by immediate count 1100 000w : 11 010 reg : imm8 data.
     * memory by immediate count 1100 000w : mod 010 r/m : imm8 data.
     */
    STRING_RCL,

    /*
     * RCR – Rotate thru Carry Right.
     * register by 1 1101 000w : 11 011 reg.
     * memory by 1 1101 000w : mod 011 r/m.
     * register by CL 1101 001w : 11 011 reg.
     * memory by CL 1101 001w : mod 011 r/m.
     * register by immediate count 1100 000w : 11 011 reg : imm8 data.
     * memory by immediate count 1100 000w : mod 011 r/m : imm8 data.
     */
    STRING_RCR,

    // RDMSR – Read from Model-Specific Register 0000 1111 : 0011 0010
    STRING_RDMSR,

    // RDPMC – Read Performance Monitoring Counters 0000 1111 : 0011 0011
    STRING_RDPMC,

    // RDTSC – Read Time-Stamp Counter 0000 1111 : 0011 0001
    STRING_RDTSC,

    // RDTSCP – Read Time-Stamp Counter and Processor ID 0000 1111 : 0000 0001: 1111 1001
    STRING_RDTSCP,

    // REP INS – Input String 1111 0011 : 0110 110w
    STRING_REP_INS,

    // REP LODS – Load String 1111 0011 : 1010 110w
    STRING_REP_LODS,

    // REP MOVS – Move String 1111 0011 : 1010 010w
    STRING_REP_MOVS,

    // REP OUTS – Output String 1111 0011 : 0110 111w
    STRING_REP_OUTS,

    // REP STOS – Store String 1111 0011 : 1010 101w
    STRING_REP_STOS,

    // REPE CMPS – Compare String 1111 0011 : 1010 011w
    STRING_REPE_CMPS,

    // REPE SCAS – Scan String 1111 0011 : 1010 111w
    STRING_REPE_SCAS,

    // REPNE CMPS – Compare String 1111 0010 : 1010 011w
    STRING_REPNE_CMPS,

    // REPNE SCAS – Scan String 1111 0010 : 1010 111w
    STRING_REPNE_SCAS,

    /*
     * RET – Return from Procedure (to same segment).
     * no argument 1100 0011.
     * adding immediate to SP 1100 0010 : 16-bit displacement.
     */
    STRING_RET,

    /*
     * RET – Return from Procedure (to other segment).
     * intersegment           -> 1100 1011.
     * adding immediate to SP -> 1100 1010 : 16-bit displacement.
     */
    STRING_RETF,

    /*
     * ROL – Rotate Left.
     * register by 1 1101 000w : 11 000 reg.
     * memory by 1 1101 000w : mod 000 r/m.
     * register by CL 1101 001w : 11 000 reg.
     * memory by CL 1101 001w : mod 000 r/m.
     * register by immediate count 1100 000w : 11 000 reg : imm8 data.
     * memory by immediate count 1100 000w : mod 000 r/m : imm8 data.
     */
    STRING_ROL,

    /*
     * ROR – Rotate Right.
     * register by 1 1101 000w : 11 001 reg.
     * memory by 1 1101 000w : mod 001 r/m.
     * register by CL 1101 001w : 11 001 reg.
     * memory by CL 1101 001w : mod 001 r/m.
     * register by immediate count 1100 000w : 11 001 reg : imm8 data.
     * memory by immediate count 1100 000w : mod 001 r/m : imm8 data.
     */
    STRING_ROR,

    // RSM – Resume from System Management Mode 0000 1111 : 1010 1010
    STRING_RSM,

    // SAHF – Store AH into Flags 1001 1110
    STRING_SAHF,

    // SAL – Shift Arithmetic Left same instruction as SHL
    STRING_SAL,

    /*
     * SAR – Shift Arithmetic Right.
     * register by 1 1101 000w : 11 111 reg.
     * memory by 1 1101 000w : mod 111 r/m.
     * register by CL 1101 001w : 11 111 reg.
     * memory by CL 1101 001w : mod 111 r/m.
     * register by immediate count 1100 000w : 11 111 reg : imm8 data.
     * memory by immediate count 1100 000w : mod 111 r/m : imm8 data.
     */
    STRING_SAR,

    /*
     * SBB – Integer Subtraction with Borrow.
     * register1 to register2 0001 100w : 11 reg1 reg2.
     * register2 to register1 0001 101w : 11 reg1 reg2.
     * memory to register 0001 101w : mod reg r/m.
     * register to memory 0001 100w : mod reg r/m.
     * immediate to register 1000 00sw : 11 011 reg : immediate data.
     * immediate to AL, AX, or EAX 0001 110w : immediate data.
     * immediate to memory 1000 00sw : mod 011 r/m : immediate data.
     */
    STRING_SBB,

    // SCAS/SCASB/SCASW/SCASD – Scan String 1010 111w
    STRING_SCAS,
        STRING_SCASB = STRING_SCAS,
        STRING_SCASW = STRING_SCAS,
        STRING_SCASD = STRING_SCAS,
    
    /*
     * SETcc – Byte Set on Condition.
     * register 0000 1111 : 1001 tttn : 11 000 reg.
     * memory 0000 1111 : 1001 tttn : mod 000 r/m.
     */
    STRING_SETcc,

    // SGDT – Store Global Descriptor Table Register 0000 1111 : 0000 0001 : modA 000 r/m
    STRING_SGDT,

    /*
     * SHL – Shift Left.
     * register by 1 1101 000w : 11 100 reg.
     * memory by 1 1101 000w : mod 100 r/m.
     * register by CL 1101 001w : 11 100 reg.
     * memory by CL 1101 001w : mod 100 r/m.
     * register by immediate count 1100 000w : 11 100 reg : imm8 data.
     * memory by immediate count 1100 000w : mod 100 r/m : imm8 data.
     */
    STRING_SHL,

    /*
     * SHLD – Double Precision Shift Left.
     * register by immediate count 0000 1111 : 1010 0100 : 11 reg2 reg1 : imm8.
     * memory by immediate count 0000 1111 : 1010 0100 : mod reg r/m : imm8.
     * register by CL 0000 1111 : 1010 0101 : 11 reg2 reg1.
     * memory by CL 0000 1111 : 1010 0101 : mod reg r/m.
     */
    STRING_SHLD,

    /*
     * SHR – Shift Right.
     * register by 1 1101 000w : 11 101 reg.
     * memory by 1 1101 000w : mod 101 r/m.
     * register by CL 1101 001w : 11 101 reg.
     * memory by CL 1101 001w : mod 101 r/m.
     * register by immediate count 1100 000w : 11 101 reg : imm8 data.
     * memory by immediate count 1100 000w : mod 101 r/m : imm8 data.
     */
    STRING_SHR,

    /*
     * SHRD – Double Precision Shift Right.
     * register by immediate count 0000 1111 : 1010 1100 : 11 reg2 reg1 : imm8.
     * memory by immediate count 0000 1111 : 1010 1100 : mod reg r/m : imm8.
     * register by CL 0000 1111 : 1010 1101 : 11 reg2 reg1.
     * memory by CL 0000 1111 : 1010 1101 : mod reg r/m.
     */
    STRING_SHRD,

    // SIDT – Store Interrupt Descriptor Table Register 0000 1111 : 0000 0001 : modA 001 r/m
    STRING_SIDT,

    /*
     * SLDT – Store Local Descriptor Table Register.
     * to register 0000 1111 : 0000 0000 : 11 000 reg.
     * to memory 0000 1111 : 0000 0000 : mod 000 r/m.
     */
    STRING_SLDT,

    /*
     * SMSW – Store Machine Status Word.
     * to register 0000 1111 : 0000 0001 : 11 100 reg.
     * to memory 0000 1111 : 0000 0001 : mod 100 r/m.
    */
    STRING_SMSW,

    // STC – Set Carry Flag 1111 1001
    STRING_STC,

    // STD – Set Direction Flag 1111 1101
    STRING_STD,

    // STI – Set Interrupt Flag 1111 1011
    STRING_STI,

    // STOS/STOSB/STOSW/STOSD – Store String Data 1010 101w
    STRING_STOS,
        STRING_STOSB = STRING_STOS,
        STRING_STOSW = STRING_STOS,
        STRING_STOSD = STRING_STOS,

    /*
     * STR – Store Task Register.
     * to register 0000 1111 : 0000 0000 : 11 001 reg.
     * to memory 0000 1111 : 0000 0000 : mod 001 r/m.
     */
    STRING_STR,

    /*
     * SUB – Integer Subtraction.
     * register1 to register2 0010 100w : 11 reg1 reg2.
     * register2 to register1 0010 101w : 11 reg1 reg2.
     * memory to register 0010 101w : mod reg r/m.
     * register to memory 0010 100w : mod reg r/m.
     * immediate to register 1000 00sw : 11 101 reg : immediate data.
     * immediate to AL, AX, or EAX 0010 110w : immediate data.
     * immediate to memory 1000 00sw : mod 101 r/m : immediate data.
     */
    STRING_SUB,

    /*
     * TEST – Logical Compare.
     * register1 and register2 1000 010w : 11 reg1 reg2.
     * memory and register 1000 010w : mod reg r/m.
     * immediate and register 1111 011w : 11 000 reg : immediate data.
     * immediate and AL, AX, or EAX 1010 100w : immediate data.
     * immediate and memory 1111 011w : mod 000 r/m : immediate data.
     */
    STRING_TEST,
    
    /*
     * UD0 – Undefined instruction 0000 1111 : 1111 1111. -> 0f ff.
     * UD1 – Undefined instruction 0000 1111 : 1011 1001. -> 0f b9.
     * UD2 – Undefined instruction 0000 1111 : 0000 1011. -> 0f 0b.
     */
    STRING_UD,

    /*
     * VERR – Verify a Segment for Reading.
     * register 0000 1111 : 0000 0000 : 11 100 reg.
     * memory 0000 1111 : 0000 0000 : mod 100 r/m.
     */
    STRING_VERR,

    /*
     * VERW – Verify a Segment for Writing.
     * register 0000 1111 : 0000 0000 : 11 101 reg.
     * memory 0000 1111 : 0000 0000 : mod 101 r/m.
    */
    STRING_VERW,

    // WAIT – Wait 1001 1011
    STRING_WAIT,

    // WBINVD – Writeback and Invalidate Data Cache 0000 1111 : 0000 1001
    STRING_WBINVD,

    // WRMSR – Write to Model-Specific Register 0000 1111 : 0011 0000
    STRING_WRMSR,

    /*
     * XADD – Exchange and Add.
     * register1, register2 0000 1111 : 1100 000w : 11 reg2 reg1.
     * memory, reg 0000 1111 : 1100 000w : mod reg r/m.
     */
    STRING_XADD,

    /*
     * XCHG – Exchange Register/Memory with Register.
     * register1 with register2 1000 011w : 11 reg1 reg2.
     * AX or EAX with reg 1001 0 reg.
     * memory with reg 1000 011w : mod reg r/m.
     * XLAT/XLATB – Table Look-up Translation 1101 0111.
    */
    STRING_XCHG,

    /*
     * XOR – Logical Exclusive OR.
     * register1 to register2 0011 000w : 11 reg1 reg2.
     * register2 to register1 0011 001w : 11 reg1 reg2.
     * memory to register 0011 001w : mod reg r/m.
     * register to memory 0011 000w : mod reg r/m.
     * immediate to register 1000 00sw : 11 110 reg : immediate data.
     * immediate to AL, AX, or EAX 0011 010w : immediate data.
     * immediate to memory 1000 00sw : mod 110 r/m : immediate data.
    */
    STRING_XOR
} string_instrution_id_64;

#define STRING_INSTRUCTION8086(name)  STRING_ ## name ## _8086
typedef enum string_instrution_id_8086 {
    STRING_INSTRUCTION8086(ADD),
    STRING_INSTRUCTION8086(OR),
    STRING_INSTRUCTION8086(ADC),
    STRING_INSTRUCTION8086(SBB),
    STRING_INSTRUCTION8086(AND),
    STRING_INSTRUCTION8086(DAA),
    STRING_INSTRUCTION8086(SUB),
    STRING_INSTRUCTION8086(DAS),
    STRING_INSTRUCTION8086(XOR),
    STRING_INSTRUCTION8086(AAA),
    STRING_INSTRUCTION8086(CMP),
    STRING_INSTRUCTION8086(AAS),
    STRING_INSTRUCTION8086(JO),
    STRING_INSTRUCTION8086(JNO),
    STRING_INSTRUCTION8086(JB),
    STRING_INSTRUCTION8086(JNB),
    STRING_INSTRUCTION8086(JZ),
    STRING_INSTRUCTION8086(JNZ),
    STRING_INSTRUCTION8086(JBE),
    STRING_INSTRUCTION8086(JNBE),
    STRING_INSTRUCTION8086(JS),
    STRING_INSTRUCTION8086(JNS),
    STRING_INSTRUCTION8086(JP),
    STRING_INSTRUCTION8086(JNP),
    STRING_INSTRUCTION8086(JL),
    STRING_INSTRUCTION8086(JNL),
    STRING_INSTRUCTION8086(JLE),
    STRING_INSTRUCTION8086(JNLE),
    STRING_INSTRUCTION8086(TEST),
    STRING_INSTRUCTION8086(LEA),
    STRING_INSTRUCTION8086(PUSH),
    STRING_INSTRUCTION8086(POP),
    STRING_INSTRUCTION8086(NOP),
    STRING_INSTRUCTION8086(XCHG),
    STRING_INSTRUCTION8086(CBW),
    STRING_INSTRUCTION8086(CWD),
    STRING_INSTRUCTION8086(JMP),
    STRING_INSTRUCTION8086(WAIT),
    STRING_INSTRUCTION8086(PUSHF),
    STRING_INSTRUCTION8086(POPF),
    STRING_INSTRUCTION8086(SAHF),
    STRING_INSTRUCTION8086(LAHF),
    STRING_INSTRUCTION8086(MOV),
    STRING_INSTRUCTION8086(MOVS),
    STRING_INSTRUCTION8086(CMPS),
    STRING_INSTRUCTION8086(STOS),
    STRING_INSTRUCTION8086(LODS),
    STRING_INSTRUCTION8086(SCAS),
    STRING_INSTRUCTION8086(RET),
    STRING_INSTRUCTION8086(LES),
    STRING_INSTRUCTION8086(LDS),
    STRING_INSTRUCTION8086(INT_3),
    STRING_INSTRUCTION8086(INT),
    STRING_INSTRUCTION8086(INTO),
    STRING_INSTRUCTION8086(IRET),
    STRING_INSTRUCTION8086(ROL),
    STRING_INSTRUCTION8086(ROR),
    STRING_INSTRUCTION8086(RCL),
    STRING_INSTRUCTION8086(RCR),
    STRING_INSTRUCTION8086(SHL),
    STRING_INSTRUCTION8086(SHR),
    STRING_INSTRUCTION8086(SAR),
    STRING_INSTRUCTION8086(AAM),
    STRING_INSTRUCTION8086(SALC),
    STRING_INSTRUCTION8086(AAD),
    STRING_INSTRUCTION8086(XLAT),
    STRING_INSTRUCTION8086(ESC),
    STRING_INSTRUCTION8086(LOOPNE),
    STRING_INSTRUCTION8086(LOOPE),
    STRING_INSTRUCTION8086(LOOP),
    STRING_INSTRUCTION8086(JCXZ),
    STRING_INSTRUCTION8086(IN),
    STRING_INSTRUCTION8086(OUT),
    STRING_INSTRUCTION8086(CALL),
    STRING_INSTRUCTION8086(REPNE),
    STRING_INSTRUCTION8086(REP),
    STRING_INSTRUCTION8086(LOCK),
    STRING_INSTRUCTION8086(CMD),
    STRING_INSTRUCTION8086(HLT),
    STRING_INSTRUCTION8086(CMC),
    STRING_INSTRUCTION8086(NOT),
    STRING_INSTRUCTION8086(NEG),
    STRING_INSTRUCTION8086(MUL),
    STRING_INSTRUCTION8086(IMUL),
    STRING_INSTRUCTION8086(DIV),
    STRING_INSTRUCTION8086(IDIV),
    STRING_INSTRUCTION8086(CLC),
    STRING_INSTRUCTION8086(STC),
    STRING_INSTRUCTION8086(CLI),
    STRING_INSTRUCTION8086(STI),
    STRING_INSTRUCTION8086(CLD),
    STRING_INSTRUCTION8086(STD),
    STRING_INSTRUCTION8086(INC),
    STRING_INSTRUCTION8086(DEC)
} string_instrution_id_8086;
static char *instruction_8086[] = {
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
    [STRING_INSTRUCTION8086(DEC)]   = "DEC"
    
};
static const uint8_t *Mod_rm_disp_8086[3][8] = {
    // rm    0                      1                    10                    11                   100              101                110              111
    {   "[BX + SI]",           "[BX + DI]",          "[BP + SI]",          "[BP + DI]",             "[SI]",          "[DI]",            "[BP]",          "[BX]"         },  // mod 00
    { "[BX + SI + 0x%02x]",    "[BX + DI + 0x%02x]", "[BP + SI + 0x%02x]", "[BP + DI + 0x%02x]",    "[SI + 0x%02x]", "[DI + 0x%02x]",   "[BP + 0x%02x]", "[BX + 0x%02x]"},  // mod 01
    { "[BX + SI + 0x%04x]",    "[BX + DI + 0x%04x]", "[BP + SI + 0x%04x]", "[BP + DI + 0x%04x]",    "[SI + 0x%04x]", "[DI + 0x%04x]",   "[BP + 0x%04x]", "[BX + 0x%04x]"}   // mod 10
};
static const uint8_t *reg_8086[2][8] = {
    // rm    0                   1                    10                    11                   100              101                110              111
    { "AL",                    "CL",                 "DL",                 "BL",                    "AH",            "CH",              "DH",            "BH"           },  // mod 11
    { "AX",                    "CX",                 "DX",                 "BX",                    "SP",            "BP",              "SI",            "DI"           }   // mod 11
};
static const uint8_t *reg_seg[] = {
    "ES", "CS", "SS", "DS", "FS", "GS"
};

typedef enum encoder_x86 { // se especifica el formato a encodificar / descodificar las instrucciones
    ENCODER_IN_16bits,
    ENCODER_IN_32bits,
    ENCODER_IN_64bits
} encoder_x86;

typedef enum register_id { // se especifica los registros
    REGISTER_A  = 0b000, // AL, AX, EAX = 000
    REGISTER_C  = 0b001, // CL, CX, ECX = 001
    REGISTER_B  = 0b010, // BL, BX, EBX = 010
    REGISTER_D  = 0b011, // DL, DX, EDX = 011
    REGISTER_S  = 0b100, // AH, SP, ESX = 100
    REGISTER_BP = 0b101, // CH, BP, EBX = 101
    REGISTER_SP = 0b110, // DH, SI, ESX = 110
    REGISTER_DI = 0b111, // BH, DI, EDX = 111
} register_id;

#pragma pack(push, 1)

typedef union opcode // estructura para representar los opcodes
{
    struct opcode_bits_final {
        uint8_t      s:1;   /* 
                            * Longitud del operando(size?):
                            * Si s = 0, los operandos son registros de 8 bits y posiciones de memoria.
                            * Si s = 1, los operandos son de 16 bits o de 32 bits:
                            */
        uint8_t      d:1;   /* 
                             * direcion:
                             * Si d=0, REG es la fuente, MOD R/M <- REG.
                             * Si d=1, REG es el destino, REG <- MOD R/M.
                             */
        uint8_t opcode:6;    // opcode de 1 byte
    } opcode_bits_final;     // no siempre se da este formato en las instrucciones
    struct opcode_bits {
        uint8_t b1:1; uint8_t b2:1; uint8_t b3:1; uint8_t b4:1; 
        uint8_t b5:1; uint8_t b6:1; uint8_t b7:1; uint8_t b8:1; 
    } opcode_bits;          // acceso a los campos de bit a bit (para los casos en los que el campo "w", "d", "s", puedan estar en diferentes ubicaciones)

    struct opcode_byte {
        uint8_t byte;       // acceder al opcode en forma de byte 
    } opcode_byte;          // acceso a todos los campos en forma de byte
} opcode;                   

typedef struct Mod_rm { // estructura para representar el mod/rm (¿Register/Memory?) https://en.wikipedia.org/wiki/ModR/M
        union {
        struct {
            uint8_t    R_M:3; /* 
                            * campo ¿Registro/Memoria?  (reg2?).
                            * dependiendo de la instruccion este campo se usa como indicar de un segundo registro fuente o destino.
                            * En caso contrario se usa para el acceso a memoria o indicar el uso de un campo SIB.
                            * 
                            * Formas con el Byte ModR/M solo para 32bits:
                            * |===|===|=================================.
                            * |MOD|R/M|     Addressing Mode             . 
                            * |===|===|=================================.
                            * | 00|000|[ eax ]                          .            
                            * | 01|000|[ eax + disp8 ]               (1).                   
                            * | 10|000|[ eax + disp32 ]                 .  
                            * | 11|000|register  ( al / ax / eax )   (2).
                            * | 00|001|[ ecx ]                          .            
                            * | 01|001|[ ecx + disp8 ]                  . 
                            * | 10|001|[ ecx + disp32 ]                 .                     
                            * | 11|001|register  ( cl / cx / ecx )      .             
                            * | 00|010|[ edx ]                          .            
                            * | 01|010|[ edx + disp8 ]                  .                                                          
                            * | 10|010|[ edx + disp32 ]                 .                     
                            * | 11|010|register  ( dl / dx / edx )      .                                
                            * | 00|011|[ ebx ]                          .            
                            * | 01|011|[ ebx + disp8 ]                  .                    
                            * | 10|011|[ ebx + disp32 ]                 .                     
                            * | 11|011|register  ( bl / bx / ebx )      .             
                            * | 00|100|SIB  Mode                     (3).                   
                            * | 01|100|SIB  +  disp8  Mode              .     
                            * | 10|100|SIB  +  disp32  Mode             .                         
                            * | 11|100|register  ( ah / sp / esp )      .             
                            * | 00|101|32-bit Displacement-Only Mode (4).                   
                            * | 01|101|[ ebp + disp8 ]                  .                    
                            * | 10|101|[ ebp + disp32 ]                 .                     
                            * | 11|101|register  ( ch / bp / ebp )      .             
                            * | 00|110|[ esi ]                          .            
                            * | 01|110|[ esi + disp8 ]                  .                    
                            * | 10|110|[ esi + disp32 ]                 .                     
                            * | 11|110|register  ( dh / si / esi )      .                                
                            * | 00|111|[ edi ]                          .            
                            * | 01|111|[ edi + disp8 ]                  .                    
                            * | 10|111|[ edi + disp32 ]                 .                     
                            * | 11|111|register  ( bh / di / edi )      .     
                            * |===|===|=================================. 
                            */
            uint8_t    reg:3; /* 
                            * campo registro (reg1?).
                            * - 000 -> al(si w = 0) / ax(si w = 1) / eax (32bits) / rax.
                            * - 001 -> cl(si w = 0) / cx(si w = 1) / ecx (32bits) / rcx.
                            * - 010 -> dl(si w = 0) / dx(si w = 1) / edx (32bits) / rdx.
                            * - 011 -> bl(si w = 0) / bx(si w = 1) / ebx (32bits) / rbx.
                            * - 100 -> ah(si w = 0) / sp(si w = 1) / esp (32bits) / rsp.
                            * - 101 -> ch(si w = 0) / bp(si w = 1) / ebp (32bits) / rbp.
                            * - 110 -> dh(si w = 0) / si(si w = 1) / esi (32bits) / rsi.
                            * - 111 -> bh(si w = 0) / di(si w = 1) / edi (32bits) / rdi.
                            */
            uint8_t    mod:2; /*
                            * campo MOD:
                            *  - 00 Modo de direccionamiento indirecto de registro o SIB sin desplazamiento (cuando R/M = 100) o 
                            *        modo de direccionamiento de sólo desplazamiento (cuando R/M = 101).
                            *  - 01 El desplazamiento con signo de un byte sigue a los bytes del modo de direccionamiento.
                            *  - 10 El desplazamiento con signo de cuatro/dos bytes sigue a los bytes del modo de direccionamiento.
                            *  - 11 Modo de direccionamiento de registro.
                            */
        } fields;
        uint8_t byte;
    };
} Mod_rm;

/*
 * Byte SIB (Byte de índice escalado): ( Valor SIB = Index * scale + base ) 
 * El byte SIB es un byte opcional post-opcode en ensamblador x86 en el i386 y posteriores, utilizado 
 * para direccionamiento complejo. El modo de direccionamiento indexado escalado utiliza el segundo byte (es decir, el byte SIB) 
 * que sigue al byte MOD-REG-R/M en el formato de instrucción.
 * El campo MOD todavía especifica el tamaño de desplazamiento de cero, uno o cuatro bytes.
 * Los bytes MOD-REG-R/M y SIB son complejos, porque Intel reutilizó los circuitos de direccionamiento de 16 bits en el modo de 
 * 32 bits, en lugar de abandonar simplemente el formato de 16 bits en el modo de 32 bits.
 * Hay buenas razones de hardware para ello, pero el resultado final es un complejo esquema 
 * para especificar los modos de direccionamiento en los opcodes.
 * 
 * En cada modo de direccionamiento indexado escalado, el campo MOD del byte MOD-REG-R/M especifica el tamaño del desplazamiento. Puede ser cero, uno o cuatro bytes:
 *     MOD R/M Modo de direccionamiento.
 *     --- --- ---------------------------.
 *      00 100 SIB.
 *      01 100 SIB + disp8.
 *      10 100 SIB + disp32.
 * 
 *  [ reg32 + eax*n ] MOD = 00.
 *  [ reg32 + ebx*n ].
 *  [ reg32 + ecx*n ].
 *  [ reg32 + edx*n ].
 *  [ reg32 + ebp*n ].
 *  [ reg32 + esi*n ].
 *  [ reg32 + edi*n ].
 *  
 *  [ disp + reg8 + eax*n ] MOD = 01.
 *  [ disp + reg8 + ebx*n ].
 *  [ disp + reg8 + ecx*n ].
 *  [ disp + reg8 + edx*n ].
 *  [ disp + reg8 + ebp*n ].
 *  [ disp + reg8 + esi*n ].
 *  [ disp + reg8 + edi*n ].
 *  
 *  [ disp + reg32 + eax*n ] MOD = 10.
 *  [ disp + reg32 + ebx*n ].
 *  [ disp + reg32 + ecx*n ].
 *  [ disp + reg32 + edx*n ].
 *  [ disp + reg32 + ebp*n ].
 *  [ disp + reg32 + esi*n ].
 *  [ disp + reg32 + edi*n ].
 *  
 *  [ disp + eax*n ] MOD = 00, and.
 *  [ disp + ebx*n ] BASE field = 101.
 *  [ disp + ecx*n ].
 *  [ disp + edx*n ].
 *  [ disp + ebp*n ].
 *  [ disp + esi*n ].
 *  [ disp + edi*n ].
 * 
 */
typedef struct SIB {
    uint8_t    base:3; /*
                        * BASE (3bits 2 a 0):  
                        *   bit(000) -> eax. 
                        *   bit(001) -> ecx.
                        *   bit(010) -> edx.
                        *   bit(011) -> ebx.
                        *   bit(100) -> esp.
                        *   bit(101) -> ebp -> si MOD = 01 o 10. sino, solo si MOD es 00.
                        *   bit(110) -> esi.
                        *   bit(111) -> edi.
                        */
    uint8_t   index:3; /*
                        * INDEX (3bits 5 a 3):
                        *   bit(000) ->  eax.
                        *   bit(001) ->  ecx.
                        *   bit(010) ->  edx.
                        *   bit(011) ->  ebx.
                        *   bit(100) -> ilegal.
                        *   bit(101) ->  ebp.
                        *   bit(110) ->  esi.
                        *   bit(111) ->  edi.
                        */
    uint8_t   scale:2; /*
                        * SCALE (2bits 7 a 6):
                        *   bit(00)  -> index * 1.
                        *   bit(01)  -> index * 2.
                        *   bit(10)  -> index * 4.
                        *   bit(11)  -> index * 8.
                        */
} SIB;

/*
 * Cambios en 64 bits:
 * El byte ModR/M es fundamental para los cambios introducidos con la extensión de 64 bits de AMD al 
 * conjunto de instrucciones original. En modo largo, cualquier opcode cuyos cuatro bits más altos 
 * sean 0100 (decimal 4) se considera un nuevo prefijo, el prefijo REX
 * Los cuatro bits más bajos del byte de prefijo sirven para varios propósitos, 
 * incluyendo un bit extra para los campos REG y R/M del byte ModR/M que le sigue. 
 * Entre otros cambios, la ampliación de estos valores de tres bits a cuatro duplica el número 
 * de registros disponibles en el procesador de ocho a dieciséis.
 */
/*
 *
 * El campo TTTN definen la condicion de la instruccion, en el caso de las instrucciones JCC (instrucciones de salto)
 * La instruccion JZ constiene como bit's tttn el valor 0100. siendo la codificacin del salto el  0111 tttn : 8-bit displacement
 * donde 0111 indica que se trata de las instruciones de salto y tttn siendo la condicion, 8-bit displacement siendo una cantidad
 * de bytes (un desplazamiento de 8bits) a saltar (maximos 0-255)
 * 
 * |-----------------------------------------------------------|
 * | tttn | Mnemonic |  Condition                              |  
 * |-----------------------------------------------------------|       
 * | 0000 | O        | Overflow                                |     
 * | 0001 | NO       | No overflow                             |         
 * | 0010 | B, NAE   | Below, Not above or equal               |                         
 * | 0011 | NB, AE   | Not below, Above or equal               |                         
 * | 0100 | E, Z     | Equal, Zero                             |         
 * | 0101 | NE, NZ   | Not equal, Not zero                     |                 
 * | 0110 | BE, NA   | Below or equal, Not above               |                         
 * | 0111 | NBE, A   | Not below or equal, Above               |                         
 * | 1000 | S        | Sign                                    | 
 * | 1001 | NS       | Not sign                                |     
 * | 1010 | P, PE    | Parity, Parity Even                     |                 
 * | 1011 | NP, PO   | Not parity, Parity Odd                  |                     
 * | 1100 | L, NGE   | Less than, Not greater than or equal to |                                     
 * | 1101 | NL, GE   | Not less than, Greater than or equal to |                                     
 * | 1110 | LE, NG   | Less than or equal to, Not greater than |                                     
 * | 1111 | NLE, G   | Not less than or equal to, Greater than |
 * |-----------------------------------------------------------|  
 */

typedef union data
{
    uint8_t  ui8;
    uint16_t ui16;
    uint32_t ui32;
    uint64_t ui64;
} data;

typedef enum reg_seg_x86 {
    reg_seg_ES,
    reg_seg_CS,
    reg_seg_SS,
    reg_seg_DS
} reg_seg_x86;

typedef struct Instruction_info
{
    reg_seg_x86 reg_seg;         // almacena el registro de segmento
    opcode  opcode1;         // 7
    Mod_rm  Mod_rm;          // 8
    SIB     SIB;             // 9
    data    displacement;   // desplazamiento de 0, 1, 2, 4 bytes
    data    immediate;    // immediato de 0, 1, 2, 4 bytes

    uint16_t flags;          // flags de la instruccion
    uint8_t  flags_prefix;   // flags que indica prefijos de la instrucccion
    uint8_t  flags_x87;      // flags para las instrucciones del x87
    #define FLAG_PREFIX_Prefix_addr_size (1 << 0)
    #define FLAG_PREFIX_Prefix_SS        (1 << 1)
    #define FLAG_PREFIX_Prefix_CS        (1 << 3)
    #define FLAG_PREFIX_Prefix_ES        (1 << 4)
    #define FLAG_PREFIX_Prefix_DS        (1 << 5)
    #define FLAG_PREFIX_Prefix_FS        (1 << 6)
    #define FLAG_PREFIX_Prefix_GS        (1 << 7)
    #define FLAG_PREFIX_Prefix_REP       FLAG_PREFIX_Prefix_SS | FLAG_PREFIX_Prefix_DS
    #define FLAG_PREFIX_Prefix_LOCK      FLAG_PREFIX_Prefix_ES | FLAG_PREFIX_Prefix_DS
} Instruction_info;

#pragma pack(pop)

// (Instrucciones en page: 2845/2875) Intel® 64 and IA-32 Architectures Software Developer’s Manual, Combined Volumes: 1, 2A, 2B, 2C, 2D, 3A, 3B,

// tiene mod/rm-reg
#define MOD_RM_REG_MASK  (1 << 0)

// tiene un desplazamiento bajo opcional indicado por mod/rm:
#define DISP_LOW_MASK    (1 << 1)

// tiene un desplazamiento alto opcional indicado por mod/rm:
#define DISP_HIGH_MASK   (1 << 2)

// tiene campo datos del 8086
#define DATA_MASK_8086   (1 << 3)

// el es un prefijo
#define MASK_PREFIX      (1 << 8)

// usa registro-memoria de 16bits
#define REG_MEM_16_MASK  (1 << 5)

// tiene datos inmediatos de 8bits
#define INMED8_MASK      (1 << 6)

// tiene datos SX
#define DATA_SX_MASK     (1 << 7)

// usa registro-memoria de 8bits
#define REG_MEM_8_MASK   (1 << 4)

// tiene datos inmediatos de 16bits
#define INMED16_MASK     (1 << 9)

// usa un registro de segmento 16bits
#define REG_SEG_MASK     (1 << 10)

// instruccion indocumentada
#define UNDOCUMENTED_OPCODE_MASK     (1 << 11)

// tiene datos tttn, para instrucciones de tipo salto condicional, se usara el campo mod-reg-rm para almacenar el tttn obtenido del opcode
#define TTTN_MASK        (1 << 12)

// tiene un desplazamiento alto por ejemplo 0xffff:0x1234, donde 0xffff es un "desplazamiento alto"
#define DIS_HIGH_MASK    (1 << 13)

// insica que la instruccion es un espace para usar coprocesadores como el x87
#define X87_MASK         (1 << 14)

// ingresar id de la instruccion string
#define STRING_INSTRU(num) (num  << 24)

/*
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
 */

// tambien se usara para el x87 decoder:
//#define MOD_RM_REG_MASK  (1 << 0)

#include "./include/section_macro.h"

// indica que el opcode para el coprocesador (segundo byte de la instruccion) tiene tres bits de opcode que
// sirven para indicar que registro ST se quiere acceder usar modificar u otro
#define ST_REGISTER (1 << 1)
#define TABLE_INSTRUCTIONS_8087(name, number) name##_table_##number
ATTRIBUTE_SECTION(".instruccion") static uint8_t TABLE_INSTRUCTIONS_8087(my_instruccion_8087, 0)[] = {
    // [0xd8] = X87_MASK,

    // fcom -> 0xd8 0xd0 - 0xd8 0xd7
    [0b11010000] = ST_REGISTER, // fcom ST(0)
    [0b11010001] = ST_REGISTER, // fcom ST(1)
    [0b11010010] = ST_REGISTER, // fcom ST(2)
    [0b11010011] = ST_REGISTER, // fcom ST(3)
    [0b11010100] = ST_REGISTER, // fcom ST(4)
    [0b11010101] = ST_REGISTER, // fcom ST(5)
    [0b11010110] = ST_REGISTER, // fcom ST(6)
    [0b11010111] = ST_REGISTER, // fcom ST(7)

    // fcomp -> 0xd8 0xd8 - 0xd8 0xdf
    [0b11011000] = ST_REGISTER, // fcomp ST(0)
    [0b11011001] = ST_REGISTER, // fcomp ST(1)
    [0b11011010] = ST_REGISTER, // fcomp ST(2)
    [0b11011011] = ST_REGISTER, // fcomp ST(3)
    [0b11011100] = ST_REGISTER, // fcomp ST(4)
    [0b11011101] = ST_REGISTER, // fcomp ST(5)
    [0b11011110] = ST_REGISTER, // fcomp ST(6)
    [0b11011111] = ST_REGISTER, // fcomp ST(7)
};
ATTRIBUTE_SECTION(".instruccion") static uint8_t TABLE_INSTRUCTIONS_8087(my_instruccion_8087, 1)[] = {
    // [0xd9] = X87_MASK,

    // MF(00) -> 32bits real
    // MF(01) -> 32bits interger
    // MF(10) -> 64bits real
    // MF(11) -> 16bits interger
    // fld -> | escape | MF | 1 || mod | 000 | rm || disp |
    // fld dword mod/rm
    [0b00000000] = MOD_RM_REG_MASK,                   // D9 00          fld dword ptr [bx + si]
    [0b00000001] = MOD_RM_REG_MASK,                   // D9 01          fld dword ptr [bx + di]
    [0b00000010] = MOD_RM_REG_MASK,                   // D9 02          fld dword ptr [bp + si]
    [0b00000011] = MOD_RM_REG_MASK,                   // D9 03          fld dword ptr [bp + di]
    [0b00000100] = MOD_RM_REG_MASK,                   // D9 04          fld dword ptr [si]
    [0b00000101] = MOD_RM_REG_MASK,                   // D9 05          fld dword ptr [di]
    [0b00000110] = MOD_RM_REG_MASK | REG_MEM_16_MASK, // D9 06 12 34    fld dword ptr [mem16]
    [0b00000111] = MOD_RM_REG_MASK,                   // D9 07          fld dword ptr [bx]

    // REG_MEM_8_MASK se usa para indicar que usa un mem8
    [0b01000000] = MOD_RM_REG_MASK | REG_MEM_8_MASK,   // D9 40 12       fld dword ptr [bx + si + mem8]
    [0b01000001] = MOD_RM_REG_MASK | REG_MEM_8_MASK,   // D9 41 12       fld dword ptr [bx + di + mem8]
    [0b01000010] = MOD_RM_REG_MASK | REG_MEM_8_MASK,   // D9 42 12       fld dword ptr [bp + si + mem8]
    [0b01000011] = MOD_RM_REG_MASK | REG_MEM_8_MASK,   // D9 43 12       fld dword ptr [bp + di + mem8]
    [0b01000100] = MOD_RM_REG_MASK | REG_MEM_8_MASK,   // D9 44 12       fld dword ptr [si + mem8]
    [0b01000101] = MOD_RM_REG_MASK | REG_MEM_8_MASK,   // D9 45 12       fld dword ptr [di + mem8]
    [0b01000110] = MOD_RM_REG_MASK | REG_MEM_8_MASK,   // D9 46 12       fld dword ptr [bp + mem8]
    [0b01000111] = MOD_RM_REG_MASK | REG_MEM_8_MASK,   // D9 47 12       fld dword ptr [bx + mem8]

    [0b10000000] = MOD_RM_REG_MASK | REG_MEM_16_MASK, // D9 80 34 12    fld dword ptr [bx + si + mem16]
    [0b10000001] = MOD_RM_REG_MASK | REG_MEM_16_MASK, // D9 81 34 12    fld dword ptr [bx + di + mem16]
    [0b10000010] = MOD_RM_REG_MASK | REG_MEM_16_MASK, // D9 82 34 12    fld dword ptr [bp + si + mem16]
    [0b10000011] = MOD_RM_REG_MASK | REG_MEM_16_MASK, // D9 83 34 12    fld dword ptr [bp + di + mem16]
    [0b10000100] = MOD_RM_REG_MASK | REG_MEM_16_MASK, // D9 84 34 12    fld dword ptr [si      + mem16]
    [0b10000101] = MOD_RM_REG_MASK | REG_MEM_16_MASK, // D9 85 34 12    fld dword ptr [di      + mem16]
    [0b10000110] = MOD_RM_REG_MASK | REG_MEM_16_MASK, // D9 86 34 12    fld dword ptr [bp      + mem16]
    [0b10000111] = MOD_RM_REG_MASK | REG_MEM_16_MASK, // D9 87 34 12    fld dword ptr [bx      + mem16]

    // fld reg -> 0xd9 0xd0 - 0xd9 0xd7
    [0b11000000] = ST_REGISTER,     // D9 C0          fld st(0)
    [0b11000001] = ST_REGISTER,     // D9 C1          fld st(1)
    [0b11000010] = ST_REGISTER,     // D9 C2          fld st(2)
    [0b11000011] = ST_REGISTER,     // D9 C3          fld st(3)
    [0b11000100] = ST_REGISTER,     // D9 C4          fld st(4)
    [0b11000101] = ST_REGISTER,     // D9 C5          fld st(5)
    [0b11000110] = ST_REGISTER,     // D9 C6          fld st(6)
    [0b11000111] = ST_REGISTER,     // D9 C7          fld st(7)

    // fxch -> 0xd9 0xc8 - 0xd9 0xdf
    [0b11001000] = ST_REGISTER, // ESC(fxch st(0))
    [0b11001001] = ST_REGISTER, // ESC(fxch st(1))
    [0b11001010] = ST_REGISTER, // ESC(fxch st(2))
    [0b11001011] = ST_REGISTER, // ESC(fxch st(3))
    [0b11001100] = ST_REGISTER, // ESC(fxch st(4))
    [0b11001101] = ST_REGISTER, // ESC(fxch st(5))
    [0b11001110] = ST_REGISTER, // ESC(fxch st(6))
    [0b11001111] = ST_REGISTER, // ESC(fxch st(7))

};
ATTRIBUTE_SECTION(".instruccion") static uint8_t TABLE_INSTRUCTIONS_8087(my_instruccion_8087, 2)[] = {
    // [0xda] = X87_MASK,
};
ATTRIBUTE_SECTION(".instruccion") static uint8_t TABLE_INSTRUCTIONS_8087(my_instruccion_8087, 3)[] = {
    // [0xdb] = X87_MASK,

};
ATTRIBUTE_SECTION(".instruccion") static uint8_t TABLE_INSTRUCTIONS_8087(my_instruccion_8087, 4)[] = {
    // [0xdc] = X87_MASK,

};
ATTRIBUTE_SECTION(".instruccion") static uint8_t TABLE_INSTRUCTIONS_8087(my_instruccion_8087, 5)[] = {
    // [0xdd] = X87_MASK,
    // 1101 1 MF(10) 1

    // fld -> | escape | MF | 1 || mod | 000 | rm || disp |
    // fld qword mod/rm
    [0b00000000] = MOD_RM_REG_MASK,                   // DD 00          fld qword ptr [bx + si]
    [0b00000001] = MOD_RM_REG_MASK,                   // DD 01          fld qword ptr [bx + di]
    [0b00000010] = MOD_RM_REG_MASK,                   // DD 02          fld qword ptr [bp + si]
    [0b00000011] = MOD_RM_REG_MASK,                   // DD 03          fld qword ptr [bp + di]
    [0b00000100] = MOD_RM_REG_MASK,                   // DD 04          fld qword ptr [si]
    [0b00000101] = MOD_RM_REG_MASK,                   // DD 05          fld qword ptr [di]
    [0b00000110] = MOD_RM_REG_MASK | REG_MEM_16_MASK, // DD 06 12 34    fld qword ptr [mem16]
    [0b00000111] = MOD_RM_REG_MASK,                   // DD 07          fld qword ptr [bx]

    // fstp -> 0xdd 0xd8 - 0xdd 0xdf
    [0b11011000] = ST_REGISTER, // ESC(fstp st(0))
    [0b11011001] = ST_REGISTER, // ESC(fstp st(1))
    [0b11011010] = ST_REGISTER, // ESC(fstp st(2))
    [0b11011011] = ST_REGISTER, // ESC(fstp st(3))
    [0b11011100] = ST_REGISTER, // ESC(fstp st(4))
    [0b11011101] = ST_REGISTER, // ESC(fstp st(5))
    [0b11011110] = ST_REGISTER, // ESC(fstp st(6))
    [0b11011111] = ST_REGISTER, // ESC(fstp st(7))
};
ATTRIBUTE_SECTION(".instruccion") static uint8_t TABLE_INSTRUCTIONS_8087(my_instruccion_8087, 6)[] = {
    // [0xde] = X87_MASK,

};
ATTRIBUTE_SECTION(".instruccion") static uint8_t TABLE_INSTRUCTIONS_8087(my_instruccion_8087, 7)[] = {
    // [0xdf] = X87_MASK,

};

ATTRIBUTE_SECTION(".instruccion") static uint8_t *my_instruccion_8087_table[] = {
    TABLE_INSTRUCTIONS_8087(my_instruccion_8087, 0),
    TABLE_INSTRUCTIONS_8087(my_instruccion_8087, 1),
    TABLE_INSTRUCTIONS_8087(my_instruccion_8087, 2),
    TABLE_INSTRUCTIONS_8087(my_instruccion_8087, 3),
    TABLE_INSTRUCTIONS_8087(my_instruccion_8087, 4),
    TABLE_INSTRUCTIONS_8087(my_instruccion_8087, 5),
    TABLE_INSTRUCTIONS_8087(my_instruccion_8087, 6),
    TABLE_INSTRUCTIONS_8087(my_instruccion_8087, 7)
};
ATTRIBUTE_SECTION(".instruccion") static size_t my_instruccion_8087_table_sizes[] = {
    sizeof(TABLE_INSTRUCTIONS_8087(my_instruccion_8087, 0))/sizeof(TABLE_INSTRUCTIONS_8087(my_instruccion_8087, 0)[0]),
    sizeof(TABLE_INSTRUCTIONS_8087(my_instruccion_8087, 1))/sizeof(TABLE_INSTRUCTIONS_8087(my_instruccion_8087, 1)[0]),
    sizeof(TABLE_INSTRUCTIONS_8087(my_instruccion_8087, 2))/sizeof(TABLE_INSTRUCTIONS_8087(my_instruccion_8087, 2)[0]),
    sizeof(TABLE_INSTRUCTIONS_8087(my_instruccion_8087, 3))/sizeof(TABLE_INSTRUCTIONS_8087(my_instruccion_8087, 3)[0]),
    sizeof(TABLE_INSTRUCTIONS_8087(my_instruccion_8087, 4))/sizeof(TABLE_INSTRUCTIONS_8087(my_instruccion_8087, 4)[0]),
    sizeof(TABLE_INSTRUCTIONS_8087(my_instruccion_8087, 5))/sizeof(TABLE_INSTRUCTIONS_8087(my_instruccion_8087, 5)[0]),
    sizeof(TABLE_INSTRUCTIONS_8087(my_instruccion_8087, 6))/sizeof(TABLE_INSTRUCTIONS_8087(my_instruccion_8087, 6)[0]),
    sizeof(TABLE_INSTRUCTIONS_8087(my_instruccion_8087, 7))/sizeof(TABLE_INSTRUCTIONS_8087(my_instruccion_8087, 7)[0])
};

ATTRIBUTE_SECTION(".instruccion") static uint32_t my_instruccion_8086[] = {
    [opcodes_8086_ADD_mem8] = REG_MEM_8_MASK  | MOD_RM_REG_MASK | DISP_LOW_MASK | DISP_HIGH_MASK | STRING_INSTRU(STRING_INSTRUCTION8086(ADD)), // opcode(00 -> 0b00000000) -> (add) (mod, reg, r/m), (disp_low), (disp_high)
    [opcodes_8086_ADD_mem16] = REG_MEM_16_MASK | MOD_RM_REG_MASK | DISP_LOW_MASK | DISP_HIGH_MASK | STRING_INSTRU(STRING_INSTRUCTION8086(ADD)), // opcode(01 -> 0b00000001) -> (add) (mod, reg, r/m), (disp_low), (disp_high)
    [opcodes_8086_ADD_mem8_inverse] = REG_MEM_8_MASK  | MOD_RM_REG_MASK | DISP_LOW_MASK | DISP_HIGH_MASK | STRING_INSTRU(STRING_INSTRUCTION8086(ADD)), // opcode(02 -> 0b00000010) -> (add) (mod, reg, r/m), (disp_low), (disp_high)
    [opcodes_8086_ADD_mem16_inverse] = REG_MEM_16_MASK | MOD_RM_REG_MASK | DISP_LOW_MASK | DISP_HIGH_MASK | STRING_INSTRU(STRING_INSTRUCTION8086(ADD)), // opcode(03 -> 0b00000011) -> (add) (mod, reg, r/m), (disp_low), (disp_high)

    // add al, inmed16
    [opcodes_8086_ADD_al] = INMED8_MASK | STRING_INSTRU(STRING_INSTRUCTION8086(ADD)),  // opcode(04 -> 0b00000011) -> (add) (data)

    // add ax, inmed16
    [opcodes_8086_ADD_ax] = INMED16_MASK | STRING_INSTRU(STRING_INSTRUCTION8086(ADD)), // opcode(05 -> 0b00000011) -> (add) (data low), (data high if W = 1)

    // push es:
    [opcodes_8086_PUSH_es] = REG_SEG_MASK | STRING_INSTRU(STRING_INSTRUCTION8086(PUSH)), // opcode(06 -> 0b00000110)

    // pop es:
    [opcodes_8086_POP_es] = REG_SEG_MASK | STRING_INSTRU(STRING_INSTRUCTION8086(POP)), // opcode(07 -> 0b00000111)

    // or reg8/mem8, reg8
    [opcodes_8086_OR_mem8] = MOD_RM_REG_MASK | DISP_LOW_MASK | DISP_HIGH_MASK | REG_MEM_8_MASK | STRING_INSTRU(STRING_INSTRUCTION8086(OR)), // opcode(08 -> 0b00001000)

    // or reg16/mem16, reg16
    [opcodes_8086_OR_mem16] = MOD_RM_REG_MASK | DISP_LOW_MASK | DISP_HIGH_MASK | REG_MEM_16_MASK | STRING_INSTRU(STRING_INSTRUCTION8086(OR)), // opcode(09 -> 0b00001001)

    // or reg8 ,reg8/mem8
    [opcodes_8086_OR_mem8_inverse] = MOD_RM_REG_MASK | DISP_LOW_MASK | DISP_HIGH_MASK | REG_MEM_8_MASK | STRING_INSTRU(STRING_INSTRUCTION8086(OR)), // opcode(0a -> 0b00001010)

    // or reg16, reg16/mem16
    [opcodes_8086_OR_mem16_inverse] = MOD_RM_REG_MASK | DISP_LOW_MASK | DISP_HIGH_MASK | REG_MEM_16_MASK | STRING_INSTRU(STRING_INSTRUCTION8086(OR)), // opcode(0b -> 0b00001011)

    // or al, inmed8
    [opcodes_8086_OR_al] = INMED8_MASK | STRING_INSTRU(STRING_INSTRUCTION8086(OR)),  // opcode(0c -> 0b00001100) -> (or) (data)

    // or al, inmed16
    [opcodes_8086_OR_ax] = INMED16_MASK | STRING_INSTRU(STRING_INSTRUCTION8086(OR)),  // opcode(0d -> 0b00001101) -> (or) (data high if W = 1)

    // push cs
    [opcodes_8086_PUSH_cs] = REG_SEG_MASK | STRING_INSTRU(STRING_INSTRUCTION8086(PUSH)),                            // opcode(0e -> 0b00001110)

    // pop cs -> https://www.righto.com/2023/07/undocumented-8086-instructions.html
    [opcodes_8086_POP_cs] = REG_SEG_MASK | UNDOCUMENTED_OPCODE_MASK | STRING_INSTRU(STRING_INSTRUCTION8086(POP)), // opcode(0f -> 0b00001111)
    /*
     * El código de operación 0F es el primer agujero en la tabla de códigos de operación. El
     * 8086 tiene instrucciones para insertar y extraer los cuatro registros de segmento, excepto
     * que el código de operación 0F no está definido donde debería estar POP CS. Este código de
     * operación realiza POP CS con éxito, por lo que la pregunta es ¿por qué no está definido? La
     * razón es que POP CS es esencialmente inútil y no hace lo que se esperaría, por lo que Intel
     * pensó que era mejor no documentarlo.
     * Para entender por qué POP CS es inútil, necesito dar un paso atrás y explicar los registros de
     * segmento del 8086. El 8086 tiene un espacio de direcciones de 20 bits, pero registros de 16 bits.
     * Para que esto funcione, el 8086 tiene el concepto de segmentos: se accede a la memoria en
     * fragmentos de 64K llamados segmentos, que se colocan en el espacio de direcciones de 1 megabyte.
     * En concreto, hay cuatro segmentos: segmento de código, segmento de pila, segmento de datos y
     * segmento adicional, con cuatro registros de segmento que definen el inicio del segmento: CS, SS, DS y ES.
     * Una parte incómoda del direccionamiento de segmentos es que si desea acceder a más de 64K,
     * necesita cambiar el registro de segmento. Por lo tanto, puede insertar el registro de segmento
     * de datos, cambiarlo temporalmente para poder acceder a una nueva parte de la memoria y luego
     * extraer el valor del registro de segmento de datos anterior de la pila. Esto utilizaría las
     * instrucciones PUSH DS y POP DS. Pero, ¿por qué no POP CS?
     * El 8086 ejecuta el código desde el segmento de código, con el puntero de instrucción (IP)
     * rastreando la ubicación en el segmento de código. El problema principal con POP CS es que cambia
     * el segmento de código, pero no el puntero de instrucción, por lo que ahora está ejecutando código
     * en el desplazamiento anterior en un segmento nuevo. A menos que alinee su código con mucho cuidado,
     * el resultado es que está saltando a un lugar inesperado en la memoria. (Normalmente, se desea cambiar
     * CS y el puntero de instrucción al mismo tiempo, utilizando una instrucción CALL o JMP).
     * El segundo problema con POP CS es la precarga. Para lograr eficiencia, el 8086 precarga las
     * instrucciones antes de que sean necesarias, almacenándolas en una cola de precarga de 6 bytes.
     * Cuando se realiza un salto, por ejemplo, el microcódigo vacía la cola de precarga para que la
     * ejecución continúe con las nuevas instrucciones, en lugar de las instrucciones antiguas. Sin embargo,
     * las instrucciones que abren un registro de segmento no vacían el búfer de precarga. Por lo tanto,
     * POP CS no solo salta a una ubicación inesperada en la memoria, sino que ejecutará una cantidad
     * impredecible de instrucciones desde la ruta de código anterior.
     * El microcódigo del registro de segmento POP que se muestra a continuación contiene mucho en tres
     * microinstrucciones. La primera microinstrucciones abre un valor de la pila. Específicamente, mueve
     * el puntero de pila (SP) al registro indirecto (IND). El registro indirecto es un registro interno,
     * invisible para el programador, que contiene el desplazamiento de dirección para los accesos a la
     * memoria. La primera microinstrucción también realiza una lectura de memoria (R) desde el segmento
     * de pila (SS) y luego incrementa IND en 2 (P2, más 2). La segunda microinstrucción mueve IND al
     * puntero de pila, actualizando el puntero de pila con el nuevo valor. También le dice al motor de
     * microcódigo que esta microinstrucción es la penúltima (NXT) y que se puede iniciar la siguiente
     * instrucción de máquina. La microinstrucción final mueve el valor leído de la memoria al registro de
     * segmento apropiado y ejecuta la siguiente instrucción. Específicamente, lee y escribe datos de
     * colocación en el registro OPR (operando) interno. El hardware usa el registro N para indicar el
     * registro especificado por la instrucción. Es decir, el valor se almacenará en el registro
     * CS, DS, ES o SS, dependiendo del patrón de bits en la instrucción. Por lo tanto, el mismo
     * microcódigo funciona para los cuatro registros de segmento. Esta es la razón por la que
     * POP CS funciona aunque POP CS no se haya implementado explícitamente en el microcódigo; 
     * usa el código común.
     */

    //[0b00000100] = DISP_HIGH_MASK | DATA_MASK_8086                 , // opcode(04 -> 0b00000100) -> (add) (data), (data if w = 1)
    //[0b00000101] = DISP_HIGH_MASK | DATA_MASK_8086                 , // opcode(05 -> 0b00000101) -> (add) (data), (data if w = 1)

    [opcodes_8086_ADC_mem8] = MOD_RM_REG_MASK | DISP_LOW_MASK | DISP_HIGH_MASK | REG_MEM_8_MASK  | STRING_INSTRU(STRING_INSTRUCTION8086(ADC)), // opcode(00 -> 0b00000000) -> (adc) (mod, reg, r/m), (disp_low), (disp_high)
    [opcodes_8086_ADC_mem16] = MOD_RM_REG_MASK | DISP_LOW_MASK | DISP_HIGH_MASK | REG_MEM_16_MASK | STRING_INSTRU(STRING_INSTRUCTION8086(ADC)), // opcode(01 -> 0b00000001) -> (adc) (mod, reg, r/m), (disp_low), (disp_high)
    [opcodes_8086_ADC_mem8_inverse] = MOD_RM_REG_MASK | DISP_LOW_MASK | DISP_HIGH_MASK | REG_MEM_8_MASK  | STRING_INSTRU(STRING_INSTRUCTION8086(ADC)), // opcode(02 -> 0b00000010) -> (adc) (mod, reg, r/m), (disp_low), (disp_high)
    [opcodes_8086_ADC_mem16_inverse] = MOD_RM_REG_MASK | DISP_LOW_MASK | DISP_HIGH_MASK | REG_MEM_16_MASK | STRING_INSTRU(STRING_INSTRUCTION8086(ADC)), // opcode(03 -> 0b00000011) -> (adc) (mod, reg, r/m), (disp_low), (disp_high)

    [opcodes_8086_ADC_al] = INMED8_MASK | DISP_HIGH_MASK | DATA_MASK_8086 | STRING_INSTRU(STRING_INSTRUCTION8086(ADD)),                  // opcode(04 -> 0b00010100)  -> (add) (data), (data if w = 1)
    [opcodes_8086_ADC_ax] = INMED16_MASK | DISP_HIGH_MASK | DATA_MASK_8086 | STRING_INSTRU(STRING_INSTRUCTION8086(ADD)),                  // opcode(04 -> 0b00010101)  -> (add) (data), (data if w = 1)

    // push ss
    [opcodes_8086_PUSH_ss] = REG_SEG_MASK | STRING_INSTRU(STRING_INSTRUCTION8086(PUSH)),

    // pop ss
    [opcodes_8086_POP_ss] = REG_SEG_MASK | STRING_INSTRU(STRING_INSTRUCTION8086(POP)),

    [opcodes_8086_SBB_mem8] = MOD_RM_REG_MASK | DISP_LOW_MASK | DISP_HIGH_MASK | REG_MEM_8_MASK  | STRING_INSTRU(STRING_INSTRUCTION8086(SBB)),

    [opcodes_8086_SBB_mem16] = MOD_RM_REG_MASK | DISP_LOW_MASK | DISP_HIGH_MASK | REG_MEM_16_MASK | STRING_INSTRU(STRING_INSTRUCTION8086(SBB)),

    [opcodes_8086_SBB_mem8_inverse] = MOD_RM_REG_MASK | DISP_LOW_MASK | DISP_HIGH_MASK | REG_MEM_8_MASK  | STRING_INSTRU(STRING_INSTRUCTION8086(SBB)),

    [opcodes_8086_SBB_mem16_inverse] = MOD_RM_REG_MASK | DISP_LOW_MASK | DISP_HIGH_MASK | REG_MEM_16_MASK | STRING_INSTRU(STRING_INSTRUCTION8086(SBB)),

    [opcodes_8086_SBB_al] = INMED8_MASK | STRING_INSTRU(STRING_INSTRUCTION8086(SBB)),

    [opcodes_8086_SBB_ax] = INMED16_MASK | STRING_INSTRU(STRING_INSTRUCTION8086(SBB)),

    // push ds
    [opcodes_8086_PUSH_ds] = REG_SEG_MASK | STRING_INSTRU(STRING_INSTRUCTION8086(PUSH)),

    // pop ds
    [opcodes_8086_POP_ds] = REG_SEG_MASK | STRING_INSTRU(STRING_INSTRUCTION8086(POP)),

    [opcodes_8086_AND_mem8] = MOD_RM_REG_MASK | DISP_LOW_MASK | DISP_HIGH_MASK | REG_MEM_8_MASK  | STRING_INSTRU(STRING_INSTRUCTION8086(AND)),

    [opcodes_8086_AND_mem16] = MOD_RM_REG_MASK | DISP_LOW_MASK | DISP_HIGH_MASK | REG_MEM_16_MASK | STRING_INSTRU(STRING_INSTRUCTION8086(AND)),

    [opcodes_8086_AND_mem8_inverse] = MOD_RM_REG_MASK | DISP_LOW_MASK | DISP_HIGH_MASK | REG_MEM_8_MASK  | STRING_INSTRU(STRING_INSTRUCTION8086(AND)),

    [opcodes_8086_AND_mem16_inverse] = MOD_RM_REG_MASK | DISP_LOW_MASK | DISP_HIGH_MASK | REG_MEM_16_MASK | STRING_INSTRU(STRING_INSTRUCTION8086(AND)),

    [opcodes_8086_AND_al] = INMED8_MASK  | STRING_INSTRU(STRING_INSTRUCTION8086(AND)),

    [opcodes_8086_AND_ax] = INMED16_MASK | STRING_INSTRU(STRING_INSTRUCTION8086(AND)),

    [0x26] = MASK_PREFIX,

    [opcodes_8086_DAA] = STRING_INSTRU(STRING_INSTRUCTION8086(DAA)),

    [opcodes_8086_SUB_mem8] = MOD_RM_REG_MASK | DISP_LOW_MASK | DISP_HIGH_MASK | REG_MEM_8_MASK  | STRING_INSTRU(STRING_INSTRUCTION8086(SUB)),

    [opcodes_8086_SUB_mem16] = MOD_RM_REG_MASK | DISP_LOW_MASK | DISP_HIGH_MASK | REG_MEM_16_MASK | STRING_INSTRU(STRING_INSTRUCTION8086(SUB)),

    [opcodes_8086_SUB_mem8_inverse] = MOD_RM_REG_MASK | DISP_LOW_MASK | DISP_HIGH_MASK | REG_MEM_8_MASK  | STRING_INSTRU(STRING_INSTRUCTION8086(SUB)),

    [opcodes_8086_SUB_mem16_inverse] = MOD_RM_REG_MASK | DISP_LOW_MASK | DISP_HIGH_MASK | REG_MEM_16_MASK | STRING_INSTRU(STRING_INSTRUCTION8086(SUB)),

    [opcodes_8086_SUB_al] = INMED8_MASK  | STRING_INSTRU(STRING_INSTRUCTION8086(SUB)),

    [opcodes_8086_SUB_ax] = INMED16_MASK | STRING_INSTRU(STRING_INSTRUCTION8086(SUB)),

    [0x2e] = MASK_PREFIX,

    [opcodes_8086_DAS] =  STRING_INSTRU(STRING_INSTRUCTION8086(DAS)),

    [opcodes_8086_XOR_mem8] = MOD_RM_REG_MASK | DISP_LOW_MASK | DISP_HIGH_MASK | REG_MEM_8_MASK  | STRING_INSTRU(STRING_INSTRUCTION8086(XOR)),

    [opcodes_8086_XOR_mem16] = MOD_RM_REG_MASK | DISP_LOW_MASK | DISP_HIGH_MASK | REG_MEM_16_MASK | STRING_INSTRU(STRING_INSTRUCTION8086(XOR)),

    [opcodes_8086_XOR_mem8_inverse] = MOD_RM_REG_MASK | DISP_LOW_MASK | DISP_HIGH_MASK | REG_MEM_8_MASK  | STRING_INSTRU(STRING_INSTRUCTION8086(XOR)),

    [opcodes_8086_XOR_mem16_inverse] = MOD_RM_REG_MASK | DISP_LOW_MASK | DISP_HIGH_MASK | REG_MEM_16_MASK | STRING_INSTRU(STRING_INSTRUCTION8086(XOR)),

    [opcodes_8086_XOR_al] = INMED8_MASK  | STRING_INSTRU(STRING_INSTRUCTION8086(XOR)),

    [opcodes_8086_XOR_ax] = INMED16_MASK | STRING_INSTRU(STRING_INSTRUCTION8086(XOR)),

    [0x36] = MASK_PREFIX,

    [opcodes_8086_AAA] = STRING_INSTRU(STRING_INSTRUCTION8086(AAA)),

    [opcodes_8086_CMP_mem8] = MOD_RM_REG_MASK | DISP_LOW_MASK | DISP_HIGH_MASK | REG_MEM_8_MASK  | STRING_INSTRU(STRING_INSTRUCTION8086(CMP)),

    [opcodes_8086_CMP_mem16] = MOD_RM_REG_MASK | DISP_LOW_MASK | DISP_HIGH_MASK | REG_MEM_16_MASK | STRING_INSTRU(STRING_INSTRUCTION8086(CMP)),

    [opcodes_8086_CMP_mem8_inverse] = MOD_RM_REG_MASK | DISP_LOW_MASK | DISP_HIGH_MASK | REG_MEM_8_MASK  | STRING_INSTRU(STRING_INSTRUCTION8086(CMP)),

    [opcodes_8086_CMP_mem16_inverse] = MOD_RM_REG_MASK | DISP_LOW_MASK | DISP_HIGH_MASK | REG_MEM_16_MASK | STRING_INSTRU(STRING_INSTRUCTION8086(CMP)),

    [opcodes_8086_CMP_al] = INMED8_MASK | STRING_INSTRU(STRING_INSTRUCTION8086(CMP)),

    [opcodes_8086_CMP_ax] = INMED16_MASK | STRING_INSTRU(STRING_INSTRUCTION8086(CMP)),

    // prefijo DS
    [0x3e] = MASK_PREFIX,

    [opcodes_8086_AAS] =  STRING_INSTRU(STRING_INSTRUCTION8086(AAS)),

    [opcodes_8086_INC_ax] =  STRING_INSTRU(STRING_INSTRUCTION8086(INC)),

    [opcodes_8086_INC_cx] = STRING_INSTRU(STRING_INSTRUCTION8086(INC)),

    [opcodes_8086_INC_dx] = STRING_INSTRU(STRING_INSTRUCTION8086(INC)),

    [opcodes_8086_INC_bx] = STRING_INSTRU(STRING_INSTRUCTION8086(INC)),

    [opcodes_8086_INC_sp] = STRING_INSTRU(STRING_INSTRUCTION8086(INC)),

    [opcodes_8086_INC_bp] = STRING_INSTRU(STRING_INSTRUCTION8086(INC)),

    [opcodes_8086_INC_si] = STRING_INSTRU(STRING_INSTRUCTION8086(INC)),

    [opcodes_8086_INC_di] = STRING_INSTRU(STRING_INSTRUCTION8086(INC)),

    [opcodes_8086_DEC_ax] = STRING_INSTRU(STRING_INSTRUCTION8086(DEC)),

    [opcodes_8086_DEC_cx] = STRING_INSTRU(STRING_INSTRUCTION8086(DEC)),

    [opcodes_8086_DEC_dx] = STRING_INSTRU(STRING_INSTRUCTION8086(DEC)),

    [opcodes_8086_DEC_bx] = STRING_INSTRU(STRING_INSTRUCTION8086(DEC)),

    [opcodes_8086_DEC_sp] = STRING_INSTRU(STRING_INSTRUCTION8086(DEC)),

    [opcodes_8086_DEC_bp] = STRING_INSTRU(STRING_INSTRUCTION8086(DEC)),

    [opcodes_8086_DEC_si] = STRING_INSTRU(STRING_INSTRUCTION8086(DEC)),

    [opcodes_8086_DEC_di] = STRING_INSTRU(STRING_INSTRUCTION8086(DEC)),

    [opcodes_8086_PUSH_ax] = STRING_INSTRU(STRING_INSTRUCTION8086(PUSH)),

    [opcodes_8086_PUSH_cx] = STRING_INSTRU(STRING_INSTRUCTION8086(PUSH)),

    [opcodes_8086_PUSH_dx] = STRING_INSTRU(STRING_INSTRUCTION8086(PUSH)),

    [opcodes_8086_PUSH_bx] = STRING_INSTRU(STRING_INSTRUCTION8086(PUSH)),

    [opcodes_8086_PUSH_sp] = STRING_INSTRU(STRING_INSTRUCTION8086(PUSH)),

    [opcodes_8086_PUSH_bp] = STRING_INSTRU(STRING_INSTRUCTION8086(PUSH)),

    [opcodes_8086_PUSH_si] = STRING_INSTRU(STRING_INSTRUCTION8086(PUSH)),

    [opcodes_8086_PUSH_di] = STRING_INSTRU(STRING_INSTRUCTION8086(PUSH)),

    [opcodes_8086_POP_ax] = STRING_INSTRU(STRING_INSTRUCTION8086(POP)),

    [opcodes_8086_POP_cx] = STRING_INSTRU(STRING_INSTRUCTION8086(POP)),

    [opcodes_8086_POP_dx] = STRING_INSTRU(STRING_INSTRUCTION8086(POP)),

    [opcodes_8086_POP_bx] = STRING_INSTRU(STRING_INSTRUCTION8086(POP)),

    [opcodes_8086_POP_sp] = STRING_INSTRU(STRING_INSTRUCTION8086(POP)),

    [opcodes_8086_POP_bp] = STRING_INSTRU(STRING_INSTRUCTION8086(POP)),

    [opcodes_8086_POP_si] = STRING_INSTRU(STRING_INSTRUCTION8086(POP)),

    [opcodes_8086_POP_di] = STRING_INSTRU(STRING_INSTRUCTION8086(POP)),


    // Jxx(saltos condicionales) (no documentados)
    [undocumented_opcodes_8086_JO] = TTTN_MASK | UNDOCUMENTED_OPCODE_MASK | STRING_INSTRU(STRING_INSTRUCTION8086(JO)),    // opcode(60 -> 0b01100000) -> 0x60 (equivalent: 0x70) = JO
    [undocumented_opcodes_8086_JNO] = TTTN_MASK | UNDOCUMENTED_OPCODE_MASK | STRING_INSTRU(STRING_INSTRUCTION8086(JNO)),   // opcode(61 -> 0b01100001) -> 0x61 (equivalent: 0x71) = JNO
    [undocumented_opcodes_8086_JC] = TTTN_MASK | UNDOCUMENTED_OPCODE_MASK | STRING_INSTRU(STRING_INSTRUCTION8086(JB)),    // opcode(62 -> 0b01100010) -> 0x62 (equivalent: 0x72) = JC
    [undocumented_opcodes_8086_JAE] = TTTN_MASK | UNDOCUMENTED_OPCODE_MASK | STRING_INSTRU(STRING_INSTRUCTION8086(JNB)),   // opcode(63 -> 0b01100011) -> 0x63 (equivalent: 0x73) = JAE
    [undocumented_opcodes_8086_JE] = TTTN_MASK | UNDOCUMENTED_OPCODE_MASK | STRING_INSTRU(STRING_INSTRUCTION8086(JZ)),    // opcode(64 -> 0b01100100) -> 0x64 (equivalent: 0x74) = JE
    [undocumented_opcodes_8086_JNZ] = TTTN_MASK | UNDOCUMENTED_OPCODE_MASK | STRING_INSTRU(STRING_INSTRUCTION8086(JNZ)),   // opcode(65 -> 0b01100101) -> 0x65 (equivalent: 0x75) = JNZ
    [undocumented_opcodes_8086_JBE] = TTTN_MASK | UNDOCUMENTED_OPCODE_MASK | STRING_INSTRU(STRING_INSTRUCTION8086(JBE)),   // opcode(66 -> 0b01100110) -> 0x66 (equivalent: 0x76) = JBE
    [undocumented_opcodes_8086_JA] = TTTN_MASK | UNDOCUMENTED_OPCODE_MASK | STRING_INSTRU(STRING_INSTRUCTION8086(JNBE)),  // opcode(67 -> 0b01100111) -> 0x67 (equivalent: 0x77) = JA
    [undocumented_opcodes_8086_JS] = TTTN_MASK | UNDOCUMENTED_OPCODE_MASK | STRING_INSTRU(STRING_INSTRUCTION8086(JS)),    // opcode(68 -> 0b01101000) -> 0x68 (equivalent: 0x78) = JS
    [undocumented_opcodes_8086_JNS] = TTTN_MASK | UNDOCUMENTED_OPCODE_MASK | STRING_INSTRU(STRING_INSTRUCTION8086(JNS)),   // opcode(69 -> 0b01101001) -> 0x69 (equivalent: 0x79) = JNS
    [undocumented_opcodes_8086_JPE] = TTTN_MASK | UNDOCUMENTED_OPCODE_MASK | STRING_INSTRU(STRING_INSTRUCTION8086(JP)),    // opcode(6a -> 0b01101010) -> 0x6A (equivalent: 0x7A) = JPE
    [undocumented_opcodes_8086_JNP] = TTTN_MASK | UNDOCUMENTED_OPCODE_MASK | STRING_INSTRU(STRING_INSTRUCTION8086(JNP)),   // opcode(6b -> 0b01101011) -> 0x6B (equivalent: 0x7B) = JNP
    [undocumented_opcodes_8086_JL] = TTTN_MASK | UNDOCUMENTED_OPCODE_MASK | STRING_INSTRU(STRING_INSTRUCTION8086(JL)),    // opcode(6c -> 0b01101100) -> 0x6C (equivalent: 0x7C) = JL
    [undocumented_opcodes_8086_JGE] = TTTN_MASK | UNDOCUMENTED_OPCODE_MASK | STRING_INSTRU(STRING_INSTRUCTION8086(JNL)),   // opcode(6d -> 0b01101101) -> 0x6D (equivalent: 0x7D) = JGE
    [undocumented_opcodes_8086_JLE] = TTTN_MASK | UNDOCUMENTED_OPCODE_MASK | STRING_INSTRU(STRING_INSTRUCTION8086(JLE)),   // opcode(6e -> 0b01101110) -> 0x6E (equivalent: 0x7E) = JLE
    [undocumented_opcodes_8086_JG] = TTTN_MASK | UNDOCUMENTED_OPCODE_MASK | STRING_INSTRU(STRING_INSTRUCTION8086(JNLE)),  // opcode(6f -> 0b01101111) -> 0x6F (equivalent: 0x7F) = JG
    // Jxx(saltos condicionales) (documentados)
    [opcodes_8086_JO] = TTTN_MASK | STRING_INSTRU(STRING_INSTRUCTION8086(JO)),                               // opcode(70 -> 0b01110000) -> 0x70 (equivalent: 0x60) = JO
    [opcodes_8086_JNO] = TTTN_MASK | STRING_INSTRU(STRING_INSTRUCTION8086(JNO)),                              // opcode(71 -> 0b01110001) -> 0x71 (equivalent: 0x61) = JNO
    [opcodes_8086_JC] = TTTN_MASK | STRING_INSTRU(STRING_INSTRUCTION8086(JB)),                               // opcode(72 -> 0b01110010) -> 0x72 (equivalent: 0x62) = JC
    [opcodes_8086_JAE] = TTTN_MASK | STRING_INSTRU(STRING_INSTRUCTION8086(JNB)),                              // opcode(73 -> 0b01110011) -> 0x73 (equivalent: 0x63) = JAE
    [opcodes_8086_JE] = TTTN_MASK | STRING_INSTRU(STRING_INSTRUCTION8086(JZ)),                               // opcode(74 -> 0b01110100) -> 0x74 (equivalent: 0x64) = JE
    [opcodes_8086_JNZ] = TTTN_MASK | STRING_INSTRU(STRING_INSTRUCTION8086(JNZ)),                              // opcode(75 -> 0b01110101) -> 0x75 (equivalent: 0x65) = JNZ
    [opcodes_8086_JBE] = TTTN_MASK | STRING_INSTRU(STRING_INSTRUCTION8086(JBE)),                              // opcode(76 -> 0b01110110) -> 0x76 (equivalent: 0x66) = JBE
    [opcodes_8086_JA] = TTTN_MASK | STRING_INSTRU(STRING_INSTRUCTION8086(JNBE)),                             // opcode(77 -> 0b01110111) -> 0x77 (equivalent: 0x67) = JA
    [opcodes_8086_JS] = TTTN_MASK | STRING_INSTRU(STRING_INSTRUCTION8086(JS)),                               // opcode(78 -> 0b01111000) -> 0x78 (equivalent: 0x68) = JS
    [opcodes_8086_JNS] = TTTN_MASK | STRING_INSTRU(STRING_INSTRUCTION8086(JNS)),                              // opcode(79 -> 0b01111001) -> 0x79 (equivalent: 0x69) = JNS
    [opcodes_8086_JPE] = TTTN_MASK | STRING_INSTRU(STRING_INSTRUCTION8086(JP)),                               // opcode(7a -> 0b01111010) -> 0x7A (equivalent: 0x6A) = JPE
    [opcodes_8086_JNP] = TTTN_MASK | STRING_INSTRU(STRING_INSTRUCTION8086(JNP)),                              // opcode(7b -> 0b01111011) -> 0x7B (equivalent: 0x6B) = JNP
    [opcodes_8086_JL] = TTTN_MASK | STRING_INSTRU(STRING_INSTRUCTION8086(JL)),                               // opcode(7c -> 0b01111100) -> 0x7C (equivalent: 0x6C) = JL
    [opcodes_8086_JGE] = TTTN_MASK | STRING_INSTRU(STRING_INSTRUCTION8086(JNL)),                              // opcode(7d -> 0b01111101) -> 0x7D (equivalent: 0x6D) = JGE
    [opcodes_8086_JLE] = TTTN_MASK | STRING_INSTRU(STRING_INSTRUCTION8086(JLE)),                              // opcode(7e -> 0b01111110) -> 0x7E (equivalent: 0x6E) = JLE
    [opcodes_8086_JG] = TTTN_MASK | STRING_INSTRU(STRING_INSTRUCTION8086(JNLE)),                             // opcode(7f -> 0b01111111) -> 0x7F (equivalent: 0x6F) = JG


    // tiene Mod/rm, pero se usa para identificar varias instrucciones atraves del campo reg
    [opcodes_8086_ADD_inmmed8] = REG_MEM_8_MASK | INMED8_MASK | MOD_RM_REG_MASK | DATA_MASK_8086,
    //[0b10000000] = MOD_RM_REG_MASK | DISP_LOW_MASK | DISP_HIGH_MASK | DATA_MASK_8086, // opcode(80 -> 0b10000000) -> (add/adc) (mod, reg, r/m), (disp_low), (disp_high), (data), (data if s = W=01)
    [opcodes_8086_ADD_inmmed16] = MOD_RM_REG_MASK | REG_MEM_16_MASK | INMED16_MASK | DISP_HIGH_MASK | DATA_MASK_8086, // opcode(81 -> 0b10000001) -> (add/adc) (mod, reg, r/m), (disp_low), (disp_high), (data), (data if s = W=01)
    [opcodes_8086_ADD_inmmed8_2] = REG_MEM_8_MASK  | INMED8_MASK     | MOD_RM_REG_MASK | DISP_LOW_MASK | DISP_HIGH_MASK | DATA_MASK_8086, // opcode(82 -> 0b10000010) -> (add/adc) (mod, reg, r/m), (disp_low), (disp_high), (data), (data if s = W=01)
    
    // instruccion reg16/mem16, inmed8
    [opcodes_8086_ADD_inmmed8_reg_mem16] = REG_MEM_16_MASK | INMED8_MASK     | MOD_RM_REG_MASK | DISP_LOW_MASK | DISP_HIGH_MASK | DATA_MASK_8086 | DATA_SX_MASK, // opcode(83 -> 0b10000011) -> (add/adc) (mod, reg, r/m), (disp_low), (disp_high), (data), (data if s = W=01)

    [opcodes_8086_TEST_reg8] = STRING_INSTRU(STRING_INSTRUCTION8086(TEST)) | MOD_RM_REG_MASK | DISP_LOW_MASK | DISP_HIGH_MASK,

    [opcodes_8086_TEST_reg16] = STRING_INSTRU(STRING_INSTRUCTION8086(TEST)) | MOD_RM_REG_MASK | DISP_LOW_MASK | DISP_HIGH_MASK,

    [opcodes_8086_XCHG_reg8] = STRING_INSTRU(STRING_INSTRUCTION8086(XCHG)) | MOD_RM_REG_MASK | DISP_LOW_MASK | DISP_HIGH_MASK,

    [opcodes_8086_XCHG_reg16] = STRING_INSTRU(STRING_INSTRUCTION8086(XCHG)) | MOD_RM_REG_MASK | DISP_LOW_MASK | DISP_HIGH_MASK,

    [opcodes_8086_MOV_reg8] = STRING_INSTRU(STRING_INSTRUCTION8086(MOV)) | MOD_RM_REG_MASK | DISP_LOW_MASK | DISP_HIGH_MASK,

    [opcodes_8086_MOV_reg16] = STRING_INSTRU(STRING_INSTRUCTION8086(MOV)) | MOD_RM_REG_MASK | DISP_LOW_MASK | DISP_HIGH_MASK,

    [opcodes_8086_MOV_mem8] = STRING_INSTRU(STRING_INSTRUCTION8086(MOV)) | MOD_RM_REG_MASK | DISP_LOW_MASK | DISP_HIGH_MASK,

    [opcodes_8086_MOV_mem16] = STRING_INSTRU(STRING_INSTRUCTION8086(MOV)) | MOD_RM_REG_MASK | DISP_LOW_MASK | DISP_HIGH_MASK,

    [opcodes_8086_MOV_reg_mem16_segreg] = STRING_INSTRU(STRING_INSTRUCTION8086(MOV)) | MOD_RM_REG_MASK | DISP_LOW_MASK | DISP_HIGH_MASK,

    [opcodes_8086_LEA_mem16] = STRING_INSTRU(STRING_INSTRUCTION8086(LEA)) | MOD_RM_REG_MASK | DISP_LOW_MASK | DISP_HIGH_MASK,

    [opcodes_8086_MOV_segreg_reg_mem16] = STRING_INSTRU(STRING_INSTRUCTION8086(MOV)) | MOD_RM_REG_MASK | DISP_LOW_MASK | DISP_HIGH_MASK,

    [opcodes_8086_POP_reg_mem16] = STRING_INSTRU(STRING_INSTRUCTION8086(POP)) | MOD_RM_REG_MASK,

    // INTERCAMBIA AX CON AX
    [opcodes_8086_XCHG_ax_ax] = STRING_INSTRU(STRING_INSTRUCTION8086(NOP)),

    [opcodes_8086_XCHG_ax_cx] = STRING_INSTRU(STRING_INSTRUCTION8086(XCHG)),

    [opcodes_8086_XCHG_ax_dx] = STRING_INSTRU(STRING_INSTRUCTION8086(XCHG)),

    [opcodes_8086_XCHG_ax_bx] = STRING_INSTRU(STRING_INSTRUCTION8086(XCHG)),

    [opcodes_8086_XCHG_ax_sp] = STRING_INSTRU(STRING_INSTRUCTION8086(XCHG)),

    [opcodes_8086_XCHG_ax_bp] = STRING_INSTRU(STRING_INSTRUCTION8086(XCHG)),

    [opcodes_8086_XCHG_ax_si] = STRING_INSTRU(STRING_INSTRUCTION8086(XCHG)),

    [opcodes_8086_XCHG_ax_di] = STRING_INSTRU(STRING_INSTRUCTION8086(XCHG)),

    [opcodes_8086_CBW] = STRING_INSTRU(STRING_INSTRUCTION8086(CBW)),

    [opcodes_8086_CWD] = STRING_INSTRU(STRING_INSTRUCTION8086(CWD)),

    [opcodes_8086_CALL_FAR] = STRING_INSTRU(STRING_INSTRUCTION8086(CALL)) | DISP_LOW_MASK | DISP_HIGH_MASK | INMED16_MASK | DIS_HIGH_MASK,

    [opcodes_8086_WAIT] = STRING_INSTRU(STRING_INSTRUCTION8086(WAIT)),

    [opcodes_8086_PUSHF] = STRING_INSTRU(STRING_INSTRUCTION8086(PUSHF)),

    [opcodes_8086_POPF] = STRING_INSTRU(STRING_INSTRUCTION8086(POPF)),

    [opcodes_8086_SAHF] = STRING_INSTRU(STRING_INSTRUCTION8086(SAHF)),

    [opcodes_8086_LAHF] = STRING_INSTRU(STRING_INSTRUCTION8086(LAHF)),

    [opcodes_8086_MOV_al_mem8] = STRING_INSTRU(STRING_INSTRUCTION8086(MOV)) | INMED8_MASK ,

    [opcodes_8086_MOV_ax_mem16] = STRING_INSTRU(STRING_INSTRUCTION8086(MOV)) | INMED16_MASK ,

    [opcodes_8086_MOV_mem8_al] = STRING_INSTRU(STRING_INSTRUCTION8086(MOV)) | INMED8_MASK ,

    [opcodes_8086_MOV_mem16_ax] = STRING_INSTRU(STRING_INSTRUCTION8086(MOV)) | INMED16_MASK ,

    [opcodes_8086_MOVS_ptr8] = STRING_INSTRU(STRING_INSTRUCTION8086(MOVS)),

    [opcodes_8086_MOVS_ptr16] = STRING_INSTRU(STRING_INSTRUCTION8086(MOVS)),

    [opcodes_8086_CMPS_ptr8] = STRING_INSTRU(STRING_INSTRUCTION8086(CMPS)),

    [opcodes_8086_CMPS_ptr16] = STRING_INSTRU(STRING_INSTRUCTION8086(CMPS)),

    [opcodes_8086_TEST_al_inmmed8] = INMED8_MASK | STRING_INSTRU(STRING_INSTRUCTION8086(TEST)),

    [opcodes_8086_TEST_ax_inmmed16] = INMED16_MASK | STRING_INSTRU(STRING_INSTRUCTION8086(TEST)),

    [opcodes_8086_STOS_ptr8] = STRING_INSTRU(STRING_INSTRUCTION8086(STOS)),

    [opcodes_8086_STOS_ptr16] = STRING_INSTRU(STRING_INSTRUCTION8086(STOS)),

    [opcodes_8086_LODS_ptr8] = STRING_INSTRU(STRING_INSTRUCTION8086(LODS)),

    [opcodes_8086_LODS_ptr16] = STRING_INSTRU(STRING_INSTRUCTION8086(LODS)),

    [opcodes_8086_SCAS_ptr8] = STRING_INSTRU(STRING_INSTRUCTION8086(SCAS)),

    [opcodes_8086_SCAS_ptr16] = STRING_INSTRU(STRING_INSTRUCTION8086(SCAS)),

    [opcodes_8086_MOV_al_inmmed8] = INMED8_MASK | STRING_INSTRU(STRING_INSTRUCTION8086(MOV)),
    [opcodes_8086_MOV_cl_inmmed8] = INMED8_MASK | STRING_INSTRU(STRING_INSTRUCTION8086(MOV)),
    [opcodes_8086_MOV_dl_inmmed8] = INMED8_MASK | STRING_INSTRU(STRING_INSTRUCTION8086(MOV)),
    [opcodes_8086_MOV_bl_inmmed8] = INMED8_MASK | STRING_INSTRU(STRING_INSTRUCTION8086(MOV)),
    [opcodes_8086_MOV_ah_inmmed8] = INMED8_MASK | STRING_INSTRU(STRING_INSTRUCTION8086(MOV)),
    [opcodes_8086_MOV_ch_inmmed8] = INMED8_MASK | STRING_INSTRU(STRING_INSTRUCTION8086(MOV)),
    [opcodes_8086_MOV_dh_inmmed8] = INMED8_MASK | STRING_INSTRU(STRING_INSTRUCTION8086(MOV)),
    [opcodes_8086_MOV_bh_inmmed8] = INMED16_MASK | STRING_INSTRU(STRING_INSTRUCTION8086(MOV)),

    [opcodes_8086_MOV_ax_inmmed16] = INMED16_MASK | STRING_INSTRU(STRING_INSTRUCTION8086(MOV)),
    [opcodes_8086_MOV_cx_inmmed16] = INMED16_MASK | STRING_INSTRU(STRING_INSTRUCTION8086(MOV)),
    [opcodes_8086_MOV_dx_inmmed16] = INMED16_MASK | STRING_INSTRU(STRING_INSTRUCTION8086(MOV)),
    [opcodes_8086_MOV_bx_inmmed16] = INMED16_MASK | STRING_INSTRU(STRING_INSTRUCTION8086(MOV)),
    [opcodes_8086_MOV_sp_inmmed16] = INMED16_MASK | STRING_INSTRU(STRING_INSTRUCTION8086(MOV)),
    [opcodes_8086_MOV_bp_inmmed16] = INMED16_MASK | STRING_INSTRU(STRING_INSTRUCTION8086(MOV)),
    [opcodes_8086_MOV_si_inmmed16] = INMED16_MASK | STRING_INSTRU(STRING_INSTRUCTION8086(MOV)),
    [opcodes_8086_MOV_di_inmmed16] = INMED16_MASK | STRING_INSTRU(STRING_INSTRUCTION8086(MOV)),

    // ret near inmed16, es la misma que C2.  (intra seg)
    [undocumented_opcodes_8086_RET_NEAR_inmmed16_intraseg] = INMED16_MASK | UNDOCUMENTED_OPCODE_MASK | STRING_INSTRU(STRING_INSTRUCTION8086(RET)), // opcode(192 -> 0b11000000) -> 0xC0 (equivalent: 0xC2) = ret near inmed16

    // ret ( no documentada).  (intra seg)
    [undocumented_opcodes_8086_RET_intraseg] = UNDOCUMENTED_OPCODE_MASK | STRING_INSTRU(STRING_INSTRUCTION8086(RET)),                // opcode(193 -> 0b11000001) -> 0xC1 (equivalent: 0xC3) = ret

    // ret near inmed16, es la misma que C0.  (intra seg)
    [opcodes_8086_RET_NEAR_inmmed16_intraseg] = INMED16_MASK | STRING_INSTRU(STRING_INSTRUCTION8086(RET)), // opcode(194 -> 0b11000010) -> 0xC2 (equivalent: 0xC0) = ret near inmed16

    // ret ( documentada ), no tiene flags.  (intra seg)
    [opcodes_8086_RET_intraseg] =  STRING_INSTRU(STRING_INSTRUCTION8086(RET)),                                          // opcode(195 -> 0b11000011) -> 0xC3 (equivalent: 0xC1) = ret

    [opcodes_8086_LES_mem16] = STRING_INSTRU(STRING_INSTRUCTION8086(LES)) | MOD_RM_REG_MASK | DISP_LOW_MASK | DISP_HIGH_MASK,
    [opcodes_8086_LDS_mem16] = STRING_INSTRU(STRING_INSTRUCTION8086(LDS)) | MOD_RM_REG_MASK | DISP_LOW_MASK | DISP_HIGH_MASK,
    [opcodes_8086_MOV_mem8_inmmed8] = STRING_INSTRU(STRING_INSTRUCTION8086(MOV)) | MOD_RM_REG_MASK | INMED8_MASK ,
    [opcodes_8086_MOV_mem16_inmmed16] = STRING_INSTRU(STRING_INSTRUCTION8086(MOV)) | MOD_RM_REG_MASK | INMED16_MASK,

    // ret far inmed16, es la misma que CA. (inter-segment)
    [undocumented_opcodes_8086_RET_NEAR_inmmed16_intersegment] = INMED16_MASK | UNDOCUMENTED_OPCODE_MASK | STRING_INSTRU(STRING_INSTRUCTION8086(RET)), // opcode(200 -> 0b11001000) -> 0xC8 (equivalent: 0xCA) = ret far inmed16

    // ret far ( no documentada). (inter-segment)
    [undocumented_opcodes_8086_RET_intersegment] = UNDOCUMENTED_OPCODE_MASK | STRING_INSTRU(STRING_INSTRUCTION8086(RET)),                // opcode(201 -> 0b11001001) -> 0xC9 (equivalent: 0xCB) = ret far

    // ret far inmed16, es la misma que C8. (inter-segment)
    [opcodes_8086_RET_NEAR_inmmed16_intersegment] = INMED16_MASK | STRING_INSTRU(STRING_INSTRUCTION8086(RET)),                            // opcode(202 -> 0b11001010) -> 0xCA (equivalent: 0xC8) = ret far inmed16

    // ret far (documentada). (inter-segment)
    [opcodes_8086_RET_intersegment] = 0 | STRING_INSTRU(STRING_INSTRUCTION8086(RET)),                                       // opcode(203 -> 0b11001011) -> 0xCB (equivalent: 0xC9) = ret far

    [opcodes_8086_INT_3] = STRING_INSTRU(STRING_INSTRUCTION8086(INT_3)),

    [opcodes_8086_INT_inmmed8] = INMED8_MASK | STRING_INSTRU(STRING_INSTRUCTION8086(INT)),

    [opcodes_8086_INTO] = STRING_INSTRU(STRING_INSTRUCTION8086(INTO)),

    [opcodes_8086_IRET] = STRING_INSTRU(STRING_INSTRUCTION8086(IRET)),


    // rol/ror/rcl/rcr/shl/shr/shr/sar reg8/mem8, 1
    // cuando el segundo byte se codifica como 110 en reg, se transforma en una instruccion no documentada
    /*
     * Opcode D0h xx110xxxb
     * Documented equivalent: None
     * Instruction: SETMO byte R/M
     * Action: Moves byte -1 (FFh) to its 8-bit operand and set flags accordingly
     * 
     * 8-bit operand <— FFh (AL for D0F0h, CL for D0F1h…)
     * Clear CF (NC)
     * Set PF (PE)
     * Clear AF (NA)
     * Clear ZF (NZ)
     * Set SF (NG)
     * Clear OF (NV)
     * Byte operand and flags (not sure about AF) are modified as if the following instruction was executed: OR AL, 0FFh
     */
    [opcodes_8086_ROL_reg_mem8_1] = REG_MEM_8_MASK | MOD_RM_REG_MASK | DISP_LOW_MASK | DISP_HIGH_MASK,         // opcode(d0 -> 0b11010000)

    /*
     * Documented equivalent: None
     * Instruction: SETMO word R/M
     * Action: Moves word -1 (FFFFh) to its 16-bit operand and set flags accordingly
     * 
     * 16-bit operand <— FFFFh (AX for D1F0h, CX for D1F1h…)
     * Clear CF (NC)
     * Set PF (PE)
     * Clear AF (NA)
     * Clear ZF (NZ)
     * Set SF (NG)
     * Clear OF (NV)
     * Word operand and flags (not sure about AF) are modified as if the following instruction was executed: OR AX, 0FFFFh
     */
    // rol/ror/rcl/rcr/shl/shr/shr/sar reg16/mem16, 1
    // cuando el segundo byte se codifica como 110 en reg, se transforma en una instruccion no documentada
    [opcodes_8086_ROL_reg_mem16_1] = REG_MEM_16_MASK | MOD_RM_REG_MASK | DISP_LOW_MASK | DISP_HIGH_MASK,         // opcode(d1 -> 0b11010001)

    // rol/ror/rcl/rcr/shl/shr/shr/sar reg8/mem8, cl
    // cuando el segundo byte se codifica como 110 en reg, se transforma en una instruccion no documentada
    /*
     * Opcode D2h xx110xxxb
     * Documented equivalent: None
     * Instruction: SETMOC byte R/M
     * Action: If CL != 0, changes 8-bit operand and flags like SETMO (D0h xx110xxxb instruction code), otherwise nothing changes
     * 
     * Notes:
     * “SETMOC” stands for “SET Minus One if CL != 0”
     * D2h is the first byte of the byte-operand, CL-positions shift instructions (in the instruction matrix: “Shift b,v”). The type of shift is specified in bits 3 to 5 of the second byte, but it is not documented when these bits are 110b.
     * The destination operand can be specified, but the zero-test is always performed on CL.
    */
    [opcodes_8086_ROL_reg_mem8_cl] = REG_MEM_8_MASK | MOD_RM_REG_MASK | DISP_LOW_MASK | DISP_HIGH_MASK,         // opcode(d2 -> 0b11010010)


    // rol/ror/rcl/rcr/shl/shr/shr/sar reg16/mem16, cl
    // cuando el segundo byte se codifica como 110 en reg, se transforma en una instruccion no documentada
    /*
     * Opcode D3h xx110xxxb
     * Documented equivalent: None
     * Instruction: SETMOC word R/M
     * Action: If CL != 0, changes 16-bit operand and flags like SETMO (D1h xx110xxxb instruction code), otherwise nothing changes
     * 
     * Notes:
     * 
     * “SETMOC” stands for “SET Minus One if CL != 0”
     * D3h is the first byte of the word-operand, CL-positions shift instructions (in the instruction matrix: “Shift w,v”). The type of shift is specified in bits 3 to 5 of the second byte, but it is not documented when these bits are 110b.
     * The destination operand can be specified, but the zero-test is always performed on CL.
     */
    [opcodes_8086_ROL_reg_mem16_cl] = REG_MEM_16_MASK | MOD_RM_REG_MASK | DISP_LOW_MASK | DISP_HIGH_MASK,         // opcode(D3 -> 0b11010011)

    [opcodes_8086_AAM] = STRING_INSTRU(STRING_INSTRUCTION8086(AAM)),

    [opcodes_8086_AAD] = STRING_INSTRU(STRING_INSTRUCTION8086(AAD)),

    // SALC (SET Carry flag to AL), instruccion no documentada
    /*
     * El nombre SALC simplemente significa SET the Carry flag in AL (establecer el indicador de acarreo en AL). 
     * Esta instrucción está categorizada como una instrucción propietaria de un solo byte no documentada.
     * Intel afirma que se puede emular como una NOP. Esta instrucción, que difícilmente es una NOP,
     * establece AL=FF si el indicador de acarreo está establecido (CF=1), o restablece AL=00 si el
     * indicador de acarreo está despejado (CF=0). La mejor manera de emularla es como SBB AL,AL. SALC
     * no cambia ningún indicador, mientras que SBB AL,AL sí lo hace. Esta instrucción es más útil para
     * los programadores de lenguajes de alto nivel cuyos programas invocan lenguaje ensamblador y esperan
     * que AL indique éxito o fracaso. Dado que es conveniente para los programas de lenguaje ensamblador
     * devolver el estado en el CF, esta instrucción convertirá ese estado a una forma compatible con los
     * lenguajes de alto nivel.
     * A lo largo de los años, esta instrucción ha recibido muchos nombres por parte de varios descubridores. Originalmente le di el nombre SETCAL, pero el nombre más común que he visto impreso es SETALC. El nombre dado anteriormente, SALC, es un nombre oficial de Intel. Mientras examino el mapa de códigos de operación P6, siempre busco códigos de operación conocidos y no documentados. Después de examinar el mapa durante muchos minutos, mi paciencia y perseverancia dieron sus frutos. Encontré el código de operación y su nombre. El nombre que Intel le da a este código de operación es SALC. Esto indicaría que Intel planea documentar oficialmente esta instrucción, comenzando con el P6.
     */
    [opcodes_8086_SALC] = STRING_INSTRU(STRING_INSTRUCTION8086(SALC)),                                       // opcode(d6 -> 0b11010110) -> 0xD6

    [opcodes_8086_XLAT] = STRING_INSTRU(STRING_INSTRUCTION8086(XLAT)),

    /*
     * Los codigo de operacion de un 0xd8 al 0xdf son instrucciones de escape (ESC), permite usar
     * copreocesadores como el x87 conocido como 8087 para hacer operaciones aritmeticas, al ser un
     * codigo de espace para coprocesadores, el conjunto de instrucciones se amplia pues al usar
     * un escape se pueden usar instrucciones de coprocesador.
     */
    [opcodes_8086_ESC] = X87_MASK,
    [opcodes_8086_ESC+1] = X87_MASK,
    [opcodes_8086_ESC+2] = X87_MASK,
    [opcodes_8086_ESC+2] = X87_MASK,
    [opcodes_8086_ESC+4] = X87_MASK,
    [opcodes_8086_ESC+5] = X87_MASK,
    [opcodes_8086_ESC+6] = X87_MASK,
    [opcodes_8086_ESC+7] = X87_MASK,

    [opcodes_8086_LOOPNE_inmmed8] = STRING_INSTRU(STRING_INSTRUCTION8086(LOOPNE)) | INMED8_MASK,

    [opcodes_8086_LOOPE_inmmed8] = STRING_INSTRU(STRING_INSTRUCTION8086(LOOPE)) | INMED8_MASK,

    [opcodes_8086_LOOP_inmmed8] = STRING_INSTRU(STRING_INSTRUCTION8086(LOOP)) | INMED8_MASK,

    [opcodes_8086_JCXZ_inmmed8] = STRING_INSTRU(STRING_INSTRUCTION8086(JCXZ)) | INMED8_MASK,

    [opcodes_8086_IN_al_inmmed8] = STRING_INSTRU(STRING_INSTRUCTION8086(IN)) | INMED8_MASK,

    [opcodes_8086_IN_ax_inmmed8] = STRING_INSTRU(STRING_INSTRUCTION8086(IN)) | INMED8_MASK,

    [opcodes_8086_OUT_al_inmmed8] = STRING_INSTRU(STRING_INSTRUCTION8086(OUT)) | INMED8_MASK,

    [opcodes_8086_OUT_ax_inmmed8] = STRING_INSTRU(STRING_INSTRUCTION8086(OUT)) | INMED8_MASK,

    [opcodes_8086_CALL_NEAR] =  STRING_INSTRU(STRING_INSTRUCTION8086(CALL)) | INMED16_MASK,

    [opcodes_8086_JMP_NEAR] =  STRING_INSTRU(STRING_INSTRUCTION8086(JMP))  | INMED16_MASK,

    [opcodes_8086_JMP_FAR] = STRING_INSTRU(STRING_INSTRUCTION8086(JMP)) | DISP_LOW_MASK | DISP_HIGH_MASK | INMED16_MASK | DIS_HIGH_MASK,

    [opcodes_8086_JMP_SHORT] = STRING_INSTRU(STRING_INSTRUCTION8086(JMP)) | INMED8_MASK,

    [opcodes_8086_IN_al_dx] = STRING_INSTRU(STRING_INSTRUCTION8086(IN)),

    [opcodes_8086_IN_ax_dx] = STRING_INSTRU(STRING_INSTRUCTION8086(IN)),

    [opcodes_8086_OUT_al_dx] = STRING_INSTRU(STRING_INSTRUCTION8086(OUT)),

    [opcodes_8086_OUT_ax_dx] = STRING_INSTRU(STRING_INSTRUCTION8086(OUT)),


    // prefijo LOCK (documentado)
    [0b11110000] = STRING_INSTRU(STRING_INSTRUCTION8086(LOCK)) | MASK_PREFIX,                             // opcode(f0 -> 0b11110000) -> 0xF0 (equivalent: 0xF1) = prefijo LOCK

    // prefijo LOCK (no documentado)
    [0b11110001] = STRING_INSTRU(STRING_INSTRUCTION8086(LOCK)) | UNDOCUMENTED_OPCODE_MASK | MASK_PREFIX,  // opcode(f1 -> 0b11110001) -> 0xF1 (equivalent: 0xF0) = prefijo LOCK

    [opcodes_8086_REPENE] = STRING_INSTRU(STRING_INSTRUCTION8086(REPNE)),

    [opcodes_8086_REP] = STRING_INSTRU(STRING_INSTRUCTION8086(REP)) ,

    [opcodes_8086_HLT] = STRING_INSTRU(STRING_INSTRUCTION8086(HLT)),

    [opcodes_8086_CMC] = STRING_INSTRU(STRING_INSTRUCTION8086(CMC)),
    
    // test/not/neg/mul/imul/div/idiv/ reg8/mem8
    /*
     * Cuando reg es 001, la instruccion se transforma en una instruccion no documentada
     * la cual equivale a la misma que reg == 000 en este caso
     */
    [opcodes_8086_TEST_reg_mem8_inmmed8] = MOD_RM_REG_MASK | DISP_LOW_MASK,

    // test/not/neg/mul/imul/div/idiv/ reg16/mem16
    /*
     * Cuando reg es 001, la instruccion se transforma en una instruccion no documentada
     * la cual equivale a la misma que reg == 000 en este caso
     */
    [opcodes_8086_TEST_reg_mem16_inmmed16] = MOD_RM_REG_MASK | DISP_LOW_MASK,

    [opcodes_8086_CLC] = STRING_INSTRU(STRING_INSTRUCTION8086(CLC)),

    [opcodes_8086_STC] = STRING_INSTRU(STRING_INSTRUCTION8086(STC)),

    [opcodes_8086_CLI] = STRING_INSTRU(STRING_INSTRUCTION8086(CLI)),

    [opcodes_8086_STI] = STRING_INSTRU(STRING_INSTRUCTION8086(STI)),

    [opcodes_8086_CLD] = STRING_INSTRU(STRING_INSTRUCTION8086(CLD)),

    [opcodes_8086_STD] = STRING_INSTRU(STRING_INSTRUCTION8086(STD)),

    // inc/dec reg8/mem8
    /*
     * inc cuando mod == 000
     * dec cuando mod == 001
     * en el resto de casos se vuelve una instruccion no docmentada
     * cuando mod = 111 se vuelve en la instruccion 0xff con mod = 111, lo que
     * lo convierte en push mem16
     */
    [opcodes_8086_INC_reg_mem8] = DISP_LOW_MASK | MOD_RM_REG_MASK, // opcode(fe -> 0b11111110)

    // inc/dec/call/jmp/push reg16/mem16
    /*
     * cuando mod = 111, la instruccion se transforma en una instruccion no documentada
     * la cual equivale a la misma que mod == 110 en este caso(push mem16)
     */
    [opcodes_8086_INC_mem16] = DISP_LOW_MASK | MOD_RM_REG_MASK // opcode(ff -> 0b11111111)
    
};

typedef enum Prefix_x86_Segment_Register {
    Prefix_SS = 0x36, // 0x36 Prefijo de anulación del segmento SS (segmento de pila)
    Prefix_CS = 0x2E, // 0x2E Prefijo de anulación del segmento CS (segmento de codigo)
    Prefix_ES = 0x26, // 0x26 Prefijo de anulación del segmento ES
    Prefix_DS = 0x3E, // 0x3E Prefijo de anulación del segmento DS (segmento de datos)
    Prefix_FS = 0x64, // 0x64 Prefijo de anulación del segmento FS
    Prefix_GS = 0x65, // 0x65 Prefijo de anulación del segmento GS
} Prefix_x86_Segment_Register;

typedef enum Prefix_x86_others {
    Prefix_operand_size  = 0x66,                 /* 0x66
                                                  * Segun el manual de intel vol1, El prefijo de "anulación de tamaño de operando"(operand-size override) permite a un programa 
                                                  * cambiar entre tamaños de operando de 16 y 32 bits. Cualquiera de los dos tamaños puede ser el 
                                                  * predeterminado; el uso del prefijo selecciona el tamaño no predeterminado. en este caso el modo 
                                                  * no predeterminado seria 32bits, es por eso que decimos que sea este. No se puede cambiar de 16 o de 32 a 64 ni al reves 
                                                  * mediante este prefijo, se a de usar la correspondiente instruccion para esta tarea
                                                  */
    Prefix_addr_size     = 0x67,                  /* 0x67
                                                   * predefinido para el prefijo de "anulación de tamaño de dirección". Su significado es que si una instrucción ejecuta un tamaño 
                                                   * de dirección predeterminado, por ejemplo, 16 bits, el uso del prefijo permite que
                                                   * la instrucción utilice un tamaño de dirección distinto al predeterminado, por 
                                                   * ejemplo, 32 bits en modo de 16. Como se supone que el binario es de 16 bits, 0x67 
                                                   * cambia la instrucción al modo de 32 bits.
                                                   */
    Prefix_lock          = 0xF0,                   // 0xF0 Prefijo LOCK
    Prefix_repne_repnez  = 0xF2,                   // 0xF2 Prefijo REPNE/REPNZ (utilizado sólo con instrucciones de cadena)
    Prefix_repe_rep_repz = 0xF3,                   // 0xF3 Prefijo REP         (utilizado sólo con instrucciones de string)
                                                   // 0xF3 Prefijo REPE/REPZ   (sólo se utiliza con instrucciones de string)     
} Prefix_x86_Segment_others;

/*
 *
 *  Tablas "A" de la documentacion intel:
 *      - A02       = opcodes de 1byte de opcode
 *      - A03       = opcodes de 2byte de opcode (pagina: 2847) 
 *      - A04 a A05 = opcodes de 3byte de opcode (pagina: 2851)
 *      - A06       = extensiones para instrucciones de A2(de 1byte de opcode) y A3(2byte's de opcode)
 *      - A07       = opcode de instrucciones de punto flotante x87
 *      - A07 y A08 = contienen mapas para los opcodes de las instrucciones de escape que empiezan por 0xD8 (pagina: 2858)
 *      - A09       = ¿tabla de instrucciones FLD (double-real)?
 *      - A09 y A10 = contienen mapas para los opcodes de las instrucciones de escape que empiezan por 0xD9 (pagina: 2859)
 *      - A11 y A12 = contienen mapas para los opcodes de las instrucciones de escape que comienzan por 0xDA (pagina: 2860)
 * 
 */
int dissamble(const uint8_t* start, const uint8_t* end, size_t* position, Instruction_info* instruction, encoder_x86 encoder);
void print_Instruction_info(Instruction_info* instruction, encoder_x86 encode);
void get_string_Instruction_info_8086(Instruction_info *instruction, char* string, size_t size);

#include "./print_structs_format.h"
#include "opcodes_prefix.c"
#endif 