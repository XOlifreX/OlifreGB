#include "GB/memory/MBC/MBC2.h"

// ******************************
// ******************************
// ******************************

MBC2::MBC2(CartridgeInfo* cartInfo, SRAM* sram, ROM* rom) : MBC(cartInfo, sram, rom) {
    this->enableRam = false;
    this->romBankNumberHigher = 1;
}

MBC2::~MBC2() {}

// *****************************

u32 MBC2::translateROMAddress(u32 address) {
    // Lower ROM bank select is always 0
    if (MBC2_IS_ADDRESS_IN_LOWER_ROM_REGION(address))
        return (u32) address;
    
    // Higher ROM bank select address translation
    u32 bankAddress = this->romBankNumberHigher * MBC2_ROM_BANK_SIZE;
    return bankAddress + address;
}

u32 MBC2::translateRAMAddress(u32 address) {
    // No translation needed if RAM is non echo
    if (address <= MBC2_RAM_LOWER_TO)
        return address;
    
    // Handle echo
    u32 offset = (address - MBC2_RAM_HIGHER_FROM) / MBC2_RAM_BANK_SIZE;
    return address - ((offset + 1) * MBC2_RAM_BANK_SIZE);
}

// *****************************

u8 MBC2::readU8(u32 address) {
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

void MBC2::writeU8(u32 address, u8 data) {
    if (this->sram->isAddressInRange(address)) {
        if (!this->enableRam)
            return;
        
        u32 ramAddress = this->translateRAMAddress(address);
        this->sram->writeMemoryU8(ramAddress, data);

        return;
    }

    // RAM ROM Register
    if (address >= MBC2_ROM_RAM_REGISTER_FROM && address <= MBC2_ROM_RAM_REGISTER_TO) {
        // RAM enable/disable
        if ((data & 0x10) == 0x00) {
            this->enableRam = (data & 0x0F) == MBC2_RAM_ENABLE_VALUE;
        }
        // ROM Bank Select
        else {
            u8 bankSelect = data & 0x0F;

            if (bankSelect == 0x00)
                bankSelect++;

            this->romBankNumberHigher = bankSelect;
        }

        return;
    }

    std::cout << "[WARN] - MBC2 Tried to do a write to an address not mapped by MBC2: 0x" << std::hex << address  << "." << std::endl;

    return;
}

// ******************************
// ******************************
// ******************************