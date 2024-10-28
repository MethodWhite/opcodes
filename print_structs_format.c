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
#ifndef __PRINT_STRUCTS_FORMAT_C_
#define __PRINT_STRUCTS_FORMAT_C_

#include "print_structs_format.h"

char *get_addr_to_encoder_x86(uint64_t addr, encoder_x86 encoder_val) {
    /*
     *  
     * get_addr_to_encoder_x86(uint64_t addr, encoder_x86 encoder_val):
     * Esta funcion devuelve un string con la direccion de memoria formateada en 16, 32 o 64bits
     * 
     * Se espera recibir addr el cual es la direccion de memoria a formatear,
     * se espera recibir encoder_val, el cual indica si formatear la direcion a 16, 32 o 64bits.
     *      Posibles valores para encoder_x86 encoder_val:
     *          - ENCODER_IN_16bits = 0 : para 16bits
     *          - ENCODER_IN_32bits = 1 : para 32bits
     *          - ENCODER_IN_64bits = 2 : para 64bits
     * 
     * En caso de que malloc devuelva error, la funcion devuelve NULL
     *  
     */
    size_t size;
    char *buffer_Position_memory;
    switch (encoder_val) {
        case ENCODER_IN_16bits:
            size = (snprintf(NULL, 0, "%04x", (uint16_t)addr) + 1) * sizeof(char);
            buffer_Position_memory = (char *)malloc(size);
            if (buffer_Position_memory == NULL) return NULL;
            sprintf(buffer_Position_memory, "%04x", (uint16_t)addr);
            break;
        case ENCODER_IN_32bits:
            size = (snprintf(NULL, 0, "%08x", (uint32_t)addr) + 1) * sizeof(char);
            buffer_Position_memory = (char *)malloc(size);
            if (buffer_Position_memory == NULL) return NULL;
            sprintf(buffer_Position_memory, "%08x", (uint32_t)addr);
            break;
        case ENCODER_IN_64bits:
            size = (snprintf(NULL, 0, "%016llx", (uint64_t)addr) + 1) * sizeof(char);
            buffer_Position_memory = (char *)malloc(size);
            if (buffer_Position_memory == NULL) return NULL;
            sprintf(buffer_Position_memory, "%016llx", (uint64_t)addr);
            break;
        default: return NULL; // error
    }
    return buffer_Position_memory;
}

#endif