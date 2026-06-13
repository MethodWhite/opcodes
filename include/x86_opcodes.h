#ifndef X86_OPCODES_H
#define X86_OPCODES_H

#include <stddef.h>
#include <stdint.h>

#ifdef __cplusplus
extern "C" {
#endif

/* Instruction set architecture mode */
typedef enum {
    X86_MODE_16,
    X86_MODE_32,
    X86_MODE_64
} x86_mode;

/* Decoded instruction representation */
typedef struct {
    uint8_t  prefix[4];
    uint8_t  opcode_bytes[3];
    uint8_t  modrm;
    uint8_t  sib;
    uint32_t displacement;
    uint32_t immediate;
    uint8_t  prefix_count;
    uint8_t  opcode_len;
    uint8_t  has_modrm;
    uint8_t  has_sib;
    uint8_t  disp_bytes;
    uint8_t  imm_bytes;
    uint8_t  total_length;
} x86_instruction;

/* Decode a buffer of bytes into instruction structures.
 * Returns the number of instructions decoded.
 * `count` is the number of bytes in the buffer.
 * `out` is the output array (capacity in `max_instructions`).
 */
size_t x86_decode(const uint8_t *bytes, size_t count,
                  x86_instruction *out, size_t max_instructions,
                  x86_mode mode);

/* Get the string mnemonic for an instruction */
const char *x86_mnemonic(const x86_instruction *inst);

/* Print instruction details */
void x86_print(const x86_instruction *inst, x86_mode mode);

#ifdef __cplusplus
}
#endif

#endif /* X86_OPCODES_H */
