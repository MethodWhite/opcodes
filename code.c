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
        /*0x00, 0x80, 0x43, 0x65,         // add  byte ptr [bx + si + 0x6543], al
        0x01, 0xa8, 0x43, 0x65,              // add  word ptr [bx + si + 0x6543], bp
        0x02, 0x87, 0x34, 0x12,              // add  al, [bx+0x1234]
        0x03, 0x87, 0x34, 0x12,              // add  ax, [bx+0x1234]
        0x03, 0x00,                          // add  ax, [bx+si]
        0x04, 0x99,                          // add  al, 0x99
        0x05, 0x88, 0x99,                    // add  ax, 0x9988
        0x06,                                // push ES
        0x07,                                // pop  ES
        0x08, 0xdc,                          // or   ah,  bl
        0x08, 0x64, 0x10,                    // or   byte [si + 0x10], ah
        0x09, 0xA8, 0x43, 0x65,              // or   word ptr [bx + si + 0x6543], bp
        0x0A, 0xDC,                          // or   bl,  ah
        0x0A, 0x64, 0x10,                    // or   ah,  byte ptr [si + 0x10]
        0x0b, 0xA8, 0x43, 0x65,              // or bp, word ptr [bx + si + 0x6543]
        0x0c, 0x99,                          // or  al, 0x99
        0x0d, 0x88, 0x99,                    // or  ax, 0x9988
        0x0e,                                // push CS
        0x0f,                                // pop CS
        0x10, 0x22,                          // adc  byte ptr [bp + si], ah
        0x11, 0x33,                          // adc  word ptr [bp + di], si
        0x12, 0x44, 0x55,                    // adc  al, byte ptr [si + 0x55]
        0x13, 0x55, 0x66,                    // adc  dx, word ptr [di + 0x66]
        0x14, 0xFF,                          // adc  al, 0xff
        0x15, 0x22, 0x11,                    // adc  ax, 0x1122
        0x16,                                // push ss
        0x17,                                // pop  ss
        0x18, 0x99, 0x88, 0x88,              // sbb  byte ptr [bx + di - 0x7778], bl
        0x19, 0x66, 0x77,                    // sbb  word ptr [bp + 0x77], sp
        0x1A, 0x77, 0x88,                    // sbb  dh, byte ptr [bx - 0x78]
        0x1B, 0x11,                          // sbb  dx, word ptr [bx + di]
        0x1C, 0xFF,                          // sbb  al, 0xff
        0x1D, 0xAA, 0xBB,                    // sbb  ax, 0xbbaa
        0x1E,                                // push ds
        0x1F,                                // pop  ds
        0x20, 0x99, 0x88, 0x77,              // and  byte ptr [bx + di + 0x7788], bl
        0x21, 0x99, 0x88, 0x77,              // and  word ptr [bx + di + 0x7788], bx
        0x22, 0x99, 0x88, 0x77,              // and  bl, byte ptr [bx + di + 0x7788]
        0x23, 0x99, 0x88, 0x77,              // and  bx, word ptr [bx + di + 0x7788]
        0x24, 0x11,                          // and  al, 0x11
        0x25, 0x55, 0x66,                    // and  ax, 0x6655
        0x26,                                // prefijo ES // el prefijo de segmento no es valido con daa(se ignora)
        0x27,                                // daa
        0x26,                                // prefijo ES:
        0x28, 0x11,                          // sub byte ptr [bx + di], dl
        0x29, 0x12,                          // sub word ptr [bp + si], dx
        0x2A, 0x99, 0x88, 0x77,              // sub bl, byte ptr [bx + di + 0x7788]
        0x2B, 0x22,                          // sub sp, word ptr [bp + si]
        0x2C, 0xAB,                          // sub al, 0xab
        0x2D, 0x12, 0x34,                    // sub ax, 0x3412
        // 0x13, 0x0E,                       // adc  cx,  [ax+cx] // instruccion ilegal?
        0x2F,                                // das
        0x2E,                                // prefijo CS:
        0x30, 0x28,                          // xor byte ptr [bx + si], ch
        0x31, 0x12,                          // xor word ptr [bp + si], dx
        0x32, 0x99, 0x88, 0x77,              // xor bl, byte ptr [bx + di + 0x7788]
        0x33, 0x22,                          // xor sp, word ptr [bp + si]
        0x34, 0xAB,                          // xor al, 0xab
        0x35, 0x12, 0x34,                    // xor ax, 0x3412
        0x37,                                // aaa    
        0x36,                                // prefijo SS:
        0x38, 0x28,                          // cmp    byte ptr [bx + si], ch
        0x39, 0x12,                          // cmp    word ptr [bp + si], dx
        0x3A, 0x99, 0x88, 0x77,              // cmp    bl, byte ptr [bx + di + 0x7788]
        0x3e,                                // prefijo DS:
        0x3B, 0x22,                          // cmp    sp, word ptr [bp + si]
        0x3C, 0xAB,                          // cmp    al, 0xab
        0x3D, 0x12, 0x34,                    // cmp    ax, 0x3412
        0x3F,                                // aas    
        0x40,                                // inc    ax
        0x41,                                // inc    cx
        0x42,                                // inc    dx
        0x43,                                // inc    bx
        0x44,                                // inc    sp
        0x45,                                // inc    bp
        0x46,                                // inc    si
        0x47,                                // inc    di
        0x48,                                // dec    ax
        0x49,                                // dec    cx
        0x4A,                                // dec    dx
        0x4B,                                // dec    bx
        0x4C,                                // dec    sp
        0x4D,                                // dec    bp
        0x4E,                                // dec    si
        0x4F,                                // dec    di
        0x50,                                // push   ax
        0x51,                                // push   cx
        0x52,                                // push   dx
        0x53,                                // push   bx
        0x54,                                // push   sp
        0x55,                                // push   bp
        0x56,                                // push   si
        0x57,                                // push   di
        0x58,                                // pop    ax
        0x59,                                // pop    cx
        0x5A,                                // pop    dx
        0x5B,                                // pop    bx
        0x5C,                                // pop    sp
        0x5D,                                // pop    bp
        0x5E,                                // pop    si
        0x5F,                                // pop    di
        0x60, 0xC9,                          // jo
        0x61, 0x31,                          // jno
        0x62, 0x3A,                          // jb
        0x63, 0xC8,                          // JNB
        0x64, 0x76,                          // JZ
        0x65, 0xD3,                          // JNZ
        0x66, 0x71,                          // JNB
        0x67, 0xB0,                          // JS
        0x68, 0xED,                          // js
        0x69, 0xED,                          // jns
        0x6A, 0xEA,                          // jp
        0x6B, 0xD8,                          // jnp
        0x6C, 0xF6,                          // jl
        0x6D, 0xC4,                          // jge
        0x6E, 0x02,                          // jle
        0x6F, 0x43,                          // jg
        0x70, 0xC9,                          // jo
        0x71, 0x31,                          // jno
        0x72, 0x3A,                          // jb
        0x73, 0xC8,                          // jae
        0x74, 0x76,                          // je
        0x75, 0xD3,                          // jne
        0x76, 0x71,                          // jbe
        0x77, 0xB0,                          // ja
        0x78, 0xED,                          // js
        0x79, 0xED,                          // jns
        0x7A, 0xEA,                          // jp
        0x7B, 0xD8,                          // jnp
        0x7C, 0xF6,                          // jl
        0x7D, 0xC4,                          // jge
        0x7E, 0x02,                          // jle
        0x7F, 0x43,                          // jg
        0x80, 0x00, 0x11,                    // add byte ptr [bx + si], 0x11
        0x80, 0xc1, 0x40,                    // add  cl,  64
        0x80, 0xd1, 0x50,                    // adc  cl,  80
        0x81, 0x00, 0x11, 0x22,              // add word ptr [bx + si], 0x2211
        0x81, 0x99, 0x23, 0x45, 0x11, 0x22,  // sbb word ptr [bx + di + 0x4523], 0x2211
        0x82, 0x00, 0x11,                    // add byte ptr [bx + si], 0x11
        0x83, 0x00, 0x11,                    // add word ptr [bx + si], 0x11
        0x83, 0xc0, 0x10,                    // add  ax,  16
        0x83, 0xd1, 0x20,                    // adc  cx,  32
        0x83, 0x99, 0x23, 0x45, 0x11,        // sbb word ptr [bx + di + 0x4523], 0x11
        0x84, 0x00,                          // test byte ptr [bx + si], al
        0x85, 0x99, 0x22, 0x44,              // test word ptr [bx + di + 0x4422], bx
        0x86, 0x55, 0x33,                    // xchg byte ptr [di + 0x33], dl
        0x87, 0x99, 0x33, 0x44,              // xchg word ptr [bx + di + 0x4433], bx
        0x88, 0x33,                          // mov  byte ptr [bp + di], dh
        0x89, 0x77, 0x88,                    // mov  word ptr [bx - 0x78], si
        0x8A, 0x55, 0x33,                    // mov  dl, byte ptr [di + 0x33]
        0x8B, 0x99, 0x44, 0x55,              // mov  bx, word ptr [bx + di + 0x5544]
        0x8c, 0x99, 0x11, 0x22,              // mov word ptr [bx + di + 0x2211], ds
        0x8D, 0x99, 0x11, 0x22,              // lea bx, [bx + di + 0x2211]
        0x8E, 0x88, 0x33, 0x33,              // mov cs, word ptr [bx + si + 0x3333]
        0x8F, 0x00,                          // pop word ptr [bx + si]
        0x90,                                // nop
        0x91,                                // xchg ax, cx
        0x92,                                // xchg ax, dx
        0x93,                                // xchg ax, bx
        0x94,                                // xchg ax, sp
        0x95,                                // xchg ax, bp
        0x96,                                // xchg ax, si
        0x97,                                // xchg ax, di
        0x98,                                // cbw
        0x99,                                // cwd
        0x9a, 0x78, 0x56, 0x34, 0x12,        // lcall lcall 0x1234:0x5678 / call far 0x1234:0x5678
        0x9b,                                // wait
        0x9c,                                // pushf
        0x9d,                                // popf
        0x9e,                                // sahf
        0x9f,                                // lahf
        0xa0, 0x12,                          // mov al, [0x12]
        0xa1, 0x12, 0x34,                    // mov ax, [0x3412]
        0xa2, 0x12,                          // mov [0x12], al
        0xa3, 0x12, 0x34,                    // mov [0x3412], ax
        0xa4,                                // movsb byte es:[di], byte [si]
        0xa5,                                // movsw word es:[di], word [si]
        0xA6,                                // cmpsb byte [si], byte es:[di]
        0xA7,                                // cmpsw word [si], word es:[di]
        0xa8, 0x12,                          // test al, [0x12]
        0xa9, 0x12, 0x34,                    // test ax, [0x3412]
        0xaa,                                // stosb byte es:[di], al
        0xab,                                // stosw word es:[di], ax
        0xAC,                                // lodsb al, byte ptr [si]
        0xAD,                                // lodsw ax, word ptr [si]
        0xAE,                                // scasb al, byte ptr es:[di]
        0xAF,                                // scasw ax, word ptr es:[di]*/
        0xB0, 0x12,                          // mov   al, 0x12
        0xB1, 0x23,                          // mov   cl, 0x23
        0xB2, 0x45,                          // mov   dl, 0x45
        0xB3, 0x67,                          // mov   bl, 0x67
        0xB4, 0x89,                          // mov   ah, 0x89
        0xB5, 0xAB,                          // mov   ch, 0xab
        0xB6, 0xCD,                          // mov   dh, 0xcd
        0xB7, 0xEF,                          // mov   bh, 0xef
        0xB8, 0x12, 0x34,                    // mov   ax, 0x3412
        0xB9, 0x56, 0x78,                    // mov   cx, 0x7856
        0xBA, 0x9A, 0xBC,                    // mov   dx, 0xbc9a
        0xBB, 0x01, 0x23,                    // mov   bx, 0x2301
        0xBC, 0x45, 0x67,                    // mov   sp, 0x6745
        0xBD, 0x89, 0xAB,                    // mov   bp, 0xab89
        0xBE, 0xCD, 0xEF,                    // mov   si, 0xefcd
        0xBF, 0x01, 0x23,                    // mov   di, 0x2301
     
        // ret near inmed16, es la misma      que C2 solo para 8086
        0xC0, 0x34, 0x12,                    // ret near 0x1234
                                             // sal byte ptr [si], 0x12 en no 8086

        // ret ( no documentada) para el 8086
        0xc1,                            // ret
        // 0xC1, 0x34, 0x54,                // sal word ptr [si], 0x54 en no 8086
        
        0xC2, 0x34, 0x12,               // ret near 0x1234
        0xc3,                           // ret

        0xC4, 0x99, 0x21, 0x43,         // les  bx, ptr [bx + di + 0x4321]
        0xC5, 0x99, 0x21, 0x43,         // lds  bx, ptr [bx + di + 0x4321]
        0xC6, 0x00, 0xAA,               // mov  byte ptr [bx + si], 0xaa
        0xc7, 0x00, 0xaa, 0xbb,         // mov  word ptr [bx + si], 0xbbaa

        // ret far ( no documentada) para el 8086
        0XC8, 0X34, 0X12,               // retf 0x1234 / ret far 0x1234
                                        // invalida fuera del 8086

        0XCA, 0X34, 0X12,               // retf 0x1234 / ret far 0x1234
        0xCB,                           // retf
        0xcc,                           // int 3
        0xCD, 0x12,                     // int 0x12
        0xce,                           // into
        0xCF,                           // iret
        0xD0, 0x00,                     // rol byte ptr [bx + si], 1
        0xD0, 0x99, 0x12, 0x34,         // rcr byte ptr [bx + di + 0x3412], 1
        0xD1, 0x00,                     // rol word ptr [bx + si], 1
        0xD1, 0x99, 0x12, 0x34,         // rcr word ptr [bx + di + 0x3412], 1
        0xD2, 0x00,                     // rol byte ptr [bx + si], cl
        0xD2, 0x99, 0x12, 0x34,         // rcr byte ptr [bx + di + 0x3412], cl
        0xD3, 0x00,                     // rol word ptr [bx + si], cl
        0xD3, 0x99, 0x12, 0x34,         // rcr word ptr [bx + di + 0x3412], cl
        0xd4,                           // aam
        0xd5,                           // aad
        0xd6,                           // salc
        0xd7,                           // xlat
        

       // primera tabla de instrucciones del x87
        0xD8, 0xD0,                     // ESC(fcom  st(0))
        0xD8, 0xD1,                     // ESC(fcom  st(1))
        0xD8, 0xD2,                     // ESC(fcom  st(2))
        0xD8, 0xD3,                     // ESC(fcom  st(3))
        0xD8, 0xD4,                     // ESC(fcom  st(4))
        0xD8, 0xD5,                     // ESC(fcom  st(5))
        0xD8, 0xD6,                     // ESC(fcom  st(6))
        0xD8, 0xD7,                     // ESC(fcom  st(7))
        0xd8, 0xd8,                     // ESC(fcomp st(0))
        0xd8, 0xd9,                     // ESC(fcomp st(1))
        0xd8, 0xda,                     // ESC(fcomp st(2))
        0xd8, 0xdb,                     // ESC(fcomp st(3))
        0xd8, 0xdc,                     // ESC(fcomp st(4))
        0xd8, 0xdd,                     // ESC(fcomp st(5))
        0xd8, 0xde,                     // ESC(fcomp st(6))
        0xd8, 0xdf,                     // ESC(fcomp st(7))

        // segunda tabla de instrucciones del x87
        0xD9, 0xC0,                     // ESC(fld st(0))
        0xD9, 0xC1,                     // ESC(fld st(1))
        0xD9, 0xC2,                     // ESC(fld st(2))
        0xD9, 0xC3,                     // ESC(fld st(3))
        0xD9, 0xC4,                     // ESC(fld st(4))
        0xD9, 0xC5,                     // ESC(fld st(5))
        0xD9, 0xC6,                     // ESC(fld st(6))
        0xD9, 0xC7,                     // ESC(fld st(7))
        0xD9, 0x80, 0x34, 0x12,         // ESC(fld dword ptr [bx + si + 0x1234])
        0xD9, 0x81, 0x34, 0x12,         // ESC(fld dword ptr [bx + di + 0x1234])
        0xD9, 0x82, 0x34, 0x12,         // ESC(fld dword ptr [bp + si + 0x1234])
        0xD9, 0x83, 0x34, 0x12,         // ESC(fld dword ptr [bp + di + 0x1234])
        0xD9, 0x84, 0x34, 0x12,         // ESC(fld dword ptr [si      + 0x1234])
        0xD9, 0x85, 0x34, 0x12,         // ESC(fld dword ptr [di      + 0x1234])
        0xD9, 0x86, 0x34, 0x12,         // ESC(fld dword ptr [bp      + 0x1234])
        0xD9, 0x87, 0x34, 0x12,         // ESC(fld dword ptr [bx      + 0x1234])

        // quinta tabla de instrucciones del x87
        0xDD, 0xD8,                     // ESC(fstp st(0))
        0xDD, 0xD9,                     // ESC(fstp st(1))
        0xDD, 0xDA,                     // ESC(fstp st(2))
        0xDD, 0xDC,                     // ESC(fstp st(4))
        0xDD, 0xDD,                     // ESC(fstp st(5))
        0xDD, 0xDE,                     // ESC(fstp st(6))
        0xDD, 0xDF,                     // ESC(fstp st(7))
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
        //print_Instruction_info(&instruccion, ENCODER_IN_16bits);

        /**/char* string = calloc(64, sizeof(char));
        get_string_Instruction_info_8086(&instruccion, string, 64);
        printf("%s\n", string);
        free(string);

        printf("[*] size instruction %d (%p - %p -> %zu)\n", (position-position_old),
            instrucciones + position, instrucciones + sizeof(instrucciones), position);
        
        memset(&instruccion, 0, sizeof(Instruction_info));
        position_old = position;

        cantidad_de_instrucciones++;
        if (cantidad_de_instrucciones == 8) break;
        
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

