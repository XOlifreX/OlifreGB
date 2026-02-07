#include "GB/memory/SRAM.h"

// *****

SRAM::SRAM() : Memory(SRAM_RANGE_FROM, SRAM_RANGE_TO) {}
SRAM::~SRAM() {}

// *****

void SRAM::writeSRAM(u8* sram) {
    if (this->data != NULL)
        free(this->data);

    this->data = sram;
}

u8* SRAM::readSRAM() {
    return this->data;
}

u8 SRAM::readMemoryU8(u16 address) {
    if (!this->isAddressInRange(address)) {
        std::cerr << "Out of bounds SRAM READ:" << std::endl;
        std::cerr << "Address:  0x" << std::hex << address << std::endl;

        exit(1);
    }

    return this->data[address - SRAM_RANGE_FROM];
}

void SRAM::writeMemoryU8(u16 address, u8 value) {
    if (!this->isAddressInRange(address)) {
        std::cerr << "Out of bounds SRAM WRITE:" << std::endl;
        std::cerr << "Address:  0x" << std::hex << address << std::endl;

        exit(1);
    }

    this->data[address - SRAM_RANGE_FROM] = value;
}