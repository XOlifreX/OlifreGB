#pragma once
#ifndef VRAM_H
#define VRAM_H

#include "GB/memory/memory.h"

#include <iostream>

#define VRAM_RANGE_FROM 0x8000
#define VRAM_RANGE_TO 0x9FFF

#define VRAM_FULL_SIZE (RAM_RANGE_TO - RAM_RANGE_FROM + 1)

class VRAM: public Memory {
public:
    VRAM();
    ~VRAM();

    u8 readMemoryU8(u32 address);
    void writeMemoryU8(u32 address, u8 data);
};

#endif // VRAM_H