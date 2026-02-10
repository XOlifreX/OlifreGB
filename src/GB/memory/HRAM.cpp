#include "GB/memory/HRAM.h"

// *****

HRAM::HRAM() : Memory(HRAM_RANGE_FROM, HRAM_RANGE_TO) {}
HRAM::~HRAM() {}

// *****

u8 HRAM::readMemoryU8(u32 address) {
    if (!this->isAddressInRange(address)) {
        std::cerr << "Out of bounds HRAM READ:" << std::endl;
        std::cerr << "Address:  0x" << std::hex << address << std::endl;

        exit(1);
    }

    return this->data[address - HRAM_RANGE_FROM];
}

void HRAM::writeMemoryU8(u32 address, u8 value) {
    if (!this->isAddressInRange(address)) {
        std::cerr << "Out of bounds HRAM WRITE:" << std::endl;
        std::cerr << "Address:  0x" << std::hex << address << std::endl;

        exit(1);
    }

    this->data[address - HRAM_RANGE_FROM] = value;
}