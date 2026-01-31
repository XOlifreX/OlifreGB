#pragma once
#ifndef OPCODES_H
#define OPCODES_H

#include<vector>
#include "global.h"

// ********************

#define IS_CARRY_SET_ADD_U8(REGISTER, VALUE) \
    ((u16)REGISTER + VALUE) >= 0x100 ? 1 : 0;

#define IS_CARRY_SET_SUB_U8(REGISTER, VALUE) \
    ((s16)REGISTER - VALUE) < 0 ? 1 : 0;

#define IS_CARRY_SET_ADD_U16_SIGNED(REGISTER, VALUE) \
    ((s16)REGISTER + VALUE) >= 0x10000 ? 1 : 0;

// ********************

#define SM83_RLC(REGISTER, FLAGS) \
    u16 shifted = (REGISTER << 1) | (REGISTER >> 7); \
    FLAGS.Z = 0; \
    FLAGS.N = 0; \
    FLAGS.H = 0; \
    FLAGS.C = (shifted > 0xFF) ? 1 : 0; \
    REGISTER = (u8)shifted;
    
#define SM83_RRC(REGISTER, FLAGS) \
    u8 shifted = (REGISTER >> 1) | (REGISTER << 7); \
    FLAGS.Z = 0; \
    FLAGS.N = 0; \
    FLAGS.H = 0; \
    FLAGS.C = REGISTER & 0x01; \
    REGISTER = shifted;

#define SM83_RL(REGISTER, FLAGS) \
    u16 shifted = (REGISTER << 1) | FLAGS.C; \
    FLAGS.Z = 0; \
    FLAGS.N = 0; \
    FLAGS.H = 0; \
    FLAGS.C = REGISTER >> 7; \
    REGISTER = (u8)shifted;

#define SM83_RR(REGISTER, FLAGS) \
    u16 shifted = (REGISTER >> 1) | (FLAGS.C << 7); \
    FLAGS.Z = 0; \
    FLAGS.N = 0; \
    FLAGS.H = 0; \
    FLAGS.C = REGISTER & 0x01; \
    REGISTER = (u8)shifted;

#define SM83_SLA(REGISTER, FLAGS) \
    u16 shifted = (REGISTER << 1) | (REGISTER & 0x80); \
    FLAGS.Z = shifted == 0x00; \
    FLAGS.N = 0; \
    FLAGS.H = 0; \
    FLAGS.C = (shifted > 0xFF) ? 1 : 0; \
    REGISTER = (u8)shifted;

#define SM83_SRA(REGISTER, FLAGS) \
    u16 shifted = (REGISTER >> 1) | (REGISTER & 0x80); \
    FLAGS.Z = shifted == 0x00; \
    FLAGS.N = 0; \
    FLAGS.H = 0; \
    FLAGS.C = REGISTER & 0x01; \
    REGISTER = (u8)shifted;

#define SM83_SWAP(REGISTER, FLAGS) \
    u8 result = (REGISTER >> 4) | (REGISTER << 4); \
    FLAGS.Z = result == 0x00; \
    FLAGS.N = 0; \
    FLAGS.H = 0; \
    FLAGS.C = 0; \
    REGISTER = result;

#define SM83_SRL(REGISTER, FLAGS) \
    u16 shifted = (REGISTER >> 1); \
    FLAGS.Z = shifted == 0x00; \
    FLAGS.N = 0; \
    FLAGS.H = 0; \
    FLAGS.C = REGISTER & 0x01; \
    REGISTER = (u8)shifted;

#define SM83_BIT(REGISTER, INDEX, FLAGS) \
    u16 bitIsSet = (REGISTER >> INDEX) & 0x01; \
    FLAGS.Z = bitIsSet == 0x00; \
    FLAGS.N = 0; \
    FLAGS.H = 1;

#define SM83_RES(REGISTER, INDEX) \
    REGISTER = REGISTER & ~(1 << INDEX);

#define SM83_SET(REGISTER, INDEX) \
    REGISTER = REGISTER | (1 << INDEX); 

#define SM83_INC8(REGISTER, FLAGS) \
    FLAGS.H = ((REGISTER & 0x0F) + 1) > 0x0F; \
    REGISTER++; \
    FLAGS.Z = (REGISTER & 0xFF) == 0x00; \
    FLAGS.N = 0;

#define SM83_DEC8(REGISTER, FLAGS) \
    FLAGS.H = (REGISTER & 0x0F) == 0x00; \
    REGISTER--; \
    FLAGS.Z = (REGISTER & 0xFF) == 0x00; \
    FLAGS.N = 1;

