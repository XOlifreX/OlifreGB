#pragma once
#ifndef OPCODES_H
#define OPCODES_H

#include<vector>
#include "global.h"
#include "GB/SM83.h"

struct SM83Opcode {
    u8 opcode;
    const char* name;
    u8 size;
    u8 cycles;
    SM83Instruction** steps;
};

// ********************

#define IS_CARRY_SET_ADD_U8(REGISTER, VALUE) \
    ((u16)REGISTER + VALUE) >= 0x100 ? 1 : 0;

#define IS_CARRY_SET_SUB_U8(REGISTER, VALUE) \
    ((u16)REGISTER - VALUE) < 0 ? 1 : 0;

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
    u16 shifted = (REGISTER << 1) | (REGISTER >> 7); \
    FLAGS.Z = shifted == 0x00; \
    FLAGS.N = 0; \
    FLAGS.H = 0; \
    FLAGS.C = (shifted > 0xFF) ? 1 : 0; \
    REGISTER = (u8)shifted;

#define SM83_RR(REGISTER, FLAGS) \
    u16 shifted = (REGISTER >> 1) | (REGISTER << 7); \
    FLAGS.Z = shifted == 0x00; \
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
    
#define SM83_INSTRUCTION_INFO(OPCODE, NAME, SIZE, CYCLES, STEPS) \
    { OPCODE, NAME, SIZE, CYCLES, STEPS }

extern const SM83Opcode opcodesTable[];
extern const SM83Opcode opcodesCbTable[];

#endif // OPCODES_H