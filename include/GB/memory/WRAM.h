#pragma once
#ifndef WRAM_H
#define WRAM_H

#include "GB/memory/memory.h"

#include <iostream>

#define WRAM_RANGE_FROM 0xC000
#define WRAM_RANGE_TO 0xCFFF

#define WRAM_GBC_RANGE_FROM 0xD000
#define WRAM_GBC_RANGE_TO 0xDFFF

#define WRAM_FULL_SIZE 0x2000

#define WRAM_ECHO_RANGE_FROM 0xE000
#define WRAM_ECHO_RANGE_TO 0xFDFF

#define WRAM_IS_IN_ECHO_REGION(ADDRESS) \
    ADDRESS >= WRAM_ECHO_RANGE_FROM && ADDRESS <= WRAM_ECHO_RANGE_TO

class WRAM: public Memory {
private:
    u32 translateAddress(u32 address);

public:
    WRAM();
    ~WRAM();

    // Echo RAM => 0xE000 to 0xFDFF
    // Mirrors WRAM 0xF000 => 0xDDFF
    // So, when Echo RAM read/write, use WRAM instead

    u8 readMemoryU8(u32 address);
    void writeMemoryU8(u32 address, u8 data);
    
    bool isAddressInRange(u32 address);
};

#endif // WRAM_H