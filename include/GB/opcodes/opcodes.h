#pragma once
#ifndef OPCODES_H
#define OPCODES_H

#include "global.h"
#include "GB/SM83.h"

struct SM83Opcode {
    u8 opcode;
    const char* name;
    SM83Instruction execute;
    u8 size;
    u8 cycles;
};

#define SM83_INSTRUCTION_DECLARATION(NAME) \
    SM83_Instruction_ ## NAME

#define SM83_INSTRUCTION_IMPLEMENTATION(NAME, BODY) \
    static void SM83_Instruction_ ## NAME (SM83Cpu* cpu) { \
        BODY; \
    }

extern const SM83Opcode* opcodesTable;
extern const SM83Opcode* opcodesCbTable;

#endif // OPCODES_H