#define SM83_ADD_R16_R16(REGISTER1, REGISTER2, FLAGS) \
    u32 result = REGISTER1 + REGISTER2; \
    FLAGS.N = 0; \
    FLAGS.H = (result > 0x0FFF) ? 1 : 0; \
    FLAGS.C = (result > 0xFFFF) ? 1 : 0; \
    REGISTER1 = result;

#define SM83_ADD_R8_R8(REGISTER1, REGISTER2, FLAGS) \
    u16 result = REGISTER1 + REGISTER2; \
    FLAGS.N = 0; \
    FLAGS.H = ((REGISTER1 & 0x0F) + (REGISTER2 & 0x0F)) > 0x0F ? 1 : 0; \
    FLAGS.C = (result > 0xFF) ? 1 : 0; \
    REGISTER1 = result;

#define SM83_ADD_R8_R8_WITH_CARRY(REGISTER1, REGISTER2, FLAGS) \
    u16 result = REGISTER1 + REGISTER2 + FLAGS.C; \
    FLAGS.N = 0; \
    FLAGS.H = ((REGISTER1 & 0x0F) + (REGISTER2 & 0x0F) + FLAGS.C) > 0x0F ? 1 : 0; \
    FLAGS.C = (result > 0xFF) ? 1 : 0; \
    REGISTER1 = result;

#define SM83_SUB_R8_R8(REGISTER1, REGISTER2, FLAGS) \
    u16 result = REGISTER1 - REGISTER2; \
    FLAGS.C = IS_CARRY_SET_SUB_U8(REGISTER1, REGISTER2); \
    FLAGS.N = 1; \
    FLAGS.H = (result > 0x0F) ? 1 : 0; \
    FLAGS.Z = result == 0x0; \
    REGISTER1 = result;

#define SM83_SUB_R8_R8_WITH_CARRY(REGISTER1, REGISTER2, FLAGS) \
    u16 result = REGISTER1 - REGISTER2 - FLAGS.C; \
    FLAGS.C = IS_CARRY_SET_SUB_U8(REGISTER1, REGISTER2); \
    FLAGS.N = 1; \
    FLAGS.H = (result > 0x0F) ? 1 : 0; \
    FLAGS.Z = result == 0x0; \
    REGISTER1 = result;

#define SM83_AND_R8_R8(REGISTER1, REGISTER2, FLAGS) \
    u16 result = REGISTER1 & REGISTER2; \
    FLAGS.Z = result == 0x0; \
    FLAGS.N = 0; \
    FLAGS.H = 1; \
    FLAGS.C = 0; \
    REGISTER1 = result;

#define SM83_XOR_R8_R8(REGISTER1, REGISTER2, FLAGS) \
    u16 result = REGISTER1 ^ REGISTER2; \
    FLAGS.Z = result == 0x0; \
    FLAGS.N = 0; \
    FLAGS.H = 0; \
    FLAGS.C = 0; \
    REGISTER1 = result;

#define SM83_OR_R8_R8(REGISTER1, REGISTER2, FLAGS) \
    u16 result = REGISTER1 | REGISTER2; \
    FLAGS.Z = result == 0x0; \
    FLAGS.N = 0; \
    FLAGS.H = 1; \
    FLAGS.C = 0; \
    REGISTER1 = result;

#define SM83_CP_R8_R8(REGISTER1, REGISTER2, FLAGS) \
    u16 result = REGISTER1 - REGISTER2; \
    FLAGS.C = IS_CARRY_SET_SUB_U8(REGISTER1, REGISTER2); \
    FLAGS.N = 1; \
    FLAGS.H = (result > 0x0F) ? 1 : 0; \
    FLAGS.Z = result == 0x0;

#define SM83_ADD_R8_IMM8(REGISTER, VALUE, FLAGS) \
    u16 result = REGISTER + VALUE; \
    FLAGS.C = IS_CARRY_SET_ADD_U8(REGISTER, VALUE); \
    FLAGS.N = 0; \
    FLAGS.H = (result > 0x0F) ? 1 : 0; \
    FLAGS.Z = result == 0x0; \
    REGISTER = result;

#define SM83_ADD_R16_IMM8_SIGNED(REGISTER, VALUE, FLAGS) \
    s32 result = REGISTER + VALUE; \
    FLAGS.C = IS_CARRY_SET_ADD_U16_SIGNED(REGISTER, VALUE); \
    FLAGS.N = 0; \
    FLAGS.H = (result > 0x00FF) ? 1 : 0; \
    FLAGS.Z = 0; \
    REGISTER = result;

#define SM83_ADD_R8_IMM8_WITH_CARRY(REGISTER, VALUE, FLAGS) \
    u16 result = REGISTER + VALUE + FLAGS.C; \
    FLAGS.C = IS_CARRY_SET_ADD_U8(REGISTER, VALUE); \
    FLAGS.N = 0; \
    FLAGS.H = (result > 0x0F) ? 1 : 0; \
    FLAGS.Z = result == 0x0; \
    REGISTER = result;

