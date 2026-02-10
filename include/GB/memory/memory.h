#pragma once
#ifndef MEMORY_H
#define MEMORY_H

#include "global.h"

#include <algorithm>

class Memory {
protected:
    u8* data;
    u32 size;
    
    const u16 RANGE_FROM;
    const u16 RANGE_TO;

public:
    Memory(u16 range_from, u16 range_to);
    ~Memory();

    virtual u8 readMemoryU8(u32 address) = 0;
    virtual void writeMemoryU8(u32 address, u8 data) = 0;

    virtual bool isAddressInRange(u32 address);
    virtual bool isAddressInSizeRange(u32 address);
};

#endif // MEMORY_H