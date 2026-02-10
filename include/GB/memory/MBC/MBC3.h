#pragma once
#ifndef MBC3_H
#define MBC3_H

#include "GB/memory/MBC/MBC.h"
#include "GB/memory/cartridge_info.h"

// **********

#define MBC3_ROM_BANK_SIZE              0x4000

#define MBC3_ROM_LOWER_FROM             0x0000
#define MBC3_ROM_LOWER_TO               0x3FFF

#define MBC3_IS_ADDRESS_IN_LOWER_ROM_REGION(ADDRESS) \
    ADDRESS >= MBC3_ROM_LOWER_FROM && ADDRESS <= MBC3_ROM_LOWER_TO

#define MBC3_ROM_HIGHER_FROM            0x4000
#define MBC3_ROM_HIGHER_TO              0x7FFF
    
#define MBC3_RAM_BANK_SIZE              0x2000

#define MBC3_RAM_FROM                   0xA000
#define MBC3_RAM_TO                     0xBFFF

// **********

#define MBC3_RAM_TIMER_ENABLE_FROM      0x0000
#define MBC3_RAM_TIMER_ENABLE_TO        0x1FFF

#define MBC3_RAM_TIMER_ENABLE_VALUE     0x0A

#define MBC3_ROM_BANK_SELECT_FROM       0x2000
#define MBC3_ROM_BANK_SELECT_TO         0x3FFF

#define MBC3_RAM_BANK_TIMER_SELECT_FROM 0x4000
#define MBC3_RAM_BANK_TIMER_SELECT_TO   0x5FFF

#define MBC3_LATCH_CLOCK_DATA_FROM      0x6000
#define MBC3_LATCH_CLOCK_DATA_TO        0x7FFF

#define MBC3_RCT_REGISTER_FROM          0xA000
#define MBC3_RCT_REGISTER_TO            0xBFFF

// **********

// TODO: Should also get a RTC* Class pointer to "latch" the current RTC value
// https://gbdev.io/pandocs/MBC3.html#6000-7fff---latch-clock-data-write-only
class MBC3 : public MBC {
private:
    bool enableRamAndTimer;
    u8 romBankNumberHigher;
    u8 ramBankNumber;

    u8 rtcReg[5];
    bool rtcLatchInProgress;
    bool rtcLatched;

    u32 translateROMAddress(u32 address);
    u32 translateRAMAddress(u32 address);
    
public:
    MBC3(CartridgeInfo* cartInfo, SRAM* sram, ROM* rom);
    ~MBC3();

    u8 readU8(u32 address);
    void writeU8(u32 address, u8 data);

    bool isRTCLatched();
};

#endif // MBC3_H