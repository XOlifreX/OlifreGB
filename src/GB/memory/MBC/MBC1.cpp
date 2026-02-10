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

    this->bankingMode = /* MBC1BankMode. */ Simple;
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
        this->enableRam = (data & 0x0F) == MBC1_RAM_ENABLE_VALUE;
        return;
    }
    
    // ROM Bank Number Register
    if (address >= MBC1_RAM_ENABLE_FROM && address <= MBC1_RAM_ENABLE_TO) {
        // Select by default LSB 5 bits of incoming data
        u8 bankSelect = data & 0x1F;

        // Extend the ROM bank select if in Mode 1 & ROM/RAM sizes are correct
        if (this->bankingMode == Advanced &&
            this->cartInfo->cartInfo.romSize <= rom512KiB &&
            this->cartInfo->cartInfo.ramSize <= ram8KiB
        )
            bankSelect = ((this->ramBankNumber << 5) | bankSelect);

        // Only mask the bits we actuallty need to use based on bank count
        this->romBankNumberHigher = (0xFF >> this->romBitMaskingNum) & bankSelect;

        // Do 0 check -> Add 1
        if ((this->romBankNumberHigher & 0x1F) == 0x00)
            this->romBankNumberHigher++;
        
        return;
    }
    
    // RAM Bank Number Register / Upper ROM Bank Number Register
    if (address >= MBC1_RAM_ENABLE_FROM && address <= MBC1_RAM_ENABLE_TO) {
        if (this->bankingMode == Simple) {
            this->ramBankNumber = 0;
        
            return;
        }

        this->ramBankNumber = 0x03 & data;

        return;
    }

    // Banking Mode Select
    if (address >= MBC1_BANKING_MODE_SELECT_FROM && address <= MBC1_BANKING_MODE_SELECT_TO) {
        this->bankingMode = 0x01 & data == 0x01 ? Advanced : Simple;

        if (this->bankingMode == Simple) {
            this->romBankNumberLower = 0;
            this->ramBankNumber = 0;
        }
    }
}

// ******************************
// ******************************
// ******************************