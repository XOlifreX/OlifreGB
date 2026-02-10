#include "GB/memory/RAM.h"

// *****

RAM::RAM() : Memory(RAM_RANGE_FROM, RAM_RANGE_TO) {
    this->oam = new OAM();
    this->wram = new WRAM();
    this->vram = new VRAM();
    this->nuram = new NotUsableRAM();
    this->hram = new HRAM();
}

RAM::~RAM() {
    delete this->oam;
    delete this->wram;
    delete this->vram;
    delete this->nuram;
    delete this->hram;
}

// *****************************

Memory* RAM::getMemoryDestination(u32 address) {
    if (this->oam->isAddressInRange(address))
        return this->oam;
    if (this->wram->isAddressInRange(address))
        return this->wram;
    if (this->vram->isAddressInRange(address))
        return this->vram;
    if (this->nuram->isAddressInRange(address) && is_test_mode)
        return this->nuram;
    if (this->hram->isAddressInRange(address))
        return this->hram;

    std::cerr << "Out of bounds RAM Access:" << std::endl;
    std::cerr << "Address:  0x" << std::hex << address << std::endl;

    return NULL;
}

// *****************************

u8 RAM::readMemoryU8(u32 address) {
    u8 value = 0xFF;

    Memory* dest = this->getMemoryDestination(address);

    if (dest == NULL)
        return value;

    value = (s8) dest->readMemoryU8(address);

    return value;
}

void RAM::writeMemoryU8(u32 address, u8 value) {
    Memory* dest = this->getMemoryDestination(address);

    if (dest == NULL)
        return;

    dest->writeMemoryU8(address, value);
}
