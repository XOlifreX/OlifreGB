#pragma once
#ifndef OAM_H
#define OAM_H

#include "GB/memory/memory.h"

#define OAM_RANGE_FROM 0xFE00
#define OAM_RANGE_TO 0xFE9F

#define OAM_FULL_SIZE (OAM_RANGE_TO - OAM_RANGE_FROM + 1)

class OAM: public Memory {
public:
    OAM();
    ~OAM();

    u8 readMemoryU8(u16 address);
    void writeMemoryU8(u16 address, u8 data);
};

// https://gbdev.io/pandocs/Memory_Map.html#fea0feff-range

#endif // OAM_H