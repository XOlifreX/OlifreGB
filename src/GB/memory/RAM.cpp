#include "GB/memory/RAM.h"

// *****

RAM::RAM() : Memory(RAM_RANGE_FROM, RAM_RANGE_TO) {
    this->oam = new OAM();
    this->wram = new WRAM();
    this->vram = new VRAM();
}

RAM::~RAM() {
    delete this->oam;
    delete this->wram;
    delete this->vram;
}

// *****

u8 RAM::readMemoryU8(u16 address) {
    // TODO: Add seperation
    if (!this->isAddressInRange(address)) {
        std::cerr << "Out of bounds RAM READ:" << std::endl;
        std::cerr << "Address:  0x" << std::hex << address << std::endl;

        exit(1);
    }

    return this->data[address - RAM_RANGE_FROM];
}

void RAM::writeMemoryU8(u16 address, u8 value) {
    // TODO: Add seperation
    if (!this->isAddressInRange(address)) {
        std::cerr << "Out of bounds RAM WRITE:" << std::endl;
        std::cerr << "Address:  0x" << std::hex << address << std::endl;

        exit(1);
    }

    this->data[address - RAM_RANGE_FROM] = value;
}
