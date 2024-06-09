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

#define SM83_INSTRUCTION_DECLARATION(NAME) \
    SM83_Instruction_ ## NAME

#define SM83_INSTRUCTION_STEPS_DECLARATION(NAME) \
    SM83_Instruction_Steps_ ## NAME

#define SM83_INSTRUCTION_IMPLEMENTATION(NAME, BODY) \
    static void SM83_Instruction_ ## NAME (SM83Cpu* cpu) { \
        BODY; \
    }
    
#define SM83_INSTRUCTION_STEPS_IMPLEMENTATION(NAME, ...) \
    const static SM83Instruction* SM83_Instruction_Steps_ ## NAME[] = { __VA_ARGS__ }
    
#define SM83_INSTRUCTION_INFO(OPCODE, NAME, SIZE, CYCLES, STEPS) \
    { OPCODE, NAME, SIZE, CYCLES, STEPS }

extern const SM83Opcode opcodesTable[];
extern const SM83Opcode opcodesCbTable[];

#endif // OPCODES_H