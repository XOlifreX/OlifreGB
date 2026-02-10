#include "GB/memory/VRAM.h"

// *****

VRAM::VRAM() : Memory(VRAM_RANGE_FROM, VRAM_RANGE_TO) {}
VRAM::~VRAM() {}

// *****

u8 VRAM::readMemoryU8(u32 address) {
    if (!this->isAddressInRange(address)) {
        std::cerr << "Out of bounds VRAM READ:" << std::endl;
        std::cerr << "Address:  0x" << std::hex << address << std::endl;

        exit(1);
    }

    return this->data[address - VRAM_RANGE_FROM];
}

void VRAM::writeMemoryU8(u32 address, u8 value) {
    if (!this->isAddressInRange(address)) {
        std::cerr << "Out of bounds VRAM WRITE:" << std::endl;
        std::cerr << "Address:  0x" << std::hex << address << std::endl;

        exit(1);
    }

    this->data[address - VRAM_RANGE_FROM] = value;
}