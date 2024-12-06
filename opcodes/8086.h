#define CONVERT_MEM16 0b01
#define REVERSE_BIT_D 0b10
#define OPCODES_8086(val) opcodes_8086_ ## val

typedef enum opcodes_8086 {
    // ADD reg8/mem8, reg8
    OPCODES_8086(ADD_mem8)          = 0b00000000,

    // ADD reg16/mem16, reg16
    OPCODES_8086(ADD_mem16)         = CONVERT_MEM16 | OPCODES_8086(ADD_mem8),

    // ADD reg8, reg8/mem8
    OPCODES_8086(ADD_mem8_inverse)  = OPCODES_8086(ADD_mem8) | REVERSE_BIT_D,

    // ADD reg16, reg16/mem16
    OPCODES_8086(ADD_mem16_inverse) = OPCODES_8086(ADD_mem8) | REVERSE_BIT_D | CONVERT_MEM16,

    // ADD AL, immed16
    OPCODES_8086(ADD_al),

    // ADD AX, immed16
    OPCODES_8086(ADD_ax),
    
    // PUSH ES
    OPCODES_8086(PUSH_es),

    // POP ES
    OPCODES_8086(POP_es),

    // OR reg8/mem8, reg8
    OPCODES_8086(OR_mem8),

    // OR reg16/mem16, reg16
    OPCODES_8086(OR_mem16)         = CONVERT_MEM16 | OPCODES_8086(OR_mem8),

    // OR reg8, reg8/mem8
    OPCODES_8086(OR_mem8_inverse)  = OPCODES_8086(OR_mem8) | REVERSE_BIT_D,

    // OR reg16, reg16/mem16
    OPCODES_8086(OR_mem16_inverse) = OPCODES_8086(OR_mem8) | REVERSE_BIT_D | CONVERT_MEM16,

    // OR AL, immed16
    OPCODES_8086(OR_al),

    // OR AX, immed16
    OPCODES_8086(OR_ax),
    
    // PUSH CS
    OPCODES_8086(PUSH_cs),

    // POP CS
    OPCODES_8086(POP_cs),

    // ADC reg8/mem8, reg8
    OPCODES_8086(ADC_mem8),

    // ADC reg16/mem16, reg16
    OPCODES_8086(ADC_mem16)         = CONVERT_MEM16 | OPCODES_8086(ADC_mem8),

    // ADC reg8, reg8/mem8
    OPCODES_8086(ADC_mem8_inverse)  = OPCODES_8086(ADC_mem8) | REVERSE_BIT_D,

    // ADC reg16, reg16/mem16
    OPCODES_8086(ADC_mem16_inverse) = OPCODES_8086(ADC_mem8) | REVERSE_BIT_D | CONVERT_MEM16,

    // ADC AL, immed16
    OPCODES_8086(ADC_al),

    // ADC AX, immed16
    OPCODES_8086(ADC_ax),

    // PUSH CS
    OPCODES_8086(PUSH_cs),

    // POP CS
    OPCODES_8086(POP_cs),

    // SBB reg8/mem8, reg8
    OPCODES_8086(SBB_mem8),

    // SBB reg16/mem16, reg16
    OPCODES_8086(SBB_mem16)         = CONVERT_MEM16 | OPCODES_8086(SBB_mem8),

    // SBB reg8, reg8/mem8
    OPCODES_8086(SBB_mem8_inverse)  = OPCODES_8086(SBB_mem8) | REVERSE_BIT_D,

    // SBB reg16, reg16/mem16
    OPCODES_8086(SBB_mem16_inverse) = OPCODES_8086(SBB_mem8) | REVERSE_BIT_D | CONVERT_MEM16,

    // SBB AL, immed16
    OPCODES_8086(SBB_al),

    // SBB AX, immed16
    OPCODES_8086(SBB_ax),

    // PUSH DS
    OPCODES_8086(PUSH_ds),

    // POP DS
    OPCODES_8086(POP_ds),

    // AND reg8/mem8, reg8
    OPCODES_8086(AND_mem8),

    // AND reg16/mem16, reg16
    OPCODES_8086(AND_mem16)         = CONVERT_MEM16 | OPCODES_8086(AND_mem8),

    // AND reg8, reg8/mem8
    OPCODES_8086(AND_mem8_inverse)  = OPCODES_8086(AND_mem8) | REVERSE_BIT_D,

    // AND reg16, reg16/mem16
    OPCODES_8086(AND_mem16_inverse) = OPCODES_8086(AND_mem8) | REVERSE_BIT_D | CONVERT_MEM16,

    // AND AL, immed16
    OPCODES_8086(AND_al),

    // AND AX, immed16
    OPCODES_8086(AND_ax),

    // prefix ES

    // DAA
    OPCODES_8086(DAA) = 0x27,

    // SUB reg8/mem8, reg8
    OPCODES_8086(SUB_mem8),

    // SUB reg16/mem16, reg16
    OPCODES_8086(SUB_mem16)         = CONVERT_MEM16 | OPCODES_8086(SUB_mem8),

    // SUB reg8, reg8/mem8
    OPCODES_8086(SUB_mem8_inverse)  = OPCODES_8086(SUB_mem8) | REVERSE_BIT_D,

    // SUB reg16, reg16/mem16
    OPCODES_8086(SUB_mem16_inverse) = OPCODES_8086(SUB_mem8) | REVERSE_BIT_D | CONVERT_MEM16,

    // SUB AL, immed16
    OPCODES_8086(SUB_al),

    // SUB AX, immed16
    OPCODES_8086(SUB_ax),

    // CS prefix

    // DAS
    OPCODES_8086(DAS) = 0x2f,

    // XOR reg8/mem8, reg8
    OPCODES_8086(XOR_mem8),

    // XOR reg16/mem16, reg16
    OPCODES_8086(XOR_mem16)         = CONVERT_MEM16 | OPCODES_8086(XOR_mem8),

    // XOR reg8, reg8/mem8
    OPCODES_8086(XOR_mem8_inverse)  = OPCODES_8086(XOR_mem8) | REVERSE_BIT_D,

    // XOR reg16, reg16/mem16
    OPCODES_8086(XOR_mem16_inverse) = OPCODES_8086(XOR_mem8) | REVERSE_BIT_D | CONVERT_MEM16,

    // XOR AL, immed16
    OPCODES_8086(XOR_al),

    // XOR AX, immed16
    OPCODES_8086(XOR_ax),

    // SS prefix

    // AAA
    OPCODES_8086(AAA) = 0x37,

    // CMP reg8/mem8, reg8
    OPCODES_8086(CMP_mem8),

    // CMP reg16/mem16, reg16
    OPCODES_8086(CMP_mem16)         = CONVERT_MEM16 | OPCODES_8086(CMP_mem8),

    // CMP reg8, reg8/mem8
    OPCODES_8086(CMP_mem8_inverse)  = OPCODES_8086(CMP_mem8) | REVERSE_BIT_D,

    // CMP reg16, reg16/mem16
    OPCODES_8086(CMP_mem16_inverse) = OPCODES_8086(CMP_mem8) | REVERSE_BIT_D | CONVERT_MEM16,

    // CMP AL, immed16
    OPCODES_8086(CMP_al),

    // CMP AX, immed16
    OPCODES_8086(CMP_ax),

    // DS prefix

    // AAS
    OPCODES_8086(AAS) = 0x3F,

    // INC AX/BX/CX/DX/SI/DI/BP/SP
    OPCODES_8086(INC),


    


} opcodes_8086;