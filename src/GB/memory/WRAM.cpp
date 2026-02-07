#include "GB/memory/WRAM.h"

// *****

WRAM::WRAM() : Memory(WRAM_RANGE_FROM, WRAM_RANGE_TO) {}
WRAM::~WRAM() {}

// *****

u8 WRAM::readMemoryU8(u16 address) {
    if (!this->isAddressInRange(address)) {
        std::cerr << "Out of bounds WRAM READ:" << std::endl;
        std::cerr << "Address:  0x" << std::hex << address << std::endl;

        exit(1);
    }

    return this->data[address - WRAM_RANGE_FROM];
}

void WRAM::writeMemoryU8(u16 address, u8 value) {
    if (!this->isAddressInRange(address)) {
        std::cerr << "Out of bounds WRAM WRITE:" << std::endl;
        std::cerr << "Address:  0x" << std::hex << address << std::endl;

        exit(1);
    }

    this->data[address - WRAM_RANGE_FROM] = value;
}