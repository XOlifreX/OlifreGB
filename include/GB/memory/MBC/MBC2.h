#pragma once
#ifndef MBC2_H
#define MBC2_H

#include "GB/memory/MBC/MBC.h"
#include "GB/memory/cartridge_info.h"

// **********

#define MBC2_ROM_BANK_SIZE              0x4000

#define MBC2_ROM_LOWER_FROM             0x0000
#define MBC2_ROM_LOWER_TO               0x3FFF

#define MBC2_IS_ADDRESS_IN_LOWER_ROM_REGION(ADDRESS) \
    ADDRESS >= MBC2_ROM_LOWER_FROM && ADDRESS <= MBC2_ROM_LOWER_TO

#define MBC2_ROM_HIGHER_FROM            0x4000
#define MBC2_ROM_HIGHER_TO              0x7FFF
    
#define MBC2_RAM_BANK_SIZE              0x0200

#define MBC2_RAM_LOWER_FROM             0xA000
#define MBC2_RAM_LOWER_TO               0xA1FF

#define MBC2_RAM_HIGHER_FROM            0xA200
#define MBC2_RAM_HIGHER_TO              0xBFFF

// **********

#define MBC2_ROM_RAM_REGISTER_FROM      0x0000
#define MBC2_ROM_RAM_REGISTER_TO        0x3FFF

#define MBC2_RAM_ENABLE_VALUE           0x0A

// **********

class MBC2 : public MBC {
private:
    bool enableRam;
    u8 romBankNumberHigher;

    u32 translateROMAddress(u32 address);
    u32 translateRAMAddress(u32 address);

public:
    MBC2(CartridgeInfo* cartInfo, SRAM* sram, ROM* rom);
    ~MBC2();

    u8 readU8(u32 address);
    void writeU8(u32 address, u8 data);
};

#endif // MBC2_H