#pragma once
#ifndef SM83_H
#define SM83_H

#include <vector>
#include <iostream>

#include "global.h"
#include "bus.h"

#include "GB/memory/registers/hardware_registers.h"

#define SM83_DEFAULT_N_TCYCLES_FOR_1_MCYCLE 4
#define SM83_CCB_N_TCYCLES_FOR_1_MCYCLE 2

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
        u8 LOW; \
        u8 HIGH; \
    }; \
    u16 HIGH ## LOW; \
};

struct RegisterFile {
#pragma pack(push, 1)
    SM83_AF_REGISTER;
    SM83_REGISTER_PAIR(B, C);
    SM83_REGISTER_PAIR(D, E);
    SM83_REGISTER_PAIR(H, L);
    SM83_REGISTER_PAIR(S, P);
    u16 PC;
    SM83_REGISTER_PAIR(W, Z);
#pragma pack(pop)
};

class SM83Cpu;
typedef void (SM83Instruction)(SM83Cpu*);

struct SM83Opcode {
    u8 opcode;
    const char* name;
    u8 size;
    u8 cycles;
    u8 earlyExitSkipSteps;
    SM83Instruction** steps;
};

struct CpuContext {
    u16 currentStep;
    const SM83Opcode* currentInstruction;
    SM83_REGISTER_PAIR(T, P);
    bool instruction_exit_early;
    u8 skipSteps;
    bool CBMode;
};

#include "instructions.h"

class SM83Cpu {
public:
#pragma pack(push, 1)
    struct RegisterFile registers;
    CpuContext context;
#pragma pack(pop)
    HardwareRegisterState* hrState;

    Bus* bus;

    long tCycle;
    long mCycle;
    u8 tCycleNumForOneMCycle;

    bool isHalted;
    u8 isHaltJustSet;

    bool debugPrint;

    SM83Cpu(Bus* bus, bool debugPrint = true);
    ~SM83Cpu();

    void tick();
    
    bool hasInterrupt();
    bool canHandleInterrupt();
    void prepareInterrupt();

    bool onHaltCheckWakeUp();

    void debug_print_state();
};

#endif // SM83_H