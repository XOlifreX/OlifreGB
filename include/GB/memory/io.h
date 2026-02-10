#pragma once
#ifndef IO_H
#define IO_H

#include "GB/memory/memory.h"

#define IO_RANGE_FROM 0xFF00
#define IO_RANGE_TO 0xFF7F

#define NOTUSABLERAM_FULL_SIZE (IO_RANGE_TO - IO_RANGE_FROM + 1)

// Only used in test-mode
class IO: public Memory {
public:
    IO();
    ~IO();

    u8 readMemoryU8(u32 address);
    void writeMemoryU8(u32 address, u8 data);
};

#endif // IO_H