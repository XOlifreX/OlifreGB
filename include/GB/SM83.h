#pragma once
#ifndef SM83_H
#define SM83_H

#include <vector>
#include <iostream>

#include "global.h"
#include "bus.h"

#pragma pack(push, 1)
union FlagRegister {
    struct {
        u8 _ : 4;
        u8 C : 1;
        u8 H : 1;
        u8 N : 1;
        u8 Z : 1;
    };
    u8 flag;
};
#pragma pack(pop)

#define SM83_AF_REGISTER union { \
    struct { \
        union FlagRegister F; \
        u8 A; \
    }; \
    u16 FA; \
};

#define SM83_REGISTER_PAIR(HIGH, LOW) union { \
    struct { \
        u8 HIGH; \
        u8 LOW; \
    }; \
    u16 HIGH ## LOW; \
};

struct RegisterFile {
#pragma pack(push, 1)
    SM83_AF_REGISTER;
    SM83_REGISTER_PAIR(B, C);
    SM83_REGISTER_PAIR(D, E);
    SM83_REGISTER_PAIR(H, L);
    u16 SP;
    u16 PC;
#pragma pack(pop)
};

class SM83Cpu;
typedef void (SM83Instruction)(SM83Cpu*);

struct SM83Opcode {
    u8 opcode;
    const char* name;
    u8 size;
    u8 cycles;
    SM83Instruction** steps;
};

struct CpuContext {
    u16 currentStep;
    const SM83Opcode* currentInstruction;
    SM83_REGISTER_PAIR(T, P);
    bool instruction_exit_early;
    bool CBMode;
};

#include "instructions.h"

class SM83Cpu {
public:
#pragma pack(push, 1)
    struct RegisterFile registers;
    CpuContext context;
#pragma pack(pop)

    bool IME;
    Bus* bus;

    long tCycle;
    long mCycle;

    SM83Cpu(Bus* bus);
    ~SM83Cpu();

    void tick();
    void debug_print_state();
};

#endif // SM83_H