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

#define IS_CARRY_SET_ADD_U8(REGISTER, VALUE) \
    ((u16)REGISTER + VALUE) >= 0x100 ? 1 : 0;

#define IS_CARRY_SET_SUB_U8(REGISTER, VALUE) \
    ((u16)REGISTER - VALUE) < 0 ? 1 : 0;

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

#define SM83_CB_INSTRUCTION_IMPLEMENTATION(NAME, BODY) \
    static void SM83_CB_Instruction_ ## NAME (SM83Cpu* cpu) { \
        BODY; \
        cpu->registers.PC++; \
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