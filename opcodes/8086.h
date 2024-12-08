#define CONVERT_MEM16 0b01
#define REVERSE_BIT_D 0b10
#define OPCODES_8086(val) opcodes_8086_ ## val
#define UNDOCUMENTED(val) undocumented_opcodes_8086_ ## val

#define STRINGIFY(x) #x
#define TOSTRING(x) STRINGIFY(x)



/*
PS C:\Users\desmon0xff\Desktop\files\Shared\8086_Emulator\lib\opcodes\opcodes> .\8086.exe
Lista de valores del enum opcodes_8086:
Identificador:                                        opcodes_8086_ADD_mem8, Valor: 0x0
Identificador:                                       opcodes_8086_ADD_mem16, Valor: 0x1
Identificador:                                opcodes_8086_ADD_mem8_inverse, Valor: 0x2
Identificador:                               opcodes_8086_ADD_mem16_inverse, Valor: 0x3
Identificador:                                          opcodes_8086_ADD_al, Valor: 0x4
Identificador:                                          opcodes_8086_ADD_ax, Valor: 0x5
Identificador:                                         opcodes_8086_PUSH_es, Valor: 0x6
Identificador:                                          opcodes_8086_POP_es, Valor: 0x7
Identificador:                                         opcodes_8086_OR_mem8, Valor: 0x8
Identificador:                                        opcodes_8086_OR_mem16, Valor: 0x9
Identificador:                                 opcodes_8086_OR_mem8_inverse, Valor: 0xA
Identificador:                                opcodes_8086_OR_mem16_inverse, Valor: 0xB
Identificador:                                           opcodes_8086_OR_al, Valor: 0xC
Identificador:                                           opcodes_8086_OR_ax, Valor: 0xD
Identificador:                                         opcodes_8086_PUSH_cs, Valor: 0xE
Identificador:                                          opcodes_8086_POP_cs, Valor: 0xF
Identificador:                                        opcodes_8086_ADC_mem8, Valor: 0x10
Identificador:                                       opcodes_8086_ADC_mem16, Valor: 0x11
Identificador:                                opcodes_8086_ADC_mem8_inverse, Valor: 0x12
Identificador:                               opcodes_8086_ADC_mem16_inverse, Valor: 0x13
Identificador:                                          opcodes_8086_ADC_al, Valor: 0x14
Identificador:                                          opcodes_8086_ADC_ax, Valor: 0x15
Identificador:                                         opcodes_8086_PUSH_ss, Valor: 0x16
Identificador:                                          opcodes_8086_POP_ss, Valor: 0x17
Identificador:                                        opcodes_8086_SBB_mem8, Valor: 0x18
Identificador:                                       opcodes_8086_SBB_mem16, Valor: 0x19
Identificador:                                opcodes_8086_SBB_mem8_inverse, Valor: 0x1A
Identificador:                               opcodes_8086_SBB_mem16_inverse, Valor: 0x1B
Identificador:                                          opcodes_8086_SBB_al, Valor: 0x1C
Identificador:                                          opcodes_8086_SBB_ax, Valor: 0x1D
Identificador:                                         opcodes_8086_PUSH_ds, Valor: 0x1E
Identificador:                                          opcodes_8086_POP_ds, Valor: 0x1F
Identificador:                                        opcodes_8086_AND_mem8, Valor: 0x20
Identificador:                                       opcodes_8086_AND_mem16, Valor: 0x21
Identificador:                                opcodes_8086_AND_mem8_inverse, Valor: 0x22
Identificador:                               opcodes_8086_AND_mem16_inverse, Valor: 0x23
Identificador:                                          opcodes_8086_AND_al, Valor: 0x24
Identificador:                                          opcodes_8086_AND_ax, Valor: 0x25
Identificador:                                             opcodes_8086_DAA, Valor: 0x27
Identificador:                                        opcodes_8086_SUB_mem8, Valor: 0x28
Identificador:                                       opcodes_8086_SUB_mem16, Valor: 0x29
Identificador:                                opcodes_8086_SUB_mem8_inverse, Valor: 0x2A
Identificador:                               opcodes_8086_SUB_mem16_inverse, Valor: 0x2B
Identificador:                                          opcodes_8086_SUB_al, Valor: 0x2C
Identificador:                                          opcodes_8086_SUB_ax, Valor: 0x2D
Identificador:                                             opcodes_8086_DAS, Valor: 0x2F
Identificador:                                        opcodes_8086_XOR_mem8, Valor: 0x30
Identificador:                                       opcodes_8086_XOR_mem16, Valor: 0x31
Identificador:                                opcodes_8086_XOR_mem8_inverse, Valor: 0x32
Identificador:                               opcodes_8086_XOR_mem16_inverse, Valor: 0x33
Identificador:                                          opcodes_8086_XOR_al, Valor: 0x34
Identificador:                                          opcodes_8086_XOR_ax, Valor: 0x35
Identificador:                                             opcodes_8086_AAA, Valor: 0x37
Identificador:                                        opcodes_8086_CMP_mem8, Valor: 0x38
Identificador:                                       opcodes_8086_CMP_mem16, Valor: 0x39
Identificador:                                opcodes_8086_CMP_mem8_inverse, Valor: 0x3A
Identificador:                               opcodes_8086_CMP_mem16_inverse, Valor: 0x3B
Identificador:                                          opcodes_8086_CMP_al, Valor: 0x3C
Identificador:                                          opcodes_8086_CMP_ax, Valor: 0x3D
Identificador:                                             opcodes_8086_AAS, Valor: 0x3F
Identificador:                                          opcodes_8086_INC_ax, Valor: 0x40
Identificador:                                          opcodes_8086_INC_cx, Valor: 0x41
Identificador:                                          opcodes_8086_INC_dx, Valor: 0x42
Identificador:                                          opcodes_8086_INC_bx, Valor: 0x43
Identificador:                                          opcodes_8086_INC_sp, Valor: 0x44
Identificador:                                          opcodes_8086_INC_bp, Valor: 0x45
Identificador:                                          opcodes_8086_INC_si, Valor: 0x46
Identificador:                                          opcodes_8086_INC_di, Valor: 0x47
Identificador:                                          opcodes_8086_DEC_ax, Valor: 0x48
Identificador:                                          opcodes_8086_DEC_cx, Valor: 0x49
Identificador:                                          opcodes_8086_DEC_dx, Valor: 0x4A
Identificador:                                          opcodes_8086_DEC_bx, Valor: 0x4B
Identificador:                                          opcodes_8086_DEC_sp, Valor: 0x4C
Identificador:                                          opcodes_8086_DEC_bp, Valor: 0x4D
Identificador:                                          opcodes_8086_DEC_si, Valor: 0x4E
Identificador:                                          opcodes_8086_DEC_di, Valor: 0x4F
Identificador:                                         opcodes_8086_PUSH_ax, Valor: 0x50
Identificador:                                         opcodes_8086_PUSH_cx, Valor: 0x51
Identificador:                                         opcodes_8086_PUSH_dx, Valor: 0x52
Identificador:                                         opcodes_8086_PUSH_bx, Valor: 0x53
Identificador:                                         opcodes_8086_PUSH_sp, Valor: 0x54
Identificador:                                         opcodes_8086_PUSH_bp, Valor: 0x55
Identificador:                                         opcodes_8086_PUSH_si, Valor: 0x56
Identificador:                                         opcodes_8086_PUSH_di, Valor: 0x57
Identificador:                                          opcodes_8086_POP_ax, Valor: 0x58
Identificador:                                          opcodes_8086_POP_cx, Valor: 0x59
Identificador:                                          opcodes_8086_POP_dx, Valor: 0x5A
Identificador:                                          opcodes_8086_POP_bx, Valor: 0x5B
Identificador:                                          opcodes_8086_POP_sp, Valor: 0x5C
Identificador:                                          opcodes_8086_POP_bp, Valor: 0x5D
Identificador:                                          opcodes_8086_POP_si, Valor: 0x5E
Identificador:                                          opcodes_8086_POP_di, Valor: 0x5F
Identificador:                                 undocumented_opcodes_8086_JO, Valor: 0x60
Identificador:                                undocumented_opcodes_8086_JNO, Valor: 0x61
Identificador:                                 undocumented_opcodes_8086_JC, Valor: 0x62
Identificador:                                undocumented_opcodes_8086_JAE, Valor: 0x63
Identificador:                                 undocumented_opcodes_8086_JE, Valor: 0x64
Identificador:                                undocumented_opcodes_8086_JNZ, Valor: 0x65
Identificador:                                undocumented_opcodes_8086_JBE, Valor: 0x66
Identificador:                                 undocumented_opcodes_8086_JA, Valor: 0x67
Identificador:                                 undocumented_opcodes_8086_JS, Valor: 0x68
Identificador:                                undocumented_opcodes_8086_JNS, Valor: 0x69
Identificador:                                undocumented_opcodes_8086_JPE, Valor: 0x6A
Identificador:                                undocumented_opcodes_8086_JNP, Valor: 0x6B
Identificador:                                 undocumented_opcodes_8086_JL, Valor: 0x6C
Identificador:                                undocumented_opcodes_8086_JGE, Valor: 0x6D
Identificador:                                undocumented_opcodes_8086_JLE, Valor: 0x6E
Identificador:                                 undocumented_opcodes_8086_JG, Valor: 0x6F
Identificador:                                              opcodes_8086_JO, Valor: 0x70
Identificador:                                             opcodes_8086_JNO, Valor: 0x71
Identificador:                                              opcodes_8086_JC, Valor: 0x72
Identificador:                                             opcodes_8086_JAE, Valor: 0x73
Identificador:                                              opcodes_8086_JE, Valor: 0x74
Identificador:                                             opcodes_8086_JNZ, Valor: 0x75
Identificador:                                             opcodes_8086_JBE, Valor: 0x76
Identificador:                                              opcodes_8086_JA, Valor: 0x77
Identificador:                                              opcodes_8086_JS, Valor: 0x78
Identificador:                                             opcodes_8086_JNS, Valor: 0x79
Identificador:                                             opcodes_8086_JPE, Valor: 0x7A
Identificador:                                             opcodes_8086_JNP, Valor: 0x7B
Identificador:                                              opcodes_8086_JL, Valor: 0x7C
Identificador:                                             opcodes_8086_JGE, Valor: 0x7D
Identificador:                                             opcodes_8086_JLE, Valor: 0x7E
Identificador:                                              opcodes_8086_JG, Valor: 0x7F
Identificador:                                     opcodes_8086_ADD_inmmed8, Valor: 0x80
Identificador:                                      opcodes_8086_OR_inmmed8, Valor: 0x80
Identificador:                                     opcodes_8086_ADC_inmmed8, Valor: 0x80
Identificador:                                     opcodes_8086_SBB_inmmed8, Valor: 0x80
Identificador:                                     opcodes_8086_AND_inmmed8, Valor: 0x80
Identificador:                                     opcodes_8086_SUB_inmmed8, Valor: 0x80
Identificador:                                     opcodes_8086_XOR_inmmed8, Valor: 0x80
Identificador:                                     opcodes_8086_CMP_inmmed8, Valor: 0x80
Identificador:                                    opcodes_8086_ADD_inmmed16, Valor: 0x81
Identificador:                                     opcodes_8086_OR_inmmed16, Valor: 0x81
Identificador:                                    opcodes_8086_ADC_inmmed16, Valor: 0x81
Identificador:                                    opcodes_8086_SBB_inmmed16, Valor: 0x81
Identificador:                                    opcodes_8086_AND_inmmed16, Valor: 0x81
Identificador:                                    opcodes_8086_SUB_inmmed16, Valor: 0x81
Identificador:                                    opcodes_8086_XOR_inmmed16, Valor: 0x81
Identificador:                                    opcodes_8086_CMP_inmmed16, Valor: 0x81
Identificador:                                   opcodes_8086_ADD_inmmed8_2, Valor: 0x82
Identificador:                                    opcodes_8086_OR_inmmed8_2, Valor: 0x82
Identificador:                                   opcodes_8086_ADC_inmmed8_2, Valor: 0x82
Identificador:                                   opcodes_8086_SBB_inmmed8_2, Valor: 0x82
Identificador:                                   opcodes_8086_AND_inmmed8_2, Valor: 0x82
Identificador:                                   opcodes_8086_SUB_inmmed8_2, Valor: 0x82
Identificador:                                   opcodes_8086_XOR_inmmed8_2, Valor: 0x82
Identificador:                                   opcodes_8086_CMP_inmmed8_2, Valor: 0x82
Identificador:                           opcodes_8086_ADD_inmmed8_reg_mem16, Valor: 0x83
Identificador:                            opcodes_8086_OR_inmmed8_reg_mem16, Valor: 0x83
Identificador:                           opcodes_8086_ADC_inmmed8_reg_mem16, Valor: 0x83
Identificador:                           opcodes_8086_SBB_inmmed8_reg_mem16, Valor: 0x83
Identificador:                           opcodes_8086_AND_inmmed8_reg_mem16, Valor: 0x83
Identificador:                           opcodes_8086_SUB_inmmed8_reg_mem16, Valor: 0x83
Identificador:                           opcodes_8086_XOR_inmmed8_reg_mem16, Valor: 0x83
Identificador:                           opcodes_8086_CMP_inmmed8_reg_mem16, Valor: 0x83
Identificador:                                       opcodes_8086_TEST_reg8, Valor: 0x84
Identificador:                                      opcodes_8086_TEST_reg16, Valor: 0x85
Identificador:                                       opcodes_8086_XCHG_reg8, Valor: 0x86
Identificador:                                      opcodes_8086_XCHG_reg16, Valor: 0x87
Identificador:                                        opcodes_8086_MOV_reg8, Valor: 0x88
Identificador:                                       opcodes_8086_MOV_reg16, Valor: 0x89
Identificador:                                        opcodes_8086_MOV_mem8, Valor: 0x8A
Identificador:                                       opcodes_8086_MOV_mem16, Valor: 0x8B
Identificador:                            opcodes_8086_MOV_reg_mem16_segreg, Valor: 0x8C
Identificador:                                       opcodes_8086_LEA_mem16, Valor: 0x8D
Identificador:                            opcodes_8086_MOV_segreg_reg_mem16, Valor: 0x8E
Identificador:                                   opcodes_8086_POP_reg_mem16, Valor: 0x8F
Identificador:                                      opcodes_8086_XCHG_ax_ax, Valor: 0x90
Identificador:                                      opcodes_8086_XCHG_ax_cx, Valor: 0x91
Identificador:                                      opcodes_8086_XCHG_ax_dx, Valor: 0x92
Identificador:                                      opcodes_8086_XCHG_ax_bx, Valor: 0x93
Identificador:                                      opcodes_8086_XCHG_ax_sp, Valor: 0x94
Identificador:                                      opcodes_8086_XCHG_ax_bp, Valor: 0x95
Identificador:                                      opcodes_8086_XCHG_ax_si, Valor: 0x96
Identificador:                                      opcodes_8086_XCHG_ax_di, Valor: 0x97
Identificador:                                             opcodes_8086_CBW, Valor: 0x98
Identificador:                                             opcodes_8086_CWD, Valor: 0x99
Identificador:                                        opcodes_8086_CALL_FAR, Valor: 0x9A
Identificador:                                            opcodes_8086_WAIT, Valor: 0x9B
Identificador:                                           opcodes_8086_PUSHF, Valor: 0x9C
Identificador:                                            opcodes_8086_POPF, Valor: 0x9D
Identificador:                                            opcodes_8086_SAHF, Valor: 0x9E
Identificador:                                            opcodes_8086_LAHF, Valor: 0x9F
Identificador:                                     opcodes_8086_MOV_al_mem8, Valor: 0xA0
Identificador:                                    opcodes_8086_MOV_ax_mem16, Valor: 0xA1
Identificador:                                     opcodes_8086_MOV_mem8_al, Valor: 0xA2
Identificador:                                    opcodes_8086_MOV_mem16_ax, Valor: 0xA3
Identificador:                                       opcodes_8086_MOVS_ptr8, Valor: 0xA4
Identificador:                                      opcodes_8086_MOVS_ptr16, Valor: 0xA5
Identificador:                                       opcodes_8086_CMPS_ptr8, Valor: 0xA6
Identificador:                                      opcodes_8086_CMPS_ptr16, Valor: 0xA7
Identificador:                                 opcodes_8086_TEST_al_inmmed8, Valor: 0xA8
Identificador:                                opcodes_8086_TEST_ax_inmmed16, Valor: 0xA9
Identificador:                                       opcodes_8086_STOS_ptr8, Valor: 0xAA
Identificador:                                      opcodes_8086_STOS_ptr16, Valor: 0xAB
Identificador:                                       opcodes_8086_LODS_ptr8, Valor: 0xAC
Identificador:                                      opcodes_8086_LODS_ptr16, Valor: 0xAD
Identificador:                                       opcodes_8086_SCAS_ptr8, Valor: 0xAE
Identificador:                                      opcodes_8086_SCAS_ptr16, Valor: 0xAF
Identificador:                                  opcodes_8086_MOV_al_inmmed8, Valor: 0xB0
Identificador:                                  opcodes_8086_MOV_cl_inmmed8, Valor: 0xB1
Identificador:                                  opcodes_8086_MOV_dl_inmmed8, Valor: 0xB2
Identificador:                                  opcodes_8086_MOV_bl_inmmed8, Valor: 0xB3
Identificador:                                  opcodes_8086_MOV_ah_inmmed8, Valor: 0xB4
Identificador:                                  opcodes_8086_MOV_ch_inmmed8, Valor: 0xB5
Identificador:                                  opcodes_8086_MOV_dh_inmmed8, Valor: 0xB6
Identificador:                                  opcodes_8086_MOV_bh_inmmed8, Valor: 0xB7
Identificador:                                 opcodes_8086_MOV_ax_inmmed16, Valor: 0xB8
Identificador:                                 opcodes_8086_MOV_cx_inmmed16, Valor: 0xB9
Identificador:                                 opcodes_8086_MOV_dx_inmmed16, Valor: 0xBA
Identificador:                                 opcodes_8086_MOV_bx_inmmed16, Valor: 0xBB
Identificador:                                 opcodes_8086_MOV_sp_inmmed16, Valor: 0xBC
Identificador:                                 opcodes_8086_MOV_bp_inmmed16, Valor: 0xBD
Identificador:                                 opcodes_8086_MOV_si_inmmed16, Valor: 0xBE
Identificador:                                 opcodes_8086_MOV_di_inmmed16, Valor: 0xBF
Identificador:         undocumented_opcodes_8086_RET_NEAR_inmmed16_intraseg, Valor: 0xC0
Identificador:                       undocumented_opcodes_8086_RET_intraseg, Valor: 0xC1
Identificador:                      opcodes_8086_RET_NEAR_inmmed16_intraseg, Valor: 0xC2
Identificador:                                    opcodes_8086_RET_intraseg, Valor: 0xC3
Identificador:                                       opcodes_8086_LES_mem16, Valor: 0xC4
Identificador:                                       opcodes_8086_LDS_mem16, Valor: 0xC5
Identificador:                                opcodes_8086_MOV_mem8_inmmed8, Valor: 0xC6
Identificador:                              opcodes_8086_MOV_mem16_inmmed16, Valor: 0xC7
Identificador:     undocumented_opcodes_8086_RET_NEAR_inmmed16_intersegment, Valor: 0xC8
Identificador:                   undocumented_opcodes_8086_RET_intersegment, Valor: 0xC9
Identificador:                  opcodes_8086_RET_NEAR_inmmed16_intersegment, Valor: 0xCA
Identificador:                                opcodes_8086_RET_intersegment, Valor: 0xCB
Identificador:                                           opcodes_8086_INT_3, Valor: 0xCC
Identificador:                                     opcodes_8086_INT_inmmed8, Valor: 0xCD
Identificador:                                            opcodes_8086_INTO, Valor: 0xCE
Identificador:                                            opcodes_8086_IRET, Valor: 0xCF
Identificador:                                  opcodes_8086_ROL_reg_mem8_1, Valor: 0xD0
Identificador:                                  opcodes_8086_ROR_reg_mem8_1, Valor: 0xD0
Identificador:                                  opcodes_8086_RCL_reg_mem8_1, Valor: 0xD0
Identificador:                                  opcodes_8086_RCR_reg_mem8_1, Valor: 0xD0
Identificador:                                  opcodes_8086_SAL_reg_mem8_1, Valor: 0xD0
Identificador:                                  opcodes_8086_SHL_reg_mem8_1, Valor: 0xD0
Identificador:                                  opcodes_8086_SHR_reg_mem8_1, Valor: 0xD0
Identificador:                                  opcodes_8086_SAR_reg_mem8_1, Valor: 0xD0
Identificador:                                 opcodes_8086_ROL_reg_mem16_1, Valor: 0xD1
Identificador:                                 opcodes_8086_ROR_reg_mem16_1, Valor: 0xD1
Identificador:                                 opcodes_8086_RCL_reg_mem16_1, Valor: 0xD1
Identificador:                                 opcodes_8086_RCR_reg_mem16_1, Valor: 0xD1
Identificador:                                 opcodes_8086_SAL_reg_mem16_1, Valor: 0xD1
Identificador:                                 opcodes_8086_SHL_reg_mem16_1, Valor: 0xD1
Identificador:                                 opcodes_8086_SHR_reg_mem16_1, Valor: 0xD1
Identificador:                                 opcodes_8086_SAR_reg_mem16_1, Valor: 0xD1
Identificador:                                 opcodes_8086_ROL_reg_mem8_cl, Valor: 0xD2
Identificador:                                 opcodes_8086_ROR_reg_mem8_cl, Valor: 0xD2
Identificador:                                 opcodes_8086_RCL_reg_mem8_cl, Valor: 0xD2
Identificador:                                 opcodes_8086_RCR_reg_mem8_cl, Valor: 0xD2
Identificador:                                 opcodes_8086_SAL_reg_mem8_cl, Valor: 0xD2
Identificador:                                 opcodes_8086_SHL_reg_mem8_cl, Valor: 0xD2
Identificador:                                 opcodes_8086_SHR_reg_mem8_cl, Valor: 0xD2
Identificador:                                 opcodes_8086_SAR_reg_mem8_cl, Valor: 0xD2
Identificador:                                opcodes_8086_ROL_reg_mem16_cl, Valor: 0xD3
Identificador:                                opcodes_8086_ROR_reg_mem16_cl, Valor: 0xD3
Identificador:                                opcodes_8086_RCL_reg_mem16_cl, Valor: 0xD3
Identificador:                                opcodes_8086_RCR_reg_mem16_cl, Valor: 0xD3
Identificador:                                opcodes_8086_SAL_reg_mem16_cl, Valor: 0xD3
Identificador:                                opcodes_8086_SHL_reg_mem16_cl, Valor: 0xD3
Identificador:                                opcodes_8086_SHR_reg_mem16_cl, Valor: 0xD3
Identificador:                                opcodes_8086_SAR_reg_mem16_cl, Valor: 0xD3
Identificador:                                             opcodes_8086_AAM, Valor: 0xD4
Identificador:                                             opcodes_8086_AAD, Valor: 0xD5
Identificador:                                            opcodes_8086_SALC, Valor: 0xD6
Identificador:                                            opcodes_8086_XLAT, Valor: 0xD7
Identificador:                                             opcodes_8086_ESC, Valor: 0xD8
Identificador:                                  opcodes_8086_LOOPNE_inmmed8, Valor: 0xE0
Identificador:                                  opcodes_8086_LOOPNZ_inmmed8, Valor: 0xE0
Identificador:                                   opcodes_8086_LOOPE_inmmed8, Valor: 0xE1
Identificador:                                   opcodes_8086_LOOPZ_inmmed8, Valor: 0xE1
Identificador:                                    opcodes_8086_LOOP_inmmed8, Valor: 0xE2
Identificador:                                    opcodes_8086_JCXZ_inmmed8, Valor: 0xE3
Identificador:                                   opcodes_8086_IN_al_inmmed8, Valor: 0xE4
Identificador:                                   opcodes_8086_IN_ax_inmmed8, Valor: 0xE5
Identificador:                                  opcodes_8086_OUT_al_inmmed8, Valor: 0xE6
Identificador:                                  opcodes_8086_OUT_ax_inmmed8, Valor: 0xE7
Identificador:                                       opcodes_8086_CALL_NEAR, Valor: 0xE8
Identificador:                                        opcodes_8086_JMP_NEAR, Valor: 0xE9
Identificador:                                         opcodes_8086_JMP_FAR, Valor: 0xEA
Identificador:                                     opcodes_8086_JMP_inmmed8, Valor: 0xEB
Identificador:                                       opcodes_8086_JMP_SHORT, Valor: 0xEB
Identificador:                                        opcodes_8086_IN_al_dx, Valor: 0xEC
Identificador:                                        opcodes_8086_IN_ax_dx, Valor: 0xED
Identificador:                                       opcodes_8086_OUT_al_dx, Valor: 0xEE
Identificador:                                       opcodes_8086_OUT_ax_dx, Valor: 0xEF
Identificador:                                          opcodes_8086_REPENE, Valor: 0xF2
Identificador:                                          opcodes_8086_REPENZ, Valor: 0xF2
Identificador:                                             opcodes_8086_REP, Valor: 0xF3
Identificador:                                            opcodes_8086_REPE, Valor: 0xF3
Identificador:                                            opcodes_8086_REPZ, Valor: 0xF3
Identificador:                                             opcodes_8086_HLT, Valor: 0xF4
Identificador:                                             opcodes_8086_CMC, Valor: 0xF5
Identificador:                           opcodes_8086_TEST_reg_mem8_inmmed8, Valor: 0xF6
Identificador:                                    opcodes_8086_NOT_reg_mem8, Valor: 0xF6
Identificador:                                    opcodes_8086_NEG_reg_mem8, Valor: 0xF6
Identificador:                                    opcodes_8086_MUL_reg_mem8, Valor: 0xF6
Identificador:                                   opcodes_8086_IMUL_reg_mem8, Valor: 0xF6
Identificador:                                    opcodes_8086_DIV_reg_mem8, Valor: 0xF6
Identificador:                                   opcodes_8086_IDIV_reg_mem8, Valor: 0xF6
Identificador:                         opcodes_8086_TEST_reg_mem16_inmmed16, Valor: 0xF7
Identificador:                                   opcodes_8086_NOT_reg_mem16, Valor: 0xF7
Identificador:                                   opcodes_8086_NEG_reg_mem16, Valor: 0xF7
Identificador:                                   opcodes_8086_MUL_reg_mem16, Valor: 0xF7
Identificador:                                  opcodes_8086_IMUL_reg_mem16, Valor: 0xF7
Identificador:                                   opcodes_8086_DIV_reg_mem16, Valor: 0xF7
Identificador:                                  opcodes_8086_IDIV_reg_mem16, Valor: 0xF7
Identificador:                                             opcodes_8086_CLC, Valor: 0xF8
Identificador:                                             opcodes_8086_STC, Valor: 0xF9
Identificador:                                             opcodes_8086_CLI, Valor: 0xFA
Identificador:                                             opcodes_8086_STI, Valor: 0xFB
Identificador:                                             opcodes_8086_CLD, Valor: 0xFC
Identificador:                                             opcodes_8086_STD, Valor: 0xFD
Identificador:                                    opcodes_8086_INC_reg_mem8, Valor: 0xFE
Identificador:                                    opcodes_8086_DEC_reg_mem8, Valor: 0xFE
Identificador:                                       opcodes_8086_INC_mem16, Valor: 0xFF
Identificador:                                       opcodes_8086_DEC_mem16, Valor: 0xFF
Identificador:                                   opcodes_8086_CALL_intraseg, Valor: 0xFF
Identificador:                               opcodes_8086_CALL_intersegment, Valor: 0xFF
Identificador:                                    opcodes_8086_JMP_intraseg, Valor: 0xFF
Identificador:                                opcodes_8086_JMP_intersegment, Valor: 0xFF
Identificador:                                      opcodes_8086_PUSH_mem16, Valor: 0xFF
*/
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

    // PUSH SS
    OPCODES_8086(PUSH_ss),

    // POP SS
    OPCODES_8086(POP_ss),

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
    opcodes_8086_DAA = 0x27,

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
    opcodes_8086_DAS = 0x2f,

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
    opcodes_8086_AAA = 0x37,

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
    opcodes_8086_AAS = 0x3F,

    // INC AX/BX/CX/DX/SI/DI/BP/SP
    OPCODES_8086(INC_ax),
    OPCODES_8086(INC_cx),
    OPCODES_8086(INC_dx),
    OPCODES_8086(INC_bx),
    OPCODES_8086(INC_sp),
    OPCODES_8086(INC_bp),
    OPCODES_8086(INC_si),
    OPCODES_8086(INC_di),

    // DEC AX/BX/CX/DX/SI/DI/BP/SP
    OPCODES_8086(DEC_ax),
    OPCODES_8086(DEC_cx),
    OPCODES_8086(DEC_dx),
    OPCODES_8086(DEC_bx),
    OPCODES_8086(DEC_sp),
    OPCODES_8086(DEC_bp),
    OPCODES_8086(DEC_si),
    OPCODES_8086(DEC_di),
    
    // PUSH AX/BX/CX/DX/SI/DI/BP/SP
    OPCODES_8086(PUSH_ax),
    OPCODES_8086(PUSH_cx),
    OPCODES_8086(PUSH_dx),
    OPCODES_8086(PUSH_bx),
    OPCODES_8086(PUSH_sp),
    OPCODES_8086(PUSH_bp),
    OPCODES_8086(PUSH_si),
    OPCODES_8086(PUSH_di),

    // POP AX/BX/CX/DX/SI/DI/BP/SP
    OPCODES_8086(POP_ax),
    OPCODES_8086(POP_cx),
    OPCODES_8086(POP_dx),
    OPCODES_8086(POP_bx),
    OPCODES_8086(POP_sp),
    OPCODES_8086(POP_bp),
    OPCODES_8086(POP_si),
    OPCODES_8086(POP_di),

    // opcode(60 -> 0b01100000) -> 0x60 (equivalent: 0x70) = JO
    UNDOCUMENTED(JO),

    // opcode(61 -> 0b01100001) -> 0x61 (equivalent: 0x71) = JNO
    UNDOCUMENTED(JNO),

    // opcode(62 -> 0b01100010) -> 0x62 (equivalent: 0x72) = JC
    UNDOCUMENTED(JC),

    // opcode(63 -> 0b01100011) -> 0x63 (equivalent: 0x73) = JAE
    UNDOCUMENTED(JAE),

    // opcode(64 -> 0b01100100) -> 0x64 (equivalent: 0x74) = JE
    UNDOCUMENTED(JE),

    // opcode(65 -> 0b01100101) -> 0x65 (equivalent: 0x75) = JNZ
    UNDOCUMENTED(JNZ),

    // opcode(66 -> 0b01100110) -> 0x66 (equivalent: 0x76) = JBE
    UNDOCUMENTED(JBE),

    // opcode(67 -> 0b01100111) -> 0x67 (equivalent: 0x77) = JA
    UNDOCUMENTED(JA),

    // opcode(68 -> 0b01101000) -> 0x68 (equivalent: 0x78) = JS
    UNDOCUMENTED(JS),

    // opcode(69 -> 0b01101001) -> 0x69 (equivalent: 0x79) = JNS
    UNDOCUMENTED(JNS),

    // opcode(6a -> 0b01101010) -> 0x6A (equivalent: 0x7A) = JPE
    UNDOCUMENTED(JPE),

    // opcode(6b -> 0b01101011) -> 0x6B (equivalent: 0x7B) = JNP
    UNDOCUMENTED(JNP),

    // opcode(6c -> 0b01101100) -> 0x6C (equivalent: 0x7C) = JL
    UNDOCUMENTED(JL),

    // opcode(6d -> 0b01101101) -> 0x6D (equivalent: 0x7D) = JGE
    UNDOCUMENTED(JGE),

    // opcode(6e -> 0b01101110) -> 0x6E (equivalent: 0x7E) = JLE
    UNDOCUMENTED(JLE),

    // opcode(6f -> 0b01101111) -> 0x6F (equivalent: 0x7F) = JG
    UNDOCUMENTED(JG),
    
    // opcode(70 -> 0b01110000) -> 0x70 (equivalent: 0x60) = JO
    OPCODES_8086(JO),

    // opcode(71 -> 0b01110001) -> 0x71 (equivalent: 0x61) = JNO
    OPCODES_8086(JNO),

    // opcode(72 -> 0b01110010) -> 0x72 (equivalent: 0x62) = JC
    OPCODES_8086(JC),

    // opcode(73 -> 0b01110011) -> 0x73 (equivalent: 0x63) = JAE
    OPCODES_8086(JAE),

    // opcode(74 -> 0b01110100) -> 0x74 (equivalent: 0x64) = JE
    OPCODES_8086(JE),

    // opcode(75 -> 0b01110101) -> 0x75 (equivalent: 0x65) = JNZ
    OPCODES_8086(JNZ),

    // opcode(76 -> 0b01110110) -> 0x76 (equivalent: 0x66) = JBE
    OPCODES_8086(JBE),

    // opcode(77 -> 0b01110111) -> 0x77 (equivalent: 0x67) = JA
    OPCODES_8086(JA),

    // opcode(78 -> 0b01111000) -> 0x78 (equivalent: 0x68) = JS
    OPCODES_8086(JS),

    // opcode(79 -> 0b01111001) -> 0x79 (equivalent: 0x69) = JNS
    OPCODES_8086(JNS),

    // opcode(7a -> 0b01111010) -> 0x7A (equivalent: 0x6A) = JPE
    OPCODES_8086(JPE),

    // opcode(7b -> 0b01111011) -> 0x7B (equivalent: 0x6B) = JNP
    OPCODES_8086(JNP),

    // opcode(7c -> 0b01111100) -> 0x7C (equivalent: 0x6C) = JL
    OPCODES_8086(JL),

    // opcode(7d -> 0b01111101) -> 0x7D (equivalent: 0x6D) = JGE
    OPCODES_8086(JGE),

    // opcode(7e -> 0b01111110) -> 0x7E (equivalent: 0x6E) = JLE
    OPCODES_8086(JLE),

    // opcode(7f -> 0b01111111) -> 0x7F (equivalent: 0x6F) = JG
    OPCODES_8086(JG),

    // opcode 0x80

    // ADD reg8/mem8, inmmed8
    OPCODES_8086(ADD_inmmed8),
    
    // OR reg8/mem8, inmmed8
    opcodes_8086_OR_inmmed8 = OPCODES_8086(ADD_inmmed8),

    // ADC reg8/mem8, inmmed8
    opcodes_8086_ADC_inmmed8 = OPCODES_8086(ADD_inmmed8),

    // SBB reg8/mem8, inmmed8
    opcodes_8086_SBB_inmmed8 = OPCODES_8086(ADD_inmmed8),

    // AND reg8/mem8, inmmed8
    opcodes_8086_AND_inmmed8 = OPCODES_8086(ADD_inmmed8),

    // SUB reg8/mem8, inmmed8
    opcodes_8086_SUB_inmmed8 = OPCODES_8086(ADD_inmmed8),

    // XOR reg8/mem8, inmmed8
    opcodes_8086_XOR_inmmed8 = OPCODES_8086(ADD_inmmed8),

    // CMP reg8/mem8, inmmed8
    opcodes_8086_CMP_inmmed8 = OPCODES_8086(ADD_inmmed8),

    // opcode 0x81

    // ADD reg16/mem16, inmmed16
    OPCODES_8086(ADD_inmmed16),
    
    // OR reg16/mem16, inmmed16
    opcodes_8086_OR_inmmed16 = OPCODES_8086(ADD_inmmed16),

    // ADC reg16/mem16, inmmed16
    opcodes_8086_ADC_inmmed16 = OPCODES_8086(ADD_inmmed16),

    // SBB reg16/mem16, inmmed16
    opcodes_8086_SBB_inmmed16 = OPCODES_8086(ADD_inmmed16),

    // AND reg16/mem16, inmmed16
    opcodes_8086_AND_inmmed16 = OPCODES_8086(ADD_inmmed16),

    // SUB reg16/mem16, inmmed16
    opcodes_8086_SUB_inmmed16 = OPCODES_8086(ADD_inmmed16),

    // XOR reg16/mem16, inmmed16
    opcodes_8086_XOR_inmmed16 = OPCODES_8086(ADD_inmmed16),

    // CMP reg16/mem16, inmmed16
    opcodes_8086_CMP_inmmed16 = OPCODES_8086(ADD_inmmed16),


    // opcode 0x82

    // ADC reg8/mem8, inmmed8
    OPCODES_8086(ADD_inmmed8_2),
    
    // OR reg8/mem8, inmmed8
    opcodes_8086_OR_inmmed8_2 = OPCODES_8086(ADD_inmmed8_2),

    // ADC reg8/mem8, inmmed8
    opcodes_8086_ADC_inmmed8_2 = OPCODES_8086(ADD_inmmed8_2),

    // SBB reg8/mem8, inmmed8
    opcodes_8086_SBB_inmmed8_2 = OPCODES_8086(ADD_inmmed8_2),

    // AND reg8/mem8, inmmed8
    opcodes_8086_AND_inmmed8_2 = OPCODES_8086(ADD_inmmed8_2),

    // SUB reg8/mem8, inmmed8
    opcodes_8086_SUB_inmmed8_2 = OPCODES_8086(ADD_inmmed8_2),

    // XOR reg8/mem8, inmmed8
    opcodes_8086_XOR_inmmed8_2 = OPCODES_8086(ADD_inmmed8_2),

    // CMP reg8/mem8, inmmed8
    opcodes_8086_CMP_inmmed8_2 = OPCODES_8086(ADD_inmmed8_2),


    // opcode 0x83

    // ADD reg16/mem16, inmmed8
    OPCODES_8086(ADD_inmmed8_reg_mem16),
    
    // OR reg16/mem16, inmmed8
    opcodes_8086_OR_inmmed8_reg_mem16 = OPCODES_8086(ADD_inmmed8_reg_mem16),

    // ADC reg16/mem16, inmmed8
    opcodes_8086_ADC_inmmed8_reg_mem16 = OPCODES_8086(ADD_inmmed8_reg_mem16),

    // SBB reg16/mem16, inmmed8
    opcodes_8086_SBB_inmmed8_reg_mem16 = OPCODES_8086(ADD_inmmed8_reg_mem16),

    // AND reg16/mem16, inmmed8
    opcodes_8086_AND_inmmed8_reg_mem16 = OPCODES_8086(ADD_inmmed8_reg_mem16),

    // SUB reg16/mem16, inmmed8
    opcodes_8086_SUB_inmmed8_reg_mem16 = OPCODES_8086(ADD_inmmed8_reg_mem16),

    // XOR reg16/mem16, inmmed8
    opcodes_8086_XOR_inmmed8_reg_mem16 = OPCODES_8086(ADD_inmmed8_reg_mem16),

    // CMP reg16/mem16, inmmed8
    opcodes_8086_CMP_inmmed8_reg_mem16 = OPCODES_8086(ADD_inmmed8_reg_mem16),

    // opcode 0x84

    // TEST reg8/mem8, reg8
    OPCODES_8086(TEST_reg8),

    // TEST reg16/mem16, reg16
    OPCODES_8086(TEST_reg16),

    // XCHG reg8/mem8, reg8
    OPCODES_8086(XCHG_reg8),

    // XCHG reg16/mem16, reg16
    OPCODES_8086(XCHG_reg16),

    // MOV reg8/mem8, reg8
    OPCODES_8086(MOV_reg8),

    // MOV reg16/mem16, reg16
    OPCODES_8086(MOV_reg16),

    // MOV reg8, mem/8reg8
    opcodes_8086_MOV_mem8 = OPCODES_8086(MOV_reg8) | REVERSE_BIT_D,

    // MOV reg16, reg16/mem16.
    opcodes_8086_MOV_mem16 = OPCODES_8086(MOV_reg16) | REVERSE_BIT_D,

    // MOV reg16/mem16, SEGREG. not used opcode 0x8c mod 1---
    OPCODES_8086(MOV_reg_mem16_segreg),

    // LEA reg16, mem16
    OPCODES_8086(LEA_mem16),

    // MOV SEGREG, mem16/reg16.  not used opcode 0x8e mod 1---
    OPCODES_8086(MOV_segreg_reg_mem16),

    // POP reg16/mem16.  solo opcode 0x8f mod 000 es valido
    OPCODES_8086(POP_reg_mem16),

    // opcode 0x90

    // XCHG AX, AX == NOP
    OPCODES_8086(XCHG_ax_ax),

    // XCHG AX, CX
    OPCODES_8086(XCHG_ax_cx),

    // XCHG AX, DX
    OPCODES_8086(XCHG_ax_dx),

    // XCHG AX, BX
    OPCODES_8086(XCHG_ax_bx),

    // XCHG AX, SP
    OPCODES_8086(XCHG_ax_sp),

    // XCHG AX, BP
    OPCODES_8086(XCHG_ax_bp),

    // XCHG AX, SI
    OPCODES_8086(XCHG_ax_si),

    // XCHG AX, DI
    OPCODES_8086(XCHG_ax_di),

    // CBW
    OPCODES_8086(CBW),

    // CWD
    OPCODES_8086(CWD),

    // CALL FAR
    OPCODES_8086(CALL_FAR),

    // WAIT
    OPCODES_8086(WAIT),

    // PUSHF
    OPCODES_8086(PUSHF),

    // POPF
    OPCODES_8086(POPF),

    // SAHF
    OPCODES_8086(SAHF),

    // LAHF
    OPCODES_8086(LAHF),

    // MOV AL, mem8
    OPCODES_8086(MOV_al_mem8),

    // MOV AX, mem16
    OPCODES_8086(MOV_ax_mem16),

    // MOV mem8, AL
    OPCODES_8086(MOV_mem8_al),

    // MOV mem16, AX
    OPCODES_8086(MOV_mem16_ax),

    // movsb byte es:[di], byte [si]
    OPCODES_8086(MOVS_ptr8),

    // movsw word es:[di], word [si]
    OPCODES_8086(MOVS_ptr16),

    // cmpsb byte [si], byte es:[di]
    OPCODES_8086(CMPS_ptr8),

    // cmpsw word [si], word es:[di]
    OPCODES_8086(CMPS_ptr16),

    // TEST AL, inmmed8
    OPCODES_8086(TEST_al_inmmed8),

    // TEST AX, inmmed16
    OPCODES_8086(TEST_ax_inmmed16),

    // stosb byte es:[di], al
    OPCODES_8086(STOS_ptr8),

    // stosw word es:[di], ax
    OPCODES_8086(STOS_ptr16),

    // lodsb al, byte ptr [si]
    OPCODES_8086(LODS_ptr8),

    // lodsw ax, word ptr [si]
    OPCODES_8086(LODS_ptr16),

    // scasb al, byte ptr es:[di]
    OPCODES_8086(SCAS_ptr8),

    // scasw ax, word ptr es:[di]
    OPCODES_8086(SCAS_ptr16),

    // MOV AL/BL/CL/DL/AH/BH/CH/DH, INMMED8
    OPCODES_8086(MOV_al_inmmed8),
    OPCODES_8086(MOV_cl_inmmed8),
    OPCODES_8086(MOV_dl_inmmed8),
    OPCODES_8086(MOV_bl_inmmed8),
    OPCODES_8086(MOV_ah_inmmed8),
    OPCODES_8086(MOV_ch_inmmed8),
    OPCODES_8086(MOV_dh_inmmed8),
    OPCODES_8086(MOV_bh_inmmed8),

    // MOV AX/BX/CX/DX/SI/DI/BP/SP, INMMED16
    OPCODES_8086(MOV_ax_inmmed16),
    OPCODES_8086(MOV_cx_inmmed16),
    OPCODES_8086(MOV_dx_inmmed16),
    OPCODES_8086(MOV_bx_inmmed16),
    OPCODES_8086(MOV_sp_inmmed16),
    OPCODES_8086(MOV_bp_inmmed16),
    OPCODES_8086(MOV_si_inmmed16),
    OPCODES_8086(MOV_di_inmmed16),

    // ret near inmed16 (intra seg), (no documentada) es la misma que 0xC2
    UNDOCUMENTED(RET_NEAR_inmmed16_intraseg),

    // RET no documentada (intra seg)
    UNDOCUMENTED(RET_intraseg),

    // ret near inmed16, (documentada) (intra seg) es la misma que 0xC0
    OPCODES_8086(RET_NEAR_inmmed16_intraseg),

    // RET documentada (intra seg)
    OPCODES_8086(RET_intraseg),

    // LES reg16, mem16
    OPCODES_8086(LES_mem16),

    // LDS reg16, mem16
    OPCODES_8086(LDS_mem16),

    // MOV mem8, inmmed8.  solo opcode 0xc6 mod 000 es valido
    OPCODES_8086(MOV_mem8_inmmed8),

    // MOV mem16, inmmed16.  solo opcode 0xc7 mod 000 es valido
    OPCODES_8086(MOV_mem16_inmmed16),

    // ret near inmed16 (inter-segment), (no documentada) es la misma que 0xCA
    UNDOCUMENTED(RET_NEAR_inmmed16_intersegment),

    // RET no documentada (inter-segment)
    UNDOCUMENTED(RET_intersegment),

    // ret near inmed16, (documentada) (inter-segment) es la misma que 0xC8
    OPCODES_8086(RET_NEAR_inmmed16_intersegment),

    // RET documentada (inter-segment)
    OPCODES_8086(RET_intersegment),

    // INT 3
    OPCODES_8086(INT_3),

    // INT inmmed8
    OPCODES_8086(INT_inmmed8),

    // INTO
    OPCODES_8086(INTO),

    // IRET
    OPCODES_8086(IRET),

    // opcode 0xD0

    // ROL reg8/mem8, 1
    OPCODES_8086(ROL_reg_mem8_1),

    // ROR reg8/mem8, 1
    opcodes_8086_ROR_reg_mem8_1 = opcodes_8086_ROL_reg_mem8_1,

    // RCL reg8/mem8, 1
    opcodes_8086_RCL_reg_mem8_1 = opcodes_8086_ROL_reg_mem8_1,

    // RCR reg8/mem8, 1
    opcodes_8086_RCR_reg_mem8_1 = opcodes_8086_ROL_reg_mem8_1,

    // SAL/SHL reg8/mem8, 1
    opcodes_8086_SAL_reg_mem8_1 = opcodes_8086_ROL_reg_mem8_1,
    opcodes_8086_SHL_reg_mem8_1 = opcodes_8086_SAL_reg_mem8_1,

    // SHR reg8/mem8, 1
    opcodes_8086_SHR_reg_mem8_1 = opcodes_8086_ROL_reg_mem8_1,

    // SAR reg8/mem8, 1
    opcodes_8086_SAR_reg_mem8_1 = opcodes_8086_ROL_reg_mem8_1,

    // opcode 0xD1

    // ROL reg16/mem16, 1
    OPCODES_8086(ROL_reg_mem16_1),

    // ROR reg16/mem16, 1
    opcodes_8086_ROR_reg_mem16_1 = opcodes_8086_ROL_reg_mem16_1,

    // RCL reg16/mem16, 1
    opcodes_8086_RCL_reg_mem16_1 = opcodes_8086_ROL_reg_mem16_1,

    // RCR reg16/mem16, 1
    opcodes_8086_RCR_reg_mem16_1 = opcodes_8086_ROL_reg_mem16_1,

    // SAL/SHL reg16/mem16, 1
    opcodes_8086_SAL_reg_mem16_1  = opcodes_8086_ROL_reg_mem16_1,
    opcodes_8086_SHL_reg_mem16_1  = opcodes_8086_SAL_reg_mem16_1,

    // SHR reg16/mem16, 1
    opcodes_8086_SHR_reg_mem16_1 = opcodes_8086_ROL_reg_mem16_1,

    // SAR reg16/mem16, 1
    opcodes_8086_SAR_reg_mem16_1 = opcodes_8086_ROL_reg_mem16_1,


    // opcode 0xD2

    // ROL reg8/mem8, cl
    OPCODES_8086(ROL_reg_mem8_cl),

    // ROR reg8/mem8, cl
    opcodes_8086_ROR_reg_mem8_cl = opcodes_8086_ROL_reg_mem8_cl,

    // RCL reg8/mem8, cl
    opcodes_8086_RCL_reg_mem8_cl = opcodes_8086_ROL_reg_mem8_cl,

    // RCR reg8/mem8, cl
    opcodes_8086_RCR_reg_mem8_cl = opcodes_8086_ROL_reg_mem8_cl,

    // SAL/SHL reg8/mem8, cl
    opcodes_8086_SAL_reg_mem8_cl  = opcodes_8086_ROL_reg_mem8_cl,
    opcodes_8086_SHL_reg_mem8_cl = opcodes_8086_SAL_reg_mem8_cl,

    // SHR reg8/mem8, cl
    opcodes_8086_SHR_reg_mem8_cl = opcodes_8086_ROL_reg_mem8_cl,

    // SAR reg8/mem8, cl
    opcodes_8086_SAR_reg_mem8_cl = opcodes_8086_ROL_reg_mem8_cl,


    // opcode 0xD3

    // ROL reg16/mem16, CL
    OPCODES_8086(ROL_reg_mem16_cl),

    // ROR reg16/mem16, CL
    opcodes_8086_ROR_reg_mem16_cl = opcodes_8086_ROL_reg_mem16_cl,

    // RCL reg16/mem16, CL
    opcodes_8086_RCL_reg_mem16_cl = opcodes_8086_ROL_reg_mem16_cl,

    // RCR reg16/mem16, CL
    opcodes_8086_RCR_reg_mem16_cl = opcodes_8086_ROL_reg_mem16_cl,

    // SAL/SHL reg16/mem16, CL
    opcodes_8086_SAL_reg_mem16_cl = opcodes_8086_ROL_reg_mem16_cl,
    opcodes_8086_SHL_reg_mem16_cl = opcodes_8086_SAL_reg_mem16_cl,

    // SHR reg16/mem16, CL
    opcodes_8086_SHR_reg_mem16_cl = opcodes_8086_ROL_reg_mem16_cl,

    // SAR reg16/mem16, CL
    opcodes_8086_SAR_reg_mem16_cl = opcodes_8086_ROL_reg_mem16_cl,


    // AAM
    OPCODES_8086(AAM),

    // AAD
    OPCODES_8086(AAD),

    // SALC
    OPCODES_8086(SALC),

    // XLAT
    OPCODES_8086(XLAT),

    // ESCAPE A LAS ISNTRUCCIONES DEL X87
    OPCODES_8086(ESC),


    // opcode 0xE0

    // LOOPNE/LOOPNZ inmmed8
    opcodes_8086_LOOPNE_inmmed8 = 0xE0,
    opcodes_8086_LOOPNZ_inmmed8 = opcodes_8086_LOOPNE_inmmed8,

    // LOOPE/LOOPZ inmmed8
    OPCODES_8086(LOOPE_inmmed8),
    opcodes_8086_LOOPZ_inmmed8 = opcodes_8086_LOOPE_inmmed8,

    // LOOP inmmed8
    OPCODES_8086(LOOP_inmmed8),

    // JCXZ inmmed8
    OPCODES_8086(JCXZ_inmmed8),

    // IN AL, inmmed8
    OPCODES_8086(IN_al_inmmed8),

    // IN AX, inmmed8
    OPCODES_8086(IN_ax_inmmed8),

    // OUT AL, inmmed8
    OPCODES_8086(OUT_al_inmmed8),

    // OUT AX, inmmed8
    OPCODES_8086(OUT_ax_inmmed8),

    // CALL NEAR <label>
    OPCODES_8086(CALL_NEAR),

    // JMP NEAR <label>
    OPCODES_8086(JMP_NEAR),

    // JMP FAR <label>
    OPCODES_8086(JMP_FAR),

    // JMP SHORT <label>
    OPCODES_8086(JMP_inmmed8),
    opcodes_8086_JMP_SHORT = opcodes_8086_JMP_inmmed8,

    // IN AL, DX
    OPCODES_8086(IN_al_dx),

    // IN AX, DX
    OPCODES_8086(IN_ax_dx),

    // OUT AL, DX
    OPCODES_8086(OUT_al_dx),

    // OUT AX, DX
    OPCODES_8086(OUT_ax_dx),

    // prefijo LOCK

    // REPENE/REPENZ
    opcodes_8086_REPENE = 0XF2,
    opcodes_8086_REPENZ = opcodes_8086_REPENE,

    // REP/REPE/REPZ
    OPCODES_8086(REP),
    opcodes_8086_REPE = opcodes_8086_REP,
    opcodes_8086_REPZ = opcodes_8086_REP,

    // HLT
    OPCODES_8086(HLT),

    // CMC
    OPCODES_8086(CMC),


    // opcode 0xF6
    
    // TEST/NOT/NEG/MUL/IMUL/DIV/IDIV/TEST reg8/mem8, inmmed8
    OPCODES_8086(TEST_reg_mem8_inmmed8),
    opcodes_8086_NOT_reg_mem8  = opcodes_8086_TEST_reg_mem8_inmmed8,
    opcodes_8086_NEG_reg_mem8  = opcodes_8086_TEST_reg_mem8_inmmed8,
    opcodes_8086_MUL_reg_mem8  = opcodes_8086_TEST_reg_mem8_inmmed8,
    opcodes_8086_IMUL_reg_mem8 = opcodes_8086_TEST_reg_mem8_inmmed8,
    opcodes_8086_DIV_reg_mem8  = opcodes_8086_TEST_reg_mem8_inmmed8,
    opcodes_8086_IDIV_reg_mem8 = opcodes_8086_TEST_reg_mem8_inmmed8,


    // opcode 0xF7
    
    // TEST/NOT/NEG/MUL/IMUL/DIV/IDIV/TEST reg16/mem16, inmmed16
    OPCODES_8086(TEST_reg_mem16_inmmed16),
    opcodes_8086_NOT_reg_mem16  = opcodes_8086_TEST_reg_mem16_inmmed16,
    opcodes_8086_NEG_reg_mem16  = opcodes_8086_TEST_reg_mem16_inmmed16,
    opcodes_8086_MUL_reg_mem16  = opcodes_8086_TEST_reg_mem16_inmmed16,
    opcodes_8086_IMUL_reg_mem16 = opcodes_8086_TEST_reg_mem16_inmmed16,
    opcodes_8086_DIV_reg_mem16  = opcodes_8086_TEST_reg_mem16_inmmed16,
    opcodes_8086_IDIV_reg_mem16 = opcodes_8086_TEST_reg_mem16_inmmed16,


    // opcode 0xf8

    // CLC
    OPCODES_8086(CLC),

    // STC
    OPCODES_8086(STC),

    // CLI
    OPCODES_8086(CLI),

    // STI
    OPCODES_8086(STI),

    // CLD
    OPCODES_8086(CLD),

    // STD
    OPCODES_8086(STD),

    // INC/DEC reg8/mem8. solo 0xfe con mod 000 y 001 se usa.
    OPCODES_8086(INC_reg_mem8),
    opcodes_8086_DEC_reg_mem8  = opcodes_8086_INC_reg_mem8,

    /* INC/DEC/CALL(intraseg)/CALL(intersegment)/
     * JMP(intraseg)/JMP(intersegment)/PUSH mem16.
     *
     * 0xff con mod 111 no se usa.
     */
    opcodes_8086_INC_mem16,
    opcodes_8086_DEC_mem16          = opcodes_8086_INC_mem16,
    opcodes_8086_CALL_intraseg      = opcodes_8086_INC_mem16,
    opcodes_8086_CALL_intersegment  = opcodes_8086_INC_mem16,
    opcodes_8086_JMP_intraseg       = opcodes_8086_INC_mem16,
    opcodes_8086_JMP_intersegment   = opcodes_8086_INC_mem16,
    opcodes_8086_PUSH_mem16         = opcodes_8086_INC_mem16,

} opcodes_8086;

