#pragma once
#ifndef WRAM_H
#define WRAM_H

#include "GB/memory/memory.h"

#include <iostream>

#define WRAM_RANGE_FROM 0xC000
#define WRAM_RANGE_TO 0xCFFF

#define WRAM_GBC_RANGE_FROM 0xD000
#define WRAM_GBC_RANGE_TO 0xDFFF

class WRAM: public Memory {
public:
    WRAM();
    ~WRAM();

    // Echo RAM => 0xE000 to 0xFDFF
    // Mirrors WRAM 0xF000 => 0xDDFF
    // So, when Echo RAM read/write, use WRAM instead

    u8 readMemoryU8(u16 address);
    void writeMemoryU8(u16 address, u8 data);
};

#endif // WRAM_H