#pragma once
#ifndef CARTRIDGE_H
#define CARTRIDGE_H

#include <iostream>
#include <fstream>
#include <algorithm>

#include "GB/memory/cartridge_info.h"
#include "GB/memory/memory.h"
#include "GB/memory/SRAM.h"
#include "GB/memory/ROM.h"

#include "GB/memory/MBC/MBC.h"
#include "GB/memory/MBC/MBC1.h"
#include "GB/memory/MBC/MBC2.h"

class Cartridge: public Memory {
private:    
    CartridgeInfo* info;

    MBC* mbc;

    void initROM(ROM* rom, const char* path);
    void initSRAM(SRAM* sram);
    void initMBC(ROM* rom, SRAM* sram);
public:
    Cartridge(const char* path);
    ~Cartridge();

    void printCartridgeData();

    u8 readMemoryU8(u32 address);
    void writeMemoryU8(u32 address, u8 data);
    
    bool isAddressInRange(u32 address);
};

#endif // CARTRIDGE_H