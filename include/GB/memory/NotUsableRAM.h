#pragma once
#ifndef NOTUSABLERAM_H
#define NOTUSABLERAM_H

#include "GB/memory/memory.h"

#define NOTUSABLERAM_RANGE_FROM 0xFEA0
#define NOTUSABLERAM_RANGE_TO 0xFEFF

#define NOTUSABLERAM_FULL_SIZE (NOTUSABLERAM_RANGE_TO - NOTUSABLERAM_RANGE_FROM + 1)

// Only used in test-mode
class NotUsableRAM: public Memory {
public:
    NotUsableRAM();
    ~NotUsableRAM();

    u8 readMemoryU8(u32 address);
    void writeMemoryU8(u32 address, u8 data);
};

#endif // NOTUSABLERAM