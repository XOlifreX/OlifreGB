#pragma once
#ifndef SRAM_H
#define SRAM_H

#include "GB/memory/memory.h"

#define SRAM_RANGE_FROM 0xA000
#define SRAM_RANGE_TO 0xBFFF

#define SRAM_FULL_SIZE (SRAM_RANGE_TO - SRAM_RANGE_FROM + 1)

class SRAM: public Memory {
public:
    SRAM();
    ~SRAM();

    void writeSRAM(u8* sram, u32 size);
    u8* readSRAM();

    u8 readMemoryU8(u16 address);
    void writeMemoryU8(u16 address, u8 data);
};

#endif // SRAM_H