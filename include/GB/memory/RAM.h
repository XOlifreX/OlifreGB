#pragma once
#ifndef RAM_H
#define RAM_H

#include "GB/memory/memory.h"

#include <malloc.h>

#define INTERUPT_ENABLE_REGISTER 0xFFFF

#define RAM_RANGE_FROM 0x4000
#define RAM_RANGE_TO 0xFFFF

class RAM: public Memory {
public:
    RAM();
    ~RAM();

    u8 readMemoryU8(u16 address);
    void writeMemoryU8(u16 address, u8 data);
};

// https://gbdev.io/pandocs/Memory_Map.html#fea0feff-range

#endif // RAM_H