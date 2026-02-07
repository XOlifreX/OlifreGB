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

#define ROM_RANGE_FROM 0x0000
#define ROM_RANGE_TO 0x3FFF

#define ROM_RANGE_BANKN_FROM 0x4000
#define ROM_RANGE_BANKN_TO 0x7FFF

class Cartridge: public Memory {
private:    
    CartridgeInfo* info;
    
    SRAM* sram;
    ROM* rom;

    void loadCartridge(const char* path);
public:
    Cartridge();
    Cartridge(const char* path);
    ~Cartridge();

    void printCartridgeData();

    u8 readMemoryU8(u16 address);
    void writeMemoryU8(u16 address, u8 data);
    
    bool isAddressInRange(u16 address);
    Memory* getMemoryDestination(u16 address);

    u8* getROMBank(u8 bank);
    void setSRAM(SRAM* sram);
};

#endif // CARTRIDGE_H