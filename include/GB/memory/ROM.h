#pragma once
#ifndef ROM_H
#define ROM_H

#include "GB/memory/memory.h"

#include <iostream>

#define ROM_RANGE_FROM 0x0000
#define ROM_RANGE_TO 0x7FFF

#define ROM_RANGE_BANKN_FROM 0x4000
#define ROM_RANGE_BANKN_TO 0x7FFF

class ROM: public Memory {
public:
    ROM();
    ~ROM();

    void writeROM(u8* rom);

    u8 readMemoryU8(u16 address);
    void writeMemoryU8(u16 address, u8 data);
};

#endif // ROM_H
