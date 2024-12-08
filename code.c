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
    // https://shell-storm.org/online/Online-Assembler-and-Disassembler/?opcodes=51+52+50+BA+31+03+B9+FF+FF+EC+A8+40+74+13+D0+C0+73+1A+EB+EF+49+83+F9+01+7D+EF+58+B8+FF+FF+EB+09+90+BA+30+03+58+EE+B8+00+00+5A+59+C3+56+2E+8B+36+72+01+BA+30+03+EC+2E+88+84+4A+01+46+83+FE+28+75+02+33+F6+2E+89+36+72+01+5E+EB+B8&arch=x86-16&endianness=little&dis_with_addr=True&dis_with_raw=True&dis_with_ins=True
    uint8_t instrucciones[] = {
        // instruccion ilegal:
        //0x67, 0x12, 0x04, 0x20, // adc al, [al+ah] // 0x04 codifica desplazamiento bajo
        opcodes_8086_ADD_mem8,               0x80, 0x43, 0x65,             // add  byte ptr [bx + si + 0x6543], al
        opcodes_8086_ADD_mem16,              0xa8, 0x43, 0x65,             // add  word ptr [bx + si + 0x6543], bp
        opcodes_8086_ADD_mem8_inverse,       0x87, 0x34, 0x12,             // add  al, [bx+0x1234]
        opcodes_8086_ADD_mem16_inverse,      0x87, 0x34, 0x12,             // add  ax, [bx+0x1234]
        opcodes_8086_ADD_mem16_inverse,      0x00,                         // add  ax, [bx+si]
        opcodes_8086_ADD_al,                 0x99,                         // add  al, 0x99
        opcodes_8086_ADD_ax,                 0x88, 0x99,                   // add  ax, 0x9988
        opcodes_8086_PUSH_es,                                              // push ES
        opcodes_8086_POP_es,                                               // pop  ES
        opcodes_8086_OR_mem8,                0xdc,                         // or   ah,  bl
        opcodes_8086_OR_mem8,                0x64, 0x10,                   // or   byte [si + 0x10], ah
        opcodes_8086_OR_mem16,               0xA8, 0x43, 0x65,             // or   word ptr [bx + si + 0x6543], bp
        opcodes_8086_OR_mem8_inverse,        0xDC,                         // or   bl,  ah
        opcodes_8086_OR_mem8_inverse,        0x64, 0x10,                   // or   ah,  byte ptr [si + 0x10]
        opcodes_8086_OR_mem16_inverse,       0xA8, 0x43, 0x65,             // or bp, word ptr [bx + si + 0x6543]
        opcodes_8086_OR_al,                  0x99,                         // or  al, 0x99
        opcodes_8086_OR_ax,                  0x88, 0x99,                   // or  ax, 0x9988
        opcodes_8086_PUSH_cs,                                              // push CS
        opcodes_8086_POP_cs,                                               // pop CS
        opcodes_8086_ADC_mem8,               0x22,                         // adc  byte ptr [bp + si], ah
        opcodes_8086_ADC_mem16,              0x33,                         // adc  word ptr [bp + di], si
        opcodes_8086_ADC_mem8_inverse,       0x44, 0x55,                   // adc  al, byte ptr [si + 0x55]
        opcodes_8086_ADC_mem16_inverse,      0x55, 0x66,                   // adc  dx, word ptr [di + 0x66]
        opcodes_8086_ADC_al,                 0xFF,                         // adc  al, 0xff
        opcodes_8086_ADC_ax,                 0x22, 0x11,                   // adc  ax, 0x1122
        opcodes_8086_PUSH_ss,                                              // push ss
        opcodes_8086_POP_ss,                                               // pop  ss
        opcodes_8086_SBB_mem8,               0x99, 0x88, 0x88,             // sbb  byte ptr [bx + di - 0x7778], bl
        opcodes_8086_SBB_mem16,              0x66, 0x77,                   // sbb  word ptr [bp + 0x77], sp
        opcodes_8086_SBB_mem8_inverse,       0x77, 0x88,                   // sbb  dh, byte ptr [bx - 0x78]
        opcodes_8086_SBB_mem16_inverse,      0x11,                         // sbb  dx, word ptr [bx + di]
        opcodes_8086_SBB_al,                 0xFF,                         // sbb  al, 0xff
        opcodes_8086_SBB_ax,                 0xAA, 0xBB,                   // sbb  ax, 0xbbaa
        opcodes_8086_PUSH_ds,                                              // push ds
        opcodes_8086_POP_ds,                                               // pop  ds
        opcodes_8086_AND_mem8,               0x99, 0x88, 0x77,             // and  byte ptr [bx + di + 0x7788], bl
        opcodes_8086_AND_mem16,              0x99, 0x88, 0x77,             // and  word ptr [bx + di + 0x7788], bx
        opcodes_8086_AND_mem8_inverse,       0x99, 0x88, 0x77,             // and  bl, byte ptr [bx + di + 0x7788]
        opcodes_8086_AND_mem16_inverse,      0x99, 0x88, 0x77,             // and  bx, word ptr [bx + di + 0x7788]
        opcodes_8086_AND_al,                 0x11,                         // and  al, 0x11
        opcodes_8086_AND_ax,                 0x55, 0x66,                   // and  ax, 0x6655
        Prefix_ES,                                                         // prefijo ES // el prefijo de segmento no es valido con daa(se ignora)
        opcodes_8086_DAA,                                                  // daa
        Prefix_ES,                                                         // prefijo ES:
        opcodes_8086_SUB_mem8,               0x11,                         // sub byte ptr [bx + di], dl
        opcodes_8086_SUB_mem16,              0x12,                         // sub word ptr [bp + si], dx
        opcodes_8086_SUB_mem8_inverse,       0x99, 0x88, 0x77,             // sub bl, byte ptr [bx + di + 0x7788]
        opcodes_8086_SUB_mem16_inverse,      0x22,                         // sub sp, word ptr [bp + si]
        opcodes_8086_SUB_al,                 0xAB,                         // sub al, 0xab
        opcodes_8086_SUB_ax,                 0x12, 0x34,                   // sub ax, 0x3412
        // 0x13, 0x0E,                                                    // adc  cx,  [ax+cx] // instruccion ilegal?
        opcodes_8086_DAS,                                                  // das
        Prefix_CS,                                                         // prefijo CS:
        opcodes_8086_XOR_mem8,               0x28,                         // xor byte ptr [bx + si], ch
        opcodes_8086_XOR_mem16,              0x12,                         // xor word ptr [bp + si], dx
        opcodes_8086_XOR_mem8_inverse,       0x99, 0x88, 0x77,             // xor bl, byte ptr [bx + di + 0x7788]
        opcodes_8086_XOR_mem16_inverse,      0x22,                         // xor sp, word ptr [bp + si]
        opcodes_8086_XOR_al,                 0xAB,                         // xor al, 0xab
        opcodes_8086_XOR_ax,                 0x12, 0x34,                   // xor ax, 0x3412
        opcodes_8086_AAA,                                                  // aaa
        Prefix_SS,                                                         // prefijo SS:
        opcodes_8086_CMP_mem8,               0x28,                         // cmp    byte ptr [bx + si], ch
        opcodes_8086_CMP_mem16,              0x12,                         // cmp    word ptr [bp + si], dx
        opcodes_8086_CMP_mem8_inverse,       0x99, 0x88, 0x77,             // cmp    bl, byte ptr [bx + di + 0x7788]
        Prefix_DS,                                                         // prefijo DS:
        opcodes_8086_CMP_mem16_inverse,      0x22,                         // cmp    sp, word ptr [bp + si]
        opcodes_8086_CMP_al,                 0xAB,                         // cmp    al, 0xab
        opcodes_8086_CMP_ax,                 0x12, 0x34,                   // cmp    ax, 0x3412
        opcodes_8086_AAS,                                                  // aas
        opcodes_8086_INC_ax,                                               // inc    ax
        opcodes_8086_INC_cx,                                               // inc    cx
        opcodes_8086_INC_dx,                                               // inc    dx
        opcodes_8086_INC_bx,                                               // inc    bx
        opcodes_8086_INC_sp,                                               // inc    sp
        opcodes_8086_INC_bp,                                               // inc    bp
        opcodes_8086_INC_si,                                               // inc    si
        opcodes_8086_INC_di,                                               // inc    di
        opcodes_8086_DEC_ax,                                               // dec    ax
        opcodes_8086_DEC_cx,                                               // dec    cx
        opcodes_8086_DEC_dx,                                               // dec    dx
        opcodes_8086_DEC_bx,                                               // dec    bx
        opcodes_8086_DEC_sp,                                               // dec    sp
        opcodes_8086_DEC_bp,                                               // dec    bp
        opcodes_8086_DEC_si,                                               // dec    si
        opcodes_8086_DEC_di,                                               // dec    di
        opcodes_8086_PUSH_ax,                                              // push   ax
        opcodes_8086_PUSH_cx,                                              // push   cx
        opcodes_8086_PUSH_dx,                                              // push   dx
        opcodes_8086_PUSH_bx,                                              // push   bx
        opcodes_8086_PUSH_sp,                                              // push   sp
        opcodes_8086_PUSH_bp,                                              // push   bp
        opcodes_8086_PUSH_si,                                              // push   si
        opcodes_8086_PUSH_di,                                              // push   di
         opcodes_8086_POP_ax,                                              // pop    ax
         opcodes_8086_POP_cx,                                              // pop    cx
         opcodes_8086_POP_dx,                                              // pop    dx
         opcodes_8086_POP_bx,                                              // pop    bx
         opcodes_8086_POP_sp,                                              // pop    sp
         opcodes_8086_POP_bp,                                              // pop    bp
         opcodes_8086_POP_si,                                              // pop    si
         opcodes_8086_POP_di,                                              // pop    di
        undocumented_opcodes_8086_JO,       0xC9,                          // jo
        undocumented_opcodes_8086_JNO,      0x31,                          // jno
        undocumented_opcodes_8086_JC,       0x3A,                          // jb
        undocumented_opcodes_8086_JAE,      0xC8,                          // JNB
        undocumented_opcodes_8086_JE,       0x76,                          // JZ
        undocumented_opcodes_8086_JNZ,      0xD3,                          // JNZ
        undocumented_opcodes_8086_JBE,      0x71,                          // JNB
        undocumented_opcodes_8086_JA,       0xB0,                          // JS
        undocumented_opcodes_8086_JS,       0xED,                          // js
        undocumented_opcodes_8086_JNS,      0xED,                          // jns
        undocumented_opcodes_8086_JPE,      0xEA,                          // jp
        undocumented_opcodes_8086_JNP,      0xD8,                          // jnp
        undocumented_opcodes_8086_JL,       0xF6,                          // jl
        undocumented_opcodes_8086_JGE,      0xC4,                          // jge
        undocumented_opcodes_8086_JLE,      0x02,                          // jle
        undocumented_opcodes_8086_JG,       0x43,                          // jg
        opcodes_8086_JO,                    0xC9,                          // jo
        opcodes_8086_JNO,                   0x31,                          // jno
        opcodes_8086_JC,                    0x3A,                          // jb
        opcodes_8086_JAE,                   0xC8,                          // jae
        opcodes_8086_JE,                    0x76,                          // je
        opcodes_8086_JNZ,                   0xD3,                          // jne
        opcodes_8086_JBE,                   0x71,                          // jbe
        opcodes_8086_JA,                    0xB0,                          // ja
        opcodes_8086_JS,                    0xED,                          // js
        opcodes_8086_JNS,                   0xED,                          // jns
        opcodes_8086_JPE,                   0xEA,                          // jp
        opcodes_8086_JNP,                   0xD8,                          // jnp
        opcodes_8086_JL,                    0xF6,                          // jl
        opcodes_8086_JGE,                   0xC4,                          // jge
        opcodes_8086_JLE,                   0x02,                          // jle
        opcodes_8086_JG,                    0x43,                          // jg
        opcodes_8086_ADD_inmmed8,           0x00, 0x11,                    // add byte ptr [bx + si], 0x11
        opcodes_8086_ADD_inmmed8,           0xc1, 0x40,                    // add  cl,  64
        opcodes_8086_ADC_inmmed8,           0xd1, 0x50,                    // adc  cl,  80
        opcodes_8086_ADD_inmmed16,          0x00, 0x11, 0x22,              // add word ptr [bx + si], 0x2211
        opcodes_8086_SBB_inmmed16,          0x99, 0x23, 0x45, 0x11, 0x22,  // sbb word ptr [bx + di + 0x4523], 0x2211
        opcodes_8086_ADD_inmmed8_2,         0x00, 0x11,                    // add byte ptr [bx + si], 0x11
        opcodes_8086_ADD_inmmed8_reg_mem16, 0x00, 0x11,                    // add word ptr [bx + si], 0x11
        opcodes_8086_ADD_inmmed8_reg_mem16, 0xc0, 0x10,                    // add  ax,  16
        opcodes_8086_ADC_inmmed8_reg_mem16, 0xd1, 0x20,                    // adc  cx,  32
        opcodes_8086_SBB_inmmed8_reg_mem16, 0x99, 0x23, 0x45, 0x11,        // sbb word ptr [bx + di + 0x4523], 0x11
        opcodes_8086_TEST_reg8,             0x00,                          // test byte ptr [bx + si], al
        opcodes_8086_TEST_reg16,            0x99, 0x22, 0x44,              // test word ptr [bx + di + 0x4422], bx
        opcodes_8086_XCHG_reg8,             0x55, 0x33,                    // xchg byte ptr [di + 0x33], dl
        opcodes_8086_XCHG_reg16,            0x99, 0x33, 0x44,              // xchg word ptr [bx + di + 0x4433], bx
        opcodes_8086_MOV_reg8,              0x33,                          // mov  byte ptr [bp + di], dh
        opcodes_8086_MOV_reg16,             0x77, 0x88,                    // mov  word ptr [bx - 0x78], si
        opcodes_8086_MOV_mem8,              0x55, 0x33,                    // mov  dl, byte ptr [di + 0x33]
        opcodes_8086_MOV_mem16,             0x99, 0x44, 0x55,              // mov  bx, word ptr [bx + di + 0x5544]
        opcodes_8086_MOV_reg_mem16_segreg,  0x99, 0x11, 0x22,              // mov word ptr [bx + di + 0x2211], ds
        opcodes_8086_LEA_mem16,             0x99, 0x11, 0x22,              // lea bx, [bx + di + 0x2211]
        opcodes_8086_MOV_segreg_reg_mem16,  0x88, 0x33, 0x33,              // mov cs, word ptr [bx + si + 0x3333]
        opcodes_8086_POP_reg_mem16,         0x00,                          // pop word ptr [bx + si]
        opcodes_8086_XCHG_ax_ax,                                           // nop
        opcodes_8086_XCHG_ax_cx,                                           // xchg ax, cx
        opcodes_8086_XCHG_ax_dx,                                           // xchg ax, dx
        opcodes_8086_XCHG_ax_bx,                                           // xchg ax, bx
        opcodes_8086_XCHG_ax_sp,                                           // xchg ax, sp
        opcodes_8086_XCHG_ax_bp,                                           // xchg ax, bp
        opcodes_8086_XCHG_ax_si,                                           // xchg ax, si
        opcodes_8086_XCHG_ax_di,                                           // xchg ax, di
        opcodes_8086_CBW,                                                  // cbw
        opcodes_8086_CWD,                                                  // cwd
        opcodes_8086_CALL_FAR,              0x78, 0x56, 0x34, 0x12,        // lcall lcall 0x1234:0x5678 / call far 0x1234:0x5678
        opcodes_8086_WAIT,                                                 // wait
        opcodes_8086_PUSHF,                                                // pushf
        opcodes_8086_POPF,                                                 // popf
        opcodes_8086_SAHF,                                                 // sahf
        opcodes_8086_LAHF,                                                 // lahf
        opcodes_8086_MOV_al_mem8,           0x12,                          // mov al, [0x12]
        opcodes_8086_MOV_ax_mem16,          0x12, 0x34,                    // mov ax, [0x3412]
        opcodes_8086_MOV_mem8_al,           0x12,                          // mov [0x12], al
        opcodes_8086_MOV_mem16_ax,          0x12, 0x34,                    // mov [0x3412], ax
        opcodes_8086_MOVS_ptr8,                                            // movsb byte es:[di], byte [si]
        opcodes_8086_MOVS_ptr16,                                           // movsw word es:[di], word [si]
        opcodes_8086_CMPS_ptr8,                                            // cmpsb byte [si], byte es:[di]
        opcodes_8086_CMPS_ptr16,                                           // cmpsw word [si], word es:[di]
        opcodes_8086_TEST_al_inmmed8,       0x12,                          // test al, [0x12]
        opcodes_8086_TEST_ax_inmmed16,      0x12, 0x34,                    // test ax, [0x3412]
        opcodes_8086_STOS_ptr8,                                            // stosb byte es:[di], al
        opcodes_8086_STOS_ptr16,                                           // stosw word es:[di], ax
        opcodes_8086_LODS_ptr8,                                            // lodsb al, byte ptr [si]
        opcodes_8086_LODS_ptr16,                                           // lodsw ax, word ptr [si]
        opcodes_8086_SCAS_ptr8,                                            // scasb al, byte ptr es:[di]
        opcodes_8086_SCAS_ptr16,                                           // scasw ax, word ptr es:[di]
        opcodes_8086_MOV_al_inmmed8,        0x12,                          // mov   al, 0x12
        opcodes_8086_MOV_cl_inmmed8,        0x23,                          // mov   cl, 0x23
        opcodes_8086_MOV_dl_inmmed8,        0x45,                          // mov   dl, 0x45
        opcodes_8086_MOV_bl_inmmed8,        0x67,                          // mov   bl, 0x67
        opcodes_8086_MOV_ah_inmmed8,        0x89,                          // mov   ah, 0x89
        opcodes_8086_MOV_ch_inmmed8,        0xAB,                          // mov   ch, 0xab
        opcodes_8086_MOV_dh_inmmed8,        0xCD,                          // mov   dh, 0xcd
        opcodes_8086_MOV_bh_inmmed8,        0xEF,                          // mov   bh, 0xef
        opcodes_8086_MOV_ax_inmmed16,       0x12, 0x34,                    // mov   ax, 0x3412
        opcodes_8086_MOV_cx_inmmed16,       0x56, 0x78,                    // mov   cx, 0x7856
        opcodes_8086_MOV_dx_inmmed16,       0x9A, 0xBC,                    // mov   dx, 0xbc9a
        opcodes_8086_MOV_bx_inmmed16,       0x01, 0x23,                    // mov   bx, 0x2301
        opcodes_8086_MOV_sp_inmmed16,       0x45, 0x67,                    // mov   sp, 0x6745
        opcodes_8086_MOV_bp_inmmed16,       0x89, 0xAB,                    // mov   bp, 0xab89
        opcodes_8086_MOV_si_inmmed16,       0xCD, 0xEF,                    // mov   si, 0xefcd
        opcodes_8086_MOV_di_inmmed16,       0x01, 0x23,                    // mov   di, 0x2301
     
        // ret near inmed16, es la misma      que C2 solo para 8086
        undocumented_opcodes_8086_RET_NEAR_inmmed16_intraseg, 0x34, 0x12,   // ret near 0x1234
                                                                            // sal byte ptr [si], 0x12 en no 8086

        // ret ( no documentada) para el 808678 56 34 12 
        undocumented_opcodes_8086_RET_intraseg,                            // ret
        // 0xC1, 0x34, 0x54,                                               // sal word ptr [si], 0x54 en no 8086
        
        opcodes_8086_RET_NEAR_inmmed16_intraseg,              0x34, 0x12,  // ret near 0x1234
        opcodes_8086_RET_intraseg,                                         // ret

        opcodes_8086_LES_mem16,             0x99, 0x21, 0x43,              // les  bx, ptr [bx + di + 0x4321]
        opcodes_8086_LDS_mem16,             0x99, 0x21, 0x43,              // lds  bx, ptr [bx + di + 0x4321]
        opcodes_8086_MOV_mem8_inmmed8,      0x00, 0xAA,                    // mov  byte ptr [bx + si], 0xaa
        opcodes_8086_MOV_mem16_inmmed16,    0x00, 0xaa, 0xbb,              // mov  word ptr [bx + si], 0xbbaa

        // ret far ( no documentada) para el 8086
        undocumented_opcodes_8086_RET_NEAR_inmmed16_intersegment, 0X34, 0X12, // retf 0x1234 / ret far 0x1234
                                                                              // invalida fuera del 8086

        undocumented_opcodes_8086_RET_intersegment,                         // retf no documentada

        opcodes_8086_RET_NEAR_inmmed16_intersegment,           0X34, 0X12,  // retf 0x1234 / ret far 0x1234
        opcodes_8086_RET_intersegment,                                      // retf
        opcodes_8086_INT_3,                                                 // int 3
        opcodes_8086_INT_inmmed8,           0x12,                           // int 0x12
        opcodes_8086_INTO,                                                  // into
        opcodes_8086_IRET,                                                  // iret
        opcodes_8086_ROL_reg_mem8_1,        0x00,                           // rol byte ptr [bx + si], 1
        opcodes_8086_RCR_reg_mem8_1,        0x99, 0x12, 0x34,               // rcr byte ptr [bx + di + 0x3412], 1
        opcodes_8086_ROL_reg_mem16_1,       0x00,                           // rol word ptr [bx + si], 1
        opcodes_8086_RCR_reg_mem16_1,       0x99, 0x12, 0x34,               // rcr word ptr [bx + di + 0x3412], 1
        opcodes_8086_ROL_reg_mem8_cl,       0x00,                           // rol byte ptr [bx + si], cl
        opcodes_8086_RCR_reg_mem8_cl,       0x99, 0x12, 0x34,               // rcr byte ptr [bx + di + 0x3412], cl
        opcodes_8086_ROL_reg_mem16_cl,      0x00,                           // rol word ptr [bx + si], cl
        opcodes_8086_RCR_reg_mem16_cl,      0x99, 0x12, 0x34,               // rcr word ptr [bx + di + 0x3412], cl
        opcodes_8086_AAM,                                                   // aam
        opcodes_8086_AAD,                                                   // aad
        opcodes_8086_SALC,                                                  // salc
        opcodes_8086_XLAT,                                                  // xlat
        

       // primera tabla de instrucciones del x87
        opcodes_8086_ESC,                   0xD0,                           // ESC(fcom  st(0))
        opcodes_8086_ESC,                   0xD1,                           // ESC(fcom  st(1))
        opcodes_8086_ESC,                   0xD2,                           // ESC(fcom  st(2))
        opcodes_8086_ESC,                   0xD3,                           // ESC(fcom  st(3))
        opcodes_8086_ESC,                   0xD4,                           // ESC(fcom  st(4))
        opcodes_8086_ESC,                   0xD5,                           // ESC(fcom  st(5))
        opcodes_8086_ESC,                   0xD6,                           // ESC(fcom  st(6))
        opcodes_8086_ESC,                   0xD7,                           // ESC(fcom  st(7))
        opcodes_8086_ESC,                   0xd8,                           // ESC(fcomp st(0))
        opcodes_8086_ESC,                   0xd9,                           // ESC(fcomp st(1))
        opcodes_8086_ESC,                   0xda,                           // ESC(fcomp st(2))
        opcodes_8086_ESC,                   0xdb,                           // ESC(fcomp st(3))
        opcodes_8086_ESC,                   0xdc,                           // ESC(fcomp st(4))
        opcodes_8086_ESC,                   0xdd,                           // ESC(fcomp st(5))
        opcodes_8086_ESC,                   0xde,                           // ESC(fcomp st(6))
        opcodes_8086_ESC,                   0xdf,                           // ESC(fcomp st(7))

        // segunda tabla de instrucciones del x87
        opcodes_8086_ESC+1,                 0xC0,                           // ESC(fld st(0))
        opcodes_8086_ESC+1,                 0xC1,                           // ESC(fld st(1))
        opcodes_8086_ESC+1,                 0xC2,                           // ESC(fld st(2))
        opcodes_8086_ESC+1,                 0xC3,                           // ESC(fld st(3))
        opcodes_8086_ESC+1,                 0xC4,                           // ESC(fld st(4))
        opcodes_8086_ESC+1,                 0xC5,                           // ESC(fld st(5))
        opcodes_8086_ESC+1,                 0xC6,                           // ESC(fld st(6))
        opcodes_8086_ESC+1,                 0xC7,                           // ESC(fld st(7))
        opcodes_8086_ESC+1,                 0x80, 0x34, 0x12,               // ESC(fld dword ptr [bx + si + 0x1234])
        opcodes_8086_ESC+1,                 0x81, 0x34, 0x12,               // ESC(fld dword ptr [bx + di + 0x1234])
        opcodes_8086_ESC+1,                 0x82, 0x34, 0x12,               // ESC(fld dword ptr [bp + si + 0x1234])
        opcodes_8086_ESC+1,                 0x83, 0x34, 0x12,               // ESC(fld dword ptr [bp + di + 0x1234])
        opcodes_8086_ESC+1,                 0x84, 0x34, 0x12,               // ESC(fld dword ptr [si      + 0x1234])
        opcodes_8086_ESC+1,                 0x85, 0x34, 0x12,               // ESC(fld dword ptr [di      + 0x1234])
        opcodes_8086_ESC+1,                 0x86, 0x34, 0x12,               // ESC(fld dword ptr [bp      + 0x1234])
        opcodes_8086_ESC+1,                 0x87, 0x34, 0x12,               // ESC(fld dword ptr [bx      + 0x1234])
        // quinta tabla de instrucciones del x87
        opcodes_8086_ESC+5,                 0xD8,                           // ESC(fstp st(0))
        opcodes_8086_ESC+5,                 0xD9,                           // ESC(fstp st(1))
        opcodes_8086_ESC+5,                 0xDA,                           // ESC(fstp st(2))
        opcodes_8086_ESC+5,                 0xDC,                           // ESC(fstp st(4))
        opcodes_8086_ESC+5,                 0xDD,                           // ESC(fstp st(5))
        opcodes_8086_ESC+5,                 0xDE,                           // ESC(fstp st(6))
        opcodes_8086_ESC+5,                 0xDF,                           // ESC(fstp st(7))

        opcodes_8086_LOOPNE_inmmed8,        0x23,                           // loopne  0x25
        opcodes_8086_LOOPE_inmmed8,         0x47,                           // loope   0x49
        opcodes_8086_LOOP_inmmed8,          0x43,                           // loop    0x45
        opcodes_8086_JCXZ_inmmed8,          0x55,                           // jcxz    0x57
        opcodes_8086_IN_al_inmmed8,         0x22,                           // in  al, 0x22
        opcodes_8086_IN_ax_inmmed8,         0x33,                           // in  ax, 0x33
        opcodes_8086_OUT_al_inmmed8,        0x44,                           // out 0x44, al
        opcodes_8086_OUT_ax_inmmed8,        0x55,                           // out 0x55, ax
        opcodes_8086_CALL_NEAR,             0x11, 0x22,                     // call 0x2214
        opcodes_8086_JMP_NEAR,              0x22, 0x11,                     // jmp  0x1128
        opcodes_8086_JMP_FAR,               0x22, 0x11, 0x33, 0x44,         // ljmp 0x4433:0x1122
        opcodes_8086_JMP_inmmed8,           0x12,                           // jmp  0x1f
        opcodes_8086_IN_al_dx,                                              // in   al, dx
        opcodes_8086_IN_ax_dx,                                              // in   ax, dx
        opcodes_8086_OUT_al_dx,                                             // out  dx, al
        opcodes_8086_OUT_ax_dx,                                             // out  dx, ax
        Prefix_lock, 0x00, 0x22,                                            // lock add byte ptr [bp + si], ah
        0xF1,                                                               // lock no documentado para el 8086
        opcodes_8086_REPENE,                                                // repne/repnez
        opcodes_8086_REP,                                                   // rep/repe/repz
        opcodes_8086_HLT,                                                   // hlt
        opcodes_8086_CMC,                                                   // cmc
        opcodes_8086_IDIV_reg_mem8,         0xFF,                           // idiv bh
        opcodes_8086_DIV_reg_mem8,          0x34,                           // div  byte ptr [si]
        opcodes_8086_NOT_reg_mem8,          0x11,                           // not  byte ptr [bx + di]
        opcodes_8086_IDIV_reg_mem16,        0xFF,                           // idiv di
        opcodes_8086_DIV_reg_mem16,         0x34,                           // div  word ptr [si]
        opcodes_8086_NOT_reg_mem16,         0x11,                           // not  word ptr [bx + di]
        opcodes_8086_CLC,                                                   // clc
        opcodes_8086_STC,                                                   // stc
        opcodes_8086_CLI,                                                   // cli
        opcodes_8086_STI,                                                   // sti
        opcodes_8086_CLD,                                                   // cld
        opcodes_8086_STD,                                                   // std
        opcodes_8086_INC_reg_mem8,          0x00,                           // inc  byte ptr [bx + si]
        opcodes_8086_INC_mem16,             0x00,                           // inc  word ptr [bx + si]
    };

    // -Os -s -ffunction-sections -Wl,--gc-sections -fno-asynchronous-unwind-tables -Wl,--strip-all

    Instruction_info instruccion = {0};
    size_t position = 0, position_old = position, cantidad_de_instrucciones = 0;
    while (dissamble(
        instrucciones + position,
        instrucciones + sizeof(instrucciones),
        &position,
        &instruccion, ENCODER_IN_16bits
    )) { // mientras dissamble devuelva 1, quedara instrucciones por desensamblar
        print_Instruction_info(&instruccion, ENCODER_IN_16bits);

        /**/char* string = calloc(64, sizeof(char));
        get_string_Instruction_info_8086(&instruccion, string, 64);

        printf("[*] size instruction %d (%p - %p -> %03zu) %s\n", (position-position_old),
            instrucciones + position, instrucciones + sizeof(instrucciones), position, string);
        free(string);
        
        memset(&instruccion, 0, sizeof(Instruction_info));
        position_old = position;

        cantidad_de_instrucciones++;
        
    }
    
    /*
    for (int i = 0; i < sizeof(my_instruccion_8086)/sizeof(my_instruccion_8086[0]); i++) {
        printf("opcode(0x%02x -> %05s) flags[0x%08x] = ", i, get_string_instruction_by_id_8086((my_instruccion_8086[i] & 0xff000000) >> 24), my_instruccion_8086[i]);
        print_flags(my_instruccion_8086[i]);
    }
    
    for (int i = 0xd8; i  < (0xd8 + 8); i++) {
        for (int j = 0; j < my_instruccion_8087_table_sizes[i & 0b00000111]; j++){
            if (my_instruccion_8087_table[(i & 0b00000111)][j] != 0) { // imprimir solo aquellos opcodes que no tengan none flags
                printf("opcode(0x%02x 0x%02x) flags[0x%08x] flags_x87[0x%02x] = ", i, j,
                my_instruccion_8086[(i & 0b00000111)], my_instruccion_8087_table[(i & 0b00000111)][j]);
                print_flags_x87(my_instruccion_8087_table[(i & 0b00000111)][j]);
            }
        }
        
    }*/
    

    printf("cantidad de instrucciones: %zu\n", cantidad_de_instrucciones);
    puts("Exit...");
    return 0;

}

