#pragma once
#ifndef MEMORY_H
#define MEMORY_H

#include "global.h"

#include <algorithm>

class Memory {
protected:
    u8* data;
    const u16 RANGE_FROM;
    const u16 RANGE_TO;

public:
    Memory(u16 range_from, u16 range_to);
    ~Memory();

    virtual u8 readMemoryU8(u16 address) = 0;
    virtual void writeMemoryU8(u16 address, u8 data) = 0;

    virtual bool isAddressInRange(u16 address);
};

#endif // MEMORY_H