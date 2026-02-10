#include "GB/memory/SRAM.h"

// *****

SRAM::SRAM() : Memory(SRAM_RANGE_FROM, SRAM_RANGE_TO) {}
SRAM::~SRAM() {}

// *****

void SRAM::writeSRAM(u8* sram, u32 size) {
    if (this->data != NULL)
        free(this->data);

    this->size = size;
    this->data = sram;
}

u8* SRAM::readSRAM() {
    return this->data;
}

u8 SRAM::readMemoryU8(u32 address) {
    u32 location = address - SRAM_RANGE_FROM; 

    if (!this->isAddressInSizeRange(location)) {
        std::cerr << "Out of bounds SRAM READ:" << std::endl;
        std::cerr << "Address:  0x" << std::hex << address << std::endl;

        exit(1);
    }

    return this->data[location];
}

void SRAM::writeMemoryU8(u32 address, u8 value) {
    u32 location = address - SRAM_RANGE_FROM; 

    if (!this->isAddressInSizeRange(location)) {
        std::cerr << "Out of bounds SRAM WRITE:" << std::endl;
        std::cerr << "Address:  0x" << std::hex << address << std::endl;

        exit(1);
    }

    this->data[location] = value;
}