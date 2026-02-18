#pragma once
#ifndef INTERRUPTS_H
#define INTERRUPTS_H

#include "GB/memory/memory.h"

#define INTR_RANGE_FROM 0xFF0F
#define INTR_RANGE_TO 0xFFFF

#define INTR_IF_ADDRESS 0xFF0F
#define INTR_IE_ADDRESS 0xFFFF

#define INTR_IS_IN_REGION(ADDRESS) \
    ADDRESS >= INTR_RANGE_FROM && ADDRESS <= INTR_RANGE_TO

enum InterruptTypes {
    Intr_None = 0x00,
    Intr_VBlank = 0x40,
    Intr_STAT = 0x48,
    Intr_Timer = 0x50,
    Intr_Serial = 0x58,
    Intr_Joypad = 0x60
};

struct InterruptState {
    bool intrMasterEnable;
    
    bool intrInProgressOfEnable;
    u8 intrInProgressStep;

    union {
        u8 _unused1 : 3;
        u8 intrEnableVBlank : 1;
        u8 intrEnableLCD : 1;
        u8 intrEnableTimer : 1;
        u8 intrEnableSerial : 1;
        u8 intrEnableJoypad : 1;

        u8 intrEnable;
    };
    
    union {
        u8 _unused2 : 3;
        u8 intrFlagVBlank : 1;
        u8 intrFlagLCD : 1;
        u8 intrFlagTimer : 1;
        u8 intrFlagSerial : 1;
        u8 intrFlagJoypad : 1;

        u8 intrFlags;
    };

    InterruptTypes curr_req_intr;
};

class Interrupt : public Memory {
private:
    InterruptState* state;

    u32 translateAddress(u32 address);
    
public:
    Interrupt(InterruptState* state);
    ~Interrupt();

    u8 readMemoryU8(u32 address);
    void writeMemoryU8(u32 address, u8 data);
    
    bool isAddressInRange(u32 address);
};

#endif // INTERRUPTS_H