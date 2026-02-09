#include "GB/memory/MBC/MBC1.h"

// ******************************
// ******************************
// ******************************

MBC1::MBC1(CartridgeInfo* cartInfo, SRAM* sram, ROM* rom) : MBC(cartInfo, sram, rom) {
    this->enableRam = false;
    this->romBankNumber = 1;
    this->ramBankNumber = 1;

    this->bankingMode = /* MBC1BankMode. */ Simple;
}

MBC1::~MBC1() {}

// *****************************

u8 MBC1::readU8(u16 address) {
    u8 value = 0xFF;

    Memory* dest = this->getMemoryDestination(address);

    if (dest == NULL)
        return value;

    value = (s8) dest->readMemoryU8(address);

    return value;
}

void MBC1::writeU8(u16 address, u8 data) {
    if (this->sram->isAddressInRange(address)) {
        if (!this->enableRam)
            return;
        
        // TODO: get correct address by RAM bank
        MBC::writeU8(address, data);
        return;
    }

    // RAM Enable Register
    if (address >= MBC1_RAM_ENABLE_FROM && address <= MBC1_RAM_ENABLE_TO) {
        return;
    }
    
    // ROM Bank Number Register
    if (address >= MBC1_RAM_ENABLE_FROM && address <= MBC1_RAM_ENABLE_TO) {
        return;
    }
    
    // RAM Bank Number Register / Upper ROM Bank Number Register
    if (address >= MBC1_RAM_ENABLE_FROM && address <= MBC1_RAM_ENABLE_TO) {
        return;
    }
}

// ******************************
// ******************************
// ******************************