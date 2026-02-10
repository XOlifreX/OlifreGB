#include "GB/memory/MBC/MBC1.h"

// ******************************
// ******************************
// ******************************

MBC1::MBC1(CartridgeInfo* cartInfo, SRAM* sram, ROM* rom) : MBC(cartInfo, sram, rom) {
    this->enableRam = false;
    this->romBankNumberLower = 0;
    this->romBankNumberHigher = 1;
    this->ramBankNumber = 1;
    this->romBitMaskingNum = 5;

    this->bankingMode = MBC1_Simple_Mode;
}

MBC1::~MBC1() {}

// *****************************

void MBC1::initMBC1Values() {
    u8 bankCount = this->cartInfo->getROMBankCount();

    for (int i = 0; i < 7; i++) {
        u8 temp = bankCount >> i;
        if (temp != 0)
            continue;

        this->romBitMaskingNum = i;
        break;
    }
}

// *****************************

u32 MBC1::translateROMAddress(u32 address) {
    if (MBC1_IS_ADDRESS_IN_LOWER_ROM_REGION(address)) {
        // Mode 0 (Simple) will always have the lower ROM bank be bank 0, so no translation is needed.
        if (this->bankingMode == MBC1_Simple_Mode)
            return (u32) address;

        // Normally lower bank is always 0, bit in Mode 1 (Advance) if the higher ROM bank select is either 0x21, 0x41 or 0x61,
        // then the lower bank will read 0x20, 0x40 or 0x60 depending on the higher ROM bank select. This logic catches this case.
        u16 toUseBankNum = this->romBankNumberLower;
        switch (this->romBankNumberHigher) {
            case 0x21:
                toUseBankNum = 0x20;
                break;
            case 0x41:
                toUseBankNum = 0x40;
                break;
            case 0x61:
                toUseBankNum = 0x60;
            default:
                break;
        };

        u32 bankAddress = toUseBankNum * MBC1_ROM_BANK_SIZE;
        return bankAddress + address;
    }
    
    // Higher ROM bank select address translation
    u32 bankAddress = this->romBankNumberHigher * MBC1_ROM_BANK_SIZE;
    return bankAddress + address;
}

u32 MBC1::translateRAMAddress(u32 address) {
    // If RAM size is only 8KiB, then no RAM bank select is available, so bank 0 is default
    if (this->cartInfo->cartInfo.ramSize <= ram8KiB)
        return address;
    
    u32 bankAddress = this->ramBankNumber * MBC1_RAM_BANK_SIZE;
    return bankAddress + address;
}

// *****************************

u8 MBC1::readU8(u32 address) {
    u8 value = 0xFF;

    if (this->sram->isAddressInRange(address)) {
        if (!this->enableRam)
            return value;
        
        u32 ramAddress = this->translateRAMAddress(address);
        
        value = this->sram->readMemoryU8(ramAddress);
    }
    else {
        u32 romAddress = this->translateROMAddress(address);
        
        value = this->rom->readMemoryU8(romAddress);
    }

    return value;
}

void MBC1::writeU8(u32 address, u8 data) {
    if (this->sram->isAddressInRange(address)) {
        if (!this->enableRam)
            return;
        
        u32 ramAddress = this->translateRAMAddress(address);
        this->sram->writeMemoryU8(ramAddress, data);

        return;
    }

    // RAM Enable Register
    if (address >= MBC1_RAM_ENABLE_FROM && address <= MBC1_RAM_ENABLE_TO) {
        this->enableRam = (data & 0x0F) == MBC1_RAM_ENABLE_VALUE;
        return;
    }
    
    // ROM Bank Number Register
    if (address >= MBC1_ROM_BANK_SELECT_FROM && address <= MBC1_ROM_BANK_SELECT_TO) {
        // Select by default LSB 5 bits of incoming data
        u8 bankSelect = data & 0x1F;

        // Extend the ROM bank select if in Mode 1 & ROM/RAM sizes are correct
        if (this->bankingMode == MBC1_Advanced_Mode &&
            this->cartInfo->cartInfo.romSize > rom512KiB &&
            this->cartInfo->cartInfo.ramSize <= ram8KiB
        ) {
            bankSelect = ((this->ramBankNumber << 5) | bankSelect);
        }

        // Get bit count to use for masking the bank number
        // If we're not one Mode 1 (Advanced) and the ROM expects a larger amount of banks that is too much for 5 LSB to hold:
        // --> Use by default 5 bits then. 
        u8 bitMasking = this->romBitMaskingNum;
        if (this->bankingMode == MBC1_Simple_Mode && this->romBitMaskingNum > 5)
            bitMasking = 0x05;
        
        // Only mask the bits we actuallty need to use based on bank count
        this->romBankNumberHigher = (0xFF >> (0x08 - bitMasking)) & bankSelect;

        // Do 0 check -> Add 1 if 5 LSB are 0
        if ((this->romBankNumberHigher & 0x1F) == 0x00)
            this->romBankNumberHigher++;
        
        return;
    }
    
    // RAM Bank Number Register / Upper ROM Bank Number Register
    if (address >= MBC1_RAM_BANK_SELECT_FROM && address <= MBC1_RAM_BANK_SELECT_TO) {
        if (this->bankingMode == MBC1_Simple_Mode) {
            this->ramBankNumber = 0;
        
            return;
        }

        this->ramBankNumber = 0x03 & data;

        return;
    }

    // Banking Mode Select
    if (address >= MBC1_BANKING_MODE_SELECT_FROM && address <= MBC1_BANKING_MODE_SELECT_TO) {
        this->bankingMode = (0x01 & data) == 0x01 ? MBC1_Advanced_Mode : MBC1_Simple_Mode;

        if (this->bankingMode == MBC1_Simple_Mode) {
            this->romBankNumberLower = 0;
            this->ramBankNumber = 0;
        }

        return;
    }

    std::cout << "[WARN] - MBC1 Tried to do a write to an address not mapped by MBC1: 0x" << std::hex << address  << "." << std::endl;

    return;
}

// ******************************
// ******************************
// ******************************