#define SM83_SUB_R8_IMM8(REGISTER, VALUE, FLAGS) \
    u16 result = REGISTER - VALUE; \
    FLAGS.C = IS_CARRY_SET_SUB_U8(REGISTER, VALUE); \
    FLAGS.N = 1; \
    FLAGS.H = (result > 0x0F) ? 1 : 0; \
    FLAGS.Z = result == 0x0; \
    REGISTER = result;

#define SM83_SUB_R8_IMM8_WITH_CARRY(REGISTER, VALUE, FLAGS) \
    u16 result = REGISTER - VALUE - FLAGS.C; \
    FLAGS.C = IS_CARRY_SET_SUB_U8(REGISTER, VALUE); \
    FLAGS.N = 1; \
    FLAGS.H = (result > 0x0F) ? 1 : 0; \
    FLAGS.Z = result == 0x0; \
    REGISTER = result;

#define SM83_AND_R8_IMM8(REGISTER, VALUE, FLAGS) \
    u16 result = REGISTER & VALUE; \
    FLAGS.Z = result == 0x0; \
    FLAGS.N = 0; \
    FLAGS.H = 1; \
    FLAGS.C = 0; \
    REGISTER = result;

#define SM83_XOR_R8_IMM8(REGISTER, VALUE, FLAGS) \
    u16 result = REGISTER ^ VALUE; \
    FLAGS.Z = result == 0x0; \
    FLAGS.N = 0; \
    FLAGS.H = 0; \
    FLAGS.C = 0; \
    REGISTER = result;

#define SM83_OR_R8_IMM8(REGISTER, VALUE, FLAGS) \
    u16 result = REGISTER | VALUE; \
    FLAGS.Z = result == 0x0; \
    FLAGS.N = 0; \
    FLAGS.H = 1; \
    FLAGS.C = 0; \
    REGISTER = result;

#define SM83_CP_R8_IMM8(REGISTER, VALUE, FLAGS) \
    u16 result = REGISTER - VALUE; \
    FLAGS.C = IS_CARRY_SET_SUB_U8(REGISTER, VALUE); \
    FLAGS.N = 1; \
    FLAGS.H = (result > 0x0F) ? 1 : 0; \
    FLAGS.Z = result == 0x0;

// ********************

#define SM83_INSTRUCTION_DECLARATION(NAME) \
    SM83_Instruction_ ## NAME

#define SM83_CB_INSTRUCTION_DECLARATION(NAME) \
    SM83_CB_Instruction_ ## NAME

#define SM83_INSTRUCTION_STEPS_DECLARATION(NAME) \
    SM83_Instruction_Steps_ ## NAME

#define SM83_CB_INSTRUCTION_STEPS_DECLARATION(NAME) \
    SM83_CB_Instruction_Steps_ ## NAME

#define SM83_INSTRUCTION_IMPLEMENTATION(NAME, BODY) \
    static void SM83_Instruction_ ## NAME (SM83Cpu* cpu) { \
        BODY; \
        cpu->registers.PC++; \
    }

#define SM83_INSTRUCTION_IMPLEMENTATION_NO_PC_INCREASE(NAME, BODY) \
    static void SM83_Instruction_ ## NAME (SM83Cpu* cpu) { \
        BODY; \
    }

#define SM83_CB_INSTRUCTION_IMPLEMENTATION(NAME, BODY) \
    static void SM83_CB_Instruction_ ## NAME (SM83Cpu* cpu) { \
        BODY; \
        cpu->registers.PC++; \
    }

#define SM83_CB_INSTRUCTION_IMPLEMENTATION_NO_PC_INCREASE(NAME, BODY) \
    static void SM83_CB_Instruction_ ## NAME (SM83Cpu* cpu) { \
        BODY; \
    }
    
#define SM83_INSTRUCTION_STEPS_IMPLEMENTATION(NAME, ...) \
    const static SM83Instruction* SM83_Instruction_Steps_ ## NAME[] = { __VA_ARGS__ }

#define SM83_CB_INSTRUCTION_STEPS_IMPLEMENTATION(NAME, ...) \
    const static SM83Instruction* SM83_CB_Instruction_Steps_ ## NAME[] = { __VA_ARGS__ }
    
#define SM83_INSTRUCTION_INFO(OPCODE, NAME, SIZE, CYCLES, EARLY_EXIT_SKIP, STEPS) \
    { OPCODE, NAME, SIZE, CYCLES, EARLY_EXIT_SKIP, STEPS }

// *****    

#include "GB/SM83.h"

extern const SM83Opcode opcodesTable[];
extern const SM83Opcode opcodesCbTable[];

#endif // OPCODES_H