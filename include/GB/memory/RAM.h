#pragma once
#ifndef RAM_H
#define RAM_H

#include "GB/memory/memory.h"

#include "GB/memory/OAM.h"
#include "GB/memory/VRAM.h"
#include "GB/memory/WRAM.h"
#include "GB/memory/WRAM.h"
#include "GB/memory/NotUsableRAM.h"
#include "GB/memory/HRAM.h"

#include "test/test_mode.h"

#include <iostream>

#define INTERUPT_ENABLE_REGISTER 0xFFFF

#define RAM_RANGE_FROM 0x4000
#define RAM_RANGE_TO 0xFFFF

#define RAM_FULL_SIZE (RAM_RANGE_TO - RAM_RANGE_FROM + 1)

class RAM: public Memory {
private:
    OAM* oam;
    WRAM* wram;
    VRAM* vram;
    NotUsableRAM* nuram;
    HRAM* hram;

    Memory* getMemoryDestination(u32 address);
public:
    RAM();
    ~RAM();

    u8 readMemoryU8(u32 address);
    void writeMemoryU8(u32 address, u8 data);
};

// https://gbdev.io/pandocs/Memory_Map.html#fea0feff-range

#endif // RAM_H