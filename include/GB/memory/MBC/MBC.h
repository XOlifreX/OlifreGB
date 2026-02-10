#pragma once
#ifndef MBC_H
#define MBC_H

#include "GB/memory/cartridge_info.h"
#include "GB/memory/SRAM.h"
#include "GB/memory/ROM.h"

#include "test/test_mode.h"

// **********

class MBC {
protected:
    CartridgeInfo* cartInfo;

    SRAM* sram;
    ROM* rom;
    
    Memory* getMemoryDestination(u16 address);
public:
    MBC(CartridgeInfo* cartInfo, SRAM* sram, ROM* rom);
    ~MBC();

    bool isAddressInRange(u16 address);

    virtual u8 readU8(u16 address);
    virtual void writeU8(u16 address, u8 data);
};

// **********

#endif // MBC_H