typedef struct opcode_8086_val {
    const char* string;
    opcodes_8086 val;
} opcode_8086_val;
opcode_8086_val opcodes_8086_names[] = {
    {TOSTRING(OPCODES_8086(ADD_mem8)), OPCODES_8086(ADD_mem8), },
    {TOSTRING(OPCODES_8086(ADD_mem16)), OPCODES_8086(ADD_mem16), },
    {TOSTRING(OPCODES_8086(ADD_mem8_inverse)), OPCODES_8086(ADD_mem8_inverse), },
    {TOSTRING(OPCODES_8086(ADD_mem16_inverse)), OPCODES_8086(ADD_mem16_inverse), },
    {TOSTRING(OPCODES_8086(ADD_al)), OPCODES_8086(ADD_al), },
    {TOSTRING(OPCODES_8086(ADD_ax)), OPCODES_8086(ADD_ax), },
    {TOSTRING(OPCODES_8086(PUSH_es)), OPCODES_8086(PUSH_es), },
    {TOSTRING(OPCODES_8086(POP_es)), OPCODES_8086(POP_es), },
    {TOSTRING(OPCODES_8086(OR_mem8)), OPCODES_8086(OR_mem8), },
    {TOSTRING(OPCODES_8086(OR_mem16)), OPCODES_8086(OR_mem16), },
    {TOSTRING(OPCODES_8086(OR_mem8_inverse)), OPCODES_8086(OR_mem8_inverse), },
    {TOSTRING(OPCODES_8086(OR_mem16_inverse)), OPCODES_8086(OR_mem16_inverse), },
    {TOSTRING(OPCODES_8086(OR_al)), OPCODES_8086(OR_al), },
    {TOSTRING(OPCODES_8086(OR_ax)), OPCODES_8086(OR_ax), },
    {TOSTRING(OPCODES_8086(PUSH_cs)), OPCODES_8086(PUSH_cs), },
    {TOSTRING(OPCODES_8086(POP_cs)), OPCODES_8086(POP_cs), },
    {TOSTRING(OPCODES_8086(ADC_mem8)), OPCODES_8086(ADC_mem8), },
    {TOSTRING(OPCODES_8086(ADC_mem16)), OPCODES_8086(ADC_mem16), },
    {TOSTRING(OPCODES_8086(ADC_mem8_inverse)), OPCODES_8086(ADC_mem8_inverse), },
    {TOSTRING(OPCODES_8086(ADC_mem16_inverse)), OPCODES_8086(ADC_mem16_inverse), },
    {TOSTRING(OPCODES_8086(ADC_al)), OPCODES_8086(ADC_al), },
    {TOSTRING(OPCODES_8086(ADC_ax)), OPCODES_8086(ADC_ax), },
    {TOSTRING(OPCODES_8086(PUSH_ss)), OPCODES_8086(PUSH_ss), },
    {TOSTRING(OPCODES_8086(POP_ss)), OPCODES_8086(POP_ss), },
    {TOSTRING(OPCODES_8086(SBB_mem8)), OPCODES_8086(SBB_mem8), },
    {TOSTRING(OPCODES_8086(SBB_mem16)), OPCODES_8086(SBB_mem16), },
    {TOSTRING(OPCODES_8086(SBB_mem8_inverse)), OPCODES_8086(SBB_mem8_inverse), },
    {TOSTRING(OPCODES_8086(SBB_mem16_inverse)), OPCODES_8086(SBB_mem16_inverse), },
    {TOSTRING(OPCODES_8086(SBB_al)), OPCODES_8086(SBB_al), },
    {TOSTRING(OPCODES_8086(SBB_ax)), OPCODES_8086(SBB_ax), },
    {TOSTRING(OPCODES_8086(PUSH_ds)), OPCODES_8086(PUSH_ds), },
    {TOSTRING(OPCODES_8086(POP_ds)), OPCODES_8086(POP_ds), },
    {TOSTRING(OPCODES_8086(AND_mem8)), OPCODES_8086(AND_mem8), },
    {TOSTRING(OPCODES_8086(AND_mem16)), OPCODES_8086(AND_mem16), },
    {TOSTRING(OPCODES_8086(AND_mem8_inverse)), OPCODES_8086(AND_mem8_inverse), },
    {TOSTRING(OPCODES_8086(AND_mem16_inverse)), OPCODES_8086(AND_mem16_inverse), },
    {TOSTRING(OPCODES_8086(AND_al)), OPCODES_8086(AND_al), },
    {TOSTRING(OPCODES_8086(AND_ax)), OPCODES_8086(AND_ax), },
    {TOSTRING(OPCODES_8086(DAA)), OPCODES_8086(DAA), },
    {TOSTRING(OPCODES_8086(SUB_mem8)), OPCODES_8086(SUB_mem8), },
    {TOSTRING(OPCODES_8086(SUB_mem16)), OPCODES_8086(SUB_mem16), },
    {TOSTRING(OPCODES_8086(SUB_mem8_inverse)), OPCODES_8086(SUB_mem8_inverse), },
    {TOSTRING(OPCODES_8086(SUB_mem16_inverse)), OPCODES_8086(SUB_mem16_inverse), },
    {TOSTRING(OPCODES_8086(SUB_al)), OPCODES_8086(SUB_al), },
    {TOSTRING(OPCODES_8086(SUB_ax)), OPCODES_8086(SUB_ax), },
    {TOSTRING(OPCODES_8086(DAS)), OPCODES_8086(DAS), },
    {TOSTRING(OPCODES_8086(XOR_mem8)), OPCODES_8086(XOR_mem8), },
    {TOSTRING(OPCODES_8086(XOR_mem16)), OPCODES_8086(XOR_mem16), },
    {TOSTRING(OPCODES_8086(XOR_mem8_inverse)), OPCODES_8086(XOR_mem8_inverse), },
    {TOSTRING(OPCODES_8086(XOR_mem16_inverse)), OPCODES_8086(XOR_mem16_inverse), },
    {TOSTRING(OPCODES_8086(XOR_al)), OPCODES_8086(XOR_al), },
    {TOSTRING(OPCODES_8086(XOR_ax)), OPCODES_8086(XOR_ax), },
    {TOSTRING(OPCODES_8086(AAA)), OPCODES_8086(AAA), },
    {TOSTRING(OPCODES_8086(CMP_mem8)), OPCODES_8086(CMP_mem8), },
    {TOSTRING(OPCODES_8086(CMP_mem16)), OPCODES_8086(CMP_mem16), },
    {TOSTRING(OPCODES_8086(CMP_mem8_inverse)), OPCODES_8086(CMP_mem8_inverse), },
    {TOSTRING(OPCODES_8086(CMP_mem16_inverse)), OPCODES_8086(CMP_mem16_inverse), },
    {TOSTRING(OPCODES_8086(CMP_al)), OPCODES_8086(CMP_al), },
    {TOSTRING(OPCODES_8086(CMP_ax)), OPCODES_8086(CMP_ax), },
    {TOSTRING(OPCODES_8086(AAS)), OPCODES_8086(AAS), },
    {TOSTRING(OPCODES_8086(INC_ax)), OPCODES_8086(INC_ax), },
    {TOSTRING(OPCODES_8086(INC_cx)), OPCODES_8086(INC_cx), },
    {TOSTRING(OPCODES_8086(INC_dx)), OPCODES_8086(INC_dx), },
    {TOSTRING(OPCODES_8086(INC_bx)), OPCODES_8086(INC_bx), },
    {TOSTRING(OPCODES_8086(INC_sp)), OPCODES_8086(INC_sp), },
    {TOSTRING(OPCODES_8086(INC_bp)), OPCODES_8086(INC_bp), },
    {TOSTRING(OPCODES_8086(INC_si)), OPCODES_8086(INC_si), },
    {TOSTRING(OPCODES_8086(INC_di)), OPCODES_8086(INC_di), },
    {TOSTRING(OPCODES_8086(DEC_ax)), OPCODES_8086(DEC_ax), },
    {TOSTRING(OPCODES_8086(DEC_cx)), OPCODES_8086(DEC_cx), },
    {TOSTRING(OPCODES_8086(DEC_dx)), OPCODES_8086(DEC_dx), },
    {TOSTRING(OPCODES_8086(DEC_bx)), OPCODES_8086(DEC_bx), },
    {TOSTRING(OPCODES_8086(DEC_sp)), OPCODES_8086(DEC_sp), },
    {TOSTRING(OPCODES_8086(DEC_bp)), OPCODES_8086(DEC_bp), },
    {TOSTRING(OPCODES_8086(DEC_si)), OPCODES_8086(DEC_si), },
    {TOSTRING(OPCODES_8086(DEC_di)), OPCODES_8086(DEC_di), },
    {TOSTRING(OPCODES_8086(PUSH_ax)), OPCODES_8086(PUSH_ax), },
    {TOSTRING(OPCODES_8086(PUSH_cx)), OPCODES_8086(PUSH_cx), },
    {TOSTRING(OPCODES_8086(PUSH_dx)), OPCODES_8086(PUSH_dx), },
    {TOSTRING(OPCODES_8086(PUSH_bx)), OPCODES_8086(PUSH_bx), },
    {TOSTRING(OPCODES_8086(PUSH_sp)), OPCODES_8086(PUSH_sp), },
    {TOSTRING(OPCODES_8086(PUSH_bp)), OPCODES_8086(PUSH_bp), },
    {TOSTRING(OPCODES_8086(PUSH_si)), OPCODES_8086(PUSH_si), },
    {TOSTRING(OPCODES_8086(PUSH_di)), OPCODES_8086(PUSH_di), },
    {TOSTRING(OPCODES_8086(POP_ax)), OPCODES_8086(POP_ax), },
    {TOSTRING(OPCODES_8086(POP_cx)), OPCODES_8086(POP_cx), },
    {TOSTRING(OPCODES_8086(POP_dx)), OPCODES_8086(POP_dx), },
    {TOSTRING(OPCODES_8086(POP_bx)), OPCODES_8086(POP_bx), },
    {TOSTRING(OPCODES_8086(POP_sp)), OPCODES_8086(POP_sp), },
    {TOSTRING(OPCODES_8086(POP_bp)), OPCODES_8086(POP_bp), },
    {TOSTRING(OPCODES_8086(POP_si)), OPCODES_8086(POP_si), },
    {TOSTRING(OPCODES_8086(POP_di)), OPCODES_8086(POP_di), },
    {TOSTRING(UNDOCUMENTED(JO)), UNDOCUMENTED(JO), },
    {TOSTRING(UNDOCUMENTED(JNO)), UNDOCUMENTED(JNO), },
    {TOSTRING(UNDOCUMENTED(JC)), UNDOCUMENTED(JC), },
    {TOSTRING(UNDOCUMENTED(JAE)), UNDOCUMENTED(JAE), },
    {TOSTRING(UNDOCUMENTED(JE)), UNDOCUMENTED(JE), },
    {TOSTRING(UNDOCUMENTED(JNZ)), UNDOCUMENTED(JNZ), },
    {TOSTRING(UNDOCUMENTED(JBE)), UNDOCUMENTED(JBE), },
    {TOSTRING(UNDOCUMENTED(JA)), UNDOCUMENTED(JA), },
    {TOSTRING(UNDOCUMENTED(JS)), UNDOCUMENTED(JS), },
    {TOSTRING(UNDOCUMENTED(JNS)), UNDOCUMENTED(JNS), },
    {TOSTRING(UNDOCUMENTED(JPE)), UNDOCUMENTED(JPE), },
    {TOSTRING(UNDOCUMENTED(JNP)), UNDOCUMENTED(JNP), },
    {TOSTRING(UNDOCUMENTED(JL)), UNDOCUMENTED(JL), },
    {TOSTRING(UNDOCUMENTED(JGE)), UNDOCUMENTED(JGE), },
    {TOSTRING(UNDOCUMENTED(JLE)), UNDOCUMENTED(JLE), },
    {TOSTRING(UNDOCUMENTED(JG)), UNDOCUMENTED(JG), },
    {TOSTRING(OPCODES_8086(JO)), OPCODES_8086(JO), },
    {TOSTRING(OPCODES_8086(JNO)), OPCODES_8086(JNO), },
    {TOSTRING(OPCODES_8086(JC)), OPCODES_8086(JC), },
    {TOSTRING(OPCODES_8086(JAE)), OPCODES_8086(JAE), },
    {TOSTRING(OPCODES_8086(JE)), OPCODES_8086(JE), },
    {TOSTRING(OPCODES_8086(JNZ)), OPCODES_8086(JNZ), },
    {TOSTRING(OPCODES_8086(JBE)), OPCODES_8086(JBE), },
    {TOSTRING(OPCODES_8086(JA)), OPCODES_8086(JA), },
    {TOSTRING(OPCODES_8086(JS)), OPCODES_8086(JS), },
    {TOSTRING(OPCODES_8086(JNS)), OPCODES_8086(JNS), },
    {TOSTRING(OPCODES_8086(JPE)), OPCODES_8086(JPE), },
    {TOSTRING(OPCODES_8086(JNP)), OPCODES_8086(JNP), },
    {TOSTRING(OPCODES_8086(JL)), OPCODES_8086(JL), },
    {TOSTRING(OPCODES_8086(JGE)), OPCODES_8086(JGE), },
    {TOSTRING(OPCODES_8086(JLE)), OPCODES_8086(JLE), },
    {TOSTRING(OPCODES_8086(JG)), OPCODES_8086(JG), },
    {TOSTRING(OPCODES_8086(ADD_inmmed8)), OPCODES_8086(ADD_inmmed8), },
    {TOSTRING(OPCODES_8086(OR_inmmed8)), OPCODES_8086(OR_inmmed8), },
    {TOSTRING(OPCODES_8086(ADC_inmmed8)), OPCODES_8086(ADC_inmmed8), },
    {TOSTRING(OPCODES_8086(SBB_inmmed8)), OPCODES_8086(SBB_inmmed8), },
    {TOSTRING(OPCODES_8086(AND_inmmed8)), OPCODES_8086(AND_inmmed8), },
    {TOSTRING(OPCODES_8086(SUB_inmmed8)), OPCODES_8086(SUB_inmmed8), },
    {TOSTRING(OPCODES_8086(XOR_inmmed8)), OPCODES_8086(XOR_inmmed8), },
    {TOSTRING(OPCODES_8086(CMP_inmmed8)), OPCODES_8086(CMP_inmmed8), },
    {TOSTRING(OPCODES_8086(ADD_inmmed16)), OPCODES_8086(ADD_inmmed16), },
    {TOSTRING(OPCODES_8086(OR_inmmed16)), OPCODES_8086(OR_inmmed16), },
    {TOSTRING(OPCODES_8086(ADC_inmmed16)), OPCODES_8086(ADC_inmmed16), },
    {TOSTRING(OPCODES_8086(SBB_inmmed16)), OPCODES_8086(SBB_inmmed16), },
    {TOSTRING(OPCODES_8086(AND_inmmed16)), OPCODES_8086(AND_inmmed16), },
    {TOSTRING(OPCODES_8086(SUB_inmmed16)), OPCODES_8086(SUB_inmmed16), },
    {TOSTRING(OPCODES_8086(XOR_inmmed16)), OPCODES_8086(XOR_inmmed16), },
    {TOSTRING(OPCODES_8086(CMP_inmmed16)), OPCODES_8086(CMP_inmmed16), },
    {TOSTRING(OPCODES_8086(ADD_inmmed8_2)), OPCODES_8086(ADD_inmmed8_2), },
    {TOSTRING(OPCODES_8086(OR_inmmed8_2)), OPCODES_8086(OR_inmmed8_2), },
    {TOSTRING(OPCODES_8086(ADC_inmmed8_2)), OPCODES_8086(ADC_inmmed8_2), },
    {TOSTRING(OPCODES_8086(SBB_inmmed8_2)), OPCODES_8086(SBB_inmmed8_2), },
    {TOSTRING(OPCODES_8086(AND_inmmed8_2)), OPCODES_8086(AND_inmmed8_2), },
    {TOSTRING(OPCODES_8086(SUB_inmmed8_2)), OPCODES_8086(SUB_inmmed8_2), },
    {TOSTRING(OPCODES_8086(XOR_inmmed8_2)), OPCODES_8086(XOR_inmmed8_2), },
    {TOSTRING(OPCODES_8086(CMP_inmmed8_2)), OPCODES_8086(CMP_inmmed8_2), },
    {TOSTRING(OPCODES_8086(ADD_inmmed8_reg_mem16)), OPCODES_8086(ADD_inmmed8_reg_mem16), },
    {TOSTRING(OPCODES_8086(OR_inmmed8_reg_mem16)), OPCODES_8086(OR_inmmed8_reg_mem16), },
    {TOSTRING(OPCODES_8086(ADC_inmmed8_reg_mem16)), OPCODES_8086(ADC_inmmed8_reg_mem16), },
    {TOSTRING(OPCODES_8086(SBB_inmmed8_reg_mem16)), OPCODES_8086(SBB_inmmed8_reg_mem16), },
    {TOSTRING(OPCODES_8086(AND_inmmed8_reg_mem16)), OPCODES_8086(AND_inmmed8_reg_mem16), },
    {TOSTRING(OPCODES_8086(SUB_inmmed8_reg_mem16)), OPCODES_8086(SUB_inmmed8_reg_mem16), },
    {TOSTRING(OPCODES_8086(XOR_inmmed8_reg_mem16)), OPCODES_8086(XOR_inmmed8_reg_mem16), },
    {TOSTRING(OPCODES_8086(CMP_inmmed8_reg_mem16)), OPCODES_8086(CMP_inmmed8_reg_mem16), },
    {TOSTRING(OPCODES_8086(TEST_reg8)), OPCODES_8086(TEST_reg8), },
    {TOSTRING(OPCODES_8086(TEST_reg16)), OPCODES_8086(TEST_reg16), },
    {TOSTRING(OPCODES_8086(XCHG_reg8)), OPCODES_8086(XCHG_reg8), },
    {TOSTRING(OPCODES_8086(XCHG_reg16)), OPCODES_8086(XCHG_reg16), },
    {TOSTRING(OPCODES_8086(MOV_reg8)), OPCODES_8086(MOV_reg8), },
    {TOSTRING(OPCODES_8086(MOV_reg16)), OPCODES_8086(MOV_reg16), },
    {TOSTRING(OPCODES_8086(MOV_mem8)), OPCODES_8086(MOV_mem8), },
    {TOSTRING(OPCODES_8086(MOV_mem16)), OPCODES_8086(MOV_mem16), },
    {TOSTRING(OPCODES_8086(MOV_reg_mem16_segreg)), OPCODES_8086(MOV_reg_mem16_segreg), },
    {TOSTRING(OPCODES_8086(LEA_mem16)), OPCODES_8086(LEA_mem16), },
    {TOSTRING(OPCODES_8086(MOV_segreg_reg_mem16)), OPCODES_8086(MOV_segreg_reg_mem16), },
    {TOSTRING(OPCODES_8086(POP_reg_mem16)), OPCODES_8086(POP_reg_mem16), },
    {TOSTRING(OPCODES_8086(XCHG_ax_ax)), OPCODES_8086(XCHG_ax_ax), },
    {TOSTRING(OPCODES_8086(XCHG_ax_cx)), OPCODES_8086(XCHG_ax_cx), },
    {TOSTRING(OPCODES_8086(XCHG_ax_dx)), OPCODES_8086(XCHG_ax_dx), },
    {TOSTRING(OPCODES_8086(XCHG_ax_bx)), OPCODES_8086(XCHG_ax_bx), },
    {TOSTRING(OPCODES_8086(XCHG_ax_sp)), OPCODES_8086(XCHG_ax_sp), },
    {TOSTRING(OPCODES_8086(XCHG_ax_bp)), OPCODES_8086(XCHG_ax_bp), },
    {TOSTRING(OPCODES_8086(XCHG_ax_si)), OPCODES_8086(XCHG_ax_si), },
    {TOSTRING(OPCODES_8086(XCHG_ax_di)), OPCODES_8086(XCHG_ax_di), },
    {TOSTRING(OPCODES_8086(CBW)), OPCODES_8086(CBW), },
    {TOSTRING(OPCODES_8086(CWD)), OPCODES_8086(CWD), },
    {TOSTRING(OPCODES_8086(CALL_FAR)), OPCODES_8086(CALL_FAR), },
    {TOSTRING(OPCODES_8086(WAIT)), OPCODES_8086(WAIT), },
    {TOSTRING(OPCODES_8086(PUSHF)), OPCODES_8086(PUSHF), },
    {TOSTRING(OPCODES_8086(POPF)), OPCODES_8086(POPF), },
    {TOSTRING(OPCODES_8086(SAHF)), OPCODES_8086(SAHF), },
    {TOSTRING(OPCODES_8086(LAHF)), OPCODES_8086(LAHF), },
    {TOSTRING(OPCODES_8086(MOV_al_mem8)), OPCODES_8086(MOV_al_mem8), },
    {TOSTRING(OPCODES_8086(MOV_ax_mem16)), OPCODES_8086(MOV_ax_mem16), },
    {TOSTRING(OPCODES_8086(MOV_mem8_al)), OPCODES_8086(MOV_mem8_al), },
    {TOSTRING(OPCODES_8086(MOV_mem16_ax)), OPCODES_8086(MOV_mem16_ax), },
    {TOSTRING(OPCODES_8086(MOVS_ptr8)), OPCODES_8086(MOVS_ptr8), },
    {TOSTRING(OPCODES_8086(MOVS_ptr16)), OPCODES_8086(MOVS_ptr16), },
    {TOSTRING(OPCODES_8086(CMPS_ptr8)), OPCODES_8086(CMPS_ptr8), },
    {TOSTRING(OPCODES_8086(CMPS_ptr16)), OPCODES_8086(CMPS_ptr16), },
    {TOSTRING(OPCODES_8086(TEST_al_inmmed8)), OPCODES_8086(TEST_al_inmmed8), },
    {TOSTRING(OPCODES_8086(TEST_ax_inmmed16)), OPCODES_8086(TEST_ax_inmmed16), },
    {TOSTRING(OPCODES_8086(STOS_ptr8)), OPCODES_8086(STOS_ptr8), },
    {TOSTRING(OPCODES_8086(STOS_ptr16)), OPCODES_8086(STOS_ptr16), },
    {TOSTRING(OPCODES_8086(LODS_ptr8)), OPCODES_8086(LODS_ptr8), },
    {TOSTRING(OPCODES_8086(LODS_ptr16)), OPCODES_8086(LODS_ptr16), },
    {TOSTRING(OPCODES_8086(SCAS_ptr8)), OPCODES_8086(SCAS_ptr8), },
    {TOSTRING(OPCODES_8086(SCAS_ptr16)), OPCODES_8086(SCAS_ptr16), },
    {TOSTRING(OPCODES_8086(MOV_al_inmmed8)), OPCODES_8086(MOV_al_inmmed8), },
    {TOSTRING(OPCODES_8086(MOV_cl_inmmed8)), OPCODES_8086(MOV_cl_inmmed8), },
    {TOSTRING(OPCODES_8086(MOV_dl_inmmed8)), OPCODES_8086(MOV_dl_inmmed8), },
    {TOSTRING(OPCODES_8086(MOV_bl_inmmed8)), OPCODES_8086(MOV_bl_inmmed8), },
    {TOSTRING(OPCODES_8086(MOV_ah_inmmed8)), OPCODES_8086(MOV_ah_inmmed8), },
    {TOSTRING(OPCODES_8086(MOV_ch_inmmed8)), OPCODES_8086(MOV_ch_inmmed8), },
    {TOSTRING(OPCODES_8086(MOV_dh_inmmed8)), OPCODES_8086(MOV_dh_inmmed8), },
    {TOSTRING(OPCODES_8086(MOV_bh_inmmed8)), OPCODES_8086(MOV_bh_inmmed8), },
    {TOSTRING(OPCODES_8086(MOV_ax_inmmed16)), OPCODES_8086(MOV_ax_inmmed16), },
    {TOSTRING(OPCODES_8086(MOV_cx_inmmed16)), OPCODES_8086(MOV_cx_inmmed16), },
    {TOSTRING(OPCODES_8086(MOV_dx_inmmed16)), OPCODES_8086(MOV_dx_inmmed16), },
    {TOSTRING(OPCODES_8086(MOV_bx_inmmed16)), OPCODES_8086(MOV_bx_inmmed16), },
    {TOSTRING(OPCODES_8086(MOV_sp_inmmed16)), OPCODES_8086(MOV_sp_inmmed16), },
    {TOSTRING(OPCODES_8086(MOV_bp_inmmed16)), OPCODES_8086(MOV_bp_inmmed16), },
    {TOSTRING(OPCODES_8086(MOV_si_inmmed16)), OPCODES_8086(MOV_si_inmmed16), },
    {TOSTRING(OPCODES_8086(MOV_di_inmmed16)), OPCODES_8086(MOV_di_inmmed16), },
    {TOSTRING(UNDOCUMENTED(RET_NEAR_inmmed16_intraseg)), UNDOCUMENTED(RET_NEAR_inmmed16_intraseg), },
    {TOSTRING(UNDOCUMENTED(RET_intraseg)), UNDOCUMENTED(RET_intraseg), },
    {TOSTRING(OPCODES_8086(RET_NEAR_inmmed16_intraseg)), OPCODES_8086(RET_NEAR_inmmed16_intraseg), },
    {TOSTRING(OPCODES_8086(RET_intraseg)), OPCODES_8086(RET_intraseg), },
    {TOSTRING(OPCODES_8086(LES_mem16)), OPCODES_8086(LES_mem16), },
    {TOSTRING(OPCODES_8086(LDS_mem16)), OPCODES_8086(LDS_mem16), },
    {TOSTRING(OPCODES_8086(MOV_mem8_inmmed8)), OPCODES_8086(MOV_mem8_inmmed8), },
    {TOSTRING(OPCODES_8086(MOV_mem16_inmmed16)), OPCODES_8086(MOV_mem16_inmmed16), },
    {TOSTRING(UNDOCUMENTED(RET_NEAR_inmmed16_intersegment)), UNDOCUMENTED(RET_NEAR_inmmed16_intersegment), },
    {TOSTRING(UNDOCUMENTED(RET_intersegment)), UNDOCUMENTED(RET_intersegment), },
    {TOSTRING(OPCODES_8086(RET_NEAR_inmmed16_intersegment)), OPCODES_8086(RET_NEAR_inmmed16_intersegment), },
    {TOSTRING(OPCODES_8086(RET_intersegment)), OPCODES_8086(RET_intersegment), },
    {TOSTRING(OPCODES_8086(INT_3)), OPCODES_8086(INT_3), },
    {TOSTRING(OPCODES_8086(INT_inmmed8)), OPCODES_8086(INT_inmmed8), },
    {TOSTRING(OPCODES_8086(INTO)), OPCODES_8086(INTO), },
    {TOSTRING(OPCODES_8086(IRET)), OPCODES_8086(IRET), },
    {TOSTRING(OPCODES_8086(ROL_reg_mem8_1)), OPCODES_8086(ROL_reg_mem8_1), },
    {TOSTRING(OPCODES_8086(ROR_reg_mem8_1)), OPCODES_8086(ROR_reg_mem8_1), },
    {TOSTRING(OPCODES_8086(RCL_reg_mem8_1)), OPCODES_8086(RCL_reg_mem8_1), },
    {TOSTRING(OPCODES_8086(RCR_reg_mem8_1)), OPCODES_8086(RCR_reg_mem8_1), },
    {TOSTRING(OPCODES_8086(SAL_reg_mem8_1)), OPCODES_8086(SAL_reg_mem8_1), },
    {TOSTRING(OPCODES_8086(SHL_reg_mem8_1)), OPCODES_8086(SHL_reg_mem8_1), },
    {TOSTRING(OPCODES_8086(SHR_reg_mem8_1)), OPCODES_8086(SHR_reg_mem8_1), },
    {TOSTRING(OPCODES_8086(SAR_reg_mem8_1)), OPCODES_8086(SAR_reg_mem8_1), },
    {TOSTRING(OPCODES_8086(ROL_reg_mem16_1)), OPCODES_8086(ROL_reg_mem16_1), },
    {TOSTRING(OPCODES_8086(ROR_reg_mem16_1)), OPCODES_8086(ROR_reg_mem16_1), },
    {TOSTRING(OPCODES_8086(RCL_reg_mem16_1)), OPCODES_8086(RCL_reg_mem16_1), },
    {TOSTRING(OPCODES_8086(RCR_reg_mem16_1)), OPCODES_8086(RCR_reg_mem16_1), },
    {TOSTRING(OPCODES_8086(SAL_reg_mem16_1)), OPCODES_8086(SAL_reg_mem16_1), },
    {TOSTRING(OPCODES_8086(SHL_reg_mem16_1)), OPCODES_8086(SHL_reg_mem16_1), },
    {TOSTRING(OPCODES_8086(SHR_reg_mem16_1)), OPCODES_8086(SHR_reg_mem16_1), },
    {TOSTRING(OPCODES_8086(SAR_reg_mem16_1)), OPCODES_8086(SAR_reg_mem16_1), },
    {TOSTRING(OPCODES_8086(ROL_reg_mem8_cl)), OPCODES_8086(ROL_reg_mem8_cl), },
    {TOSTRING(OPCODES_8086(ROR_reg_mem8_cl)), OPCODES_8086(ROR_reg_mem8_cl), },
    {TOSTRING(OPCODES_8086(RCL_reg_mem8_cl)), OPCODES_8086(RCL_reg_mem8_cl), },
    {TOSTRING(OPCODES_8086(RCR_reg_mem8_cl)), OPCODES_8086(RCR_reg_mem8_cl), },
    {TOSTRING(OPCODES_8086(SAL_reg_mem8_cl)), OPCODES_8086(SAL_reg_mem8_cl), },
    {TOSTRING(OPCODES_8086(SHL_reg_mem8_cl)), OPCODES_8086(SHL_reg_mem8_cl), },
    {TOSTRING(OPCODES_8086(SHR_reg_mem8_cl)), OPCODES_8086(SHR_reg_mem8_cl), },
    {TOSTRING(OPCODES_8086(SAR_reg_mem8_cl)), OPCODES_8086(SAR_reg_mem8_cl), },
    {TOSTRING(OPCODES_8086(ROL_reg_mem16_cl)), OPCODES_8086(ROL_reg_mem16_cl), },
    {TOSTRING(OPCODES_8086(ROR_reg_mem16_cl)), OPCODES_8086(ROR_reg_mem16_cl), },
    {TOSTRING(OPCODES_8086(RCL_reg_mem16_cl)), OPCODES_8086(RCL_reg_mem16_cl), },
    {TOSTRING(OPCODES_8086(RCR_reg_mem16_cl)), OPCODES_8086(RCR_reg_mem16_cl), },
    {TOSTRING(OPCODES_8086(SAL_reg_mem16_cl)), OPCODES_8086(SAL_reg_mem16_cl), },
    {TOSTRING(OPCODES_8086(SHL_reg_mem16_cl)), OPCODES_8086(SHL_reg_mem16_cl), },
    {TOSTRING(OPCODES_8086(SHR_reg_mem16_cl)), OPCODES_8086(SHR_reg_mem16_cl), },
    {TOSTRING(OPCODES_8086(SAR_reg_mem16_cl)), OPCODES_8086(SAR_reg_mem16_cl), },
    {TOSTRING(OPCODES_8086(AAM)), OPCODES_8086(AAM), },
    {TOSTRING(OPCODES_8086(AAD)), OPCODES_8086(AAD), },
    {TOSTRING(OPCODES_8086(SALC)), OPCODES_8086(SALC), },
    {TOSTRING(OPCODES_8086(XLAT)), OPCODES_8086(XLAT), },
    {TOSTRING(OPCODES_8086(ESC)), OPCODES_8086(ESC), },
    {TOSTRING(OPCODES_8086(LOOPNE_inmmed8)), OPCODES_8086(LOOPNE_inmmed8), },
    {TOSTRING(OPCODES_8086(LOOPNZ_inmmed8)), OPCODES_8086(LOOPNZ_inmmed8), },
    {TOSTRING(OPCODES_8086(LOOPE_inmmed8)), OPCODES_8086(LOOPE_inmmed8), },
    {TOSTRING(OPCODES_8086(LOOPZ_inmmed8)), OPCODES_8086(LOOPZ_inmmed8), },
    {TOSTRING(OPCODES_8086(LOOP_inmmed8)), OPCODES_8086(LOOP_inmmed8), },
    {TOSTRING(OPCODES_8086(JCXZ_inmmed8)), OPCODES_8086(JCXZ_inmmed8), },
    {TOSTRING(OPCODES_8086(IN_al_inmmed8)), OPCODES_8086(IN_al_inmmed8), },
    {TOSTRING(OPCODES_8086(IN_ax_inmmed8)), OPCODES_8086(IN_ax_inmmed8), },
    {TOSTRING(OPCODES_8086(OUT_al_inmmed8)), OPCODES_8086(OUT_al_inmmed8), },
    {TOSTRING(OPCODES_8086(OUT_ax_inmmed8)), OPCODES_8086(OUT_ax_inmmed8), },
    {TOSTRING(OPCODES_8086(CALL_NEAR)), OPCODES_8086(CALL_NEAR), },
    {TOSTRING(OPCODES_8086(JMP_NEAR)), OPCODES_8086(JMP_NEAR), },
    {TOSTRING(OPCODES_8086(JMP_FAR)), OPCODES_8086(JMP_FAR), },
    {TOSTRING(OPCODES_8086(JMP_inmmed8)), OPCODES_8086(JMP_inmmed8), },
    {TOSTRING(OPCODES_8086(JMP_SHORT)), OPCODES_8086(JMP_SHORT), },
    {TOSTRING(OPCODES_8086(IN_al_dx)), OPCODES_8086(IN_al_dx), },
    {TOSTRING(OPCODES_8086(IN_ax_dx)), OPCODES_8086(IN_ax_dx), },
    {TOSTRING(OPCODES_8086(OUT_al_dx)), OPCODES_8086(OUT_al_dx), },
    {TOSTRING(OPCODES_8086(OUT_ax_dx)), OPCODES_8086(OUT_ax_dx), },
    {TOSTRING(OPCODES_8086(REPENE)), OPCODES_8086(REPENE), },
    {TOSTRING(OPCODES_8086(REPENZ)), OPCODES_8086(REPENZ), },
    {TOSTRING(OPCODES_8086(REP)), OPCODES_8086(REP), },
    {TOSTRING(OPCODES_8086(REPE)), OPCODES_8086(REPE), },
    {TOSTRING(OPCODES_8086(REPZ)), OPCODES_8086(REPZ), },
    {TOSTRING(OPCODES_8086(HLT)), OPCODES_8086(HLT), },
    {TOSTRING(OPCODES_8086(CMC)), OPCODES_8086(CMC), },
    {TOSTRING(OPCODES_8086(TEST_reg_mem8_inmmed8)), OPCODES_8086(TEST_reg_mem8_inmmed8), },
    {TOSTRING(OPCODES_8086(NOT_reg_mem8)), OPCODES_8086(NOT_reg_mem8), },
    {TOSTRING(OPCODES_8086(NEG_reg_mem8)), OPCODES_8086(NEG_reg_mem8), },
    {TOSTRING(OPCODES_8086(MUL_reg_mem8)), OPCODES_8086(MUL_reg_mem8), },
    {TOSTRING(OPCODES_8086(IMUL_reg_mem8)), OPCODES_8086(IMUL_reg_mem8), },
    {TOSTRING(OPCODES_8086(DIV_reg_mem8)), OPCODES_8086(DIV_reg_mem8), },
    {TOSTRING(OPCODES_8086(IDIV_reg_mem8)), OPCODES_8086(IDIV_reg_mem8), },
    {TOSTRING(OPCODES_8086(TEST_reg_mem16_inmmed16)), OPCODES_8086(TEST_reg_mem16_inmmed16), },
    {TOSTRING(OPCODES_8086(NOT_reg_mem16)), OPCODES_8086(NOT_reg_mem16), },
    {TOSTRING(OPCODES_8086(NEG_reg_mem16)), OPCODES_8086(NEG_reg_mem16), },
    {TOSTRING(OPCODES_8086(MUL_reg_mem16)), OPCODES_8086(MUL_reg_mem16), },
    {TOSTRING(OPCODES_8086(IMUL_reg_mem16)), OPCODES_8086(IMUL_reg_mem16), },
    {TOSTRING(OPCODES_8086(DIV_reg_mem16)), OPCODES_8086(DIV_reg_mem16), },
    {TOSTRING(OPCODES_8086(IDIV_reg_mem16)), OPCODES_8086(IDIV_reg_mem16), },
    {TOSTRING(OPCODES_8086(CLC)), OPCODES_8086(CLC), },
    {TOSTRING(OPCODES_8086(STC)), OPCODES_8086(STC), },
    {TOSTRING(OPCODES_8086(CLI)), OPCODES_8086(CLI), },
    {TOSTRING(OPCODES_8086(STI)), OPCODES_8086(STI), },
    {TOSTRING(OPCODES_8086(CLD)), OPCODES_8086(CLD), },
    {TOSTRING(OPCODES_8086(STD)), OPCODES_8086(STD), },
    {TOSTRING(OPCODES_8086(INC_reg_mem8)), OPCODES_8086(INC_reg_mem8), },
    {TOSTRING(OPCODES_8086(DEC_reg_mem8)), OPCODES_8086(DEC_reg_mem8), },
    {TOSTRING(OPCODES_8086(INC_mem16)), OPCODES_8086(INC_mem16), },
    {TOSTRING(OPCODES_8086(DEC_mem16)), OPCODES_8086(DEC_mem16), },
    {TOSTRING(OPCODES_8086(CALL_intraseg)), OPCODES_8086(CALL_intraseg), },
    {TOSTRING(OPCODES_8086(CALL_intersegment)), OPCODES_8086(CALL_intersegment), },
    {TOSTRING(OPCODES_8086(JMP_intraseg)), OPCODES_8086(JMP_intraseg), },
    {TOSTRING(OPCODES_8086(JMP_intersegment)), OPCODES_8086(JMP_intersegment), },
    {TOSTRING(OPCODES_8086(PUSH_mem16)), (OPCODES_8086(PUSH_mem16))},
};