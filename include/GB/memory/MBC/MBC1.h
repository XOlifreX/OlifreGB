#pragma once
#ifndef MBC1_H
#define MBC1_H

#include "GB/memory/MBC/MBC.h"
#include "GB/memory/cartridge_info.h"

// **********

#define MBC1_ROM_BANK_SIZE              0x4000

#define MBC1_ROM_LOWER_FROM             0x0000
#define MBC1_ROM_LOWER_TO               0x3FFF

#define MBC1_IS_ADDRESS_IN_LOWER_ROM_REGION(ADDRESS) \
    ADDRESS >= MBC1_ROM_LOWER_FROM && ADDRESS <= MBC1_ROM_LOWER_TO

#define MBC1_ROM_HIGHER_FROM            0x4000
#define MBC1_ROM_HIGHER_TO              0x7FFF

#define MBC1_IS_ADDRESS_IN_HIGHER_ROM_REGION(ADDRESS) \
    ADDRESS >= MBC1_ROM_HIGHER_FROM && ADDRESS <= MBC1_ROM_HIGHER_TO
    
#define MBC1_RAM_BANK_SIZE              0x2000

#define MBC1_RAM_FROM                   0xA000
#define MBC1_RAM_TO                     0xBFFF

#define MBC1_IS_ADDRESS_IN_RAM_REGION(ADDRESS) \
    ADDRESS >= MBC1_RAM_FROM && ADDRESS <= MBC1_RAM_TO

// **********

#define MBC1_RAM_ENABLE_FROM            0x0000
#define MBC1_RAM_ENABLE_TO              0x1FFF

#define MBC1_RAM_ENABLE_VALUE           0x0A

#define MBC1_ROM_BANK_SELECT_FROM       0x2000
#define MBC1_ROM_BANK_SELECT_TO         0x3FFF

#define MBC1_RAM_BANK_SELECT_FROM       0x4000
#define MBC1_RAM_BANK_SELECT_TO         0x5FFF

#define MBC1_BANKING_MODE_SELECT_FROM   0x6000
#define MBC1_BANKING_MODE_SELECT_TO     0x7FFF

// **********

enum MBC1BankMode {
    MBC1_Simple_Mode = 0,
    MBC1_Advanced_Mode = 1,
};

// **********

class MBC1 : public MBC {
private:
    bool enableRam;
    u8 romBankNumberLower;
    u8 romBankNumberHigher;
    u8 ramBankNumber;
    MBC1BankMode bankingMode;

    u8 romBitMaskingNum;

    void initMBC1Values();

    u32 translateROMAddress(u32 address);
    u32 translateRAMAddress(u32 address);
    
public:
    MBC1(CartridgeInfo* cartInfo, SRAM* sram, ROM* rom);
    ~MBC1();

    u8 readU8(u32 address);
    void writeU8(u32 address, u8 data);
};

#endif // MBC1_H