#pragma once
#ifndef MBC1_H
#define MBC1_H

#include "GB/memory/MBC/MBC.h"
#include "GB/memory/cartridge_info.h"

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
    Simple = 0,
    Advanced = 1,
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
public:
    MBC1(CartridgeInfo* cartInfo, SRAM* sram, ROM* rom);
    ~MBC1();

    virtual u8 readU8(u16 address);
    virtual void writeU8(u16 address, u8 data);
};

#endif // MBC1_H