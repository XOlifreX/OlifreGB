#include "GB/memory/MBC/MBC3.h"

// ******************************
// ******************************
// ******************************

MBC3::MBC3(CartridgeInfo* cartInfo, SRAM* sram, ROM* rom) : MBC(cartInfo, sram, rom) {
    this->enableRamAndTimer = false;
    this->romBankNumberHigher = 1;
    this->ramBankNumber = 1;

    this->rtcLatched = false;
    this->rtcLatchInProgress = false;
}

MBC3::~MBC3() {}

// *****************************

u32 MBC3::translateROMAddress(u32 address) {
    if (MBC3_IS_ADDRESS_IN_LOWER_ROM_REGION(address))
        return (u32) address;
    
    // Higher ROM bank select address translation
    u32 bankAddress = this->romBankNumberHigher * MBC3_ROM_BANK_SIZE;
    return bankAddress + address;
}

u32 MBC3::translateRAMAddress(u32 address) {
    // If RAM size is only 8KiB, then no RAM bank select is available, so bank 0 is default
    if (this->cartInfo->cartInfo.ramSize <= ram8KiB)
        return address;
    
    u32 bankAddress = this->ramBankNumber * MBC3_RAM_BANK_SIZE;
    return bankAddress + address;
}

// *****************************

u8 MBC3::readU8(u32 address) {
    u8 value = 0xFF;

    if (this->sram->isAddressInRange(address)) {
        if (!this->enableRamAndTimer)
            return value;

        // RTC Register stuff
        if (this->ramBankNumber >= 0x08) {
            value = this->rtcReg[ramBankNumber - 8];
        }
        // SRAM stuff
        else {
            u32 ramAddress = this->translateRAMAddress(address);

            value = this->sram->readMemoryU8(ramAddress);
        }
    }
    else {
        u32 romAddress = this->translateROMAddress(address);
        
        value = this->rom->readMemoryU8(romAddress);
    }

    return value;
}

void MBC3::writeU8(u32 address, u8 data) {
    if (this->sram->isAddressInRange(address)) {
        if (!this->enableRamAndTimer)
            return;

        // RTC Register stuff
        if (this->ramBankNumber >= 0x08) {
            this->rtcReg[ramBankNumber - 8] = data;
        }
        // SRAM stuff
        else {            
            u32 ramAddress = this->translateRAMAddress(address);
            this->sram->writeMemoryU8(ramAddress, data);
        }

        return;
    }

    // RAM & Timer Enable Register
    if (address >= MBC3_RAM_TIMER_ENABLE_FROM && address <= MBC3_RAM_TIMER_ENABLE_TO) {
        this->enableRamAndTimer = (data & 0x0F) == MBC3_RAM_TIMER_ENABLE_VALUE;
        return;
    }
    
    // ROM Bank Number Register
    if (address >= MBC3_ROM_BANK_SELECT_FROM && address <= MBC3_ROM_BANK_SELECT_TO) {
        // Select by default 7 bits of incoming data
        this->romBankNumberHigher = data & 0x7F;

        // Do 0 check -> Add 1 if 5 LSB are 0
        if (this->romBankNumberHigher == 0x00)
            this->romBankNumberHigher++;
        
        return;
    }
    
    // RAM Bank Number Register / RTC Register Select
    if (address >= MBC3_RAM_BANK_TIMER_SELECT_FROM && address <= MBC3_RAM_BANK_TIMER_SELECT_TO) {
        this->ramBankNumber = data & 0x0F; 

        return;
    }

    // Latch Clock Data control
    if (address >= MBC3_LATCH_CLOCK_DATA_FROM && address <= MBC3_LATCH_CLOCK_DATA_TO) {
        if (data == 0x00) {
            this->rtcLatchInProgress = true;
            this->rtcLatched = false;
        }
        else if (data == 0x01 && this->rtcLatchInProgress) {
            this->rtcLatchInProgress = false;
            this->rtcLatched = true;

            // TODO: Get RTC time and place it in rctReg
        }

        return;
    }

    std::cout << "[WARN] - MBC3 Tried to do a write to an address not mapped by MBC3: 0x" << std::hex << address  << "." << std::endl;

    return;
}

bool MBC3::isRTCLatched() {
    return this->rtcLatched;
}

// ******************************
// ******************************
// ******************************