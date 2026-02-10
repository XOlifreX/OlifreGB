#pragma once
#ifndef HRAM_H
#define HRAM_H

#include "GB/memory/memory.h"

#define HRAM_RANGE_FROM 0xFF80
#define HRAM_RANGE_TO 0xFFFE

#define HRAM_FULL_SIZE (HRAM_RANGE_TO - HRAM_RANGE_FROM + 1)

class HRAM: public Memory {
public:
    HRAM();
    ~HRAM();

    u8 readMemoryU8(u32 address);
    void writeMemoryU8(u32 address, u8 data);
};

#endif // HRAM_H