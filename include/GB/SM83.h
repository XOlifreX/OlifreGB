#pragma once
#ifndef SM83_H
#define SM83_H

#include <vector>

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
    u16 AF; \
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

struct CpuContext {
    u8 currentStep;
    SM83Instruction* currentInstruction;
    SM83_REGISTER_PAIR(T, P);
    bool finished;
};

class SM83Cpu {
public:
#pragma pack(push, 1)
    struct RegisterFile registers;
    CpuContext context;
#pragma pack(pop)

    Bus* bus;

    SM83Cpu(Bus* bus);
    ~SM83Cpu();
};

#endif // SM83_H