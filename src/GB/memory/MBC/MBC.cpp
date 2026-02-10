#include "GB/memory/MBC/MBC.h"

// ******************************
// ******************************
// ******************************

MBC::MBC(CartridgeInfo* cartInfo, SRAM* sram, ROM* rom) {
    this->cartInfo = cartInfo;
    
    this->sram = sram;
    this->rom = rom;
}

MBC::~MBC() {
    delete this->sram;
    delete this->rom;
}

// *****************************

Memory* MBC::getMemoryDestination(u32 address) {
    if (this->rom->isAddressInRange(address))
        return this->rom;
    if (this->sram->isAddressInRange(address))
        return this->sram;

    std::cerr << "Out of bounds CARTRIDGE ACCESS:" << std::endl;
    std::cerr << "Address:  0x" << std::hex << address << std::endl;

    return NULL;
}

// *****************************

bool MBC::isAddressInRange(u32 address) {
    Memory* temp = NULL;

    if (this->rom->isAddressInRange(address))
        temp = this->rom;
    if (this->sram->isAddressInRange(address))
        temp = this->sram;

    return temp != NULL;
}

// *****************************

u8 MBC::readU8(u32 address) {
    u8 value = 0xFF;

    Memory* dest = this->getMemoryDestination(address);

    if (dest == NULL)
        return value;

    value = (s8) dest->readMemoryU8(address);

    return value;
}

void MBC::writeU8(u32 address, u8 data) {
    Memory* dest = this->getMemoryDestination(address);

    if (dest == NULL)
        return;

    dest->writeMemoryU8(address, data);
}

// ******************************
// ******************************
// ******************************